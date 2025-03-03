#include "interface.h"
#include "temperature.h"
#include <EEPROM.h>  // Ajout de l'inclusion EEPROM

UserInterface ui;  // Instance globale

// Custom character bitmap definitions
const uint8_t CUSTOM_CHARS[][8] = {
    { 0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00 },  // Degree °
    { 0x04, 0x0E, 0x15, 0x04, 0x04, 0x04, 0x00, 0x00 },  // Up arrow
    { 0x04, 0x04, 0x04, 0x15, 0x0E, 0x04, 0x00, 0x00 },  // Down arrow
    { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },  // Heat block
    { 0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08, 0x00 },  // Progress
    { 0x00, 0x01, 0x03, 0x16, 0x1C, 0x08, 0x00, 0x00 },  // Check
    { 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00, 0x00 },  // Cross
    { 0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00 }   // Clock
};

UserInterface::UserInterface() :
    lcd(0x27, 20, 4),
    tempDisplay(TEMP_DISPLAY_CLK, TEMP_DISPLAY_DIO),
    spDisplay(SP_DISPLAY_CLK, SP_DISPLAY_DIO),
    currentMode(IDLE),
    modeActive(false),
    lastEncoderState(0),
    lastEncoderTime(0),
    lastButtonPress(0),
    buttonPressStart(0),
    longPressHandled(false),
    boilPower(DEFAULT_BOIL_POWER),
    pidMenuItem(PID_NONE),
    inPIDMenu(false),
    lastClickTime(0),
    clickCount(0),
    mashTempReached(false),
    boilTempReached(false),
    timerStart(0),
    configMenuItem(CONFIG_NONE),
    inConfigMenu(false),
    lastMenuActivity(0)
{
}

void UserInterface::begin() {
    lcd.init();
    lcd.backlight();
    
    // Load custom characters
    for (uint8_t i = 0; i < 8; i++) {
        lcd.createChar(i, (uint8_t*)CUSTOM_CHARS[i]);
    }
    
    tempDisplay.setBrightness(0x0f);
    spDisplay.setBrightness(0x0f);

    pinMode(ENCODER_CLK, INPUT);
    pinMode(ENCODER_DT, INPUT);
    pinMode(ENCODER_SW, INPUT_PULLUP);
    lastEncoderState = digitalRead(ENCODER_CLK);

    loadConfig();
}

void UserInterface::update() {
    // Check menu timeout
    if (inConfigMenu && (millis() - lastMenuActivity > CONFIG_MENU_TIMEOUT)) {
        inConfigMenu = false;
    }

    // Check temperature thresholds and update timer
    if (modeActive) {
        if (currentMode == MASH && !mashTempReached) {
            if (abs(tempControl.getCurrentTemp() - tempControl.getTargetTemp()) <= MASH_TEMP_THRESHOLD) {
                mashTempReached = true;
                timerStart = millis();
                playBuzzer();
            }
        } else if (currentMode == BOIL && !boilTempReached) {
            if (tempControl.getCurrentTemp() >= BOIL_TEMP_THRESHOLD) {
                boilTempReached = true;
                timerStart = millis();
                playBuzzer();
            }
        }
    }

    // Update display
    if (inConfigMenu) {
        displayConfigMenu();
    } else if (inPIDMenu) {
        displayPIDMenu();
    } else {
        updateDisplays(tempControl.getCurrentTemp(), 
                      tempControl.getTargetTemp(),
                      tempControl.getOutputPower());
    }
}

void UserInterface::updateDisplays(double currentTemp, double setPoint, double power) {
    if (inPIDMenu) {
        displayPIDMenu();
        return;
    }

    int tempToDisplay = round(currentTemp * 10);
    int spToDisplay = round(setPoint * 10);
    
    tempDisplay.showNumberDec(tempToDisplay, true, 4, 1);
    spDisplay.showNumberDec(spToDisplay, true, 4, 1);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mode: ");
    lcd.print(currentMode == IDLE ? "IDLE " : 
              currentMode == MASH ? "MASH " : "BOIL ");
    
    // Display temperature with degree symbol
    lcd.setCursor(0, 1);
    lcd.print("Power: ");
    lcd.print(power);
    lcd.print("% ");
    if (power > 0) {
        lcd.write(CHAR_HEAT);
    }

    // Timer display for both MASH and BOIL modes
    if ((currentMode == MASH && mashTempReached) || 
        (currentMode == BOIL && boilTempReached)) {
        lcd.setCursor(0, 2);
        lcd.write(CHAR_CLOCK);
        lcd.print(" ");
        unsigned long elapsed = (millis() - timerStart) / 1000; // Convert to seconds
        int minutes = elapsed / 60;
        int seconds = elapsed % 60;
        char timeStr[9];
        sprintf(timeStr, "%02d:%02d", minutes, seconds);
        lcd.print(timeStr);
    }

    lcd.setCursor(0, 3);
    lcd.print("Status: ");
    if (tempControl.isError()) {
        switch(tempControl.getErrorState()) {
            case SENSOR_ERROR:
                lcd.write(CHAR_CROSS);
                lcd.print(" SENSOR");
                playBuzzer(true);  // Error sound
                break;
            case OVERHEAT_ERROR:
                lcd.write(CHAR_CROSS);
                lcd.print(" OVERHEAT");
                playBuzzer(true);  // Error sound
                break;
            default:
                lcd.write(CHAR_CROSS);
                lcd.print(" ERROR");
                playBuzzer(true);  // Error sound
        }
    } else if (!modeActive) {
        lcd.print("STOPPED ");
    } else if ((currentMode == MASH && mashTempReached) ||
               (currentMode == BOIL && boilTempReached)) {
        lcd.write(CHAR_CHECK);
        lcd.print(currentMode == MASH ? " TEMP OK" : " BOILING");
    } else {
        lcd.write(CHAR_PROG);
        lcd.print(power > 0 ? " HEATING" : " STANDBY");
    }
}

void UserInterface::playBuzzer(bool isError = false) {
    if (isError) {
        // Error sound: 3 high-pitched beeps
        for(int i = 0; i < BEEP_REPEATS_ERROR; i++) {
            tone(BUZZER_PIN, BEEP_FREQUENCY_ERROR, BEEP_DURATION_ERROR);
            delay(BEEP_DURATION_ERROR);
            noTone(BUZZER_PIN);
            delay(BEEP_DURATION_ERROR/2);
        }
    } else {
        // Normal sound: single short beep
        tone(BUZZER_PIN, BEEP_FREQUENCY_NORMAL, BEEP_DURATION_NORMAL);
    }
}

void UserInterface::handleEncoder() {
    if (millis() - lastEncoderTime < ENCODER_DEBOUNCE_TIME) return;
    
    int currentState = digitalRead(ENCODER_CLK);
    if (currentState != lastEncoderState && currentState == 1) {
        bool increase = digitalRead(ENCODER_DT) != currentState;
        
        if (currentMode == IDLE && inConfigMenu) {
            // Configuration menu navigation
            if (!increase && configMenuItem > CONFIG_FILTER) {
                configMenuItem = (ConfigMenuItem)(configMenuItem - 1);
            } else if (increase && configMenuItem < CONFIG_EXIT) {
                configMenuItem = (ConfigMenuItem)(configMenuItem + 1);
            }
            lastMenuActivity = millis();
        } else if (inPIDMenu) {
            adjustPIDValue(!increase);  // Inverted for more intuitive rotation
        } else {
            if (digitalRead(ENCODER_DT) != currentState) {
                // Counter-clockwise rotation
                switch(currentMode) {
                    case MASH:
                        if (modeActive) {
                            double newTemp = tempControl.getTargetTemp() - MASH_TEMP_STEP;
                            tempControl.setTargetTemp(constrain(newTemp, MIN_MASH_TEMP, MAX_MASH_TEMP));
                        }
                        break;
                    case BOIL:
                        if (modeActive) {
                            boilPower = constrain(boilPower - 1, MIN_BOIL_POWER, MAX_BOIL_POWER);
                        }
                        break;
                }
            } else {
                // Clockwise rotation
                switch(currentMode) {
                    case MASH:
                        if (modeActive) {
                            double newTemp = tempControl.getTargetTemp() + MASH_TEMP_STEP;
                            tempControl.setTargetTemp(constrain(newTemp, MIN_MASH_TEMP, MAX_MASH_TEMP));
                        }
                        break;
                    case BOIL:
                        if (modeActive) {
                            boilPower = constrain(boilPower + 1, MIN_BOIL_POWER, MAX_BOIL_POWER);
                        }
                        break;
                }
            }
        }
        if (currentMode == MASH) {
            mashTempReached = false;  // Reset when temperature changes
        }
        lastEncoderTime = millis();
    }
    lastEncoderState = currentState;
}

void UserInterface::handleButton() {
    if (digitalRead(ENCODER_SW) == LOW) {  // Button pressed
        if (buttonPressStart == 0) {
            buttonPressStart = millis();
            
            // Double-click detection
            if (millis() - lastClickTime < DOUBLE_CLICK_TIME) {
                clickCount++;
                if (clickCount == 2 && !inPIDMenu) {
                    inPIDMenu = true;
                    pidMenuItem = PID_P;
                    clickCount = 0;
                    playBuzzer();
                    return;
                }
            } else {
                clickCount = 1;
            }
            lastClickTime = millis();
            longPressHandled = false;
        }
        
        // Long press handling
        if (!longPressHandled && (millis() - buttonPressStart) > LONG_PRESS_TIME) {
            if (inPIDMenu) {
                if (pidMenuItem == PID_SAVE) {
                    savePIDSettings();
                } else if (pidMenuItem == PID_AUTOTUNE) {
                    if (tempControl.isAutoTuning()) {
                        tempControl.stopAutoTune();
                    } else {
                        tempControl.startAutoTune(65.0);  // Target temperature for autotune
                    }
                    playBuzzer();
                } else if (pidMenuItem == PID_PONM) {
                    tempControl.setPOnM(!tempControl.getPOnM());
                    playBuzzer();
                }
                inPIDMenu = false;
                pidMenuItem = PID_NONE;
            } else {
                currentMode = (Mode)((currentMode + 1) % 3);  // Cycle IDLE -> MASH -> BOIL
                modeActive = false;
            }
            longPressHandled = true;
            playBuzzer();
        }
    } else {
        // Short press handling if not already handled as long press
        if (buttonPressStart > 0 && !longPressHandled && 
            (millis() - buttonPressStart) < LONG_PRESS_TIME) {
            if (inPIDMenu) {
                pidMenuItem = (PIDMenuItem)(((int)pidMenuItem + 1) % 6);
                playBuzzer();
            } else if (currentMode != IDLE) {
                modeActive = !modeActive;
                if (!modeActive) {
                    analogWrite(SSR_PIN, 0);
                }
                playBuzzer();
            }
        }
        buttonPressStart = 0;
    }
    if (currentMode == MASH && modeActive) {
        // Check if target temperature is reached
        if (!mashTempReached && 
            abs(tempControl.getCurrentTemp() - tempControl.getTargetTemp()) <= TEMP_THRESHOLD) {
            mashTempReached = true;
            playBuzzer();
        }
    }

    if (currentMode == IDLE && !longPressHandled && 
        (millis() - buttonPressStart) < LONG_PRESS_TIME) {
        if (!inConfigMenu) {
            inConfigMenu = true;
            configMenuItem = CONFIG_FILTER;
            lastMenuActivity = millis();
        } else {
            switch(configMenuItem) {
                case CONFIG_FILTER:
                    enableTempFilter = !enableTempFilter;  // Utilisation de la variable globale
                    saveConfig();
                    break;
                case CONFIG_EXIT:
                    inConfigMenu = false;
                    break;
            }
        }
        playBuzzer();
    }
}

void UserInterface::adjustPIDValue(bool increase) {
    double step = 0;
    double currentValue = 0;
    
    switch(pidMenuItem) {
        case PID_P:
            step = PID_P_STEP;
            currentValue = tempControl.getKp();
            if (increase) currentValue += step;
            else currentValue -= step;
            tempControl.setPIDTunings(currentValue, tempControl.getKi(), tempControl.getKd());
            break;
        case PID_I:
            step = PID_I_STEP;
            currentValue = tempControl.getKi();
            if (increase) currentValue += step;
            else currentValue -= step;
            tempControl.setPIDTunings(tempControl.getKp(), currentValue, tempControl.getKd());
            break;
        case PID_D:
            step = PID_D_STEP;
            currentValue = tempControl.getKd();
            if (increase) currentValue += step;
            else currentValue -= step;
            tempControl.setPIDTunings(tempControl.getKp(), tempControl.getKi(), currentValue);
            break;
        default:
            return;
    }
}

void UserInterface::displayPIDMenu() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PID Setup Menu");
    
    lcd.setCursor(0, 1);
    switch(pidMenuItem) {
        case PID_P:
            lcd.print("P: ");
            lcd.print(tempControl.getKp());
            lcd.write(CHAR_UP);
            lcd.write(CHAR_DOWN);
            break;
        case PID_I:
            lcd.print("I: ");
            lcd.print(tempControl.getKi());
            break;
        case PID_D:
            lcd.print("D: ");
            lcd.print(tempControl.getKd());
            break;
        case PID_SAVE:
            lcd.print("Save settings");
            break;
        case PID_EXIT:
            lcd.print("Exit menu");
            break;
        case PID_AUTOTUNE:
            if (tempControl.isAutoTuning()) {
                lcd.print("Autotune: ");
                lcd.print(tempControl.getAutoTuneProgress(), 0);
                lcd.print("%");
                lcd.setCursor(0, 2);
                lcd.print("Long press: Cancel");
            } else {
                lcd.print("Start Autotune");
                lcd.setCursor(0, 2);
                lcd.print("Long press: Start");
            }
            break;
        case PID_PONM:
            lcd.print("P on M: ");
            lcd.print(tempControl.getPOnM() ? "ON" : "OFF");
            lcd.setCursor(0, 2);
            lcd.print("Long press: Toggle");
            break;
    }
    
    lcd.setCursor(0, 3);
    lcd.print("Click: Next Long: OK");
}

void UserInterface::savePIDSettings() {
    tempControl.savePIDSettings();
    playBuzzer();
}

void UserInterface::showStartupScreen() {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Brew Controller");
    lcd.setCursor(4, 2);
    lcd.print("Version 1.0");
    delay(2000);  // Display for 2 seconds
}

void UserInterface::showSensorStatus(bool isOk) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Temperature Sensor:");
    lcd.setCursor(4, 2);
    if (isOk) {
        lcd.print("OK - Ready!");
    } else {
        lcd.print("NOT FOUND!");
    }
    delay(2000);  // Display for 2 seconds
}

void UserInterface::loadConfig() {
    byte config;
    EEPROM.get(EEPROM_CONFIG_ADDR, config);
    if (config != 0xFF) {  // If the value is valid
        enableTempFilter = config & 0x01;  // Utilisation de la variable globale
    }
}

void UserInterface::saveConfig() {
    byte config = 0;
    if (enableTempFilter) config |= 0x01;  // Utilisation de la variable globale
    EEPROM.put(EEPROM_CONFIG_ADDR, config);
    playBuzzer();
}

void UserInterface::displayConfigMenu() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Configuration Menu");
    
    lcd.setCursor(0, 1);
    switch(configMenuItem) {
        case CONFIG_FILTER:
            lcd.print("Temperature Filter:");
            lcd.setCursor(0, 2);
            lcd.print(enableTempFilter ? "ON" : "OFF");  // Utilisation de la variable globale
            break;
        case CONFIG_EXIT:
            lcd.print("Exit Menu");
            break;
    }
    
    lcd.setCursor(0, 3);
    lcd.print("Click: Toggle/Exit");
}

#pragma once

#include "config.h"
#include <LiquidCrystal_I2C.h>
#include <TM1637Display.h>

enum PIDMenuItem {
    PID_NONE,
    PID_P,
    PID_I,
    PID_D,
    PID_PONM,     // Nouveau menu item pour P_ON_M
    PID_AUTOTUNE,  // Ajout de l'option autotune
    PID_SAVE,
    PID_EXIT
};

enum ConfigMenuItem {
    CONFIG_NONE,
    CONFIG_FILTER,
    CONFIG_EXIT
};

class UserInterface {
public:
    UserInterface();
    void begin();
    void update();
    void updateDisplays(double currentTemp, double setPoint, double power);
    void handleEncoder();
    void handleButton();
    Mode getCurrentMode() { return currentMode; }
    bool isModeActive() { return modeActive; }
    void showStartupScreen();
    void showSensorStatus(bool isOk);

private:
    LiquidCrystal_I2C lcd;
    TM1637Display tempDisplay;
    TM1637Display spDisplay;
    Mode currentMode;
    bool modeActive;
    bool mashTempReached;  // Ajout de la variable
    bool boilTempReached;    // New flag for boil temperature
    unsigned long timerStart; // Timer start timestamp
    
    // Variables pour l'encodeur et le bouton
    int lastEncoderState;
    unsigned long lastEncoderTime;
    unsigned long lastButtonPress;
    unsigned long buttonPressStart;
    bool longPressHandled;
    double boilPower;

    PIDMenuItem pidMenuItem;
    bool inPIDMenu;
    unsigned long lastClickTime;
    int clickCount;
    
    ConfigMenuItem configMenuItem;
    bool inConfigMenu;
    unsigned long lastMenuActivity;
    
    void playBuzzer(bool isError = false);
    void handlePIDMenu();
    void displayPIDMenu();
    void adjustPIDValue(bool increase);
    void savePIDSettings();
    void handleConfigMenu();
    void displayConfigMenu();
    void toggleTempFilter();
    void loadConfig();
    void saveConfig();
    void updateTimer();      // New method for timer update
};

extern UserInterface ui;

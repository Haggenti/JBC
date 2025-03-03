#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PID_v1.h>
#include <LiquidCrystal_I2C.h>
#include <TM1637Display.h>
#include <EEPROM.h>
#include "config.h"
#include "temperature.h"
#include "interface.h"

void setup() {
    // Configuration des pins
    pinMode(SSR_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // Initialisation des périphériques
    ui.begin();  // Cette méthode initialise déjà le LCD
    
    // Écran de démarrage
    ui.showStartupScreen();
    
    // Test de la sonde
    bool sensorOk = tempControl.checkSensor();
    ui.showSensorStatus(sensorOk);
    
    if (!sensorOk && !SIMULATION_MODE) {
        while(1) {
            // Boucle infinie avec clignotement LED en cas d'erreur
            digitalWrite(LED_PIN, HIGH);
            tone(BUZZER_PIN, 1000, 1000);
            delay(500);
            digitalWrite(LED_PIN, LOW);
            delay(500);
        }
    }

    // Suite de l'initialisation normale
    tempControl.begin();
}

void loop() {
    ui.handleEncoder();
    ui.handleButton();
    
    tempControl.update();
    
    // Protection température maximale
    if (tempControl.getCurrentTemp() >= MAX_SAFE_TEMP) {
        // ...safety handling...
        return;
    }

    // Update displays
    ui.update();

    delay(100);
}
#pragma once

#include <Arduino.h>
#include <EEPROM.h>

// Pin definitions
#define TEMP_SENSOR_PIN 2
#define SSR_PIN 3
#define ENCODER_CLK 4
#define ENCODER_DT 5
#define ENCODER_SW 6
#define TEMP_DISPLAY_CLK 7
#define TEMP_DISPLAY_DIO 8
#define SP_DISPLAY_CLK 9
#define SP_DISPLAY_DIO 10
#define BUZZER_PIN 11
#define LED_PIN 12

// Constants
#define BOIL_TEMP 100.0
#define PWM_PERIOD 5000
#define TEMP_THRESHOLD 0.5
#define SIMULATION_MODE true
#define TEMP_SIMULATION_STEP 0.1
#define HEATING_POWER_FACTOR 0.005
#define DEFAULT_BOIL_POWER 80.0
#define MIN_BOIL_POWER 50.0
#define MAX_BOIL_POWER 100.0
#define MIN_MASH_TEMP 40.0
#define MAX_MASH_TEMP 80.0
#define MASH_TEMP_STEP 1.0
#define MAX_SAFE_TEMP 110.0
#define LONG_PRESS_TIME 1000
#define ENCODER_DEBOUNCE_TIME 5
#define BUTTON_DEBOUNCE_TIME 250

// Safety parameters
#define TEMP_ERROR_THRESHOLD -50.0    // Temperature below = sensor error
#define MAX_TEMP_RISE_RATE 5.0        // Maximum °C per second
#define TEMP_READ_INTERVAL 1000       // Reading interval in ms

// Temperature filtering
extern bool enableTempFilter;         // Global filter enable variable
#define TEMP_FILTER_SAMPLES 10        // Number of samples for average
#define TEMP_FILTER_WEIGHT 0.3        // Weight of new sample (0.0-1.0)

// EEPROM addresses
#define EEPROM_BOIL_POWER_ADDR 0
#define EEPROM_PID_P_ADDR 4
#define EEPROM_PID_I_ADDR 8
#define EEPROM_PID_D_ADDR 12
#define EEPROM_CONFIG_ADDR 16         // General configuration address
#define EEPROM_PID_MODE_ADDR 17       // PID mode address

// Configuration menu
#define CONFIG_MENU_TIMEOUT 10000     // Menu timeout in ms

// PID menu
#define DOUBLE_CLICK_TIME 400         // Maximum time between clicks (ms)
#define PID_P_STEP 0.1                // P adjustment step
#define PID_I_STEP 0.01               // I adjustment step
#define PID_D_STEP 0.1                // D adjustment step

// Buzzer sounds
#define BEEP_FREQUENCY_NORMAL 1000    // Normal frequency (Hz)
#define BEEP_FREQUENCY_ERROR 2000     // Error frequency (Hz)
#define BEEP_DURATION_NORMAL 100      // Normal duration (ms)
#define BEEP_DURATION_ERROR 500       // Error duration (ms)
#define BEEP_REPEATS_ERROR 3          // Error beep repetitions

// Custom characters for UI
#define CHAR_DEGREE    0  // ° Temperature symbol
#define CHAR_UP        1  // ↑ Up arrow
#define CHAR_DOWN      2  // ↓ Down arrow
#define CHAR_HEAT      3  // █ Heating indicator
#define CHAR_PROG      4  // → Progress indicator
#define CHAR_CHECK     5  // ✓ Check mark
#define CHAR_CROSS     6  // × Error symbol
#define CHAR_CLOCK     7  // ○ Timer symbol

// Operating modes
enum Mode {
    IDLE,
    MASH,
    BOIL
};

// Error states
enum ErrorState {
    NO_ERROR,
    SENSOR_ERROR,
    OVERHEAT_ERROR
};

// Temperature thresholds
#define MASH_TEMP_THRESHOLD 0.5      // Temperature threshold for mash
#define BOIL_TEMP_THRESHOLD 97.0     // Temperature threshold for boil start
#define TEMP_THRESHOLD 0.5           // General temperature threshold

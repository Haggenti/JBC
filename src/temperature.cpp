#include "temperature.h"
#include <EEPROM.h>

TemperatureControl tempControl;  // Instance globale

TemperatureControl::TemperatureControl() :
    oneWire(TEMP_SENSOR_PIN),
    sensors(&oneWire),
    myPID(&currentTemp, &outputPower, &setPoint, 2, 0.1, 1, DIRECT),
    currentTemp(20),
    setPoint(65),
    outputPower(0),
    simulatedTemp(20),
    Kp(2.0), Ki(0.1), Kd(1.0),
    errorState(NO_ERROR),
    lastTemp(20),
    lastTempRead(0),
    filteredTemp(20),
    bufferIndex(0),
    autoTune(&autoTuneInput, &autoTuneOutput),
    autoTuning(false),
    autoTuneStart(0),
    autoTuneTemp(0),
    pOnM(true)  // P_ON_M activé par défaut
{
    for(int i = 0; i < TEMP_FILTER_SAMPLES; i++) {
        tempBuffer[i] = 20.0;
    }
    myPID.SetTunings(Kp, Ki, Kd, P_ON_M);  // Initialisation avec P_ON_M
}

void TemperatureControl::begin() {
    sensors.begin();
    loadPIDSettings();
    myPID.SetMode(AUTOMATIC);
    myPID.SetSampleTime(1000);
    myPID.SetOutputLimits(0, 100);
}

void TemperatureControl::update() {
    unsigned long currentTime = millis();
    
    // Check read interval
    if (currentTime - lastTempRead < TEMP_READ_INTERVAL) {
        return;
    }
    lastTempRead = currentTime;

    // Temperature reading
    double rawTemp;
    if (SIMULATION_MODE) {
        updateSimulatedTemp();
        rawTemp = simulatedTemp;
    } else {
        sensors.requestTemperatures();
        rawTemp = sensors.getTempCByIndex(0);
    }

    // Error checking
    if (checkSensorError(rawTemp)) {
        errorState = SENSOR_ERROR;
        outputPower = 0;
        return;
    }

    // Temperature filtering if enabled
    if (enableTempFilter) {
        currentTemp = filterTemperature(rawTemp);
    } else {
        currentTemp = rawTemp;
    }

    // PID update if no error
    if (autoTuning) {
        // Autotune mode
        autoTuneInput = currentTemp;
        outputPower = autoTuneOutput;
        autoTune.Runtime();
        updateAutoTune();
    } else {
        // Normal PID mode
        if (errorState == NO_ERROR) {
            myPID.Compute();
        }
    }

    lastTemp = rawTemp;
}

void TemperatureControl::updateSimulatedTemp() {
    if (outputPower > 0) {
        double heatRate = (outputPower * HEATING_POWER_FACTOR) * 
                         (1.0 - ((simulatedTemp - 20.0) / 100.0));
        simulatedTemp += heatRate;
    } else if (simulatedTemp > 20.0) {
        simulatedTemp -= TEMP_SIMULATION_STEP;
    }
}

void TemperatureControl::setPIDTunings(double p, double i, double d) {
    Kp = p; Ki = i; Kd = d;
    myPID.SetTunings(Kp, Ki, Kd, pOnM ? P_ON_M : P_ON_E);
}

void TemperatureControl::setPOnM(bool enabled) {
    pOnM = enabled;
    myPID.SetTunings(Kp, Ki, Kd, pOnM ? P_ON_M : P_ON_E);
    EEPROM.put(EEPROM_PID_MODE_ADDR, pOnM);
}

void TemperatureControl::loadPIDSettings() {
    EEPROM.get(EEPROM_PID_P_ADDR, Kp);
    EEPROM.get(EEPROM_PID_I_ADDR, Ki);
    EEPROM.get(EEPROM_PID_D_ADDR, Kd);
    
    if (isnan(Kp) || Kp < 0 || Kp > 100) Kp = 2.0;
    if (isnan(Ki) || Ki < 0 || Ki > 100) Ki = 0.1;
    if (isnan(Kd) || Kd < 0 || Kd > 100) Kd = 1.0;
    
    EEPROM.get(EEPROM_PID_MODE_ADDR, pOnM);
    if (pOnM != true && pOnM != false) pOnM = true;  // Valeur par défaut si invalide
    
    setPIDTunings(Kp, Ki, Kd);
}

void TemperatureControl::savePIDSettings() {
    EEPROM.put(EEPROM_PID_P_ADDR, Kp);
    EEPROM.put(EEPROM_PID_I_ADDR, Ki);
    EEPROM.put(EEPROM_PID_D_ADDR, Kd);
}

bool TemperatureControl::checkSensorError(double temp) {
    return temp < TEMP_ERROR_THRESHOLD || isnan(temp);
}

bool TemperatureControl::checkOverheatError(double temp) {
    if (temp >= MAX_SAFE_TEMP) return true;
    
    // Vérification du taux de variation
    double tempRise = (temp - lastTemp) * (1000.0 / TEMP_READ_INTERVAL);
    return tempRise > MAX_TEMP_RISE_RATE;
}

double TemperatureControl::filterTemperature(double newTemp) {
    // Filtre moyenne mobile pondérée exponentielle
    tempBuffer[bufferIndex] = newTemp;
    bufferIndex = (bufferIndex + 1) % TEMP_FILTER_SAMPLES;

    if (enableTempFilter) {  // Utilisation de la variable globale
        filteredTemp = (newTemp * TEMP_FILTER_WEIGHT) + 
                      (filteredTemp * (1.0 - TEMP_FILTER_WEIGHT));
        return filteredTemp;
    }
    return newTemp;
}

bool TemperatureControl::checkSensor() {
    if (SIMULATION_MODE) return true;
    
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);
    return temp != DEVICE_DISCONNECTED_C && temp > TEMP_ERROR_THRESHOLD;
}

void TemperatureControl::startAutoTune(double targetTemp) {
    autoTuneTemp = targetTemp;
    autoTuning = true;
    autoTuneStart = millis();
    
    // Autotune configuration
    autoTune.SetNoiseBand(0.5);  // 0.5°C acceptable noise
    autoTune.SetOutputStep(50);   // 50% output change
    autoTune.SetLookbackSec(20);  // 20 seconds analysis period
    autoTune.SetControlType(1);   // PID (0 for PI)
}

void TemperatureControl::stopAutoTune() {
    autoTuning = false;
    outputPower = 0;
}

bool TemperatureControl::updateAutoTune() {
    if (!autoTuning) return false;
    
    if (autoTune.Runtime()) {
        autoTuning = false;
        
        // Récupération des paramètres calculés
        Kp = autoTune.GetKp();
        Ki = autoTune.GetKi();
        Kd = autoTune.GetKd();
        
        // Application des nouveaux paramètres
        myPID.SetTunings(Kp, Ki, Kd);
        
        // Sauvegarde en EEPROM
        savePIDSettings();
        return true;
    }
    return false;
}

double TemperatureControl::getAutoTuneProgress() {
    if (!autoTuning) return 100.0;
    // Estimation du progrès basée sur le temps (environ 10 cycles)
    unsigned long elapsed = millis() - autoTuneStart;
    return constrain(elapsed / (10.0 * autoTune.GetLookbackSec() * 1000.0) * 100.0, 0, 99);
}

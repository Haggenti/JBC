#pragma once

#include "config.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>

class TemperatureControl {
public:
    TemperatureControl();
    void begin();
    void update();
    double getCurrentTemp() { return currentTemp; }
    double getTargetTemp() { return setPoint; }  // Ajout du getter
    void setTargetTemp(double temp) { setPoint = temp; }
    double getOutputPower() { return outputPower; }
    void setPIDTunings(double p, double i, double d);
    void loadPIDSettings();
    void savePIDSettings();
    ErrorState getErrorState() { return errorState; }
    bool isError() { return errorState != NO_ERROR; }
    double getKp() { return Kp; }
    double getKi() { return Ki; }
    double getKd() { return Kd; }
    bool checkSensor();
    void startAutoTune(double targetTemp);
    void stopAutoTune();
    bool isAutoTuning() { return autoTuning; }
    bool updateAutoTune();
    double getAutoTuneProgress();
    bool getPOnM() { return pOnM; }
    void setPOnM(bool enabled);

private:
    OneWire oneWire;
    DallasTemperature sensors;
    PID myPID;
    
    double currentTemp;
    double setPoint;
    double outputPower;
    double simulatedTemp;
    double Kp, Ki, Kd;
    ErrorState errorState;
    double lastTemp;
    unsigned long lastTempRead;
    double filteredTemp;
    
    double tempBuffer[TEMP_FILTER_SAMPLES];
    int bufferIndex;
    
    void updateSimulatedTemp();
    bool checkSensorError(double temp);
    bool checkOverheatError(double temp);
    double filterTemperature(double newTemp);
    PID_ATune autoTune;
    double autoTuneInput;    // Variable pour l'autotune
    double autoTuneOutput;   // Variable pour l'autotune
    bool autoTuning;
    unsigned long autoTuneStart;
    double autoTuneTemp;
    bool pOnM;          // État de P_ON_M
};

extern TemperatureControl tempControl;

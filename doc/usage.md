# User Guide

## Operating Modes
1. **IDLE Mode**
   - Rest state, heating disabled
   - Current temperature display
   - No active control

2. **MASH Mode**
   - PID temperature control
   - Temperature range: 40°C to 80°C
   - 1.0°C increments
   - Buzzer when target temperature is reached
   - Automatic timer when temperature is reached

3. **BOIL Mode**
   - Simple PWM control
   - Adjustable power 50% to 100%
   - Automatic cutoff at 100°C

## Display
- **Left Display**: Current temperature
- **Right Display**: Target temperature (MASH) or unused (other modes)
- **LCD**:
  - Line 1: Current mode
  - Line 2: Heating power
  - Line 3: Timer (MASH mode)
  - Line 4: System status

## Navigation and Controls

### Basic Controls
- **Long press**: Change mode (IDLE -> MASH -> BOIL -> IDLE)
- **Short press**: Activate/deactivate current mode
- **Encoder rotation**:
  - MASH mode: Adjust target temperature (1.0°C steps)
  - BOIL mode: Adjust heating power

### PID Menu (MASH Mode)
- **Access**: Double-click button
- **Navigation**:
  - Single click: Next parameter
  - Encoder rotation: Adjust value
  - Long press: Toggle option or save
- **Parameters**:
  - P (Proportional): 0.1 to 100 in 0.1 steps
  - I (Integral): 0.01 to 100 in 0.01 steps
  - D (Derivative): 0.1 to 100 in 0.1 steps
  - P on M: Enable/disable proportional on measurement
  - Autotune: Start/stop automatic tuning
  - Save: Save parameters
  - Exit: Leave menu

### Configuration Menu (IDLE Mode)
- **Access**: Short press in IDLE mode
- **Options**:
  - Temperature Filter: Enable/disable smoothing
  - Exit: Leave menu
- **Timeout**: Auto-return after 10 seconds of inactivity

## Safety Features
- Disconnected sensor detection
- Overheat protection (>110°C)
- Rapid temperature change detection
- Red LED heating indicator
- Automatic shutdown on error

## States and Indicators
1. **LCD Status**
   - STOPPED: Inactive mode
   - HEATING: Heating in progress
   - TEMP OK: Target temperature reached (MASH)
   - STANDBY: Waiting
   - SENSOR ERR: Sensor error
   - OVERHEAT: Overheating

2. **Indicators**
   - LED on: Active heating
   - Buzzer:
     - One beep: Mode change
     - One beep: Temperature reached
     - One beep: Error detected

## Simulation Mode
- Activatable via SIMULATION_MODE in config.h
- Simulates thermal behavior
- Perfect for testing without hardware
- Includes simulated thermal inertia

## Parameter Storage
- PID parameters saved in EEPROM
- Automatic restoration at startup
- Protection against invalid values

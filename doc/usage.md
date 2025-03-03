# JBC Brewing Controller - User Guide

## Operating Modes

### 1. IDLE Mode
- System at rest, heating disabled
- Displays current temperature
- Access to configuration menu
- Safety monitoring active

### 2. MASH Mode
- PID temperature control
- Temperature range: 40°C to 80°C
- 0.5°C increments
- Temperature reached notification
- Automatic timer after reaching target
- Full PID control with auto-tuning

### 3. BOIL Mode
- Manual power control
- Power range: 50% to 100%
- 1% increments
- Automatic cutoff at 100°C
- Power level memory

## Display System

### Main Display Elements
- Left Display (4 digits): Current temperature (×10)
- Right Display (4 digits): Target temperature or power level
- 20x4 LCD Screen:
  - Line 1: Operating mode
  - Line 2: Current power level
  - Line 3: Timer (MASH mode)
  - Line 4: System status

### Status Indicators
- LED: Shows active heating
- Buzzer: 
  - Single beep: Normal operations
  - Triple high-pitch beep: Errors/Alerts
- LCD Status Messages:
  - STOPPED: Mode inactive
  - HEATING: Active temperature control
  - TEMP OK: Target temperature reached
  - STANDBY: Waiting for action
  - SENSOR ERR: Temperature sensor error
  - OVERHEAT: Temperature too high

## Control Interface

### Basic Controls
- Rotary Encoder:
  - Rotate: Adjust values
  - Short press: Activate/deactivate mode
  - Long press: Change mode
  - Double click: Enter PID menu (MASH mode)

### Navigation Rules
- Mode Sequence: IDLE -> MASH -> BOIL -> IDLE
- Each mode must be explicitly activated
- Safety stops when changing modes
- Auto-exit from menus after timeout

## Configuration Menus

### PID Settings (MASH Mode)
- Access: Double-click in MASH mode
- Parameters:
  - P: Proportional (0.1-100.0)
  - I: Integral (0.01-100.0)
  - D: Derivative (0.1-100.0)
  - P on M: Proportional on Measurement
  - AutoTune: Automatic PID calibration
  - Save: Store to EEPROM
  - Exit: Return to main screen
- Navigation:
  - Click: Next parameter
  - Long press: Activate/save
  - Rotate: Adjust values

### System Configuration (IDLE Mode)
- Access: Short press in IDLE mode
- Settings:
  - Temperature Filter: Smooth readings
  - Exit: Return to main display
- Auto-exit: 10 seconds timeout

## Safety Features

### Temperature Protection
- Sensor error detection
- Maximum temperature limit (110°C)
- Rate of change monitoring
- Automatic shutdown on error

### System Safeguards
- EEPROM parameter validation
- Power output limits
- Mode transition safety
- Automatic error recovery

## Advanced Features

### Temperature Filtering
- Optional digital filtering
- Configurable through menu
- Saved across power cycles
- Improved stability

### PID Control
- P on M enabled by default
- Auto-tuning capability
- EEPROM parameter storage
- Real-time adjustments

### Simulation Mode
- Hardware-free testing
- Thermal simulation
- Configurable parameters
- Development aid

## Maintenance

### Settings Management
- Automatic EEPROM storage
- Parameter validation
- Factory reset option
- Error recovery

### Troubleshooting
1. Sensor Errors:
   - Check connections
   - Verify temperature range
   - Check for water damage
2. Control Issues:
   - Verify PID settings
   - Check SSR function
   - Monitor power output
3. Display Problems:
   - Check I2C connections
   - Verify power supply
   - Test communication

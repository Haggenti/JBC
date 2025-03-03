# Features and Specifications

## Control Features
1. **Temperature Control**
   - PID control with anti-windup protection
   - P-on-M capability for better stability
   - Configurable temperature filtering
   - Auto-tuning functionality
   - Temperature range: 40°C to 80°C (mash)
   - 1.0°C adjustment steps

2. **Operating Modes**
   - IDLE: Monitoring only
   - MASH: PID-controlled temperature
   - BOIL: Manual power control (50-100%)

3. **Display System**
   - Dual TM1637 4-digit displays
   - 20x4 I2C LCD display
   - Custom characters for enhanced UI
   - Real-time power indication
   - Timer display for mash/boil

## Safety Features
1. **Temperature Protection**
   - Sensor error detection
   - Overheat protection (110°C max)
   - Rate-of-change monitoring
   - Automatic shutdown on error

2. **Power Control**
   - SSR control with zero-crossing
   - Power soft-start
   - Emergency stop capability
   - Automatic timeout safety

## Hardware Specifications
1. **Main Controller**
   - Arduino Nano (ATmega328P)
   - 32KB Flash memory
   - 2KB SRAM
   - 1KB EEPROM

2. **Sensors & Inputs**
   - DS18B20 waterproof temperature sensor
   - Rotary encoder with push button
   - Visual and audible feedback

3. **Outputs**
   - Solid State Relay (SSR)
   - Status LED
   - Configurable buzzer
   - Dual display system

## Advanced Features
1. **PID Control**
   - Dynamic anti-windup protection
   - Configurable gain parameters
   - Automatic tuning capability
   - EEPROM parameter storage

2. **User Interface**
   - Multi-level menu system
   - Custom character set
   - Real-time status display
   - Context-sensitive controls

3. **Data Management**
   - Non-volatile settings storage
   - Parameter validation
   - Configuration backup
   - Factory reset capability

## System Requirements
1. **Power**
   - 230V AC mains supply
   - 30mA RCD protection
   - Appropriate fusing

2. **Environmental**
   - Operating temperature: 0-40°C
   - IP54 minimum enclosure
   - Adequate ventilation

3. **Safety Standards**
   - Electrical isolation
   - Temperature failsafes
   - Emergency shutdown
   - User access control

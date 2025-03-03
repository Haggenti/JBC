# JBC - Joe's Brewing Controller 🍺

An Arduino-based brewing controller with advanced PID control and feature-rich interface.

## Features

### Temperature Control
- Precise PID control with anti-windup protection
- Auto-tuning capability
- Configurable temperature filtering
- Temperature range 40-80°C for mashing
- Boil control up to 100°C
- Safety thermal protection

### User Interface
- 20x4 LCD display with custom characters
- Dual 4-digit temperature displays
- Rotary encoder navigation
- Visual and audio feedback
- Real-time status monitoring

### Operating Modes
- **MASH**: PID-controlled temperature
- **BOIL**: Manual power control (50-100%)
- **IDLE**: Monitoring only

### Safety Features
- Sensor error detection
- Overheat protection
- Rate-of-change monitoring
- Emergency shutdown
- Power monitoring

## Hardware Requirements

### Core Components
- Arduino Nano (ATmega328P)
- DS18B20 waterproof temperature sensor
- Solid State Relay (SSR)
- 20x4 I2C LCD display
- 2x TM1637 4-digit displays
- Rotary encoder with button
- Status LED and buzzer

### Power Requirements
- 230V AC power supply
- 30mA RCD protection
- Appropriate fusing
- Minimum 2.5mm² wiring

## Installation

1. Clone this repository
2. Install PlatformIO
3. Install required libraries:
   - OneWire
   - DallasTemperature
   - PID
   - PID-AutoTune
   - LiquidCrystal_I2C
   - TM1637Display

## Usage

See the [documentation](doc/usage.md) for detailed instructions.

## Safety Warnings ⚠️

This project involves high voltage electricity and heating elements. Installation should only be performed by qualified individuals familiar with electrical safety standards.

## Documentation

Full documentation available in the [doc](doc/) directory:
- [Features List](doc/features.md)
- [Installation Guide](doc/installation.md)
- [User Manual](doc/usage.md)
- [Maintenance Guide](doc/maintenance.md)
- [Wiring Diagrams](doc/diagrams/)

## Contributing

Contributions are welcome! Please read our [Contributing Guidelines](CONTRIBUTING.md) first.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- PID library by Brett Beauregard
- Original inspiration from various homebrew controllers
- Community feedback and contributions

## Author

[Joe]

## Project Status

Current version: 1.0.7
Last update: March 2025

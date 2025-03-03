# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.7] - 2025-03-03
### Added
- Anti-windup protection for PID control
- Dynamic windup guard based on integral gain
- Output saturation detection
- Improved integral term management

## [1.0.6] - 2025-03-03
### Changed
- Temperature adjustment step changed to 1.0°C for better control
- Documentation updated to reflect new temperature increments

## [1.0.5] - 2025-03-03
### Added
- TODO list for future improvements
- Enhanced documentation structure
- Future feature planning section

### Changed
- Removed non-English documentation
- Consolidated all documentation in English
- Improved usage guide clarity

## [1.0.4] - 2025-03-03
### Added
- P_ON_M option in PID menu with EEPROM storage
- P_ON_M enabled by default for better stability
- Configurable temperature filtering via menu
- Filter state saved in EEPROM

## [1.0.3] - 2025-03-03
### Changed
- Migrated to Arduino Nano ATmega328P for more memory
- Updated documentation to reflect hardware change

## [1.0.2] - 2025-03-03
### Added
- Differentiated buzzer sounds (normal/error)
- Configurable frequencies and durations for beeps
- Error sound with multiple repetitions

## [1.0.1] - 2024-01-XX
### Added
- Startup screen with project name and version
- Temperature sensor presence check at startup
- Sensor status message on LCD
- Safety loop with visual and sound alarm if sensor not detected

### Changed
- Reorganized startup sequence
- Improved startup error handling
- Split documentation files by language (/doc/fr and /doc/en)

## [1.0.0] - 2024-01-XX
### Added
- Initial project creation
- Implementation of three modes: IDLE, MASH, BOIL
- PID control for MASH mode
- PWM control for BOIL mode
- User interface with 20x4 LCD and two TM1637 displays
- PID configuration menu accessible via double-click
- Parameter storage in EEPROM
- Simulation mode for hardware-free testing
- Safety features:
  - Disconnected sensor detection
  - Overheat protection
  - Abnormal temperature variation detection
- Documentation:
  - Detailed wiring instructions
  - Complete user guide
  - Feature description

### Technical Features
- Optional temperature filtering
- Encoder and button debounce handling
- Realistic thermal inertia simulation
- Heating indicator LED
- Sound feedback on important actions
- Modular code structure:
  - Interface/temperature control separation
  - Centralized configuration
  - Integrated documentation

[1.0.0]: https://github.com/username/JBC/releases/tag/v1.0.0

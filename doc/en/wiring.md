# Brewing System Wiring Instructions

## Required Components
- Arduino Nano (ATmega328P)
- SSR Relay for heating element
- Waterproof DS18B20 temperature sensor
- 2x TM1637 4-digit displays
- 20x4 I2C LCD display
- Rotary encoder with push button
- Red LED (heating indicator)
- Passive buzzer
- Resistors: 2x 4.7kΩ, 1x 220Ω

## Arduino Connections

### DS18B20 Temperature Sensor
- Signal (yellow wire) -> D2
- VCC (red wire) -> 5V
- GND (black wire) -> GND
- 4.7kΩ pull-up resistor between Signal and VCC

### SSR Relay
- Signal -> D3
- VCC -> 5V
- GND -> GND

### Rotary Encoder
- CLK -> D4
- DT -> D5
- SW -> D6
- VCC -> 5V
- GND -> GND
- 4.7kΩ pull-up resistor on SW

### Temperature Display TM1637
- CLK -> D7
- DIO -> D8
- VCC -> 5V
- GND -> GND

### Setpoint Display TM1637
- CLK -> D9
- DIO -> D10
- VCC -> 5V
- GND -> GND

### Buzzer
- Signal -> D11
- GND -> GND

### Indicator LED
- Anode (+) -> D12 via 220Ω resistor
- Cathode (-) -> GND

### I2C LCD Screen
- SDA -> A4
- SCL -> A5
- VCC -> 5V
- GND -> GND

## Power Section Wiring

### SSR Relay
- A1/A2 (control side) -> Arduino output
- L1/L2 (power side) -> In series with heating element
- Provide heatsink appropriate for power rating

### Heating Element
- Live -> Via SSR
- Neutral -> Direct
- Ground -> Direct to earth

## Important Notes
1. Use appropriate wire gauge for power section (minimum 2.5mm²)
2. Properly insulate all connections
3. Place power section in separate enclosure
4. Provide thermal protection on vessel
5. Add fuse rated for heating element
6. Use screw terminals for power connections
7. Temperature sensor must be in thermowell

## Protection and Safety
- Install 30mA differential circuit breaker
- Verify all connections are waterproof
- Test software safety features
- Properly ventilate SSR enclosure

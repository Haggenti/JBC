# Schéma de câblage

```ascii
                       Arduino Nano
                    ┌────────────┐
     DS18B20  ──────┤D2          │
     SSR      ──────┤D3          │
     ENC_CLK  ──────┤D4          │
     ENC_DT   ──────┤D5    A4├───┐
     ENC_SW   ──────┤D6    A5├───┤
     TMP_CLK  ──────┤D7          │
     TMP_DIO  ──────┤D8          │
     SP_CLK   ──────┤D9          │
     SP_DIO   ──────┤D10         │
     BUZZER   ──────┤D11         │
     LED      ──────┤D12         │
                    │            │
                    │     5V├────┼─────┐
                    │    GND├────┼─────┼─────┐
                    └────────────┘     │     │
                                       │     │
                    LCD I2C            │     │
                    ┌─────────┐        │     │
                    │SDA──────┘        │     │
                    │SCL──────┘        │     │
                    │VCC───────────────┘     │
                    │GND─────────────────────┘
                    └─────────┘

   SSR          DS18B20     Encodeur    TM1637 (x2)
   ┌───┐        ┌───┐       ┌───┐       ┌───┐
   │OUT├─Heat   │SIG├─D2    │CLK├─D4    │CLK├─D7/D9
   │VCC├─5V     │VCC├─5V    │DT ├─D5    │DIO├─D8/D10
   │GND├─GND    │GND├─GND   │SW ├─D6    │VCC├─5V
   └───┘        └───┘       │VCC├─5V    │GND├─GND
                            │GND├─GND   └───┘
                            └───┘

Notes:
- Résistance pull-up 4.7kΩ entre VCC et Signal DS18B20
- Résistance pull-up 4.7kΩ sur SW de l'encodeur
- Résistance 220Ω en série avec la LED
- Radiateur sur le SSR
```

# Instructions de câblage du système de brassage

## Composants nécessaires
- Arduino Nano (ATmega168)
- Relais SSR pour la résistance
- Sonde de température DS18B20 étanche
- 2 Afficheurs 4 digits TM1637
- Écran LCD I2C 20x4
- Encodeur rotatif avec bouton poussoir
- LED rouge (témoin de chauffe)
- Buzzer passif
- Résistances : 2x 4.7kΩ, 1x 220Ω

## Connexions Arduino

### Sonde température DS18B20
- Signal (fil jaune) -> D2
- VCC (fil rouge) -> 5V
- GND (fil noir) -> GND
- Résistance pull-up 4.7kΩ entre Signal et VCC

### Relais SSR
- Signal -> D3
- VCC -> 5V
- GND -> GND

### Encodeur rotatif
- CLK -> D4
- DT -> D5
- SW -> D6
- VCC -> 5V
- GND -> GND
- Résistance pull-up 4.7kΩ sur SW

### Afficheur température TM1637
- CLK -> D7
- DIO -> D8
- VCC -> 5V
- GND -> GND

### Afficheur consigne TM1637
- CLK -> D9
- DIO -> D10
- VCC -> 5V
- GND -> GND

### Buzzer
- Signal -> D11
- GND -> GND

### LED témoin
- Anode (+) -> D12 via résistance 220Ω
- Cathode (-) -> GND

### Écran LCD I2C
- SDA -> A4
- SCL -> A5
- VCC -> 5V
- GND -> GND

## Schéma de câblage de la partie puissance

### Relais SSR
- A1/A2 (côté commande) -> Sortie Arduino
- L1/L2 (côté puissance) -> En série avec la résistance
- Prévoir un radiateur adapté à la puissance

### Résistance de chauffe
- Phase -> Via SSR
- Neutre -> Direct
- Terre -> Direct sur terre

## Notes importantes
1. Utiliser des fils de section adaptée pour la partie puissance (2.5mm² minimum)
2. Bien isoler toutes les connexions
3. Mettre la partie puissance dans un boîtier séparé
4. Prévoir une protection thermique sur la cuve
5. Ajouter un fusible adapté à la puissance de la résistance
6. Utiliser des borniers à vis pour les connexions de puissance
7. La sonde de température doit être dans un doigt de gant

## Protection et sécurité
- Prévoir un disjoncteur différentiel 30mA
- Vérifier l'étanchéité de toutes les connexions
- Tester le bon fonctionnement des sécurités logicielles
- Ventiler correctement le boîtier contenant le SSR

# Changelog
Tous les changements notables apportés à ce projet seront documentés dans ce fichier.

Le format est basé sur [Keep a Changelog](https://keepachangelog.com/fr/1.1.0/),
et ce projet adhère à la [Gestion sémantique de version](https://semver.org/lang/fr/).

## [1.0.0] - 2024-01-XX
### Ajouté
- Création initiale du projet
- Implémentation des trois modes : IDLE, MASH, BOIL
- Contrôle PID pour le mode MASH
- Contrôle PWM pour le mode BOIL
- Interface utilisateur avec LCD 20x4 et deux afficheurs TM1637
- Menu de configuration PID accessible par double-clic
- Sauvegarde des paramètres en EEPROM
- Mode simulation pour tests sans matériel
- Sécurités :
  - Détection de sonde déconnectée
  - Protection contre la surchauffe
  - Détection de variation de température anormale
- Documentation :
  - Instructions de câblage détaillées
  - Guide d'utilisation complet
  - Description des fonctionnalités

### Fonctionnalités techniques
- Filtrage de température optionnel
- Gestion du debounce pour l'encodeur et le bouton
- Simulation d'inertie thermique réaliste
- LED témoin de chauffe
- Retour sonore sur les actions importantes
- Structure modulaire du code :
  - Séparation interface/contrôle température
  - Configuration centralisée
  - Documentation intégrée

[1.0.0]: https://github.com/username/JBC/releases/tag/v1.0.0

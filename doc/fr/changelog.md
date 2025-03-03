# Changelog
// ...existing header...

## [1.0.4] - 2025-03-03
### Ajouté
- Option P_ON_M dans le menu PID avec sauvegarde en EEPROM
- Activation par défaut de P_ON_M pour une meilleure stabilité
- Filtrage de température configurable via le menu
- Sauvegarde de l'état du filtre en EEPROM

## [1.0.3] - 2025-03-03
### Modifié
- Migration vers Arduino Nano ATmega328P pour plus de mémoire
- Mise à jour de la documentation pour refléter le changement de matériel

## [1.0.2] - 2025-03-03
### Ajouté
- Différenciation des sons du buzzer (normal/erreur)
- Configuration des fréquences et durées des bips
- Son d'erreur avec répétition multiple

## [1.0.1] - 2024-03-03
### Ajouté
- Écran de démarrage avec nom du projet et version
- Test de présence de la sonde au démarrage
- Message de statut de la sonde sur LCD
- Boucle de sécurité avec alarme visuelle et sonore si sonde non détectée

### Modifié
- Réorganisation de la séquence de démarrage
- Amélioration de la gestion des erreurs au démarrage
- Séparation des fichiers de documentation par langue (/doc/fr et /doc/en)

## [1.0.0] - 2024-03-03
// ...rest of existing content...

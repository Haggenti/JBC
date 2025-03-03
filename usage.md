# Guide d'utilisation

## Modes de fonctionnement
1. **Mode IDLE**
   - État de repos, chauffage désactivé
   - Affichage de la température actuelle
   - Aucun contrôle actif

2. **Mode MASH**
   - Contrôle PID de la température
   - Température réglable de 40°C à 80°C
   - Buzzer quand la température cible est atteinte
   - Chronomètre automatique une fois la température atteinte

3. **Mode BOIL**
   - Contrôle PWM simple
   - Puissance réglable de 50% à 100%
   - Coupure automatique à 100°C

## Affichage
- **Afficheur gauche** : Température actuelle
- **Afficheur droit** : Température cible (MASH) ou non utilisé (autres modes)
- **LCD** :
  - Ligne 1 : Mode actuel
  - Ligne 2 : Puissance de chauffe
  - Ligne 3 : Chronomètre (en mode MASH)
  - Ligne 4 : État du système

## Navigation et contrôles

### Contrôles de base
- **Appui long** : Change de mode (IDLE -> MASH -> BOIL -> IDLE)
- **Appui court** : Active/désactive le mode actuel
- **Rotation encodeur** :
  - Mode MASH : Ajuste la température cible
  - Mode BOIL : Ajuste la puissance de chauffe

### Menu PID (Mode MASH)
- **Accès** : Double-clic sur le bouton
- **Navigation** :
  - Clic simple : Passe au paramètre suivant
  - Rotation encodeur : Ajuste la valeur
  - Appui long sur "Save" : Sauvegarde les paramètres
  - Appui long sur "Exit" : Quitte sans sauvegarder

### Paramètres PID
- P (Proportionnel) : 0.1 à 100 par pas de 0.1
- I (Intégral) : 0.01 à 100 par pas de 0.01
- D (Dérivé) : 0.1 à 100 par pas de 0.1

## Sécurités
- Détection de sonde déconnectée
- Protection surchauffe (>110°C)
- Détection de variation trop rapide
- LED rouge indiquant la chauffe
- Désactivation automatique en cas d'erreur

## États et indications
1. **Status sur LCD**
   - STOPPED : Mode inactif
   - HEATING : Chauffe en cours
   - TEMP OK : Température cible atteinte (MASH)
   - STANDBY : En attente
   - SENSOR ERR : Erreur de sonde
   - OVERHEAT : Surchauffe

2. **Indicateurs**
   - LED allumée : Chauffe active
   - Buzzer : 
     - Un bip : Changement de mode
     - Un bip : Température atteinte
     - Un bip : Erreur détectée

## Mode simulation
- Activable via SIMULATION_MODE dans config.h
- Simule le comportement thermique
- Parfait pour les tests sans matériel
- Inclut l'inertie thermique simulée

## Sauvegarde des paramètres
- Paramètres PID sauvegardés en EEPROM
- Restauration automatique au démarrage
- Protection contre les valeurs invalides

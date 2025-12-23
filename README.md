# Systeme de Gestion de Parking

## Description

Ce projet est un systeme complet de gestion de parking developpe en langage C. 
Il a ete realise dans le cadre du module d'Algorithmique du cursus ingenieur.

## Auteur

- **Encadrant** : Dr ANAKPA
- **Annee** : 2024-2025

## Fonctionnalites

### Gestion des vehicules
- Enregistrement des entrees avec attribution automatique de place
- Enregistrement des sorties avec calcul automatique du montant
- Recherche de vehicules par plaque d'immatriculation
- Affichage des vehicules presents

### Gestion des places
- Affichage de l'etat de toutes les places
- Mise hors service / remise en service
- Reservation de places
- Carte visuelle du parking

### Statistiques et rapports
- Resume journalier
- Rapport complet d'occupation
- Historique des vehicules
- Recettes par type de vehicule

### Persistance des donnees
- Sauvegarde automatique a la fermeture
- Chargement des donnees au demarrage

## Structure du projet

```
projet_parking/
    |-- main.c                 # Point d'entree du programme
    |-- Makefile               # Script de compilation
    |-- README.md              # Ce fichier
    |
    |-- include/               # Fichiers d'en-tete (.h)
    |   |-- types.h            # Definitions des types et constantes
    |   |-- utilitaires.h      # Fonctions utilitaires
    |   |-- parking.h          # Fonctions de gestion du parking
    |   |-- tri_recherche.h    # Algorithmes de tri et recherche
    |   |-- statistiques.h     # Fonctions de statistiques
    |   +-- menu.h             # Interface utilisateur
    |
    |-- src/                   # Fichiers sources (.c)
    |   |-- utilitaires.c      # Implementation des utilitaires
    |   |-- utilitaires_temps.c # Gestion du temps
    |   |-- parking_init.c     # Initialisation du parking
    |   |-- parking_places.c   # Gestion des places
    |   |-- parking_vehicules.c # Gestion des vehicules
    |   |-- parking_affichage.c # Affichage et tickets
    |   |-- tri_recherche.c    # Algorithmes de tri
    |   |-- recherche.c        # Algorithmes de recherche
    |   |-- statistiques.c     # Calcul des statistiques
    |   |-- statistiques_suite.c # Historique et sauvegarde
    |   |-- menu.c             # Affichage des menus
    |   +-- menu_traitement.c  # Traitement des actions
    |
    +-- docs/                  # Documentation
        +-- rapport.tex        # Rapport en LaTeX
```

## Compilation

### Prerequis
- Compilateur GCC
- Make (optionnel)

### Avec Make
```bash
# Compilation
make all

# Nettoyage
make clean

# Reconstruction
make rebuild

# Execution
make run
```

### Sans Make (Windows)
```cmd
gcc -Wall -Wextra -std=c99 -o parking.exe main.c src/*.c
```

### Sans Make (Linux/Mac)
```bash
gcc -Wall -Wextra -std=c99 -o parking main.c src/*.c
```

## Utilisation

1. Lancer l'executable genere
2. Naviguer dans les menus avec les numeros
3. Les donnees sont sauvegardees automatiquement

## Notions algorithmiques couvertes

Ce projet met en pratique les concepts suivants :

| Notion | Implementation |
|--------|----------------|
| Variables et constantes | Fichier types.h |
| Types de base | int, float, char |
| Types enumeres | TypeVehicule, EtatPlace |
| Structures | Vehicule, Place, Parking |
| Tableaux 1D | places[], historique[] |
| Boucles for | Parcours des tableaux |
| Boucles while | Menus et saisies |
| Conditions if/else | Logique metier |
| Switch | Selection de menu |
| Fonctions | Modularite du code |
| Pointeurs | Passage par reference |
| Tri par selection | triSelectionVehicules() |
| Tri par insertion | triInsertionVehicules() |
| Recherche sequentielle | rechercheSequentielle() |
| Recherche dichotomique | rechercheDichotomique() |
| Technique du drapeau | rechercheAvecDrapeau() |

## Configuration

Les constantes du systeme sont definies dans `include/types.h` :

```c
#define MAX_PLACES 100        /* Nombre max de places */
#define MAX_VEHICULES 500     /* Taille de l'historique */
#define TARIF_HORAIRE 200     /* Tarif en FCFA */
#define TARIF_JOURNALIER_MAX 2000
```

## Tarification

| Type de vehicule | Coefficient | Tarif horaire |
|------------------|-------------|---------------|
| Moto | 0.5 | 100 FCFA |
| Voiture | 1.0 | 200 FCFA |
| Camion | 1.5 | 300 FCFA |
| Bus | 2.0 | 400 FCFA |

Le montant est plafonne a 2000 FCFA par jour.

## Rapport

Le rapport complet du projet est disponible dans le dossier `docs/` au format LaTeX.
Pour generer le PDF :

```bash
cd docs
pdflatex rapport.tex
pdflatex rapport.tex  # Deux fois pour la table des matieres
```

## Licence

Projet academique - Tous droits reserves.

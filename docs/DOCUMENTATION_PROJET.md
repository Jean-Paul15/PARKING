# Documentation du Système de Gestion de Parking

## Vue d'ensemble

Projet développé en langage C dans le cadre du cursus ingénieur - Module Algorithmique.
Système complet de gestion de parking couvrant les notions fondamentales : structures de données, 
algorithmes de tri et recherche, gestion de fichiers, et interface utilisateur en console.

**Encadrant:** Dr ANAKPA  
**Année:** 2024-2025  
**Date:** Décembre 2025

## Objectifs pédagogiques

- Manipulation des structures de données complexes
- Implementation d'algorithmes de tri (sélection, insertion)
- Implementation d'algorithmes de recherche (séquentielle, dichotomique)
- Gestion de fichiers pour la persistance des données
- Conception d'interface utilisateur interactive
- Application des principes de modularité et séparation des responsabilités

## Architecture du projet

Le projet suit une architecture modulaire avec séparation claire des responsabilités :

```
projet_parking/
├── main.c                          # Point d'entrée du programme
├── Makefile                        # Script de compilation automatisée
├── README.md                       # Documentation utilisateur
│
├── include/                        # Fichiers d'en-tête (.h)
│   ├── types.h                     # Définitions des types et structures
│   ├── parking.h                   # Interface de gestion du parking
│   ├── menu.h                      # Interface utilisateur
│   ├── statistiques.h              # Interface de statistiques
│   ├── tri_recherche.h             # Algorithmes de tri et recherche
│   ├── utilitaires.h               # Fonctions utilitaires
│   └── prototypes.h                # Prototypes globaux (si utilisé)
│
├── src/                            # Implémentations (.c)
│   ├── parking_init.c              # Initialisation du parking
│   ├── parking_places.c            # Gestion des places
│   ├── parking_vehicules.c         # Gestion des véhicules
│   ├── parking_affichage.c         # Génération tickets et affichages
│   ├── tri_recherche.c             # Algorithmes de tri
│   ├── recherche.c                 # Algorithmes de recherche
│   ├── statistiques.c              # Calcul des statistiques
│   ├── statistiques_suite.c        # Historique et sauvegarde
│   ├── menu.c                      # Affichage des menus
│   ├── menu_traitement.c           # Traitement des actions utilisateur
│   ├── utilitaires.c               # Fonctions utilitaires générales
│   └── utilitaires_temps.c         # Gestion du temps et horodatage
│
├── obj/                            # Fichiers objets de compilation
├── bin/                            # Exécutables
└── docs/                           # Documentation
    ├── rapport.tex                 # Rapport LaTeX
    └── DOCUMENTATION_PROJET.md     # Ce fichier
```

## Modules fonctionnels

### 1. Module Types (types.h)

**Rôle:** Définitions centrales du système

**Contenu:**
- **Constantes système:**
  - `MAX_PLACES = 100` : Capacité maximale
  - `MAX_VEHICULES = 500` : Taille historique
  - `TARIF_HORAIRE = 200` : Tarification en FCFA
  - `TAILLE_PLAQUE = 15` : Longueur plaque

- **Énumérations:**
  ```c
  TypeVehicule : VOITURE, MOTO, CAMION, BUS
  EtatPlace : LIBRE, OCCUPEE, RESERVEE, HORS_SERVICE
  ```

- **Structures principales:**
  - `Horodatage` : Date et heure (jour, mois, année, heure, minute)
  - `Vehicule` : Plaque, propriétaire, type, entrée/sortie, montant
  - `Place` : Numéro, état, type autorisé, véhicule actuel
  - `Parking` : Nom, tableau de places, historique, recettes
  - `Statistiques` : Métriques d'occupation et revenus

**But:** Fournir un typage fort et éviter la duplication de définitions.


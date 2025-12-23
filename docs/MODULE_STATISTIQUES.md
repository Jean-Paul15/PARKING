# Documentation du Module Statistiques

## Module Statistiques (statistiques.h / statistiques.c / statistiques_suite.c)

### Objectif
Fournir des métriques d'exploitation, rapports détaillés et persistance des données 
pour l'analyse et le suivi du parking.

---

## Partie 1 : Calcul des Statistiques (statistiques.c)

### `void calculerStatistiques(const Parking *parking, Statistiques *stats)`

**Responsabilité:** Calcul complet de toutes les métriques du parking.

**Calculs effectués:**
1. Total des entrées (véhicules actuellement présents)
2. Total des sorties (véhicules dans l'historique qui sont sortis)
3. Taux d'occupation actuel
4. Recette moyenne par véhicule
5. Distribution des véhicules par type

**Algorithme:**
```
stats.totalEntrees = 0
stats.totalSorties = 0
Initialiser compteurs par type à 0

Pour chaque véhicule dans l'historique:
    Si véhicule.estPresent:
        stats.totalEntrees++
    Sinon:
        stats.totalSorties++
    
    stats.vehiculesParType[vehicule.type]++

stats.tauxOccupation = calculerTauxOccupation(parking)
stats.recetteMoyenne = calculerRecetteMoyenne(parking)
```

---

### `float calculerTauxOccupation(const Parking *parking)`

**Formule:**
```
tauxOccupation = (placesOccupees / nombrePlaces) × 100
```

**Retour:** Pourcentage entre 0.0 et 100.0

**Cas particuliers:**
- Si nombrePlaces = 0 : retourne 0.0
- Exclut les places HORS_SERVICE du dénominateur

**Exemple:**
```
50 places au total
3 places hors service
35 places occupées
Taux = 35 / (50-3) × 100 = 74.47%
```

---

### `void compterVehiculesParType(const Parking *parking, int compteurs[])`

**Principe:** Parcourt les véhicules présents et incrémente les compteurs.

**Tableau de sortie:**
```c
compteurs[0] : Non utilisé (ou total)
compteurs[1] : Nombre de VOITURE
compteurs[2] : Nombre de MOTO
compteurs[3] : Nombre de CAMION
compteurs[4] : Nombre de BUS
```

**Usage:** Permet d'adapter la capacité par type de véhicule.

---

### `float calculerRecetteMoyenne(const Parking *parking)`

**Formule:**
```
Si nombreVehiculesSortis > 0:
    recetteMoyenne = recetteTotale / nombreVehiculesSortis
Sinon:
    recetteMoyenne = 0.0
```

**But:** Indicateur de durée moyenne de stationnement.

**Interprétation:**
- Recette moyenne basse → stationnements courts
- Recette moyenne élevée → stationnements longs ou clients réguliers

---

## Partie 2 : Affichage des Rapports (statistiques.c)

### `void afficherRapportComplet(const Parking *parking)`

**Contenu:**
```
========================================
    RAPPORT COMPLET - PARKING CENTRAL
========================================

OCCUPATION:
  Places totales     : 50
  Places occupées    : 35
  Places libres      : 12
  Places réservées   : 0
  Places hors service: 3
  Taux d'occupation  : 74.47%

VEHICULES:
  Total entrées      : 35
  Total sorties      : 142
  Voitures          : 28
  Motos             : 5
  Camions           : 2
  Bus               : 0

RECETTES:
  Recette journalière: 12 400 FCFA
  Recette totale     : 284 000 FCFA
  Recette moyenne    : 2 000 FCFA
========================================
```

**Utilité:** Vue globale pour le gestionnaire.

---

### `void afficherResumeJournalier(const Parking *parking)`

**Contenu:** Version condensée du rapport complet, focus sur la journée en cours.

**Filtre:** Ne compte que les véhicules avec date d'entrée = date actuelle.

**Format:**
```
=== RESUME JOURNALIER ===
Date          : 23/12/2025
Entrées       : 18
Sorties       : 15
Véhicules actifs: 3
Recette       : 12 400 FCFA
=========================
```

---

### `void afficherHistorique(const Parking *parking, int nombreMax)`

**Principe:** Affiche les N derniers véhicules de l'historique.

**Paramètres:**
- `nombreMax` : Nombre maximum d'entrées à afficher (par ex. 20)
- Si nombreMax = 0 ou négatif : affiche tout l'historique

**Format:**
```
=== HISTORIQUE DES VEHICULES ===

#   Plaque      Propriétaire    Type    Entrée          Sortie          Montant
1   AB-123-CD   Dupont Martin   Voiture 23/12 14:30    23/12 18:45     1000
2   XY-987-ZT   Durand Sophie   Moto    23/12 09:15    23/12 11:30     600
...
```

**Tri:** Par défaut, affiche dans l'ordre d'arrivée (ou peut être trié par date).

---

### `void afficherRecettesParType(const Parking *parking)`

**Principe:** Agrège les recettes par catégorie de véhicule.

**Algorithme:**
```
Initialiser recettes[5] à 0.0

Pour chaque véhicule dans historique:
    Si véhicule.estPresent == 0:  // A payé et sorti
        recettes[vehicule.type] += vehicule.montantPaye

Afficher recettes par type
```

**Format:**
```
=== RECETTES PAR TYPE ===
Voitures : 186 000 FCFA (65.5%)
Motos    :  42 000 FCFA (14.8%)
Camions  :  48 000 FCFA (16.9%)
Bus      :   8 000 FCFA ( 2.8%)
--------------------------
TOTAL    : 284 000 FCFA
==========================
```

**Utilité:** Identifier les segments les plus rentables.

---

## Partie 3 : Persistance des Données (statistiques_suite.c)

### `int sauvegarderDonnees(const Parking *parking, const char *nomFichier)`

**Responsabilité:** Sauvegarde complète de l'état du parking dans un fichier binaire.

**Structure du fichier:**
```
[En-tête]
- Nom du parking (MAX_CHAINE octets)
- Nombre de places (int)
- Nombre de véhicules dans l'historique (int)

[Section Places]
- Pour chaque place:
  - numero, etat, typeAutorise
  - Si occupée: données du véhicule

[Section Historique]
- Pour chaque véhicule:
  - Tous les champs de la structure Vehicule

[Section Compteurs]
- placesLibres, placesOccupees
- recetteJournaliere, recetteTotale
```

**Algorithme:**
```c
FILE *fichier = fopen(nomFichier, "wb")
Si fichier == NULL:
    Retourner 0

// Écriture en-tête
fwrite(&parking->nom, sizeof(char), MAX_CHAINE, fichier)
fwrite(&parking->nombrePlaces, sizeof(int), 1, fichier)
fwrite(&parking->nombreVehicules, sizeof(int), 1, fichier)

// Écriture places
Pour i de 0 à nombrePlaces-1:
    fwrite(&parking->places[i], sizeof(Place), 1, fichier)

// Écriture historique
Pour i de 0 à nombreVehicules-1:
    fwrite(&parking->historique[i], sizeof(Vehicule), 1, fichier)

// Écriture compteurs
fwrite(&parking->recetteTotale, sizeof(float), 1, fichier)
fwrite(&parking->recetteJournaliere, sizeof(float), 1, fichier)

fclose(fichier)
Retourner 1
```

**Gestion des erreurs:**
- Vérifie que le fichier s'ouvre correctement
- Affiche message d'erreur en cas d'échec
- Retourne 0 si échec, 1 si succès

---

### `int chargerDonnees(Parking *parking, const char *nomFichier)`

**Responsabilité:** Restauration de l'état du parking depuis le fichier.

**Algorithme:**
```c
FILE *fichier = fopen(nomFichier, "rb")
Si fichier == NULL:
    Afficher "Aucune sauvegarde trouvée"
    Retourner 0

// Lecture en-tête
fread(&parking->nom, sizeof(char), MAX_CHAINE, fichier)
fread(&parking->nombrePlaces, sizeof(int), 1, fichier)
fread(&parking->nombreVehicules, sizeof(int), 1, fichier)

// Lecture places
Pour i de 0 à nombrePlaces-1:
    fread(&parking->places[i], sizeof(Place), 1, fichier)

// Lecture historique
Pour i de 0 à nombreVehicules-1:
    fread(&parking->historique[i], sizeof(Vehicule), 1, fichier)

// Lecture compteurs
fread(&parking->recetteTotale, sizeof(float), 1, fichier)
fread(&parking->recetteJournaliere, sizeof(float), 1, fichier)

fclose(fichier)
Recalculer placesLibres et placesOccupees
Retourner 1
```

**Validation post-chargement:**
- Vérifier cohérence des compteurs
- Recalculer les valeurs dérivées
- Vérifier l'intégrité des pointeurs

**Sécurité:**
- Vérifie que nombrePlaces <= MAX_PLACES
- Vérifie que nombreVehicules <= MAX_VEHICULES
- Arrête le chargement si données corrompues

---

## Cas d'Usage Typiques

### Scénario 1 : Fermeture de journée
```
1. Appeler afficherResumeJournalier() → impression rapport
2. Appeler sauvegarderDonnees() → backup automatique
3. Réinitialiser recetteJournaliere à 0 pour le lendemain
```

### Scénario 2 : Analyse hebdomadaire
```
1. Appeler afficherRapportComplet() → métriques globales
2. Appeler afficherRecettesParType() → segments rentables
3. Appeler afficherHistorique(100) → 100 derniers clients
```

### Scénario 3 : Reprise après panne
```
1. Au démarrage: chargerDonnees()
2. Si échec: initialiserParking() → état vierge
3. Si succès: continuer normalement
```

---

## Formats de Fichier

### Nom par défaut
`parking_data.dat` (défini dans main.c)

### Taille estimée
```
En-tête : ~60 octets
Places : 100 × sizeof(Place) ≈ 100 × 32 = 3 200 octets
Historique : 500 × sizeof(Vehicule) ≈ 500 × 120 = 60 000 octets
Compteurs : ~20 octets
------------------------
Total : ~63 Ko maximum
```

### Avantages format binaire
- Taille réduite vs texte
- Lecture/écriture rapide
- Préserve précision des flottants

### Inconvénients
- Non portable entre architectures différentes
- Non lisible par humain
- Sensible à la corruption

**Alternative possible:** Format texte CSV ou JSON pour portabilité.


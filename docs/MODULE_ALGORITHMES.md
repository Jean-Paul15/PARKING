# Documentation des Algorithmes

## Module Tri et Recherche (tri_recherche.h / tri_recherche.c / recherche.c)

### Objectif pédagogique
Implémentation des algorithmes classiques enseignés en cours d'algorithmique avec analyse 
de complexité et cas d'usage pratiques.

---

## Algorithmes de Tri

### 1. Tri par Sélection

#### `void triSelectionVehicules(Vehicule vehicules[], int taille)`

**Principe:**
- Trouve le minimum dans la partie non triée
- L'échange avec le premier élément non trié
- Répète jusqu'à ce que tout soit trié

**Algorithme:**
```
Pour i de 0 à taille-1:
    min_idx = i
    Pour j de i+1 à taille-1:
        Si vehicules[j].plaque < vehicules[min_idx].plaque:
            min_idx = j
    Echanger vehicules[i] et vehicules[min_idx]
```

**Complexité:**
- Temps: O(n²) dans tous les cas
- Espace: O(1) - tri en place
- Comparaisons: n(n-1)/2
- Échanges: au plus n

**Avantages:**
- Simple à implémenter
- Nombre d'échanges minimal

**Inconvénients:**
- Inefficace sur grands tableaux
- Pas de meilleur cas

**Cas d'usage:** Tri des véhicules par plaque d'immatriculation (ordre alphabétique).

---

### 2. Tri par Insertion

#### `void triInsertionVehicules(Vehicule vehicules[], int taille)`

**Principe:**
- Construit progressivement une partie triée
- Insère chaque élément à sa place dans la partie triée
- Comme trier des cartes à jouer

**Algorithme:**
```
Pour i de 1 à taille-1:
    cle = vehicules[i]
    j = i - 1
    Tant que j >= 0 ET vehicules[j].entree > cle.entree:
        vehicules[j+1] = vehicules[j]
        j = j - 1
    vehicules[j+1] = cle
```

**Complexité:**
- Temps:
  - Meilleur cas: O(n) - tableau déjà trié
  - Pire cas: O(n²) - tableau trié en ordre inverse
  - Moyen: O(n²)
- Espace: O(1) - tri en place

**Avantages:**
- Efficace sur petits tableaux
- Efficace sur tableaux presque triés
- Stable (préserve l'ordre relatif)
- Adaptatif

**Inconvénients:**
- Inefficace sur grands tableaux désordonnés

**Cas d'usage:** Tri chronologique des véhicules par date d'entrée.

---

### 3. Tri par montant décroissant

#### `void triVehiculesParMontant(Vehicule vehicules[], int taille)`

**Principe:** Tri par sélection modifié pour ordre décroissant.

**Cas d'usage:** Identification des clients ayant payé le plus (statistiques).

---

## Algorithmes de Recherche

### 1. Recherche Séquentielle

#### `int rechercheSequentielle(Vehicule vehicules[], int taille, const char *plaque)`

**Principe:**
- Parcourt le tableau élément par élément
- Compare chaque plaque avec celle recherchée
- S'arrête dès qu'il trouve ou atteint la fin

**Algorithme:**
```
Pour i de 0 à taille-1:
    Si strcmp(vehicules[i].plaque, plaque) == 0:
        Retourner i
Retourner -1 (non trouvé)
```

**Complexité:**
- Temps:
  - Meilleur cas: O(1) - élément en première position
  - Pire cas: O(n) - élément en dernière position ou absent
  - Moyen: O(n/2) = O(n)
- Espace: O(1)

**Avantages:**
- Simple à implémenter
- Fonctionne sur tableau non trié
- Pas de contrainte sur les données

**Inconvénients:**
- Lent sur grands tableaux

**Cas d'usage:** Recherche de véhicule par plaque lors de la sortie.

---

### 2. Recherche Dichotomique

#### `int rechercheDichotomique(Vehicule vehicules[], int taille, const char *plaque)`

**Principe:**
- Divise l'espace de recherche par 2 à chaque itération
- Compare avec l'élément du milieu
- Continue dans la moitié appropriée

**Prérequis:** TABLEAU TRIÉ par ordre alphabétique des plaques.

**Algorithme:**
```
gauche = 0
droite = taille - 1

Tant que gauche <= droite:
    milieu = (gauche + droite) / 2
    comparaison = strcmp(vehicules[milieu].plaque, plaque)
    
    Si comparaison == 0:
        Retourner milieu
    Sinon si comparaison < 0:
        gauche = milieu + 1
    Sinon:
        droite = milieu - 1

Retourner -1 (non trouvé)
```

**Complexité:**
- Temps:
  - Meilleur cas: O(1) - élément au milieu
  - Pire cas: O(log n)
  - Moyen: O(log n)
- Espace: O(1) pour version itérative

**Exemple avec 1000 éléments:**
- Recherche séquentielle: jusqu'à 1000 comparaisons
- Recherche dichotomique: au plus 10 comparaisons (log₂(1000) ≈ 10)

**Avantages:**
- Très rapide sur grands tableaux
- Efficacité logarithmique

**Inconvénients:**
- Nécessite tableau trié (coût du tri : O(n²) ou O(n log n))
- Légèrement plus complexe à implémenter

**Cas d'usage:** Recherche rapide dans l'historique complet des véhicules.

---

### 3. Recherche avec Drapeau (Sentinelle)

#### `int rechercheAvecDrapeau(Vehicule vehicules[], int taille, const char *plaque, int *trouve)`

**Principe:**
- Variante de la recherche séquentielle
- Utilise une variable booléenne (drapeau) pour indiquer le succès
- Évite certaines vérifications dans la boucle

**Algorithme:**
```
*trouve = 0
i = 0

Tant que i < taille ET *trouve == 0:
    Si strcmp(vehicules[i].plaque, plaque) == 0:
        *trouve = 1
    Sinon:
        i = i + 1

Si *trouve == 1:
    Retourner i
Sinon:
    Retourner -1
```

**Avantages:**
- Clarté de la logique avec variable booléenne
- Facilite la compréhension du concept de drapeau

**Cas d'usage:** Pédagogique - illustration du concept de sentinelle.

---

## Fonctions Auxiliaires

### `int comparerPlaques(const char *plaque1, const char *plaque2)`
- Wrapper autour de `strcmp`
- Retourne: négatif si plaque1 < plaque2, 0 si égales, positif sinon
- Facilite la maintenance et le changement de critère de comparaison

### `int comparerDates(Horodatage date1, Horodatage date2)`
- Compare deux horodatages
- Ordre chronologique complet (année, mois, jour, heure, minute)
- Retourne: -1 si date1 < date2, 0 si égales, 1 si date1 > date2

---

## Analyse Comparative

| Algorithme | Meilleur Cas | Pire Cas | Moyen | Stable | En place |
|------------|-------------|----------|-------|--------|----------|
| Tri Sélection | O(n²) | O(n²) | O(n²) | Non | Oui |
| Tri Insertion | O(n) | O(n²) | O(n²) | Oui | Oui |
| Recherche Séquentielle | O(1) | O(n) | O(n) | - | - |
| Recherche Dichotomique | O(1) | O(log n) | O(log n) | - | - |

**Choix recommandés selon le contexte:**
- **Petit tableau (< 50):** Tri insertion + Recherche séquentielle
- **Grand tableau:** Tri une fois + Recherche dichotomique répétée
- **Ajouts fréquents:** Tri insertion (adaptatif)
- **Recherches rares:** Pas de tri, recherche séquentielle directe


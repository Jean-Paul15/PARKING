# Documentation Détaillée des Modules

## Module Parking (parking.h / parking_*.c)

### parking_init.c - Initialisation du système

**Responsabilité:** Configuration initiale du parking et de ses composants.

**Fonctions principales:**

#### `int initialiserParking(Parking *parking, const char *nom, int nombrePlaces)`
- Initialise la structure principale du parking
- Alloue et configure toutes les places
- Initialise les compteurs à zéro
- **Retour:** 1 si succès, 0 en cas d'erreur
- **Validation:** Vérifie que nombrePlaces <= MAX_PLACES

#### `void initialiserPlace(Place *place, int numero, TypeVehicule typeAutorise)`
- Configure une place individuelle
- Définit le numéro et le type de véhicule autorisé
- Met l'état à LIBRE par défaut
- Initialise le pointeur véhicule à NULL

#### `void libererParking(Parking *parking)`
- Libère toutes les ressources allouées
- Nettoie la mémoire dynamique si utilisée
- Réinitialise les compteurs

**But:** Garantir un état cohérent du système au démarrage.

---

### parking_places.c - Gestion des places

**Responsabilité:** Opérations sur les places de stationnement.

**Fonctions principales:**

#### `int rechercherPlaceLibre(Parking *parking, TypeVehicule type)`
- Parcourt le tableau des places
- Cherche une place LIBRE et compatible avec le type
- **Retour:** Numéro de place (0-based) ou -1 si aucune
- **Algorithme:** Recherche séquentielle simple
- **Complexité:** O(n) où n = nombre de places

#### `int modifierEtatPlace(Parking *parking, int numeroPlace, EtatPlace nouvelEtat)`
- Change l'état d'une place (LIBRE, OCCUPEE, RESERVEE, HORS_SERVICE)
- Valide le numéro de place
- Met à jour les compteurs (placesLibres, placesOccupees)
- **Retour:** 1 si succès, 0 si erreur

#### `void afficherEtatPlaces(const Parking *parking)`
- Liste toutes les places avec leur état actuel
- Affiche le type autorisé et le véhicule occupant si présent
- Formatage en tableau pour lisibilité

#### `void afficherCartePaking(const Parking *parking)`
- Représentation visuelle du parking
- Utilise des symboles pour chaque état :
  - `[ ]` : Libre
  - `[X]` : Occupée
  - `[R]` : Réservée
  - `[H]` : Hors service
- Organisée en lignes (par exemple 10 places par ligne)

**But:** Fournir contrôle et visibilité sur les places.

---

### parking_vehicules.c - Gestion des véhicules

**Responsabilité:** Opérations d'entrée/sortie des véhicules.

**Fonctions principales:**

#### `int enregistrerEntree(Parking *parking, const char *plaque, const char *proprietaire, TypeVehicule type)`
- Vérifie qu'un véhicule avec la même plaque n'est pas déjà présent
- Recherche une place libre compatible
- Crée une entrée dans l'historique
- Enregistre l'horodatage d'entrée
- Affecte le véhicule à la place trouvée
- Met à jour les compteurs
- **Retour:** Numéro de place attribuée ou -1

**Algorithme:**
```
1. Validation des entrées
2. Vérification absence du véhicule
3. Recherche place libre
4. Création véhicule dans historique
5. Affectation place ← véhicule
6. Mise à jour compteurs
```

#### `float enregistrerSortie(Parking *parking, const char *plaque)`
- Recherche le véhicule par plaque
- Calcule la durée de stationnement
- Applique le tarif horaire (200 FCFA/heure)
- Limite au tarif journalier max (2000 FCFA)
- Libère la place
- Met à jour les recettes
- **Retour:** Montant calculé ou -1.0 si erreur

**Formule de tarification:**
```c
duree_minutes = calculerDuree(entree, sortie)
heures = (duree_minutes + 59) / 60  // Arrondi supérieur
montant = heures * TARIF_HORAIRE
if (montant > TARIF_JOURNALIER_MAX)
    montant = TARIF_JOURNALIER_MAX
```

#### `Vehicule* rechercherVehicule(Parking *parking, const char *plaque)`
- Parcourt l'historique ou les places occupées
- Compare les plaques d'immatriculation
- **Retour:** Pointeur vers le véhicule ou NULL

**But:** Gérer le cycle de vie complet des véhicules dans le parking.

---

### parking_affichage.c - Génération de documents

**Responsabilité:** Production de tickets et affichages formatés.

**Fonctions principales:**

#### `void afficherTicketEntree(const Parking *parking, const Vehicule *vehicule, int numeroPlace)`
- Génère un ticket formaté avec :
  - Nom du parking
  - Date et heure d'entrée
  - Plaque et propriétaire
  - Numéro de place attribuée
  - Tarifs applicables
- Bordures décoratives pour impression

#### `void afficherTicketSortie(const Parking *parking, const Vehicule *vehicule, float montant)`
- Génère le ticket de sortie avec :
  - Informations d'entrée
  - Date et heure de sortie
  - Durée de stationnement
  - Montant à payer
  - Message de remerciement

**Format type:**
```
================================
    PARKING CENTRAL
================================
Plaque   : AB-123-CD
Entrée   : 23/12/2025 14:30
Sortie   : 23/12/2025 18:45
Durée    : 4h15min
Montant  : 1000 FCFA
================================
```

**But:** Fournir des documents professionnels pour les clients.


# Documentation du Module Interface Utilisateur

## Module Menu (menu.h / menu.c / menu_traitement.c)

### Objectif
Fournir une interface interactive complète permettant à l'utilisateur d'accéder à 
toutes les fonctionnalités du système de manière intuitive.

---

## Partie 1 : Affichage des Menus (menu.c)

### Architecture des Menus

Le système utilise une hiérarchie de menus :
```
Menu Principal
├── 1. Gestion des Véhicules
│   ├── 1. Enregistrer entrée
│   ├── 2. Enregistrer sortie
│   ├── 3. Rechercher véhicule
│   ├── 4. Afficher véhicules présents
│   └── 0. Retour
├── 2. Gestion des Places
│   ├── 1. Afficher état des places
│   ├── 2. Mettre place hors service
│   ├── 3. Remettre place en service
│   ├── 4. Réserver une place
│   └── 0. Retour
├── 3. Statistiques
│   ├── 1. Résumé journalier
│   ├── 2. Rapport complet
│   ├── 3. Historique véhicules
│   ├── 4. Recettes par type
│   └── 0. Retour
├── 4. Carte du parking
├── 5. Sauvegarder données
├── 6. Charger données
└── 0. Quitter
```

---

### `int afficherMenuPrincipal(void)`

**Format:**
```
========================================
    SYSTEME DE GESTION DE PARKING
========================================
         PARKING CENTRAL
========================================

1. Gestion des vehicules
2. Gestion des places
3. Statistiques et rapports
4. Afficher la carte du parking
5. Sauvegarder les donnees
6. Charger les donnees
0. Quitter le programme

========================================
Votre choix :
```

**Implémentation:**
```c
int afficherMenuPrincipal(void) {
    effacerEcran();
    afficherLigne('=', 60);
    afficherCadre("SYSTEME DE GESTION DE PARKING");
    afficherLigne('=', 60);
    
    printf("\n1. Gestion des vehicules\n");
    printf("2. Gestion des places\n");
    printf("3. Statistiques et rapports\n");
    printf("4. Afficher la carte du parking\n");
    printf("5. Sauvegarder les donnees\n");
    printf("6. Charger les donnees\n");
    printf("0. Quitter le programme\n\n");
    
    afficherLigne('=', 60);
    
    return lireEntier(0, 6);
}
```

---

### `int afficherMenuVehicules(void)`

**Format:**
```
========================================
     GESTION DES VEHICULES
========================================

1. Enregistrer une entree
2. Enregistrer une sortie
3. Rechercher un vehicule
4. Afficher vehicules presents
0. Retour au menu principal

========================================
Votre choix :
```

**Retour:** Choix de l'utilisateur (0-4).

---

### `int afficherMenuPlaces(void)`

**Format:**
```
========================================
      GESTION DES PLACES
========================================

1. Afficher l'etat de toutes les places
2. Mettre une place hors service
3. Remettre une place en service
4. Reserver une place
0. Retour au menu principal

========================================
Votre choix :
```

---

### `int afficherMenuStatistiques(void)`

**Format:**
```
========================================
    STATISTIQUES ET RAPPORTS
========================================

1. Resume journalier
2. Rapport complet d'occupation
3. Historique des vehicules
4. Recettes par type de vehicule
0. Retour au menu principal

========================================
Votre choix :
```

---

## Partie 2 : Traitement des Actions (menu_traitement.c)

### Vue d'ensemble

Ce fichier contient les fonctions intermédiaires qui:
1. Collectent les informations nécessaires auprès de l'utilisateur
2. Appellent les fonctions métier appropriées
3. Affichent les résultats
4. Gèrent les erreurs

---

### `void traiterEntreeVehicule(Parking *parking)`

**Responsabilité:** Gérer le processus complet d'entrée d'un véhicule.

**Déroulement:**
```
1. Afficher titre "ENREGISTREMENT D'ENTREE"
2. Saisir plaque d'immatriculation
3. Saisir nom du propriétaire
4. Afficher types de véhicules disponibles
5. Saisir type de véhicule (1-4)
6. Appeler enregistrerEntree(parking, plaque, proprietaire, type)
7. Si succès (place >= 0):
   - Afficher ticket d'entrée
   - Afficher numéro de place
   - Afficher message de confirmation
8. Sinon:
   - Afficher message d'erreur approprié
   - "Parking complet" ou "Aucune place pour ce type"
9. Pause pour lecture
```

**Code type:**
```c
void traiterEntreeVehicule(Parking *parking) {
    char plaque[TAILLE_PLAQUE];
    char proprietaire[MAX_CHAINE];
    int typeChoix;
    TypeVehicule type;
    
    effacerEcran();
    afficherCadre("ENREGISTREMENT D'ENTREE");
    
    printf("\nPlaque d'immatriculation : ");
    lireChaine(plaque, TAILLE_PLAQUE);
    
    printf("Nom du proprietaire : ");
    lireChaine(proprietaire, MAX_CHAINE);
    
    printf("\nType de vehicule:\n");
    printf("  1. Voiture\n");
    printf("  2. Moto\n");
    printf("  3. Camion\n");
    printf("  4. Bus\n");
    typeChoix = lireEntier(1, 4);
    type = (TypeVehicule)typeChoix;
    
    int place = enregistrerEntree(parking, plaque, proprietaire, type);
    
    if (place >= 0) {
        printf("\n*** ENTREE ENREGISTREE AVEC SUCCES ***\n");
        printf("Place attribuee : %d\n", place + 1);
        
        Vehicule *v = rechercherVehicule(parking, plaque);
        if (v != NULL) {
            afficherTicketEntree(parking, v, place);
        }
    } else {
        printf("\nERREUR : Impossible d'enregistrer l'entree.\n");
        printf("Raison possible : Parking complet ou aucune place pour ce type.\n");
    }
    
    pause();
}
```

---

### `void traiterSortieVehicule(Parking *parking)`

**Déroulement:**
```
1. Afficher titre "ENREGISTREMENT DE SORTIE"
2. Saisir plaque d'immatriculation
3. Appeler enregistrerSortie(parking, plaque)
4. Si succès (montant >= 0):
   - Récupérer informations véhicule
   - Afficher ticket de sortie avec montant
   - Afficher durée de stationnement
   - Message de remerciement
5. Sinon:
   - Afficher "Véhicule non trouvé"
6. Pause pour lecture
```

**Calcul durée affichée:**
```c
int duree = calculerDuree(vehicule->entree, vehicule->sortie);
int heures = duree / 60;
int minutes = duree % 60;
printf("Duree : %dh%02dmin\n", heures, minutes);
```

---

### `void traiterRechercheVehicule(Parking *parking)`

**Déroulement:**
```
1. Afficher titre "RECHERCHE DE VEHICULE"
2. Saisir plaque à rechercher
3. Appeler rechercherVehicule(parking, plaque)
4. Si trouvé:
   - Afficher toutes les informations:
     * Plaque
     * Propriétaire
     * Type de véhicule
     * Date et heure d'entrée
     * Numéro de place
     * Durée actuelle de stationnement
     * Montant estimé à ce stade
5. Sinon:
   - Afficher "Véhicule non trouvé dans le parking"
6. Pause
```

**Montant estimé:**
```c
Horodatage maintenant = obtenirHorodatageActuel();
int duree = calculerDuree(vehicule->entree, maintenant);
float estimation = ((duree + 59) / 60) * TARIF_HORAIRE;
if (estimation > TARIF_JOURNALIER_MAX) {
    estimation = TARIF_JOURNALIER_MAX;
}
printf("Montant estime : %.2f FCFA\n", estimation);
```

---

### `void afficherTicketSortie(const Parking *parking, const Vehicule *vehicule, float montant)`

**Format du ticket:**
```
========================================
       TICKET DE SORTIE
    PARKING CENTRAL
========================================

Plaque        : AB-123-CD
Proprietaire  : Martin Dupont
Type          : Voiture

Entree        : 23/12/2025 14:30
Sortie        : 23/12/2025 18:45
----------------------------------------
Duree         : 4h15min
Tarif horaire : 200 FCFA
----------------------------------------
MONTANT A PAYER : 1000 FCFA
========================================

Merci de votre visite !
A bientot au Parking Central

========================================
```

**Implémentation:**
```c
void afficherTicketSortie(const Parking *parking, 
                         const Vehicule *vehicule, 
                         float montant) {
    afficherLigne('=', 60);
    afficherCadre("TICKET DE SORTIE");
    printf("%s\n", parking->nom);
    afficherLigne('=', 60);
    
    printf("\nPlaque        : %s\n", vehicule->plaque);
    printf("Proprietaire  : %s\n", vehicule->proprietaire);
    printf("Type          : %s\n", typeVehiculeEnChaine(vehicule->type));
    printf("\n");
    
    printf("Entree        : ");
    afficherHorodatage(vehicule->entree);
    printf("\n");
    
    printf("Sortie        : ");
    afficherHorodatage(vehicule->sortie);
    printf("\n");
    
    afficherLigne('-', 60);
    
    int duree = calculerDuree(vehicule->entree, vehicule->sortie);
    printf("Duree         : %dh%02dmin\n", duree / 60, duree % 60);
    printf("Tarif horaire : %d FCFA\n", TARIF_HORAIRE);
    
    afficherLigne('-', 60);
    printf("\nMONTANT A PAYER : %.2f FCFA\n\n", montant);
    afficherLigne('=', 60);
    
    printf("\nMerci de votre visite !\n");
    printf("A bientot au %s\n\n", parking->nom);
    afficherLigne('=', 60);
}
```

---

## Partie 3 : Boucle Principale (main.c)

### Structure du main()

```c
int main(void) {
    Parking parking;
    int choix;
    int continuer = 1;
    
    // 1. INITIALISATION
    effacerEcran();
    afficherBanniere();
    
    if (initialiserParking(&parking, "Parking Central", 50) == 0) {
        printf("Erreur fatale : Impossible d'initialiser.\n");
        return 1;
    }
    
    // 2. CHARGEMENT AUTOMATIQUE
    chargerDonnees(&parking, FICHIER_SAUVEGARDE);
    
    // 3. BOUCLE PRINCIPALE
    while (continuer == 1) {
        choix = afficherMenuPrincipal();
        
        switch (choix) {
            case 1:
                executerMenuVehicules(&parking);
                break;
            case 2:
                executerMenuPlaces(&parking);
                break;
            case 3:
                executerMenuStatistiques(&parking);
                break;
            case 4:
                afficherCartePaking(&parking);
                pause();
                break;
            case 5:
                sauvegarderDonnees(&parking, FICHIER_SAUVEGARDE);
                printf("Donnees sauvegardees avec succes.\n");
                pause();
                break;
            case 6:
                chargerDonnees(&parking, FICHIER_SAUVEGARDE);
                pause();
                break;
            case 0:
                // Sauvegarde automatique avant quitter
                printf("\nSauvegarde automatique...\n");
                sauvegarderDonnees(&parking, FICHIER_SAUVEGARDE);
                printf("Merci d'avoir utilise le systeme.\n");
                continuer = 0;
                break;
            default:
                printf("Choix invalide.\n");
                pause();
        }
    }
    
    // 4. NETTOYAGE
    libererParking(&parking);
    return 0;
}
```

---

### `void executerMenuVehicules(Parking *parking)`

**Sous-boucle pour le menu véhicules:**
```c
void executerMenuVehicules(Parking *parking) {
    int choix;
    int continuer = 1;
    
    while (continuer == 1) {
        choix = afficherMenuVehicules();
        
        switch (choix) {
            case 1:
                traiterEntreeVehicule(parking);
                break;
            case 2:
                traiterSortieVehicule(parking);
                break;
            case 3:
                traiterRechercheVehicule(parking);
                break;
            case 4:
                afficherVehiculesPresents(parking);
                pause();
                break;
            case 0:
                continuer = 0;
                break;
            default:
                printf("Choix invalide.\n");
                pause();
        }
    }
}
```

**Même structure pour:** `executerMenuPlaces()` et `executerMenuStatistiques()`.

---

## Partie 4 : Bannière et Messages

### `void afficherBanniere(void)`

**Bannière ASCII art affichée au démarrage:**
```
  ____   _    ____  _  _____ _   _  ____ 
 |  _ \ / \  |  _ \| |/ /_ _| \ | |/ ___|
 | |_) / _ \ | |_) | ' / | ||  \| | |  _ 
 |  __/ ___ \|  _ <| . \ | || |\  | |_| |
 |_| /_/   \_\_| \_\_|\_\___|_| \_|\____|
                                          
    SYSTEME DE GESTION - Version 1.0
         Decembre 2025
```

**But:** Identification visuelle du système au démarrage.

---

## Flux d'Exécution Type

### Scénario complet : Entrée et sortie d'un véhicule

```
1. Démarrage
   └─> main() initialise parking

2. Menu principal
   └─> Utilisateur choisit "1. Gestion véhicules"
   
3. Menu véhicules
   └─> Utilisateur choisit "1. Enregistrer entrée"
   
4. traiterEntreeVehicule()
   ├─> Saisie : AB-123-CD
   ├─> Saisie : Martin Dupont
   ├─> Choix : 1 (Voiture)
   └─> enregistrerEntree() retourne place 15
   
5. Affichage ticket entrée
   └─> Pause

6. Retour menu véhicules
   └─> Utilisateur choisit "2. Enregistrer sortie"
   
7. traiterSortieVehicule()
   ├─> Saisie : AB-123-CD
   └─> enregistrerSortie() retourne 1000.00
   
8. Affichage ticket sortie
   └─> Montant : 1000 FCFA
   
9. Retour menu véhicules
   └─> Utilisateur choisit "0. Retour"
   
10. Retour menu principal
    └─> Utilisateur choisit "0. Quitter"
    
11. Sauvegarde automatique
    └─> Programme termine
```

---

## Robustesse de l'Interface

### Validation des entrées
- Tous les choix de menu utilisent `lireEntier()` avec limites
- Toutes les chaînes utilisent `lireChaine()` avec taille max
- Boucles jusqu'à obtenir entrée valide

### Gestion des erreurs
- Messages clairs en cas d'échec
- Aucune interruption brutale du programme
- Retour au menu après chaque action

### Feedback utilisateur
- Confirmation après chaque action réussie
- Messages d'erreur explicites
- Pause après chaque affichage d'informations


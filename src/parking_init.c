/**
 * @file parking_init.c
 * @brief Implementation des fonctions d'initialisation du parking
 * @date Decembre 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parking.h"
#include "../include/utilitaires.h"
#include "../include/prototypes.h"

/* ============================================================================
 * INITIALISATION ET CONFIGURATION
 * ============================================================================ */

int initialiserParking(Parking *parking, const char *nom, int nombrePlaces)
{
    int i;
    TypeVehicule typePlace;
    
    /* Validation des parametres d'entree */
    if (parking == NULL || nom == NULL) {
        return 0;
    }
    
    if (nombrePlaces <= 0 || nombrePlaces > MAX_PLACES) {
        printf("Erreur : Nombre de places invalide (1-%d).\n", MAX_PLACES);
        return 0;
    }
    
    /* Copie securisee du nom */
    strncpy(parking->nom, nom, MAX_CHAINE - 1);
    parking->nom[MAX_CHAINE - 1] = '\0';
    
    /* Initialisation des compteurs */
    parking->nombrePlaces = nombrePlaces;
    parking->placesLibres = nombrePlaces;
    parking->placesOccupees = 0;
    parking->nombreVehicules = 0;
    parking->recetteJournaliere = 0.0f;
    parking->recetteTotale = 0.0f;
    
    /* Initialisation des places avec repartition par type */
    for (i = 0; i < nombrePlaces; i++) {
        /* Repartition : 60% voitures, 20% motos, 10% camions, 10% bus */
        if (i < nombrePlaces * 0.6) {
            typePlace = VOITURE;
        } else if (i < nombrePlaces * 0.8) {
            typePlace = MOTO;
        } else if (i < nombrePlaces * 0.9) {
            typePlace = CAMION;
        } else {
            typePlace = BUS;
        }
        
        initialiserPlace(&parking->places[i], i + 1, typePlace);
    }
    
    /* Initialisation de l'historique */
    for (i = 0; i < MAX_VEHICULES; i++) {
        parking->historique[i].estPresent = 0;
        parking->historique[i].plaque[0] = '\0';
    }
    
    return 1;
}

void initialiserPlace(Place *place, int numero, TypeVehicule typeAutorise)
{
    if (place == NULL) {
        return;
    }
    
    place->numero = numero;
    place->etat = LIBRE;
    place->typeAutorise = typeAutorise;
    place->vehiculeActuel = NULL;
}

void libererParking(Parking *parking)
{
    int i;
    
    if (parking == NULL) {
        return;
    }
    
    /* Liberation des pointeurs de vehicules dans les places */
    for (i = 0; i < parking->nombrePlaces; i++) {
        if (parking->places[i].vehiculeActuel != NULL) {
            parking->places[i].vehiculeActuel = NULL;
        }
    }
    
    /* Reinitialisation des compteurs */
    parking->placesLibres = 0;
    parking->placesOccupees = 0;
    parking->nombreVehicules = 0;
}

/* ============================================================================
 * AFFICHAGE DES PLACES
 * ============================================================================ */

void afficherEtatPlaces(const Parking *parking)
{
    int i;
    const Place *place;
    
    if (parking == NULL) {
        return;
    }
    
    afficherLigne('=', 70);
    printf("   ETAT DES PLACES - %s\n", parking->nom);
    afficherLigne('=', 70);
    
    printf("%-8s %-12s %-15s %-20s\n", 
           "Place", "Etat", "Type autorise", "Vehicule");
    afficherLigne('-', 70);
    
    for (i = 0; i < parking->nombrePlaces; i++) {
        place = &parking->places[i];
        
        printf("%-8d %-12s %-15s ",
               place->numero,
               etatPlaceEnChaine(place->etat),
               typeVehiculeEnChaine(place->typeAutorise));
        
        if (place->vehiculeActuel != NULL) {
            printf("%-20s", place->vehiculeActuel->plaque);
        } else {
            printf("%-20s", "-");
        }
        printf("\n");
    }
    
    afficherLigne('=', 70);
    printf("Total : %d places | Libres : %d | Occupees : %d\n",
           parking->nombrePlaces, parking->placesLibres, parking->placesOccupees);
}

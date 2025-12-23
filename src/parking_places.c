/**
 * @file parking_places.c
 * @brief Implementation des fonctions de gestion des places
 * @date Decembre 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parking.h"
#include "../include/utilitaires.h"
#include "../include/prototypes.h"

/* ============================================================================
 * GESTION DES PLACES
 * ============================================================================ */

int rechercherPlaceLibre(Parking *parking, TypeVehicule type)
{
    int i;
    int placeCompatible;
    
    if (parking == NULL) {
        return -1;
    }
    
    /* Premiere passe : rechercher une place du type exact */
    for (i = 0; i < parking->nombrePlaces; i++) {
        if (parking->places[i].etat == LIBRE && 
            parking->places[i].typeAutorise == type) {
            return parking->places[i].numero;
        }
    }
    
    /* Deuxieme passe : rechercher une place compatible */
    /* Une moto peut aller sur une place voiture, etc. */
    placeCompatible = -1;
    
    for (i = 0; i < parking->nombrePlaces; i++) {
        if (parking->places[i].etat == LIBRE) {
            /* Verifier la compatibilite */
            if (type == MOTO) {
                /* Une moto peut aller partout sauf place bus */
                if (parking->places[i].typeAutorise != BUS) {
                    placeCompatible = parking->places[i].numero;
                    break;
                }
            }
        }
    }
    
    return placeCompatible;
}

int modifierEtatPlace(Parking *parking, int numeroPlace, EtatPlace nouvelEtat)
{
    int indice;
    EtatPlace ancienEtat;
    
    if (parking == NULL) {
        return 0;
    }
    
    /* Validation du numero de place */
    if (numeroPlace < 1 || numeroPlace > parking->nombrePlaces) {
        printf("Erreur : Numero de place invalide.\n");
        return 0;
    }
    
    indice = numeroPlace - 1;
    ancienEtat = parking->places[indice].etat;
    
    /* Mise a jour des compteurs */
    if (ancienEtat == LIBRE && nouvelEtat == OCCUPEE) {
        parking->placesLibres--;
        parking->placesOccupees++;
    } else if (ancienEtat == OCCUPEE && nouvelEtat == LIBRE) {
        parking->placesLibres++;
        parking->placesOccupees--;
    }
    
    parking->places[indice].etat = nouvelEtat;
    
    return 1;
}

void afficherCartePaking(const Parking *parking)
{
    int i;
    int j;
    int placesParLigne;
    int numeroPlace;
    char symbole;
    
    if (parking == NULL) {
        return;
    }
    
    placesParLigne = 10;
    
    printf("\n");
    afficherLigne('=', 50);
    printf("      CARTE DU PARKING : %s\n", parking->nom);
    afficherLigne('=', 50);
    
    printf("\nLegende : [L] Libre  [O] Occupee  [R] Reservee  [X] Hors service\n\n");
    
    /* Affichage en grille */
    for (i = 0; i < parking->nombrePlaces; i += placesParLigne) {
        /* Numeros des places */
        printf("    ");
        for (j = 0; j < placesParLigne && (i + j) < parking->nombrePlaces; j++) {
            numeroPlace = i + j + 1;
            printf("%3d ", numeroPlace);
        }
        printf("\n");
        
        /* Etat des places */
        printf("    ");
        for (j = 0; j < placesParLigne && (i + j) < parking->nombrePlaces; j++) {
            switch (parking->places[i + j].etat) {
                case LIBRE:
                    symbole = 'L';
                    break;
                case OCCUPEE:
                    symbole = 'O';
                    break;
                case RESERVEE:
                    symbole = 'R';
                    break;
                case HORS_SERVICE:
                    symbole = 'X';
                    break;
                default:
                    symbole = '?';
            }
            printf("[%c] ", symbole);
        }
        printf("\n\n");
    }
    
    afficherLigne('-', 50);
    printf("Places libres : %d/%d (%.1f%%)\n",
           parking->placesLibres,
           parking->nombrePlaces,
           (float)parking->placesLibres / parking->nombrePlaces * 100);
}

/**
 * @brief Obtient une place par son numero
 * @param parking Pointeur vers le parking
 * @param numero Numero de la place
 * @return Pointeur vers la place, NULL si non trouvee
 */
Place* obtenirPlaceParNumero(Parking *parking, int numero)
{
    if (parking == NULL) {
        return NULL;
    }
    
    if (numero < 1 || numero > parking->nombrePlaces) {
        return NULL;
    }
    
    return &parking->places[numero - 1];
}

/**
 * @brief Compte les places libres par type de vehicule
 * @param parking Pointeur vers le parking
 * @param type Type de vehicule
 * @return Nombre de places libres pour ce type
 */
int compterPlacesLibresParType(const Parking *parking, TypeVehicule type)
{
    int i;
    int compteur;
    
    if (parking == NULL) {
        return 0;
    }
    
    compteur = 0;
    
    for (i = 0; i < parking->nombrePlaces; i++) {
        if (parking->places[i].etat == LIBRE &&
            parking->places[i].typeAutorise == type) {
            compteur++;
        }
    }
    
    return compteur;
}

/**
 * @file statistiques.c
 * @brief Implementation des fonctions de statistiques et rapports
 * @date Decembre 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/statistiques.h"
#include "../include/utilitaires.h"
#include "../include/prototypes.h"

/* ============================================================================
 * CALCUL DES STATISTIQUES
 * ============================================================================ */

void calculerStatistiques(const Parking *parking, Statistiques *stats)
{
    int i;
    
    if (parking == NULL || stats == NULL) {
        return;
    }
    
    /* Initialisation */
    stats->totalEntrees = parking->nombreVehicules;
    stats->totalSorties = 0;
    stats->tauxOccupation = 0.0f;
    stats->recetteMoyenne = 0.0f;
    
    for (i = 0; i < 5; i++) {
        stats->vehiculesParType[i] = 0;
    }
    
    /* Calcul des sorties et comptage par type */
    for (i = 0; i < parking->nombreVehicules; i++) {
        if (parking->historique[i].estPresent == 0) {
            stats->totalSorties++;
        }
        
        /* Comptage par type */
        if (parking->historique[i].type >= VOITURE && 
            parking->historique[i].type <= BUS) {
            stats->vehiculesParType[parking->historique[i].type]++;
        }
    }
    
    /* Calcul du taux d'occupation */
    stats->tauxOccupation = calculerTauxOccupation(parking);
    
    /* Calcul de la recette moyenne */
    stats->recetteMoyenne = calculerRecetteMoyenne(parking);
}

float calculerTauxOccupation(const Parking *parking)
{
    if (parking == NULL || parking->nombrePlaces == 0) {
        return 0.0f;
    }
    
    return ((float)parking->placesOccupees / parking->nombrePlaces) * 100.0f;
}

void compterVehiculesParType(const Parking *parking, int compteurs[])
{
    int i;
    
    if (parking == NULL || compteurs == NULL) {
        return;
    }
    
    /* Initialisation des compteurs */
    for (i = 0; i < 5; i++) {
        compteurs[i] = 0;
    }
    
    /* Comptage des vehicules presents par type */
    for (i = 0; i < parking->nombreVehicules; i++) {
        if (parking->historique[i].estPresent == 1) {
            TypeVehicule type = parking->historique[i].type;
            if (type >= VOITURE && type <= BUS) {
                compteurs[type]++;
            }
        }
    }
}

float calculerRecetteMoyenne(const Parking *parking)
{
    int i;
    int nombreSorties;
    float totalRecettes;
    
    if (parking == NULL) {
        return 0.0f;
    }
    
    nombreSorties = 0;
    totalRecettes = 0.0f;
    
    for (i = 0; i < parking->nombreVehicules; i++) {
        if (parking->historique[i].estPresent == 0 &&
            parking->historique[i].montantPaye > 0) {
            totalRecettes += parking->historique[i].montantPaye;
            nombreSorties++;
        }
    }
    
    if (nombreSorties == 0) {
        return 0.0f;
    }
    
    return totalRecettes / nombreSorties;
}

/* ============================================================================
 * AFFICHAGE DES RAPPORTS
 * ============================================================================ */

void afficherRapportComplet(const Parking *parking)
{
    Statistiques stats;
    int compteurs[5];
    
    if (parking == NULL) {
        return;
    }
    
    calculerStatistiques(parking, &stats);
    compterVehiculesParType(parking, compteurs);
    
    printf("\n");
    afficherLigne('=', 60);
    printf("         RAPPORT COMPLET DU PARKING\n");
    afficherLigne('=', 60);
    
    printf("\n[INFORMATIONS GENERALES]\n");
    afficherLigne('-', 40);
    printf("Nom du parking       : %s\n", parking->nom);
    printf("Capacite totale      : %d places\n", parking->nombrePlaces);
    printf("Places libres        : %d\n", parking->placesLibres);
    printf("Places occupees      : %d\n", parking->placesOccupees);
    printf("Taux d'occupation    : %.1f%%\n", stats.tauxOccupation);
    
    printf("\n[STATISTIQUES VEHICULES]\n");
    afficherLigne('-', 40);
    printf("Total entrees        : %d\n", stats.totalEntrees);
    printf("Total sorties        : %d\n", stats.totalSorties);
    printf("Vehicules presents   : %d\n", 
           stats.totalEntrees - stats.totalSorties);
    
    printf("\n[REPARTITION PAR TYPE]\n");
    afficherLigne('-', 40);
    printf("Voitures             : %d\n", compteurs[VOITURE]);
    printf("Motos                : %d\n", compteurs[MOTO]);
    printf("Camions              : %d\n", compteurs[CAMION]);
    printf("Bus                  : %d\n", compteurs[BUS]);
    
    printf("\n[RECETTES]\n");
    afficherLigne('-', 40);
    printf("Recette journaliere  : %.2f FCFA\n", parking->recetteJournaliere);
    printf("Recette totale       : %.2f FCFA\n", parking->recetteTotale);
    printf("Recette moyenne      : %.2f FCFA\n", stats.recetteMoyenne);
    
    afficherLigne('=', 60);
}

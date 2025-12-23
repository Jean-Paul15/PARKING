/**
 * @file parking_vehicules.c
 * @brief Implementation des fonctions de gestion des vehicules
 * @date Decembre 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parking.h"
#include "../include/utilitaires.h"
#include "../include/prototypes.h"

/* ============================================================================
 * GESTION DES ENTREES ET SORTIES
 * ============================================================================ */

int enregistrerEntree(Parking *parking, const char *plaque, 
                      const char *proprietaire, TypeVehicule type)
{
    int numeroPlace;
    int indicePlace;
    int indiceVehicule;
    Vehicule *vehicule;
    
    /* Validation des parametres */
    if (parking == NULL || plaque == NULL || proprietaire == NULL) {
        return -1;
    }
    
    /* Verifier si le vehicule n'est pas deja present */
    if (rechercherVehicule(parking, plaque) != NULL) {
        printf("Erreur : Ce vehicule est deja dans le parking.\n");
        return -1;
    }
    
    /* Rechercher une place libre */
    numeroPlace = rechercherPlaceLibre(parking, type);
    
    if (numeroPlace == -1) {
        printf("Erreur : Aucune place disponible pour ce type de vehicule.\n");
        return -1;
    }
    
    /* Verifier la capacite de l'historique */
    if (parking->nombreVehicules >= MAX_VEHICULES) {
        printf("Erreur : Historique des vehicules plein.\n");
        return -1;
    }
    
    /* Creer l'enregistrement du vehicule */
    indiceVehicule = parking->nombreVehicules;
    vehicule = &parking->historique[indiceVehicule];
    
    strncpy(vehicule->plaque, plaque, TAILLE_PLAQUE - 1);
    vehicule->plaque[TAILLE_PLAQUE - 1] = '\0';
    
    strncpy(vehicule->proprietaire, proprietaire, MAX_CHAINE - 1);
    vehicule->proprietaire[MAX_CHAINE - 1] = '\0';
    
    vehicule->type = type;
    vehicule->entree = obtenirHorodatageActuel();
    vehicule->estPresent = 1;
    vehicule->montantPaye = 0.0f;
    
    /* Associer le vehicule a la place */
    indicePlace = numeroPlace - 1;
    parking->places[indicePlace].vehiculeActuel = vehicule;
    modifierEtatPlace(parking, numeroPlace, OCCUPEE);
    
    /* Incrementer le compteur */
    parking->nombreVehicules++;
    
    return numeroPlace;
}

float enregistrerSortie(Parking *parking, const char *plaque)
{
    int numeroPlace;
    int indicePlace;
    int dureeMinutes;
    float montant;
    Vehicule *vehicule;
    
    /* Validation des parametres */
    if (parking == NULL || plaque == NULL) {
        return -1.0f;
    }
    
    /* Rechercher le vehicule */
    vehicule = rechercherVehicule(parking, plaque);
    
    if (vehicule == NULL) {
        printf("Erreur : Vehicule non trouve dans le parking.\n");
        return -1.0f;
    }
    
    if (vehicule->estPresent == 0) {
        printf("Erreur : Ce vehicule a deja quitte le parking.\n");
        return -1.0f;
    }
    
    /* Enregistrer l'heure de sortie */
    vehicule->sortie = obtenirHorodatageActuel();
    
    /* Calculer le montant a payer */
    dureeMinutes = calculerDureeMinutes(vehicule->entree, vehicule->sortie);
    montant = calculerMontant(dureeMinutes, vehicule->type);
    
    vehicule->montantPaye = montant;
    vehicule->estPresent = 0;
    
    /* Liberer la place */
    numeroPlace = rechercherPlaceParVehicule(parking, plaque);
    if (numeroPlace != -1) {
        indicePlace = numeroPlace - 1;
        parking->places[indicePlace].vehiculeActuel = NULL;
        modifierEtatPlace(parking, numeroPlace, LIBRE);
    }
    
    /* Mettre a jour les recettes */
    parking->recetteJournaliere += montant;
    parking->recetteTotale += montant;
    
    return montant;
}

/* ============================================================================
 * RECHERCHE DE VEHICULES
 * ============================================================================ */

Vehicule* rechercherVehicule(Parking *parking, const char *plaque)
{
    int i;
    
    if (parking == NULL || plaque == NULL) {
        return NULL;
    }
    
    for (i = 0; i < parking->nombreVehicules; i++) {
        if (parking->historique[i].estPresent == 1 &&
            strcmp(parking->historique[i].plaque, plaque) == 0) {
            return &parking->historique[i];
        }
    }
    
    return NULL;
}

int rechercherPlaceParVehicule(Parking *parking, const char *plaque)
{
    int i;
    
    if (parking == NULL || plaque == NULL) {
        return -1;
    }
    
    for (i = 0; i < parking->nombrePlaces; i++) {
        if (parking->places[i].vehiculeActuel != NULL &&
            strcmp(parking->places[i].vehiculeActuel->plaque, plaque) == 0) {
            return parking->places[i].numero;
        }
    }
    
    return -1;
}

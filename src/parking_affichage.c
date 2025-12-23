/**
 * @file parking_affichage.c
 * @brief Implementation des fonctions d'affichage des vehicules

 * @date Decembre 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parking.h"
#include "../include/utilitaires.h"
#include "../include/prototypes.h"

/* ============================================================================
 * AFFICHAGE DES VEHICULES
 * ============================================================================ */

void afficherVehiculesPresents(const Parking *parking)
{
    int i;
    int compteur;
    char buffer[30];
    const Vehicule *vehicule;
    
    if (parking == NULL) {
        return;
    }
    
    afficherLigne('=', 80);
    printf("   LISTE DES VEHICULES PRESENTS - %s\n", parking->nom);
    afficherLigne('=', 80);
    
    printf("%-15s %-20s %-12s %-20s %-8s\n",
           "Plaque", "Proprietaire", "Type", "Heure entree", "Place");
    afficherLigne('-', 80);
    
    compteur = 0;
    
    for (i = 0; i < parking->nombreVehicules; i++) {
        vehicule = &parking->historique[i];
        
        if (vehicule->estPresent == 1) {
            formaterHorodatage(vehicule->entree, buffer);
            
            printf("%-15s %-20s %-12s %-20s %-8d\n",
                   vehicule->plaque,
                   vehicule->proprietaire,
                   typeVehiculeEnChaine(vehicule->type),
                   buffer,
                   rechercherPlaceParVehicule((Parking*)parking, vehicule->plaque));
            
            compteur++;
        }
    }
    
    afficherLigne('=', 80);
    printf("Total vehicules presents : %d\n", compteur);
}

/**
 * @brief Affiche les details d'un vehicule
 * @param vehicule Pointeur vers le vehicule
 */
void afficherDetailsVehicule(const Vehicule *vehicule)
{
    char bufferEntree[30];
    char bufferSortie[30];
    
    if (vehicule == NULL) {
        printf("Erreur : Vehicule non valide.\n");
        return;
    }
    
    afficherLigne('=', 50);
    printf("   DETAILS DU VEHICULE\n");
    afficherLigne('=', 50);
    
    printf("Plaque         : %s\n", vehicule->plaque);
    printf("Proprietaire   : %s\n", vehicule->proprietaire);
    printf("Type           : %s\n", typeVehiculeEnChaine(vehicule->type));
    
    formaterHorodatage(vehicule->entree, bufferEntree);
    printf("Heure entree   : %s\n", bufferEntree);
    
    if (vehicule->estPresent == 0) {
        formaterHorodatage(vehicule->sortie, bufferSortie);
        printf("Heure sortie   : %s\n", bufferSortie);
        printf("Montant paye   : %.2f FCFA\n", vehicule->montantPaye);
    } else {
        printf("Statut         : Actuellement present\n");
    }
    
    afficherLigne('=', 50);
}

/**
 * @brief Calcule le montant a payer selon la duree et le type
 * @param dureeMinutes Duree de stationnement en minutes
 * @param type Type de vehicule
 * @return Montant a payer
 */
float calculerMontant(int dureeMinutes, TypeVehicule type)
{
    float tarifBase;
    float montant;
    int heures;
    
    /* Tarif de base selon le type de vehicule */
    switch (type) {
        case MOTO:
            tarifBase = TARIF_HORAIRE * 0.5f;
            break;
        case VOITURE:
            tarifBase = TARIF_HORAIRE;
            break;
        case CAMION:
            tarifBase = TARIF_HORAIRE * 1.5f;
            break;
        case BUS:
            tarifBase = TARIF_HORAIRE * 2.0f;
            break;
        default:
            tarifBase = TARIF_HORAIRE;
    }
    
    /* Calcul du nombre d'heures (arrondies a l'heure superieure) */
    heures = (dureeMinutes + 59) / 60;
    
    /* Minimum une heure */
    if (heures < 1) {
        heures = 1;
    }
    
    montant = tarifBase * heures;
    
    /* Plafonner au tarif journalier maximum */
    if (montant > TARIF_JOURNALIER_MAX) {
        montant = TARIF_JOURNALIER_MAX;
    }
    
    return montant;
}

/**
 * @brief Affiche le ticket d'entree
 * @param parking Pointeur vers le parking
 * @param plaque Plaque du vehicule
 * @param numeroPlace Numero de la place attribuee
 */
void afficherTicketEntree(const Parking *parking, const char *plaque, 
                          int numeroPlace)
{
    char buffer[30];
    Horodatage maintenant;
    
    maintenant = obtenirHorodatageActuel();
    formaterHorodatage(maintenant, buffer);
    
    printf("\n");
    afficherLigne('*', 40);
    printf("*      TICKET D'ENTREE              *\n");
    afficherLigne('*', 40);
    printf("  Parking    : %s\n", parking->nom);
    printf("  Plaque     : %s\n", plaque);
    printf("  Place      : %d\n", numeroPlace);
    printf("  Date/Heure : %s\n", buffer);
    afficherLigne('*', 40);
    printf("  Conservez ce ticket pour la sortie\n");
    afficherLigne('*', 40);
    printf("\n");
}

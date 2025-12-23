/**
 * @file menu_traitement.c
 * @brief Implementation des fonctions de traitement des menus
 * @date Decembre 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/menu.h"
#include "../include/parking.h"
#include "../include/utilitaires.h"
#include "../include/prototypes.h"

/* Prototype local */
TypeVehicule saisirTypeVehicule(void);

/* ============================================================================
 * TRAITEMENT ENTREE VEHICULE
 * ============================================================================ */

void traiterEntreeVehicule(Parking *parking)
{
    char plaque[TAILLE_PLAQUE];
    char proprietaire[MAX_CHAINE];
    TypeVehicule type;
    int numeroPlace;
    
    if (parking == NULL) {
        return;
    }
    
    printf("\n--- ENREGISTREMENT D'UNE ENTREE ---\n\n");
    
    /* Saisie de la plaque */
    printf("Plaque d'immatriculation : ");
    lireChaine(plaque, TAILLE_PLAQUE);
    
    /* Verification que la plaque n'est pas vide */
    if (strlen(plaque) == 0) {
        printf("Erreur : La plaque ne peut pas etre vide.\n");
        return;
    }
    
    /* Saisie du proprietaire */
    printf("Nom du proprietaire : ");
    lireChaine(proprietaire, MAX_CHAINE);
    
    if (strlen(proprietaire) == 0) {
        strcpy(proprietaire, "Anonyme");
    }
    
    /* Saisie du type de vehicule */
    type = saisirTypeVehicule();
    
    /* Enregistrement de l'entree */
    numeroPlace = enregistrerEntree(parking, plaque, proprietaire, type);
    
    if (numeroPlace != -1) {
        printf("\nVehicule enregistre avec succes !\n");
        afficherTicketEntree(parking, plaque, numeroPlace);
    }
}

/* ============================================================================
 * TRAITEMENT SORTIE VEHICULE
 * ============================================================================ */

void traiterSortieVehicule(Parking *parking)
{
    char plaque[TAILLE_PLAQUE];
    float montant;
    Vehicule *vehicule;
    Vehicule copieVehicule;
    
    if (parking == NULL) {
        return;
    }
    
    printf("\n--- ENREGISTREMENT D'UNE SORTIE ---\n\n");
    
    /* Saisie de la plaque */
    printf("Plaque d'immatriculation : ");
    lireChaine(plaque, TAILLE_PLAQUE);
    
    if (strlen(plaque) == 0) {
        printf("Erreur : La plaque ne peut pas etre vide.\n");
        return;
    }
    
    /* Recherche du vehicule pour copier ses infos avant la sortie */
    vehicule = rechercherVehicule(parking, plaque);
    
    if (vehicule == NULL) {
        printf("Erreur : Vehicule non trouve dans le parking.\n");
        return;
    }
    
    /* Copie des informations pour le ticket */
    copieVehicule = *vehicule;
    
    /* Enregistrement de la sortie */
    montant = enregistrerSortie(parking, plaque);
    
    if (montant >= 0) {
        afficherTicketSortie(parking, &copieVehicule, montant);
    }
}

/* ============================================================================
 * TRAITEMENT RECHERCHE VEHICULE
 * ============================================================================ */

void traiterRechercheVehicule(Parking *parking)
{
    char plaque[TAILLE_PLAQUE];
    Vehicule *vehicule;
    int numeroPlace;
    char buffer[30];
    
    if (parking == NULL) {
        return;
    }
    
    printf("\n--- RECHERCHE D'UN VEHICULE ---\n\n");
    
    /* Saisie de la plaque */
    printf("Plaque d'immatriculation : ");
    lireChaine(plaque, TAILLE_PLAQUE);
    
    if (strlen(plaque) == 0) {
        printf("Erreur : La plaque ne peut pas etre vide.\n");
        return;
    }
    
    /* Recherche du vehicule */
    vehicule = rechercherVehicule(parking, plaque);
    
    if (vehicule == NULL) {
        printf("\nVehicule non trouve dans le parking.\n");
        return;
    }
    
    /* Affichage des informations */
    printf("\n");
    afficherLigne('=', 45);
    printf("   VEHICULE TROUVE\n");
    afficherLigne('=', 45);
    
    printf("Plaque         : %s\n", vehicule->plaque);
    printf("Proprietaire   : %s\n", vehicule->proprietaire);
    printf("Type           : %s\n", typeVehiculeEnChaine(vehicule->type));
    
    formaterHorodatage(vehicule->entree, buffer);
    printf("Heure entree   : %s\n", buffer);
    
    numeroPlace = rechercherPlaceParVehicule(parking, plaque);
    if (numeroPlace != -1) {
        printf("Place          : %d\n", numeroPlace);
    }
    
    afficherLigne('=', 45);
}

/**
 * @brief Traite la gestion d'une place (hors service / en service)
 * @param parking Pointeur vers le parking
 * @param nouvelEtat Nouvel etat a appliquer
 */
void traiterModificationPlace(Parking *parking, EtatPlace nouvelEtat)
{
    int numeroPlace;
    
    if (parking == NULL) {
        return;
    }
    
    printf("Numero de la place (1-%d) : ", parking->nombrePlaces);
    numeroPlace = lireEntier(1, parking->nombrePlaces);
    
    if (modifierEtatPlace(parking, numeroPlace, nouvelEtat)) {
        printf("Place %d modifiee avec succes.\n", numeroPlace);
    }
}

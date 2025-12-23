/**
 * @file menu.c
 * @brief Implementation des fonctions de menu
 * @date Decembre 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/menu.h"
#include "../include/utilitaires.h"
#include "../include/prototypes.h"

/* ============================================================================
 * AFFICHAGE DES MENUS
 * ============================================================================ */

int afficherMenuPrincipal(void)
{
    int choix;
    
    printf("\n");
    afficherLigne('=', 50);
    printf("     SYSTEME DE GESTION DE PARKING\n");
    afficherLigne('=', 50);
    printf("\n");
    printf("  1. Gestion des vehicules\n");
    printf("  2. Gestion des places\n");
    printf("  3. Statistiques et rapports\n");
    printf("  4. Afficher la carte du parking\n");
    printf("  5. Sauvegarder les donnees\n");
    printf("  6. Charger les donnees\n");
    printf("  0. Quitter\n");
    printf("\n");
    afficherLigne('-', 50);
    
    choix = lireEntier(0, 6);
    
    return choix;
}

int afficherMenuVehicules(void)
{
    int choix;
    
    printf("\n");
    afficherLigne('=', 50);
    printf("     GESTION DES VEHICULES\n");
    afficherLigne('=', 50);
    printf("\n");
    printf("  1. Enregistrer une entree\n");
    printf("  2. Enregistrer une sortie\n");
    printf("  3. Rechercher un vehicule\n");
    printf("  4. Afficher les vehicules presents\n");
    printf("  0. Retour au menu principal\n");
    printf("\n");
    afficherLigne('-', 50);
    
    choix = lireEntier(0, 4);
    
    return choix;
}

int afficherMenuStatistiques(void)
{
    int choix;
    
    printf("\n");
    afficherLigne('=', 50);
    printf("     STATISTIQUES ET RAPPORTS\n");
    afficherLigne('=', 50);
    printf("\n");
    printf("  1. Resume journalier\n");
    printf("  2. Rapport complet\n");
    printf("  3. Historique des vehicules\n");
    printf("  4. Recettes par type de vehicule\n");
    printf("  0. Retour au menu principal\n");
    printf("\n");
    afficherLigne('-', 50);
    
    choix = lireEntier(0, 4);
    
    return choix;
}

int afficherMenuPlaces(void)
{
    int choix;
    
    printf("\n");
    afficherLigne('=', 50);
    printf("     GESTION DES PLACES\n");
    afficherLigne('=', 50);
    printf("\n");
    printf("  1. Afficher l'etat des places\n");
    printf("  2. Mettre une place hors service\n");
    printf("  3. Remettre une place en service\n");
    printf("  4. Reserver une place\n");
    printf("  0. Retour au menu principal\n");
    printf("\n");
    afficherLigne('-', 50);
    
    choix = lireEntier(0, 4);
    
    return choix;
}

/* ============================================================================
 * SAISIE DU TYPE DE VEHICULE
 * ============================================================================ */

/**
 * @brief Affiche le menu de selection du type de vehicule
 * @return Type de vehicule selectionne
 */
TypeVehicule saisirTypeVehicule(void)
{
    int choix;
    
    printf("\nType de vehicule :\n");
    printf("  1. Voiture\n");
    printf("  2. Moto\n");
    printf("  3. Camion\n");
    printf("  4. Bus\n");
    
    choix = lireEntier(1, 4);
    
    return (TypeVehicule)choix;
}

/* ============================================================================
 * AFFICHAGE DU TICKET DE SORTIE
 * ============================================================================ */

void afficherTicketSortie(const Parking *parking, const Vehicule *vehicule,
                          float montant)
{
    char bufferEntree[30];
    char bufferSortie[30];
    Horodatage sortie;
    int duree;
    
    if (parking == NULL || vehicule == NULL) {
        return;
    }
    
    sortie = obtenirHorodatageActuel();
    formaterHorodatage(vehicule->entree, bufferEntree);
    formaterHorodatage(sortie, bufferSortie);
    duree = calculerDureeMinutes(vehicule->entree, sortie);
    
    printf("\n");
    afficherLigne('*', 45);
    printf("*          TICKET DE SORTIE               *\n");
    afficherLigne('*', 45);
    printf("  Parking       : %s\n", parking->nom);
    printf("  Plaque        : %s\n", vehicule->plaque);
    printf("  Proprietaire  : %s\n", vehicule->proprietaire);
    printf("  Type          : %s\n", typeVehiculeEnChaine(vehicule->type));
    afficherLigne('-', 45);
    printf("  Entree        : %s\n", bufferEntree);
    printf("  Sortie        : %s\n", bufferSortie);
    printf("  Duree         : %d h %02d min\n", duree / 60, duree % 60);
    afficherLigne('-', 45);
    printf("  MONTANT A PAYER : %.2f FCFA\n", montant);
    afficherLigne('*', 45);
    printf("       Merci de votre visite !\n");
    afficherLigne('*', 45);
    printf("\n");
}

/**
 * @file main.c
 * @brief Point d'entree du systeme de gestion de parking
 * @date Decembre 2025
 * 
 * Programme principal implementant un systeme complet de gestion
 * de parking en langage C. Ce projet couvre les notions fondamentales
 * d'algorithmique : variables, structures, tableaux, boucles,
 * conditions, fonctions, pointeurs, tri et recherche.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/types.h"
#include "include/utilitaires.h"
#include "include/parking.h"
#include "include/statistiques.h"
#include "include/menu.h"

/* Prototypes des fonctions locales */
void executerMenuVehicules(Parking *parking);
void executerMenuPlaces(Parking *parking);
void executerMenuStatistiques(Parking *parking);
void afficherBanniere(void);

/* Nom du fichier de sauvegarde */
#define FICHIER_SAUVEGARDE "parking_data.dat"

/* ============================================================================
 * FONCTION PRINCIPALE
 * ============================================================================ */

int main(void)
{
    Parking parking;
    int choix;
    int continuer;
    
    /* Affichage de la banniere d'accueil */
    effacerEcran();
    afficherBanniere();
    
    /* Initialisation du parking */
    if (initialiserParking(&parking, "Parking Central", 50) == 0) {
        printf("Erreur fatale : Impossible d'initialiser le parking.\n");
        return 1;
    }
    
    /* Tentative de chargement des donnees existantes */
    chargerDonnees(&parking, FICHIER_SAUVEGARDE);
    
    /* Boucle principale du programme */
    continuer = 1;
    
    while (continuer == 1) {
        choix = afficherMenuPrincipal();
        
        switch (choix) {
            case 1:
                /* Gestion des vehicules */
                executerMenuVehicules(&parking);
                break;
                
            case 2:
                /* Gestion des places */
                executerMenuPlaces(&parking);
                break;
                
            case 3:
                /* Statistiques */
                executerMenuStatistiques(&parking);
                break;
                
            case 4:
                /* Carte du parking */
                afficherCartePaking(&parking);
                break;
                
            case 5:
                /* Sauvegarde */
                sauvegarderDonnees(&parking, FICHIER_SAUVEGARDE);
                break;
                
            case 6:
                /* Chargement */
                chargerDonnees(&parking, FICHIER_SAUVEGARDE);
                break;
                
            case 0:
                /* Quitter */
                printf("\nSauvegarde automatique en cours...\n");
                sauvegarderDonnees(&parking, FICHIER_SAUVEGARDE);
                printf("\nMerci d'avoir utilise le systeme.\n");
                printf("Au revoir !\n\n");
                continuer = 0;
                break;
                
            default:
                printf("Option non valide.\n");
        }
    }
    
    /* Liberation des ressources */
    libererParking(&parking);
    
    return 0;
}

/* ============================================================================
 * EXECUTION DES SOUS-MENUS
 * ============================================================================ */

void executerMenuVehicules(Parking *parking)
{
    int choix;
    int continuer;
    
    continuer = 1;
    
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
                break;
            case 0:
                continuer = 0;
                break;
            default:
                printf("Option non valide.\n");
        }
    }
}

void executerMenuPlaces(Parking *parking)
{
    int choix;
    int continuer;
    int numeroPlace;
    
    continuer = 1;
    
    while (continuer == 1) {
        choix = afficherMenuPlaces();
        
        switch (choix) {
            case 1:
                afficherEtatPlaces(parking);
                break;
            case 2:
                printf("Place a mettre hors service : ");
                numeroPlace = lireEntier(1, parking->nombrePlaces);
                modifierEtatPlace(parking, numeroPlace, HORS_SERVICE);
                printf("Place %d mise hors service.\n", numeroPlace);
                break;
            case 3:
                printf("Place a remettre en service : ");
                numeroPlace = lireEntier(1, parking->nombrePlaces);
                modifierEtatPlace(parking, numeroPlace, LIBRE);
                printf("Place %d remise en service.\n", numeroPlace);
                break;
            case 4:
                printf("Place a reserver : ");
                numeroPlace = lireEntier(1, parking->nombrePlaces);
                modifierEtatPlace(parking, numeroPlace, RESERVEE);
                printf("Place %d reservee.\n", numeroPlace);
                break;
            case 0:
                continuer = 0;
                break;
        }
    }
}

void executerMenuStatistiques(Parking *parking)
{
    int choix;
    int continuer;
    
    continuer = 1;
    
    while (continuer == 1) {
        choix = afficherMenuStatistiques();
        
        switch (choix) {
            case 1:
                afficherResumeJournalier(parking);
                break;
            case 2:
                afficherRapportComplet(parking);
                break;
            case 3:
                afficherHistorique(parking, 20);
                break;
            case 4:
                afficherRecettesParType(parking);
                break;
            case 0:
                continuer = 0;
                break;
        }
    }
}

/* ============================================================================
 * AFFICHAGE DE LA BANNIERE
 * ============================================================================ */

void afficherBanniere(void)
{
    printf("\n");
    afficherLigne('=', 55);
    printf("*                                                     *\n");
    printf("*     SYSTEME DE GESTION DE PARKING                   *\n");
    printf("*                                                     *\n");
    printf("*     Projet Algorithmique - Langage C                *\n");
    printf("*     Encadrant : Dr ANAKPA                           *\n");
    printf("*                                                     *\n");
    afficherLigne('=', 55);
    printf("\n");
}

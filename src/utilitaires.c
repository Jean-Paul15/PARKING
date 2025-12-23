/**
 * @file utilitaires.c
 * @brief Implementation des fonctions utilitaires
 * @date Decembre 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/utilitaires.h"

/* ============================================================================
 * FONCTIONS D'AFFICHAGE
 * ============================================================================ */

void effacerEcran(void)
{
    /* Commande specifique au systeme d'exploitation */
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void afficherLigne(char caractere, int longueur)
{
    int i;
    
    for (i = 0; i < longueur; i++) {
        printf("%c", caractere);
    }
    printf("\n");
}

void afficherCadre(const char *message)
{
    int longueur;
    int i;
    
    longueur = strlen(message) + 4;
    
    /* Ligne superieure */
    printf("+");
    for (i = 0; i < longueur - 2; i++) {
        printf("-");
    }
    printf("+\n");
    
    /* Message */
    printf("| %s |\n", message);
    
    /* Ligne inferieure */
    printf("+");
    for (i = 0; i < longueur - 2; i++) {
        printf("-");
    }
    printf("+\n");
}

void pause(void)
{
    printf("\nAppuyez sur Entree pour continuer...");
    getchar();
    /* Vider le buffer si necessaire */
    while (getchar() != '\n');
}

/* ============================================================================
 * FONCTIONS DE SAISIE SECURISEE
 * ============================================================================ */

int lireEntier(int min, int max)
{
    int valeur;
    int resultat;
    char buffer[100];
    
    do {
        printf("Votre choix [%d-%d] : ", min, max);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            resultat = sscanf(buffer, "%d", &valeur);
            
            if (resultat != 1) {
                printf("Erreur : Veuillez entrer un nombre valide.\n");
                continue;
            }
            
            if (valeur < min || valeur > max) {
                printf("Erreur : La valeur doit etre entre %d et %d.\n", min, max);
                continue;
            }
            
            return valeur;
        }
    } while (1);
}

void lireChaine(char *chaine, int taille)
{
    char *position;
    
    if (fgets(chaine, taille, stdin) != NULL) {
        /* Supprimer le caractere de nouvelle ligne si present */
        position = strchr(chaine, '\n');
        if (position != NULL) {
            *position = '\0';
        }
    }
}

float lireFlottant(float min, float max)
{
    float valeur;
    int resultat;
    char buffer[100];
    
    do {
        printf("Votre choix [%.2f-%.2f] : ", min, max);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            resultat = sscanf(buffer, "%f", &valeur);
            
            if (resultat != 1) {
                printf("Erreur : Veuillez entrer un nombre valide.\n");
                continue;
            }
            
            if (valeur < min || valeur > max) {
                printf("Erreur : Valeur hors limites.\n");
                continue;
            }
            
            return valeur;
        }
    } while (1);
}

/* ============================================================================
 * FONCTIONS DE CONVERSION
 * ============================================================================ */

const char* typeVehiculeEnChaine(TypeVehicule type)
{
    switch (type) {
        case VOITURE:
            return "Voiture";
        case MOTO:
            return "Moto";
        case CAMION:
            return "Camion";
        case BUS:
            return "Bus";
        default:
            return "Inconnu";
    }
}

const char* etatPlaceEnChaine(EtatPlace etat)
{
    switch (etat) {
        case LIBRE:
            return "Libre";
        case OCCUPEE:
            return "Occupee";
        case RESERVEE:
            return "Reservee";
        case HORS_SERVICE:
            return "Hors service";
        default:
            return "Inconnu";
    }
}

/**
 * @file statistiques_suite.c
 * @brief Implementation des fonctions d'historique et sauvegarde
 * @date Decembre 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/statistiques.h"
#include "../include/utilitaires.h"
#include "../include/prototypes.h"

/* ============================================================================
 * AFFICHAGE DE L'HISTORIQUE
 * ============================================================================ */

void afficherResumeJournalier(const Parking *parking)
{
    Horodatage maintenant;
    char buffer[30];
    
    if (parking == NULL) {
        return;
    }
    
    maintenant = obtenirHorodatageActuel();
    formaterHorodatage(maintenant, buffer);
    
    printf("\n");
    afficherLigne('=', 50);
    printf("      RESUME JOURNALIER\n");
    afficherLigne('=', 50);
    
    printf("Date/Heure actuelle  : %s\n", buffer);
    printf("Parking              : %s\n", parking->nom);
    afficherLigne('-', 50);
    printf("Places libres        : %d / %d\n", 
           parking->placesLibres, parking->nombrePlaces);
    printf("Taux d'occupation    : %.1f%%\n", 
           calculerTauxOccupation(parking));
    printf("Recette du jour      : %.2f FCFA\n", 
           parking->recetteJournaliere);
    afficherLigne('=', 50);
}

void afficherHistorique(const Parking *parking, int nombreMax)
{
    int i;
    int compteur;
    char bufferEntree[30];
    char bufferSortie[30];
    const Vehicule *vehicule;
    
    if (parking == NULL) {
        return;
    }
    
    printf("\n");
    afficherLigne('=', 90);
    printf("   HISTORIQUE DES VEHICULES (derniers %d)\n", nombreMax);
    afficherLigne('=', 90);
    
    printf("%-15s %-10s %-18s %-18s %-10s\n",
           "Plaque", "Type", "Entree", "Sortie", "Montant");
    afficherLigne('-', 90);
    
    compteur = 0;
    
    /* Afficher depuis le plus recent */
    for (i = parking->nombreVehicules - 1; i >= 0 && compteur < nombreMax; i--) {
        vehicule = &parking->historique[i];
        
        formaterHorodatage(vehicule->entree, bufferEntree);
        
        if (vehicule->estPresent == 0) {
            formaterHorodatage(vehicule->sortie, bufferSortie);
        } else {
            strcpy(bufferSortie, "En cours");
        }
        
        printf("%-15s %-10s %-18s %-18s ",
               vehicule->plaque,
               typeVehiculeEnChaine(vehicule->type),
               bufferEntree,
               bufferSortie);
        
        if (vehicule->estPresent == 0) {
            printf("%.2f FCFA\n", vehicule->montantPaye);
        } else {
            printf("-\n");
        }
        
        compteur++;
    }
    
    afficherLigne('=', 90);
    printf("Total affiche : %d enregistrements\n", compteur);
}

void afficherRecettesParType(const Parking *parking)
{
    int i;
    float recettesParType[5];
    int compteurParType[5];
    
    if (parking == NULL) {
        return;
    }
    
    /* Initialisation */
    for (i = 0; i < 5; i++) {
        recettesParType[i] = 0.0f;
        compteurParType[i] = 0;
    }
    
    /* Calcul des recettes par type */
    for (i = 0; i < parking->nombreVehicules; i++) {
        if (parking->historique[i].estPresent == 0) {
            TypeVehicule type = parking->historique[i].type;
            if (type >= VOITURE && type <= BUS) {
                recettesParType[type] += parking->historique[i].montantPaye;
                compteurParType[type]++;
            }
        }
    }
    
    printf("\n");
    afficherLigne('=', 50);
    printf("   RECETTES PAR TYPE DE VEHICULE\n");
    afficherLigne('=', 50);
    
    printf("%-15s %-10s %-15s\n", "Type", "Nombre", "Recettes");
    afficherLigne('-', 50);
    
    printf("%-15s %-10d %.2f FCFA\n", "Voiture", 
           compteurParType[VOITURE], recettesParType[VOITURE]);
    printf("%-15s %-10d %.2f FCFA\n", "Moto", 
           compteurParType[MOTO], recettesParType[MOTO]);
    printf("%-15s %-10d %.2f FCFA\n", "Camion", 
           compteurParType[CAMION], recettesParType[CAMION]);
    printf("%-15s %-10d %.2f FCFA\n", "Bus", 
           compteurParType[BUS], recettesParType[BUS]);
    
    afficherLigne('=', 50);
}

/* ============================================================================
 * SAUVEGARDE ET CHARGEMENT
 * ============================================================================ */

int sauvegarderDonnees(const Parking *parking, const char *nomFichier)
{
    FILE *fichier;
    int i;
    
    if (parking == NULL || nomFichier == NULL) {
        return 0;
    }
    
    fichier = fopen(nomFichier, "wb");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nomFichier);
        return 0;
    }
    
    /* Ecriture des donnees du parking */
    fwrite(parking, sizeof(Parking), 1, fichier);
    
    fclose(fichier);
    printf("Donnees sauvegardees avec succes dans %s\n", nomFichier);
    
    return 1;
}

int chargerDonnees(Parking *parking, const char *nomFichier)
{
    FILE *fichier;
    
    if (parking == NULL || nomFichier == NULL) {
        return 0;
    }
    
    fichier = fopen(nomFichier, "rb");
    if (fichier == NULL) {
        printf("Information : Aucune sauvegarde trouvee.\n");
        return 0;
    }
    
    /* Lecture des donnees du parking */
    if (fread(parking, sizeof(Parking), 1, fichier) != 1) {
        fclose(fichier);
        return 0;
    }
    
    fclose(fichier);
    printf("Donnees chargees avec succes depuis %s\n", nomFichier);
    
    return 1;
}

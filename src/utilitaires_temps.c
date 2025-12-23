/**
 * @file utilitaires_temps.c
 * @brief Implementation des fonctions de gestion du temps
 * @date Decembre 2025
 */

#include <stdio.h>
#include <time.h>
#include "../include/utilitaires.h"

/* ============================================================================
 * FONCTIONS DE GESTION DU TEMPS
 * ============================================================================ */

Horodatage obtenirHorodatageActuel(void)
{
    Horodatage h;
    time_t tempsActuel;
    struct tm *infoTemps;
    
    /* Obtenir le temps systeme */
    time(&tempsActuel);
    infoTemps = localtime(&tempsActuel);
    
    /* Remplir la structure Horodatage */
    h.jour = infoTemps->tm_mday;
    h.mois = infoTemps->tm_mon + 1;      /* tm_mon commence a 0 */
    h.annee = infoTemps->tm_year + 1900; /* tm_year depuis 1900 */
    h.heure = infoTemps->tm_hour;
    h.minute = infoTemps->tm_min;
    
    return h;
}

int calculerDureeMinutes(Horodatage debut, Horodatage fin)
{
    struct tm tempsDebut;
    struct tm tempsFin;
    time_t t1;
    time_t t2;
    double difference;
    
    /* Initialiser les structures tm */
    tempsDebut.tm_year = debut.annee - 1900;
    tempsDebut.tm_mon = debut.mois - 1;
    tempsDebut.tm_mday = debut.jour;
    tempsDebut.tm_hour = debut.heure;
    tempsDebut.tm_min = debut.minute;
    tempsDebut.tm_sec = 0;
    tempsDebut.tm_isdst = -1;
    
    tempsFin.tm_year = fin.annee - 1900;
    tempsFin.tm_mon = fin.mois - 1;
    tempsFin.tm_mday = fin.jour;
    tempsFin.tm_hour = fin.heure;
    tempsFin.tm_min = fin.minute;
    tempsFin.tm_sec = 0;
    tempsFin.tm_isdst = -1;
    
    /* Convertir en time_t */
    t1 = mktime(&tempsDebut);
    t2 = mktime(&tempsFin);
    
    /* Calculer la difference en secondes puis convertir en minutes */
    difference = difftime(t2, t1);
    
    return (int)(difference / 60.0);
}

void formaterHorodatage(Horodatage h, char *buffer)
{
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d",
            h.jour, h.mois, h.annee, h.heure, h.minute);
}

/**
 * @brief Verifie si un horodatage est valide
 * @param h Horodatage a verifier
 * @return 1 si valide, 0 sinon
 */
int horodatageValide(Horodatage h)
{
    /* Verification des bornes */
    if (h.jour < 1 || h.jour > 31) {
        return 0;
    }
    if (h.mois < 1 || h.mois > 12) {
        return 0;
    }
    if (h.annee < 2000 || h.annee > 2100) {
        return 0;
    }
    if (h.heure < 0 || h.heure > 23) {
        return 0;
    }
    if (h.minute < 0 || h.minute > 59) {
        return 0;
    }
    
    return 1;
}

/**
 * @brief Cree un horodatage a partir de valeurs
 * @param jour Jour du mois
 * @param mois Mois de l'annee
 * @param annee Annee
 * @param heure Heure
 * @param minute Minute
 * @return Structure Horodatage initialisee
 */
Horodatage creerHorodatage(int jour, int mois, int annee, int heure, int minute)
{
    Horodatage h;
    
    h.jour = jour;
    h.mois = mois;
    h.annee = annee;
    h.heure = heure;
    h.minute = minute;
    
    return h;
}

/**
 * @brief Affiche un horodatage sur la sortie standard
 * @param h Horodatage a afficher
 */
void afficherHorodatage(Horodatage h)
{
    printf("%02d/%02d/%04d a %02d:%02d",
           h.jour, h.mois, h.annee, h.heure, h.minute);
}

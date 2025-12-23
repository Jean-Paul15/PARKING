/**
 * @file recherche.c
 * @brief Implementation des algorithmes de recherche
 * @date Decembre 2025
 * 
 * Ce fichier contient les implementations des algorithmes de recherche
 * sequentielle, dichotomique et avec drapeau.
 */

#include <stdio.h>
#include <string.h>
#include "../include/tri_recherche.h"
#include "../include/prototypes.h"

/* ============================================================================
 * ALGORITHMES DE RECHERCHE
 * ============================================================================ */

/**
 * @brief Recherche sequentielle d'un vehicule par plaque
 * 
 * Algorithme :
 * 1. Parcourir le tableau du debut a la fin
 * 2. Comparer chaque element avec la valeur recherchee
 * 3. Retourner l'indice si trouve, -1 sinon
 * 
 * Complexite temporelle : O(n)
 * Complexite spatiale : O(1)
 */
int rechercheSequentielle(Vehicule vehicules[], int taille, const char *plaque)
{
    int i;
    
    /* Validation des parametres */
    if (vehicules == NULL || plaque == NULL || taille <= 0) {
        return -1;
    }
    
    /* Parcours lineaire du tableau */
    for (i = 0; i < taille; i++) {
        if (strcmp(vehicules[i].plaque, plaque) == 0) {
            return i;
        }
    }
    
    /* Element non trouve */
    return -1;
}

/**
 * @brief Recherche dichotomique d'un vehicule par plaque
 * 
 * Prerequis : Le tableau doit etre trie par ordre alphabetique des plaques
 * 
 * Algorithme :
 * 1. Definir les bornes gauche et droite
 * 2. Calculer le milieu
 * 3. Comparer l'element du milieu avec la valeur recherchee
 * 4. Reduire l'intervalle de recherche en consequence
 * 5. Repeter jusqu'a trouver ou epuiser l'intervalle
 * 
 * Complexite temporelle : O(log n)
 * Complexite spatiale : O(1)
 */
int rechercheDichotomique(Vehicule vehicules[], int taille, const char *plaque)
{
    int gauche;
    int droite;
    int milieu;
    int comparaison;
    
    /* Validation des parametres */
    if (vehicules == NULL || plaque == NULL || taille <= 0) {
        return -1;
    }
    
    /* Initialisation des bornes */
    gauche = 0;
    droite = taille - 1;
    
    /* Boucle de recherche */
    while (gauche <= droite) {
        /* Calcul du milieu (evite le debordement) */
        milieu = gauche + (droite - gauche) / 2;
        
        /* Comparaison avec l'element du milieu */
        comparaison = strcmp(plaque, vehicules[milieu].plaque);
        
        if (comparaison == 0) {
            /* Element trouve */
            return milieu;
        } else if (comparaison < 0) {
            /* Rechercher dans la moitie gauche */
            droite = milieu - 1;
        } else {
            /* Rechercher dans la moitie droite */
            gauche = milieu + 1;
        }
    }
    
    /* Element non trouve */
    return -1;
}

/**
 * @brief Recherche avec drapeau (technique de la sentinelle)
 * 
 * Cette technique utilise une variable booleenne (drapeau) pour
 * indiquer si l'element a ete trouve, ce qui simplifie la logique
 * de sortie de boucle.
 * 
 * Complexite temporelle : O(n)
 * Complexite spatiale : O(1)
 */
int rechercheAvecDrapeau(Vehicule vehicules[], int taille, 
                         const char *plaque, int *trouve)
{
    int i;
    
    /* Validation des parametres */
    if (vehicules == NULL || plaque == NULL || trouve == NULL || taille <= 0) {
        if (trouve != NULL) {
            *trouve = 0;
        }
        return -1;
    }
    
    /* Initialiser le drapeau a "non trouve" */
    *trouve = 0;
    i = 0;
    
    /* Parcours avec condition sur le drapeau */
    while (i < taille && *trouve == 0) {
        if (strcmp(vehicules[i].plaque, plaque) == 0) {
            *trouve = 1;  /* Lever le drapeau */
        } else {
            i++;
        }
    }
    
    /* Retourner l'indice si trouve */
    if (*trouve == 1) {
        return i;
    }
    
    return -1;
}

/**
 * @brief Recherche du vehicule avec le plus long stationnement
 * @param vehicules Tableau de vehicules
 * @param taille Nombre d'elements
 * @return Indice du vehicule trouve, -1 si aucun
 */
int rechercherPlusLongStationnement(Vehicule vehicules[], int taille)
{
    int i;
    int indiceMax;
    Horodatage maintenant;
    int dureeMax;
    int dureeCourante;
    
    if (vehicules == NULL || taille <= 0) {
        return -1;
    }
    
    /* Obtenir l'heure actuelle pour les vehicules presents */
    maintenant.jour = 0;  /* Sera initialise si necessaire */
    
    indiceMax = -1;
    dureeMax = 0;
    
    for (i = 0; i < taille; i++) {
        if (vehicules[i].estPresent == 1) {
            /* Pour un vehicule present, calculer depuis l'entree */
            /* Note : cette fonction necessite l'horodatage actuel */
            dureeCourante = vehicules[i].entree.heure * 60 + 
                           vehicules[i].entree.minute;
            
            if (indiceMax == -1 || dureeCourante < dureeMax) {
                dureeMax = dureeCourante;
                indiceMax = i;
            }
        }
    }
    
    return indiceMax;
}

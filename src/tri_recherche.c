/**
 * @file tri_recherche.c
 * @brief Implementation des algorithmes de tri et recherche
 * @date Decembre 2025
 * 
 * Ce fichier contient les implementations des algorithmes de tri
 * par selection et par insertion, ainsi que les algorithmes de
 * recherche sequentielle et dichotomique.
 */

#include <stdio.h>
#include <string.h>
#include "../include/tri_recherche.h"
#include "../include/prototypes.h"

/* ============================================================================
 * FONCTIONS AUXILIAIRES
 * ============================================================================ */

int comparerPlaques(const char *plaque1, const char *plaque2)
{
    return strcmp(plaque1, plaque2);
}

int comparerHorodatages(Horodatage h1, Horodatage h2)
{
    /* Comparaison annee */
    if (h1.annee != h2.annee) {
        return h1.annee - h2.annee;
    }
    
    /* Comparaison mois */
    if (h1.mois != h2.mois) {
        return h1.mois - h2.mois;
    }
    
    /* Comparaison jour */
    if (h1.jour != h2.jour) {
        return h1.jour - h2.jour;
    }
    
    /* Comparaison heure */
    if (h1.heure != h2.heure) {
        return h1.heure - h2.heure;
    }
    
    /* Comparaison minute */
    return h1.minute - h2.minute;
}

void echangerVehicules(Vehicule *v1, Vehicule *v2)
{
    Vehicule temp;
    
    if (v1 == NULL || v2 == NULL) {
        return;
    }
    
    temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

/* ============================================================================
 * ALGORITHMES DE TRI
 * ============================================================================ */

/**
 * @brief Tri par selection des vehicules par plaque d'immatriculation
 * 
 * Algorithme :
 * 1. Parcourir le tableau de l'indice 0 a n-2
 * 2. Pour chaque position i, trouver le minimum dans [i, n-1]
 * 3. Echanger l'element en position i avec le minimum trouve
 * 
 * Complexite temporelle : O(n^2) dans tous les cas
 * Complexite spatiale : O(1) - tri en place
 */
void triSelectionVehicules(Vehicule vehicules[], int taille)
{
    int i;
    int j;
    int indiceMin;
    
    /* Validation des parametres */
    if (vehicules == NULL || taille <= 1) {
        return;
    }
    
    /* Parcours du tableau */
    for (i = 0; i < taille - 1; i++) {
        /* Initialiser l'indice du minimum */
        indiceMin = i;
        
        /* Rechercher le minimum dans la partie non triee */
        for (j = i + 1; j < taille; j++) {
            if (comparerPlaques(vehicules[j].plaque, 
                               vehicules[indiceMin].plaque) < 0) {
                indiceMin = j;
            }
        }
        
        /* Echanger si necessaire */
        if (indiceMin != i) {
            echangerVehicules(&vehicules[i], &vehicules[indiceMin]);
        }
    }
}

/**
 * @brief Tri par insertion des vehicules par date d'entree
 * 
 * Algorithme :
 * 1. Le premier element est considere comme trie
 * 2. Pour chaque element suivant, l'inserer a sa place dans la partie triee
 * 3. Decaler les elements plus grands vers la droite
 * 
 * Complexite temporelle : O(n^2) pire cas, O(n) meilleur cas (deja trie)
 * Complexite spatiale : O(1) - tri en place
 */
void triInsertionVehicules(Vehicule vehicules[], int taille)
{
    int i;
    int j;
    Vehicule vehiculeACaser;
    
    /* Validation des parametres */
    if (vehicules == NULL || taille <= 1) {
        return;
    }
    
    /* Parcours a partir du deuxieme element */
    for (i = 1; i < taille; i++) {
        /* Sauvegarder l'element a inserer */
        vehiculeACaser = vehicules[i];
        j = i - 1;
        
        /* Decaler les elements plus recents vers la droite */
        while (j >= 0 && comparerHorodatages(vehicules[j].entree, 
                                              vehiculeACaser.entree) > 0) {
            vehicules[j + 1] = vehicules[j];
            j--;
        }
        
        /* Inserer l'element a sa place */
        vehicules[j + 1] = vehiculeACaser;
    }
}

void triPlacesParNumero(Place places[], int taille)
{
    int i;
    int j;
    int indiceMin;
    Place temp;
    
    if (places == NULL || taille <= 1) {
        return;
    }
    
    for (i = 0; i < taille - 1; i++) {
        indiceMin = i;
        
        for (j = i + 1; j < taille; j++) {
            if (places[j].numero < places[indiceMin].numero) {
                indiceMin = j;
            }
        }
        
        if (indiceMin != i) {
            temp = places[i];
            places[i] = places[indiceMin];
            places[indiceMin] = temp;
        }
    }
}

void triVehiculesParMontant(Vehicule vehicules[], int taille)
{
    int i;
    int j;
    
    if (vehicules == NULL || taille <= 1) {
        return;
    }
    
    /* Tri par insertion decroissant */
    for (i = 1; i < taille; i++) {
        Vehicule vehiculeACaser = vehicules[i];
        j = i - 1;
        
        while (j >= 0 && vehicules[j].montantPaye < vehiculeACaser.montantPaye) {
            vehicules[j + 1] = vehicules[j];
            j--;
        }
        
        vehicules[j + 1] = vehiculeACaser;
    }
}

/**
 * @file tri_recherche.h
 * @brief Prototypes des algorithmes de tri et recherche
 * @date Decembre 2025
 * 
 * Implementation des algorithmes de tri par selection et insertion,
 * ainsi que des algorithmes de recherche sequentielle et dichotomique.
 */

#ifndef TRI_RECHERCHE_H
#define TRI_RECHERCHE_H

#include "types.h"

/* ============================================================================
 * ALGORITHMES DE TRI
 * ============================================================================ */

/**
 * @brief Tri par selection des vehicules par plaque
 * @param vehicules Tableau de vehicules
 * @param taille Nombre d'elements
 * 
 * Complexite : O(n^2)
 * Principe : Selectionne le minimum et le place en debut
 */
void triSelectionVehicules(Vehicule vehicules[], int taille);

/**
 * @brief Tri par insertion des vehicules par date d'entree
 * @param vehicules Tableau de vehicules
 * @param taille Nombre d'elements
 * 
 * Complexite : O(n^2) pire cas, O(n) meilleur cas
 * Principe : Insere chaque element a sa place dans la partie triee
 */
void triInsertionVehicules(Vehicule vehicules[], int taille);

/**
 * @brief Tri des places par numero
 * @param places Tableau de places
 * @param taille Nombre d'elements
 */
void triPlacesParNumero(Place places[], int taille);

/**
 * @brief Tri des vehicules par montant paye (decroissant)
 * @param vehicules Tableau de vehicules
 * @param taille Nombre d'elements
 */
void triVehiculesParMontant(Vehicule vehicules[], int taille);

/* ============================================================================
 * ALGORITHMES DE RECHERCHE
 * ============================================================================ */

/**
 * @brief Recherche sequentielle d'un vehicule par plaque
 * @param vehicules Tableau de vehicules
 * @param taille Nombre d'elements
 * @param plaque Plaque a rechercher
 * @return Indice du vehicule trouve, -1 sinon
 * 
 * Complexite : O(n)
 */
int rechercheSequentielle(Vehicule vehicules[], int taille, const char *plaque);

/**
 * @brief Recherche dichotomique d'un vehicule par plaque
 * @param vehicules Tableau de vehicules trie par plaque
 * @param taille Nombre d'elements
 * @param plaque Plaque a rechercher
 * @return Indice du vehicule trouve, -1 sinon
 * 
 * Complexite : O(log n)
 * Prerequis : Tableau trie par ordre alphabetique des plaques
 */
int rechercheDichotomique(Vehicule vehicules[], int taille, const char *plaque);

/**
 * @brief Recherche avec drapeau (sentinelle)
 * @param vehicules Tableau de vehicules
 * @param taille Nombre d'elements
 * @param plaque Plaque a rechercher
 * @param trouve Pointeur vers le drapeau de resultat
 * @return Indice du vehicule trouve, -1 sinon
 */
int rechercheAvecDrapeau(Vehicule vehicules[], int taille, 
                         const char *plaque, int *trouve);

/* ============================================================================
 * FONCTIONS AUXILIAIRES
 * ============================================================================ */

/**
 * @brief Compare deux plaques d'immatriculation
 * @param plaque1 Premiere plaque
 * @param plaque2 Deuxieme plaque
 * @return Valeur negative, nulle ou positive selon l'ordre
 */
int comparerPlaques(const char *plaque1, const char *plaque2);

/**
 * @brief Compare deux horodatages
 * @param h1 Premier horodatage
 * @param h2 Deuxieme horodatage
 * @return Valeur negative si h1 < h2, positive si h1 > h2, 0 si egaux
 */
int comparerHorodatages(Horodatage h1, Horodatage h2);

/**
 * @brief Echange deux vehicules
 * @param v1 Pointeur vers premier vehicule
 * @param v2 Pointeur vers deuxieme vehicule
 */
void echangerVehicules(Vehicule *v1, Vehicule *v2);

#endif /* TRI_RECHERCHE_H */

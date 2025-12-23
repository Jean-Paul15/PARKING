/**
 * @file parking.h
 * @brief Prototypes des fonctions de gestion du parking
 * @date Decembre 2025
 */

#ifndef PARKING_H
#define PARKING_H

#include "types.h"

/* ============================================================================
 * INITIALISATION ET CONFIGURATION
 * ============================================================================ */

/**
 * @brief Initialise le parking avec les parametres par defaut
 * @param parking Pointeur vers la structure Parking
 * @param nom Nom du parking
 * @param nombrePlaces Nombre total de places
 * @return 1 si succes, 0 sinon
 */
int initialiserParking(Parking *parking, const char *nom, int nombrePlaces);

/**
 * @brief Initialise une place de parking
 * @param place Pointeur vers la place
 * @param numero Numero de la place
 * @param typeAutorise Type de vehicule autorise
 */
void initialiserPlace(Place *place, int numero, TypeVehicule typeAutorise);

/**
 * @brief Libere les ressources du parking
 * @param parking Pointeur vers le parking
 */
void libererParking(Parking *parking);

/* ============================================================================
 * GESTION DES PLACES
 * ============================================================================ */

/**
 * @brief Recherche une place libre pour un type de vehicule
 * @param parking Pointeur vers le parking
 * @param type Type de vehicule
 * @return Numero de la place trouvee, -1 si aucune
 */
int rechercherPlaceLibre(Parking *parking, TypeVehicule type);

/**
 * @brief Modifie l'etat d'une place
 * @param parking Pointeur vers le parking
 * @param numeroPlace Numero de la place
 * @param nouvelEtat Nouvel etat de la place
 * @return 1 si succes, 0 sinon
 */
int modifierEtatPlace(Parking *parking, int numeroPlace, EtatPlace nouvelEtat);

/**
 * @brief Affiche l'etat de toutes les places
 * @param parking Pointeur vers le parking
 */
void afficherEtatPlaces(const Parking *parking);

/**
 * @brief Affiche la carte visuelle du parking
 * @param parking Pointeur vers le parking
 */
void afficherCartePaking(const Parking *parking);

/* ============================================================================
 * GESTION DES VEHICULES
 * ============================================================================ */

/**
 * @brief Enregistre l'entree d'un vehicule
 * @param parking Pointeur vers le parking
 * @param plaque Plaque d'immatriculation
 * @param proprietaire Nom du proprietaire
 * @param type Type de vehicule
 * @return Numero de place attribuee, -1 si echec
 */
int enregistrerEntree(Parking *parking, const char *plaque, 
                      const char *proprietaire, TypeVehicule type);

/**
 * @brief Enregistre la sortie d'un vehicule
 * @param parking Pointeur vers le parking
 * @param plaque Plaque d'immatriculation
 * @return Montant a payer, -1.0 si erreur
 */
float enregistrerSortie(Parking *parking, const char *plaque);

/**
 * @brief Recherche un vehicule par sa plaque
 * @param parking Pointeur vers le parking
 * @param plaque Plaque a rechercher
 * @return Pointeur vers le vehicule trouve, NULL sinon
 */
Vehicule* rechercherVehicule(Parking *parking, const char *plaque);

/**
 * @brief Recherche la place occupee par un vehicule
 * @param parking Pointeur vers le parking
 * @param plaque Plaque du vehicule
 * @return Numero de la place, -1 si non trouve
 */
int rechercherPlaceParVehicule(Parking *parking, const char *plaque);

/**
 * @brief Affiche la liste des vehicules presents
 * @param parking Pointeur vers le parking
 */
void afficherVehiculesPresents(const Parking *parking);

#endif /* PARKING_H */

/**
 * @file menu.h
 * @brief Prototypes des fonctions de menu et interface utilisateur
 * @date Decembre 2025
 */

#ifndef MENU_H
#define MENU_H

#include "types.h"

/* ============================================================================
 * FONCTIONS DE MENU
 * ============================================================================ */

/**
 * @brief Affiche le menu principal et retourne le choix
 * @return Choix de l'utilisateur
 */
int afficherMenuPrincipal(void);

/**
 * @brief Affiche le sous-menu de gestion des vehicules
 * @return Choix de l'utilisateur
 */
int afficherMenuVehicules(void);

/**
 * @brief Affiche le sous-menu des statistiques
 * @return Choix de l'utilisateur
 */
int afficherMenuStatistiques(void);

/**
 * @brief Affiche le sous-menu de gestion des places
 * @return Choix de l'utilisateur
 */
int afficherMenuPlaces(void);

/* ============================================================================
 * FONCTIONS DE TRAITEMENT
 * ============================================================================ */

/**
 * @brief Traite l'entree d'un nouveau vehicule
 * @param parking Pointeur vers le parking
 */
void traiterEntreeVehicule(Parking *parking);

/**
 * @brief Traite la sortie d'un vehicule
 * @param parking Pointeur vers le parking
 */
void traiterSortieVehicule(Parking *parking);

/**
 * @brief Traite la recherche d'un vehicule
 * @param parking Pointeur vers le parking
 */
void traiterRechercheVehicule(Parking *parking);

/**
 * @brief Affiche le ticket de sortie
 * @param parking Pointeur vers le parking
 * @param vehicule Pointeur vers le vehicule
 * @param montant Montant a payer
 */
void afficherTicketSortie(const Parking *parking, const Vehicule *vehicule,
                          float montant);

#endif /* MENU_H */

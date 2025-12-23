/**
 * @file prototypes.h
 * @brief Declaration centralisee de tous les prototypes de fonctions
 * @date Decembre 2025
 * 
 * Ce fichier regroupe les prototypes des fonctions internes
 * utilisees entre les differents modules du projet.
 */

#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "types.h"

/* ============================================================================
 * PROTOTYPES DES FONCTIONS INTERNES
 * ============================================================================ */

/* --- Fonctions de calcul de montant (parking_affichage.c) --- */

/**
 * @brief Calcule le montant a payer selon la duree et le type de vehicule
 * @param dureeMinutes Duree de stationnement en minutes
 * @param type Type de vehicule
 * @return Montant a payer en FCFA
 */
float calculerMontant(int dureeMinutes, TypeVehicule type);

/**
 * @brief Affiche les details d'un vehicule
 * @param vehicule Pointeur vers le vehicule
 */
void afficherDetailsVehicule(const Vehicule *vehicule);

/**
 * @brief Affiche le ticket d'entree
 * @param parking Pointeur vers le parking
 * @param plaque Plaque du vehicule
 * @param numeroPlace Numero de la place attribuee
 */
void afficherTicketEntree(const Parking *parking, const char *plaque, 
                          int numeroPlace);

/* --- Fonctions de gestion des places (parking_places.c) --- */

/**
 * @brief Obtient une place par son numero
 * @param parking Pointeur vers le parking
 * @param numero Numero de la place
 * @return Pointeur vers la place, NULL si non trouvee
 */
Place* obtenirPlaceParNumero(Parking *parking, int numero);

/**
 * @brief Compte les places libres par type de vehicule
 * @param parking Pointeur vers le parking
 * @param type Type de vehicule
 * @return Nombre de places libres pour ce type
 */
int compterPlacesLibresParType(const Parking *parking, TypeVehicule type);

/* --- Fonctions de temps (utilitaires_temps.c) --- */

/**
 * @brief Verifie si un horodatage est valide
 * @param h Horodatage a verifier
 * @return 1 si valide, 0 sinon
 */
int horodatageValide(Horodatage h);

/**
 * @brief Cree un horodatage a partir de valeurs
 * @param jour Jour du mois
 * @param mois Mois de l'annee
 * @param annee Annee
 * @param heure Heure
 * @param minute Minute
 * @return Structure Horodatage initialisee
 */
Horodatage creerHorodatage(int jour, int mois, int annee, int heure, int minute);

/**
 * @brief Affiche un horodatage sur la sortie standard
 * @param h Horodatage a afficher
 */
void afficherHorodatage(Horodatage h);

/* --- Fonctions de recherche avancee (recherche.c) --- */

/**
 * @brief Recherche du vehicule avec le plus long stationnement
 * @param vehicules Tableau de vehicules
 * @param taille Nombre d'elements
 * @return Indice du vehicule trouve, -1 si aucun
 */
int rechercherPlusLongStationnement(Vehicule vehicules[], int taille);

/* --- Fonctions de menu (menu.c) --- */

/**
 * @brief Affiche le menu de selection du type de vehicule
 * @return Type de vehicule selectionne
 */
TypeVehicule saisirTypeVehicule(void);

/* --- Fonctions de traitement (menu_traitement.c) --- */

/**
 * @brief Traite la modification d'etat d'une place
 * @param parking Pointeur vers le parking
 * @param nouvelEtat Nouvel etat a appliquer
 */
void traiterModificationPlace(Parking *parking, EtatPlace nouvelEtat);

#endif /* PROTOTYPES_H */

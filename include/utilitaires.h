/**
 * @file utilitaires.h
 * @brief Prototypes des fonctions utilitaires du systeme

 * @date Decembre 2025
 */

#ifndef UTILITAIRES_H
#define UTILITAIRES_H

#include "types.h"

/* ============================================================================
 * FONCTIONS D'AFFICHAGE
 * ============================================================================ */

/**
 * @brief Efface l'ecran de la console
 */
void effacerEcran(void);

/**
 * @brief Affiche une ligne de separation
 * @param caractere Caractere a utiliser pour la ligne
 * @param longueur Longueur de la ligne
 */
void afficherLigne(char caractere, int longueur);

/**
 * @brief Affiche un message dans un cadre
 * @param message Message a afficher
 */
void afficherCadre(const char *message);

/**
 * @brief Met en pause l'execution et attend une touche
 */
void pause(void);

/* ============================================================================
 * FONCTIONS DE SAISIE SECURISEE
 * ============================================================================ */

/**
 * @brief Lit un entier avec validation
 * @param min Valeur minimale acceptee
 * @param max Valeur maximale acceptee
 * @return Entier valide saisi par l'utilisateur
 */
int lireEntier(int min, int max);

/**
 * @brief Lit une chaine de caracteres securisee
 * @param chaine Pointeur vers le buffer de destination
 * @param taille Taille maximale de la chaine
 */
void lireChaine(char *chaine, int taille);

/**
 * @brief Lit un nombre flottant avec validation
 * @param min Valeur minimale acceptee
 * @param max Valeur maximale acceptee
 * @return Nombre flottant valide
 */
float lireFlottant(float min, float max);

/* ============================================================================
 * FONCTIONS DE CONVERSION
 * ============================================================================ */

/**
 * @brief Convertit un type de vehicule en chaine
 * @param type Type de vehicule
 * @return Chaine representant le type
 */
const char* typeVehiculeEnChaine(TypeVehicule type);

/**
 * @brief Convertit un etat de place en chaine
 * @param etat Etat de la place
 * @return Chaine representant l'etat
 */
const char* etatPlaceEnChaine(EtatPlace etat);

/* ============================================================================
 * FONCTIONS DE GESTION DU TEMPS
 * ============================================================================ */

/**
 * @brief Obtient l'horodatage actuel du systeme
 * @return Structure Horodatage avec la date et heure actuelles
 */
Horodatage obtenirHorodatageActuel(void);

/**
 * @brief Calcule la duree en minutes entre deux horodatages
 * @param debut Horodatage de debut
 * @param fin Horodatage de fin
 * @return Duree en minutes
 */
int calculerDureeMinutes(Horodatage debut, Horodatage fin);

/**
 * @brief Formate un horodatage en chaine lisible
 * @param h Horodatage a formater
 * @param buffer Buffer de destination
 */
void formaterHorodatage(Horodatage h, char *buffer);

#endif /* UTILITAIRES_H */

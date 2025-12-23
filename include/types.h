/**
 * @file types.h
 * @brief Definitions des types et structures du systeme de gestion de parking
 * @date Decembre 2025
 * 
 * Ce fichier contient toutes les definitions de types, constantes et structures
 * utilisees dans le systeme de gestion de parking.
 */

#ifndef TYPES_H
#define TYPES_H

/* ============================================================================
 * CONSTANTES DU SYSTEME
 * ============================================================================ */

/** Nombre maximum de places dans le parking */
#define MAX_PLACES 100

/** Nombre maximum de vehicules dans l'historique */
#define MAX_VEHICULES 500

/** Longueur maximale d'une chaine de caracteres */
#define MAX_CHAINE 50

/** Longueur d'une plaque d'immatriculation */
#define TAILLE_PLAQUE 15

/** Tarif horaire en francs CFA */
#define TARIF_HORAIRE 200

/** Tarif journalier maximum */
#define TARIF_JOURNALIER_MAX 2000

/* ============================================================================
 * TYPES ENUMERES
 * ============================================================================ */

/**
 * @enum TypeVehicule
 * @brief Types de vehicules acceptes dans le parking
 */
typedef enum {
    VOITURE = 1,
    MOTO = 2,
    CAMION = 3,
    BUS = 4
} TypeVehicule;

/**
 * @enum EtatPlace
 * @brief Etats possibles d'une place de parking
 */
typedef enum {
    LIBRE = 0,
    OCCUPEE = 1,
    RESERVEE = 2,
    HORS_SERVICE = 3
} EtatPlace;

/* ============================================================================
 * STRUCTURES DE DONNEES
 * ============================================================================ */

/**
 * @struct Horodatage
 * @brief Structure pour representer une date et heure
 */
typedef struct {
    int jour;
    int mois;
    int annee;
    int heure;
    int minute;
} Horodatage;

/**
 * @struct Vehicule
 * @brief Structure representant un vehicule
 */
typedef struct {
    char plaque[TAILLE_PLAQUE];
    char proprietaire[MAX_CHAINE];
    TypeVehicule type;
    Horodatage entree;
    Horodatage sortie;
    int estPresent;
    float montantPaye;
} Vehicule;

/**
 * @struct Place
 * @brief Structure representant une place de parking
 */
typedef struct {
    int numero;
    EtatPlace etat;
    TypeVehicule typeAutorise;
    Vehicule *vehiculeActuel;
} Place;

/**
 * @struct Parking
 * @brief Structure principale du parking
 */
typedef struct {
    char nom[MAX_CHAINE];
    Place places[MAX_PLACES];
    int nombrePlaces;
    int placesLibres;
    int placesOccupees;
    Vehicule historique[MAX_VEHICULES];
    int nombreVehicules;
    float recetteJournaliere;
    float recetteTotale;
} Parking;

/**
 * @struct Statistiques
 * @brief Structure pour les statistiques du parking
 */
typedef struct {
    int totalEntrees;
    int totalSorties;
    float tauxOccupation;
    float recetteMoyenne;
    int vehiculesParType[5];
} Statistiques;

#endif /* TYPES_H */

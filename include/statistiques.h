/**
 * @file statistiques.h
 * @brief Prototypes des fonctions de statistiques et rapports
 * @date Decembre 2025
 */

#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include "types.h"

/* ============================================================================
 * CALCUL DES STATISTIQUES
 * ============================================================================ */

/**
 * @brief Calcule les statistiques actuelles du parking
 * @param parking Pointeur vers le parking
 * @param stats Pointeur vers la structure de statistiques
 */
void calculerStatistiques(const Parking *parking, Statistiques *stats);

/**
 * @brief Calcule le taux d'occupation actuel
 * @param parking Pointeur vers le parking
 * @return Taux d'occupation en pourcentage
 */
float calculerTauxOccupation(const Parking *parking);

/**
 * @brief Compte les vehicules par type
 * @param parking Pointeur vers le parking
 * @param compteurs Tableau de compteurs par type
 */
void compterVehiculesParType(const Parking *parking, int compteurs[]);

/**
 * @brief Calcule la recette moyenne par vehicule
 * @param parking Pointeur vers le parking
 * @return Recette moyenne
 */
float calculerRecetteMoyenne(const Parking *parking);

/* ============================================================================
 * AFFICHAGE DES RAPPORTS
 * ============================================================================ */

/**
 * @brief Affiche le rapport complet des statistiques
 * @param parking Pointeur vers le parking
 */
void afficherRapportComplet(const Parking *parking);

/**
 * @brief Affiche le resume journalier
 * @param parking Pointeur vers le parking
 */
void afficherResumeJournalier(const Parking *parking);

/**
 * @brief Affiche l'historique des vehicules
 * @param parking Pointeur vers le parking
 * @param nombreMax Nombre maximum d'entrees a afficher
 */
void afficherHistorique(const Parking *parking, int nombreMax);

/**
 * @brief Affiche les recettes par type de vehicule
 * @param parking Pointeur vers le parking
 */
void afficherRecettesParType(const Parking *parking);

/* ============================================================================
 * SAUVEGARDE ET CHARGEMENT
 * ============================================================================ */

/**
 * @brief Sauvegarde les donnees du parking dans un fichier
 * @param parking Pointeur vers le parking
 * @param nomFichier Nom du fichier de sauvegarde
 * @return 1 si succes, 0 sinon
 */
int sauvegarderDonnees(const Parking *parking, const char *nomFichier);

/**
 * @brief Charge les donnees du parking depuis un fichier
 * @param parking Pointeur vers le parking
 * @param nomFichier Nom du fichier a charger
 * @return 1 si succes, 0 sinon
 */
int chargerDonnees(Parking *parking, const char *nomFichier);

#endif /* STATISTIQUES_H */

# Documentation des Modules Utilitaires et Interface

## Module Utilitaires (utilitaires.h / utilitaires.c / utilitaires_temps.c)

### Objectif
Fournir des fonctions réutilisables pour l'affichage, la saisie sécurisée, 
la conversion et la gestion du temps.

---

## Partie 1 : Fonctions d'Affichage (utilitaires.c)

### `void effacerEcran(void)`

**Implémentation multi-plateforme:**
```c
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
```

**But:** Nettoyer l'interface entre les menus.

---

### `void afficherLigne(char caractere, int longueur)`

**Principe:** Affiche une ligne de séparation visuelle.

**Exemple:**
```c
afficherLigne('=', 50);
// Sortie: ==================================================

afficherLigne('-', 30);
// Sortie: ------------------------------
```

**Usage:** Délimiter sections de rapports et menus.

---

### `void afficherCadre(const char *message)`

**Format:**
```
+----------------------------------+
|        MESSAGE AU CENTRE         |
+----------------------------------+
```

**Calcul du centrage:**
```c
longueur_cadre = 50
longueur_message = strlen(message)
espaces_gauche = (longueur_cadre - longueur_message) / 2
espaces_droite = longueur_cadre - longueur_message - espaces_gauche
```

**But:** Titres et messages importants mis en évidence.

---

### `void pause(void)`

**Implémentation:**
```c
printf("\nAppuyez sur ENTREE pour continuer...");
while (getchar() != '\n');  // Vider buffer
getchar();                   // Attendre touche
```

**Nécessité:** Permet à l'utilisateur de lire les informations avant changement d'écran.

---

## Partie 2 : Saisie Sécurisée (utilitaires.c)

### Problématique
Les fonctions standard `scanf` sont dangereuses :
- Dépassement de buffer
- Mauvaise gestion des erreurs
- Buffer non vidé

**Solution:** Fonctions custom avec validation.

---

### `int lireEntier(int min, int max)`

**Principe:** Boucle jusqu'à obtenir une valeur valide.

**Algorithme:**
```c
int valeur
int valide = 0

Tant que valide == 0:
    printf("Entrez un nombre entre %d et %d : ", min, max)
    
    Si scanf("%d", &valeur) != 1:
        printf("Erreur : saisie invalide\n")
        Vider buffer d'entrée
        Continue
    
    Si valeur < min OU valeur > max:
        printf("Erreur : hors limites\n")
        Continue
    
    valide = 1

Retourner valeur
```

**Vidage du buffer:**
```c
int c;
while ((c = getchar()) != '\n' && c != EOF);
```

---

### `void lireChaine(char *chaine, int taille)`

**Sécurité:**
```c
if (fgets(chaine, taille, stdin) != NULL) {
    // Supprimer le '\n' final si présent
    size_t len = strlen(chaine);
    if (len > 0 && chaine[len-1] == '\n') {
        chaine[len-1] = '\0';
    }
} else {
    chaine[0] = '\0';  // Chaîne vide en cas d'erreur
}
```

**Avantages vs `scanf("%s")`:**
- Pas de dépassement de buffer
- Accepte les espaces
- Gestion propre des erreurs

---

### `float lireFlottant(float min, float max)`

**Similaire à lireEntier mais pour nombres décimaux.**

**Usage:** Saisie de montants, pourcentages, etc.

---

## Partie 3 : Fonctions de Conversion (utilitaires.c)

### `const char* typeVehiculeEnChaine(TypeVehicule type)`

**Table de conversion:**
```c
switch (type) {
    case VOITURE: return "Voiture";
    case MOTO:    return "Moto";
    case CAMION:  return "Camion";
    case BUS:     return "Bus";
    default:      return "Inconnu";
}
```

**But:** Affichage lisible dans les rapports.

---

### `const char* etatPlaceEnChaine(EtatPlace etat)`

**Table de conversion:**
```c
switch (etat) {
    case LIBRE:        return "Libre";
    case OCCUPEE:      return "Occupée";
    case RESERVEE:     return "Réservée";
    case HORS_SERVICE: return "Hors service";
    default:           return "Erreur";
}
```

---

## Partie 4 : Gestion du Temps (utilitaires_temps.c)

### `Horodatage obtenirHorodatageActuel(void)`

**Implémentation avec time.h:**
```c
Horodatage h;
time_t maintenant = time(NULL);
struct tm *temps_local = localtime(&maintenant);

h.jour   = temps_local->tm_mday;
h.mois   = temps_local->tm_mon + 1;     // tm_mon : 0-11
h.annee  = temps_local->tm_year + 1900; // Années depuis 1900
h.heure  = temps_local->tm_hour;
h.minute = temps_local->tm_min;

return h;
```

**Usage:** Horodatage d'entrée et sortie des véhicules.

---

### `int calculerDuree(Horodatage debut, Horodatage fin)`

**Retour:** Durée en minutes entre deux horodatages.

**Algorithme simplifié:**
```c
// Conversion en timestamps Unix
time_t t_debut = horodatageVersTimestamp(debut)
time_t t_fin = horodatageVersTimestamp(fin)

// Différence en secondes
double diff_secondes = difftime(t_fin, t_debut)

// Conversion en minutes
int minutes = (int)(diff_secondes / 60.0)

return minutes
```

**Fonction auxiliaire:**
```c
time_t horodatageVersTimestamp(Horodatage h) {
    struct tm temps;
    temps.tm_year = h.annee - 1900;
    temps.tm_mon = h.mois - 1;
    temps.tm_mday = h.jour;
    temps.tm_hour = h.heure;
    temps.tm_min = h.minute;
    temps.tm_sec = 0;
    temps.tm_isdst = -1;  // Détection automatique DST
    
    return mktime(&temps);
}
```

**Gestion des cas limites:**
- Changement de jour
- Changement de mois
- Changement d'année
- Heure d'été/hiver

---

### `void afficherHorodatage(Horodatage h)`

**Format:**
```c
printf("%02d/%02d/%04d %02d:%02d", 
       h.jour, h.mois, h.annee, h.heure, h.minute);
// Sortie: 23/12/2025 14:30
```

**Note:** %02d force affichage sur 2 chiffres avec zéro devant si besoin.

---

### `int comparerHorodatages(Horodatage h1, Horodatage h2)`

**Retour:**
- -1 si h1 < h2 (h1 est avant)
- 0 si h1 == h2 (même instant)
- 1 si h1 > h2 (h1 est après)

**Algorithme:**
```c
Si h1.annee != h2.annee:
    Retourner (h1.annee < h2.annee) ? -1 : 1

Si h1.mois != h2.mois:
    Retourner (h1.mois < h2.mois) ? -1 : 1

Si h1.jour != h2.jour:
    Retourner (h1.jour < h2.jour) ? -1 : 1

Si h1.heure != h2.heure:
    Retourner (h1.heure < h2.heure) ? -1 : 1

Si h1.minute != h2.minute:
    Retourner (h1.minute < h2.minute) ? -1 : 1

Retourner 0  // Égalité complète
```

**Usage:** Tri chronologique des véhicules.

---

## Bonnes Pratiques Appliquées

### 1. Validation systématique
Toutes les entrées utilisateur sont validées avant utilisation.

### 2. Gestion des erreurs
Toutes les fonctions système (scanf, fgets, time) ont leurs retours vérifiés.

### 3. Portabilité
Code conditionnel pour Windows/Linux.

### 4. Réutilisabilité
Fonctions génériques utilisables dans tout projet C.

### 5. Documentation
Chaque fonction a un commentaire Doxygen expliquant son usage.

---

## Exemples d'Usage

### Exemple 1 : Menu avec saisie sécurisée
```c
effacerEcran();
afficherCadre("MENU PRINCIPAL");
printf("1. Option A\n");
printf("2. Option B\n");
printf("0. Quitter\n");
afficherLigne('-', 40);

int choix = lireEntier(0, 2);
```

### Exemple 2 : Affichage de durée
```c
Horodatage entree = obtenirHorodatageActuel();
// ... temps s'écoule ...
Horodatage sortie = obtenirHorodatageActuel();

int duree = calculerDuree(entree, sortie);
int heures = duree / 60;
int minutes = duree % 60;

printf("Durée de stationnement : %dh%02dmin\n", heures, minutes);
```

### Exemple 3 : Formatage de rapport
```c
afficherLigne('=', 50);
afficherCadre("RAPPORT JOURNALIER");
afficherLigne('=', 50);
printf("Date : ");
afficherHorodatage(obtenirHorodatageActuel());
printf("\n");
afficherLigne('-', 50);
// ... contenu rapport ...
afficherLigne('=', 50);
pause();
```


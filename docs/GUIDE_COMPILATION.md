# Guide de Compilation et d'Utilisation

## Compilation du Projet

### Prérequis

**Compilateur:**
- GCC (GNU Compiler Collection) version 4.8 ou supérieure
- Support du standard C99

**Système d'exploitation:**
- Windows 7/8/10/11
- Linux (toutes distributions)
- macOS

**Outils optionnels:**
- Make (pour utiliser le Makefile)
- Git (pour gestion de version)

---

## Méthode 1 : Compilation avec Make (Recommandée)

### Vérification de Make

**Windows:**
```powershell
make --version
```

Si absent, installer MinGW ou utiliser la méthode manuelle.

**Linux:**
```bash
make --version
```

Si absent :
```bash
sudo apt-get install build-essential  # Debian/Ubuntu
sudo yum install make gcc             # RedHat/CentOS
```

---

### Commandes Make Disponibles

#### `make all` ou `make`
Compile l'intégralité du projet.

**Processus:**
```
1. Création des répertoires obj/ et bin/ si absents
2. Compilation de chaque fichier .c en .o
3. Édition de liens pour créer l'exécutable
4. Résultat : bin/parking.exe (Windows) ou bin/parking (Linux)
```

**Sortie attendue:**
```
gcc -Wall -Wextra -std=c99 -pedantic -c main.c -o obj/main.o
gcc -Wall -Wextra -std=c99 -pedantic -c src/utilitaires.c -o obj/utilitaires.o
...
gcc obj/*.o -o bin/parking
Compilation terminee avec succes !
```

---

#### `make clean`
Supprime tous les fichiers compilés.

**Actions:**
```
- Suppression de obj/*.o
- Suppression de bin/parking
- Conservation des sources
```

**Usage:** Avant recompilation complète après modifications importantes.

---

#### `make rebuild`
Nettoie puis recompile entièrement.

**Équivalent à:**
```bash
make clean
make all
```

---

#### `make run`
Compile (si nécessaire) puis exécute le programme.

**Commande équivalente:**
```bash
make all
./bin/parking    # Linux
bin\parking.exe  # Windows
```

---

## Méthode 2 : Compilation Manuelle

### Windows (PowerShell ou CMD)

#### Commande Simplifiée
```cmd
gcc -Wall -Wextra -std=c99 -o parking.exe main.c src\*.c
```

#### Commande Complète avec Options
```cmd
gcc -Wall -Wextra -std=c99 -pedantic ^
    -o parking.exe ^
    main.c ^
    src\utilitaires.c ^
    src\utilitaires_temps.c ^
    src\parking_init.c ^
    src\parking_places.c ^
    src\parking_vehicules.c ^
    src\parking_affichage.c ^
    src\tri_recherche.c ^
    src\recherche.c ^
    src\statistiques.c ^
    src\statistiques_suite.c ^
    src\menu.c ^
    src\menu_traitement.c
```

**Note:** Le caractère `^` permet la continuation sur plusieurs lignes en CMD.

---

### Linux / macOS (Bash)

#### Commande Simplifiée
```bash
gcc -Wall -Wextra -std=c99 -o parking main.c src/*.c
```

#### Commande Complète
```bash
gcc -Wall -Wextra -std=c99 -pedantic \
    -o parking \
    main.c \
    src/utilitaires.c \
    src/utilitaires_temps.c \
    src/parking_init.c \
    src/parking_places.c \
    src/parking_vehicules.c \
    src/parking_affichage.c \
    src/tri_recherche.c \
    src/recherche.c \
    src/statistiques.c \
    src/statistiques_suite.c \
    src/menu.c \
    src/menu_traitement.c
```

**Note:** Le caractère `\` permet la continuation sur plusieurs lignes.

---

## Options du Compilateur Expliquées

### `-Wall`
Active tous les avertissements de base.

**Détecte:**
- Variables non initialisées
- Code inaccessible
- Fonctions sans valeur de retour
- Comparaisons ambiguës

---

### `-Wextra`
Active des avertissements supplémentaires.

**Détecte:**
- Paramètres non utilisés
- Comparaisons entre signés et non-signés
- Champs de structure manquants dans initialisations

---

### `-std=c99`
Impose le standard C99.

**Caractéristiques C99 utilisées:**
- Déclarations de variables dans les boucles for
- Commentaires `//`
- Type `_Bool` (via `stdbool.h`)
- Fonctions inline

---

### `-pedantic`
Mode strict du standard.

**Rejette:**
- Extensions non standard du compilateur
- Code non portable

---

### `-o nom_fichier`
Spécifie le nom de l'exécutable de sortie.

**Par défaut:** `a.out` (Linux) ou `a.exe` (Windows)

---

## Résolution de Problèmes de Compilation

### Erreur : "gcc: command not found"

**Cause:** GCC n'est pas installé ou pas dans le PATH.

**Solution Windows:**
```
1. Télécharger MinGW ou MSYS2
2. Installer avec composant gcc
3. Ajouter C:\MinGW\bin au PATH système
```

**Solution Linux:**
```bash
sudo apt-get install build-essential
```

---

### Erreur : Fichiers d'en-tête non trouvés

**Message:**
```
fatal error: include/types.h: No such file or directory
```

**Cause:** Exécution depuis mauvais répertoire.

**Solution:**
```bash
cd c:\CURSUS INGENIEUR\MISE_A_NIVEAU\ALGO\projet_parking
```

Puis relancer compilation.

---

### Avertissements "unused variable"

**Message:**
```
warning: unused variable 'i' [-Wunused-variable]
```

**Cause:** Variable déclarée mais jamais utilisée.

**Solution:**
- Supprimer la variable si inutile
- Utiliser `(void)variable;` pour indiquer usage intentionnel

---

### Erreur "undefined reference to..."

**Message:**
```
undefined reference to `enregistrerEntree'
```

**Cause:** Fichier source manquant dans la compilation.

**Solution:** Vérifier que tous les fichiers .c sont inclus dans la commande.

---

## Exécution du Programme

### Windows
```cmd
cd bin
parking.exe
```

Ou directement :
```cmd
bin\parking.exe
```

---

### Linux / macOS
```bash
cd bin
./parking
```

Ou directement :
```bash
./bin/parking
```

---

## Utilisation du Système

### Première Utilisation

**Démarrage:**
1. Lancer l'exécutable
2. La bannière s'affiche
3. Le parking est initialisé avec 50 places
4. Tentative de chargement de `parking_data.dat`
5. Si fichier absent : démarrage avec parking vide
6. Menu principal s'affiche

---

### Enregistrer une Entrée

**Navigation:**
```
Menu Principal → 1. Gestion des véhicules
                → 1. Enregistrer une entrée
```

**Saisies demandées:**
1. Plaque d'immatriculation (ex: AB-123-CD)
2. Nom du propriétaire (ex: Martin Dupont)
3. Type de véhicule :
   - 1 pour Voiture
   - 2 pour Moto
   - 3 pour Camion
   - 4 pour Bus

**Résultat:**
- Ticket d'entrée affiché
- Numéro de place attribué
- Horodatage enregistré

---

### Enregistrer une Sortie

**Navigation:**
```
Menu Principal → 1. Gestion des véhicules
                → 2. Enregistrer une sortie
```

**Saisie demandée:**
- Plaque d'immatriculation du véhicule sortant

**Résultat:**
- Calcul automatique de la durée
- Application du tarif horaire (200 FCFA/h)
- Ticket de sortie avec montant
- Place libérée automatiquement

---

### Consulter les Statistiques

**Navigation:**
```
Menu Principal → 3. Statistiques et rapports
```

**Options:**
1. **Résumé journalier** : Vue rapide du jour en cours
2. **Rapport complet** : Toutes les métriques détaillées
3. **Historique** : Liste des véhicules passés
4. **Recettes par type** : Répartition des revenus

---

### Visualiser le Parking

**Navigation:**
```
Menu Principal → 4. Afficher la carte du parking
```

**Affichage:**
```
=== CARTE DU PARKING ===
[ ] [ ] [X] [X] [ ] [R] [ ] [X] [ ] [ ]
[X] [ ] [ ] [X] [X] [ ] [ ] [ ] [X] [ ]
[ ] [X] [ ] [ ] [H] [H] [ ] [X] [ ] [X]
...

Légende:
[ ] : Libre
[X] : Occupée
[R] : Réservée
[H] : Hors service
```

---

### Sauvegarde et Chargement

#### Sauvegarde Automatique
- Exécutée automatiquement à la sortie du programme (choix 0)
- Fichier créé : `parking_data.dat`

#### Sauvegarde Manuelle
**Navigation:**
```
Menu Principal → 5. Sauvegarder les données
```

#### Chargement Manuel
**Navigation:**
```
Menu Principal → 6. Charger les données
```

**Usage:** Restaurer un état précédent après test ou erreur.

---

## Fichiers Générés

### parking_data.dat
**Emplacement:** Racine du projet  
**Type:** Binaire  
**Contenu:**
- État complet du parking
- Toutes les places et véhicules
- Historique complet
- Recettes cumulées

**Taille typique:** 60-65 Ko maximum

**Sauvegarde:** Faire des copies régulières pour éviter perte de données.

---

### Fichiers de Compilation

**obj/*.o** : Fichiers objets intermédiaires  
**bin/parking** : Exécutable final

**Gestion:** Peuvent être supprimés avec `make clean`, recréés avec `make all`.

---

## Conseils d'Utilisation

### Performance
- Le système gère jusqu'à 100 places et 500 véhicules en historique
- Performances optimales : < 50 places, < 200 véhicules
- Recherche dichotomique activée pour historique trié

### Sécurité des Données
- Sauvegarder manuellement avant tests importants
- Faire des copies de `parking_data.dat` périodiquement
- Ne pas éditer le fichier .dat manuellement (binaire)

### Dépannage
- En cas de comportement errant : charger sauvegarde précédente
- Si corruption de données : supprimer .dat et repartir de zéro
- Pour reset complet : supprimer parking_data.dat

### Limitations Connues
- Pas de gestion multi-utilisateurs simultanés
- Pas de sauvegarde incrémentale
- Format de sauvegarde non portable entre OS différents
- Interface console uniquement (pas de GUI)


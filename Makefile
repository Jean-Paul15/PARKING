# Makefile pour le projet de gestion de parking
# Date : Decembre 2025

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
LDFLAGS =

# Repertoires
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Fichiers sources
SOURCES = main.c \
          $(SRC_DIR)/utilitaires.c \
          $(SRC_DIR)/utilitaires_temps.c \
          $(SRC_DIR)/parking_init.c \
          $(SRC_DIR)/parking_places.c \
          $(SRC_DIR)/parking_vehicules.c \
          $(SRC_DIR)/parking_affichage.c \
          $(SRC_DIR)/tri_recherche.c \
          $(SRC_DIR)/recherche.c \
          $(SRC_DIR)/statistiques.c \
          $(SRC_DIR)/statistiques_suite.c \
          $(SRC_DIR)/menu.c \
          $(SRC_DIR)/menu_traitement.c

# Fichiers objets
OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/utilitaires.o \
          $(OBJ_DIR)/utilitaires_temps.o \
          $(OBJ_DIR)/parking_init.o \
          $(OBJ_DIR)/parking_places.o \
          $(OBJ_DIR)/parking_vehicules.o \
          $(OBJ_DIR)/parking_affichage.o \
          $(OBJ_DIR)/tri_recherche.o \
          $(OBJ_DIR)/recherche.o \
          $(OBJ_DIR)/statistiques.o \
          $(OBJ_DIR)/statistiques_suite.o \
          $(OBJ_DIR)/menu.o \
          $(OBJ_DIR)/menu_traitement.o

# Nom de l'executable
TARGET = $(BIN_DIR)/parking

# Regle principale
all: directories $(TARGET)

# Creation des repertoires
directories:
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)

# Edition de liens
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo Compilation terminee avec succes !

# Regles de compilation
$(OBJ_DIR)/main.o: main.c $(INC_DIR)/*.h
	$(CC) $(CFLAGS) -c main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/utilitaires.o: $(SRC_DIR)/utilitaires.c $(INC_DIR)/utilitaires.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/utilitaires.c -o $(OBJ_DIR)/utilitaires.o

$(OBJ_DIR)/utilitaires_temps.o: $(SRC_DIR)/utilitaires_temps.c $(INC_DIR)/utilitaires.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/utilitaires_temps.c -o $(OBJ_DIR)/utilitaires_temps.o

$(OBJ_DIR)/parking_init.o: $(SRC_DIR)/parking_init.c $(INC_DIR)/parking.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/parking_init.c -o $(OBJ_DIR)/parking_init.o

$(OBJ_DIR)/parking_places.o: $(SRC_DIR)/parking_places.c $(INC_DIR)/parking.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/parking_places.c -o $(OBJ_DIR)/parking_places.o

$(OBJ_DIR)/parking_vehicules.o: $(SRC_DIR)/parking_vehicules.c $(INC_DIR)/parking.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/parking_vehicules.c -o $(OBJ_DIR)/parking_vehicules.o

$(OBJ_DIR)/parking_affichage.o: $(SRC_DIR)/parking_affichage.c $(INC_DIR)/parking.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/parking_affichage.c -o $(OBJ_DIR)/parking_affichage.o

$(OBJ_DIR)/tri_recherche.o: $(SRC_DIR)/tri_recherche.c $(INC_DIR)/tri_recherche.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/tri_recherche.c -o $(OBJ_DIR)/tri_recherche.o

$(OBJ_DIR)/recherche.o: $(SRC_DIR)/recherche.c $(INC_DIR)/tri_recherche.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/recherche.c -o $(OBJ_DIR)/recherche.o

$(OBJ_DIR)/statistiques.o: $(SRC_DIR)/statistiques.c $(INC_DIR)/statistiques.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/statistiques.c -o $(OBJ_DIR)/statistiques.o

$(OBJ_DIR)/statistiques_suite.o: $(SRC_DIR)/statistiques_suite.c $(INC_DIR)/statistiques.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/statistiques_suite.c -o $(OBJ_DIR)/statistiques_suite.o

$(OBJ_DIR)/menu.o: $(SRC_DIR)/menu.c $(INC_DIR)/menu.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/menu.c -o $(OBJ_DIR)/menu.o

$(OBJ_DIR)/menu_traitement.o: $(SRC_DIR)/menu_traitement.c $(INC_DIR)/menu.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/menu_traitement.c -o $(OBJ_DIR)/menu_traitement.o

# Nettoyage
clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)
	@echo Nettoyage termine.

# Reconstruction complete
rebuild: clean all

# Execution
run: all
	$(TARGET)

.PHONY: all clean rebuild run directories

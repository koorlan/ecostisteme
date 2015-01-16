#ifndef __GRILLE__H
#define __GRILLE__H 
#include "libgraphique.h"




void draw_grid(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int mode) ;

void init_grid(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

void spawn_island(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

void spawn_list_animal_random(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * listeAnimal );

int isPlaceFree (Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int a , int b);

Liste * free_neighboor_case_list(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Mob * mob);

#endif

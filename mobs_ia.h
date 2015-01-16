#ifndef __MOBS__IA__H
#define __MOBS__IA__H 

#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <time.h>
#include "grille.h"
#include "mob.h"
#include "liste.h"
#include "pont.h"

void  destroy_list (Liste ** l);

void free_list (Liste *l);

Liste * destroy_mob (Mob mob, Liste * list_of_specific_species );

int survie(Mob * mob, Liste * species[NB_SPECIES]);

int reproduction(Mob *mob, Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES]);

int predation(Mob * mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES]);

int deplacement(Mob * mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES]);

void tour(Mob * mob);

void ia_mob(Mob * mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES]);






#endif

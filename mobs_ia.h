#ifndef __MOBS__IA__H
#define __MOBS__IA__H 

#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <time.h>
#include "grille.h"
#include "mob.h"
#include "liste.h"

Liste * destroy_mob (Mob mob, Liste * list_of_specific_species );

int survie(Mob mob, Liste * species[NB_SPECIES]);

int reproduction(Mob mob);

int predation(Mob * mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES]);

int deplacement(Mob mob);

int tour();





#endif

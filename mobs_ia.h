#ifndef __MOBS__IA__H
#define __MOBS__IA__H 

#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <time.h>
#include "grille.h"
#include "mob.h"
#include "liste.h"

void destroy_mob (Mob mob, Liste * liste_plancton, Liste * liste_corail, Liste * liste_bar, Liste * liste_thon);

int survie(Mob mob, Liste * liste_plancton, Liste * liste_corail, Liste * liste_bar, Liste * liste_thon);

int reproduction(Mob mob);

void predation(Mob mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste_plancton, Liste * liste_corail, Liste * liste_bar, Liste * liste_thon);

int deplacement(Mob mob);

int tour();





#endif

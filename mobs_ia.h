#ifndef __MOBS__IA__H
#define __MOBS__IA__H 

#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <time.h>
#include "grille.h"
#include "mob.h"
#include "liste.h"


int survie(Mob mob);

int reproduction(Mob mob);

int predation(Mob mob);

int deplacement(Mob mob);

int tour();





#endif
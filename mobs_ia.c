#include "main.h"



int survie(Mob mob){
	if (mob.satiete == 0 && WORLD_TIME - mob.dernier_repas> mob.duree_survie){
		//destroymob
		//return -1
	} 
 //return 1;
}

int reproduction(Mob mob)

int predation(Mob mob);

int deplacement(Mob mob);

int tour();
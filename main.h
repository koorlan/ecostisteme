#ifndef __MAIN__H
#define __MAIN__H 
#define TAILLE_PLATEAU 30
#define NB_SPECIES 5
#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <time.h>
#include "eco.h"
#include "mob.h"
#include "liste.h"
#include "grille.h"
#include "libgraphique.h"
#include "mobs_ia.h"

int WORLD_TIME;

	/********************
	**Identifiants......  Survie........Taille...Taille_du_bide.....Saut_max..metabolisme...gestation........frequen_reproduction
	**espece vide.......0  10 000	   -1        0                	0         0		0	 	 10 000
	**plancton .........1  10 000       1        0 			0	  0		1	 	 4 	
	**corail............2  1            1        2			1    	  1	  	1	 	 4	
	**bar...............3  3 	    2        2			2	  1		1        	 4
	**thon..............4  5            2        1       		3         2		1        	 4
	**pollution.........5  10 000       0        1			1         0		0	 	 10 000
	**pyranha...........6  3            2        3			3	  2		2 	 	 4
	**requin............7  4            4        3			2         2		2 	 	 4
	**baleine...........9  3            5        2			2   	  2		2 	 	 4
	**pecheur...........10 10 000       3        0			1         0		0	 	 10 000
	**pont..............11 10 000       2        0			0         0		0	 	 10 000
	*********************/

static const int duree_survie[]={10000, 10000, 1, 3, 5, 10000, 3, 4, 4, 3, 10000, 10000};
static const int taille[]={-1, 1, 1, 2, 2, 0, 2, 4, 4, 5, 3, 2};
static const int taille_du_bide[]={0, 0, 2, 2, 1, 1, 3, 3, 4, 2, 0, 0};
static const int saut_max[]={ 0, 0, 1, 2, 3, 0, 3, 2, 2, 2, 1, 0};
static const int metabolisme[]={0, 0, 1, 1, 2, 0, 2, 2, 2, 0, 0};
static const int gestation[]={0, 1, 1, 1, 1, 0, 2, 2, 2, 0, 0};
static const int frequence_reproduction[]={10000, 4, 4, 4, 4, 10000, 4, 4, 4, 10000, 10000};
static const couleurs mobs_draw[20]={color_WHITE, color_LIGHTGREEN, color_LIGHTRED, color_CYAN, color_BLUE, color_LIGHTMAGENTA, color_BLACK, color_YELLOW};


int rand_a_b(int a, int b);

#endif

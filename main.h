#ifndef __MAIN__H
#define __MAIN__H 

#define TAILLE_PLATEAU 70
#define NB_SPECIES 9

#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <time.h>
#include <math.h>

/* TYPE DU PECHEUR */
typedef struct fisher {	int id_proie; 		//identifiant du dernier poisson peché 
			char nom_joueur[9] ; 	//Au maximum 9 caractères/nom 
			int x; 			//coordonnées du joueur
			int y; 
			int reserves; 		//reserves disponibles
			int nv_reserves;	//reserves pechees au tour precedent (bonus poisson)
			int bridge;		//pont contruit au dernier tour
			int allo; 		//vaut 1 si le pecheur est tombé à l'eau au tour précédent 
			int xp; 		//experience du pecheur
			int id; 		//identifiant du pecheur pour le mode 2 joueurs
			int ecolo; 		//total des poissons rejetés à l'eau (bonus écolo)
			}fisher;



#include "eco.h"
#include "mob.h"
#include "liste.h"
#include "grille.h"
#include "libgraphique.h"
#include "mobs_ia.h"
#include "pecheur.h"
#include "canne.h"
#include "filet.h"
#include "pont.h"
#include "bonus.h"
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


int WORLD_TIME;


	/********************
	**Identifiants......  Survie........Taille...Taille_du_bide.........Saut_max..metabolisme...gestation........freq_reproduction
	**0espece vide.......0  10 000	   	-1        0                	0         0		0	 	 10 000
	**1plancton .........1  10 000      	 2        0 			0	  0		1	 	 0 	
	**2corail............2  1            	 1        2			1    	  1	  	2	 	 3	
	**3bar...............3  10 	    	 2        4			2	  1		3        	 3
	**4thon..............4  2           	 2        3       		2         1		2        	 2
	**5pollution.........5  10 000      	 10       10 000		0         0		0	 	 10 000
	**6pyranha...........6  8           	 2        3			3	  1		1 	 	 1
	**7requin............7  100            	 4        6			2         1		1 	 	 10
	**8orque.............8	50		 4	  4			2	  2		2		 2
	**9baleine...........9  100         	 5        2			20   	  2		10 	 	 25
	**10pecheur...........10 10 000       	 3        0			1         0		0	 	 10 000
	**11pont..............11 10 000          2        0			0         0		0	 	 10 000	
	**12ile		
	*********************/


static const int duree_survie[]={10000, 10000, 1, 10, 2, 10000, 8, 100, 50, 100, 10000, 10000, 10000};
static const int taille[]={-1, 2, 1, 2, 2, 10, 2, 4, 4, 5, 3, 2, 2};
static const int taille_du_bide[]={0, 0, 2, 4, 3, 10000, 3, 6, 4, 2, 0, 0, 0};
static const int saut_max[]={0, 0, 1, 2, 2, 0, 3, 2, 2, 20, 1, 0, 0};
static const int metabolisme[]={0, 0, 1, 1, 1, 0, 1, 1, 2, 2, 0, 0, 0};
static const int gestation[]={0, 1, 2, 3, 2, 0, 1, 1, 2, 10, 0, 0, 0};
static const int frequence_reproduction[]={10000, 0, 3, 3, 2, 10000, 1, 10, 2, 25, 10000, 10000, 10000};



static const char *mobs_name[20] = {"Vide","Plancton","Corail","Bar","Thon","Pollution","Pyranha","Requin","Orque","Baleine","Pecheur","Pont","Ile"};

//Tableau des couleurs associées à chaque espèce (inidice du tab = id de l'espèce)
static const couleurs mobs_draw[20]={(87<<24)+(113<<16)+(144<<8), (77<<24)+(255<<16)+(84<<8), (254<<24)+(84<<16)+(6<<8), (120<<24)+(192<<16)+(168<<8), (27<<24)+(234<<16)+(255<<8), color_LIGHTGRAY, color_BLACK, color_YELLOW, color_LIGHTMAGENTA, color_MAGENTA, color_RED, color_BROWN, (241<<24)+(184<<16)+(40<<8)};


//Matrice de prédation 
static const int eat_mat[13][13]={	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//esp vide
					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 	//plancton
					{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 	//corail
					{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},	//bar
					{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//thon
					{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//pollution
					{0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0},	//piranha
					{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},	//requin
					{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},	//orque
					{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},	//baleine
					{0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0},	//pecheur
					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};	//pont

/*static const int eat_mat[13][13]={{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							   	  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							      {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
								  {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0},
								  {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0}, 
								  {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0}, 
								  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
								  {0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0}, 
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};*/


int rand_a_b(int a, int b);

#endif

#ifndef __MAIN__H
#define __MAIN__H 

#define TAILLE_PLATEAU 70
#define NB_SPECIES 9

#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct fisher {	int id_proie; //identifiant du dernier poisson peché 
			char nom_joueur[9] ; //Au maximum 8 caractère/nom pour des raisons d'affichage c'est peut etre mal fait pour le caractere d'echappement "\0"
			int x; //coordonnées du joueur
			int y; 
			int reserves; //reserves disponibles
			int nv_reserves; //reserves pechees au tour precedent (bonus poisson)
			int bridge; 
			int allo; //vaut 1 si le pecheur est tombé à l'eau au tour précédent 
			int xp; //experience du pecheur
			int id; //identifiant du pecheur pour le mode 2 joueurs
			int ecolo; //total des poissons rejetés à l'eau (bonus écolo)
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
	**Identifiants......  Survie........Taille...Taille_du_bide.....Saut_max..metabolisme...gestation........frequen_reproduction
	**0espece vide.......0  10 000	   	-1        0                	0         0		0	 	 10 000
	**1plancton .........1  10 000      	 1        0 			0	  0		1	 	 4 	
	**2corail............2  1            	 1        2			1    	  1	  	1	 	 4	
	**3bar...............3  3 	    	 2        2			2	  1		1        	 4
	**4thon..............4  5           	 2        1       		3         2		1        	 4
	**5pollution.........5  10 000      	 0        1			1         0		0	 	 10 000
	**6pyranha...........6  3           	 2        3			3	  2		2 	 	 4
	**7requin............7  4            	 4        3			2         2		2 	 	 4
	**8orque.............8
	**9baleine...........9  3          	 5        2			2   	  2		2 	 	 4
	**10pecheur...........10 10 000       	 3        0			1         0		0	 	 10 000
	**11pont..............11 10 000          1        0			0         0		0	 	 10 000	
	**12ile		
*********************/


static const int duree_survie[]={10000, 10000, 1, 10, 2, 10000, 8, 100, 50, 100, 10000, 10000, 10000};
static const int taille[]={-1, 2, 1, 2, 2, 10, 2, 4, 4, 5, 3, 2, 2};
static const int taille_du_bide[]={0, 0, 2, 4, 3, 10000, 3, 6, 4, 2, 0, 0, 0};
static const int saut_max[]={0, 0, 1, 2, 2, 0, 3, 2, 2, 20, 1, 0, 0};
static const int metabolisme[]={0, 0, 1, 1, 1, 0, 1, 1, 2, 2, 0, 0, 0};
static const int gestation[]={0, 1, 2, 3, 2, 0, 1, 1, 2, 10, 0, 0, 0};
static const int frequence_reproduction[]={10000, 0, 3, 3, 2, 10000, 1, 10, 2, 25, 10000, 10000, 10000};


/*
static const int duree_survie[]={10000, 10000, 5, 6, 1, 10000, 3, 25, 100, 100, 10000, 10000};
static const int taille[]={-1, 2, 1, 2, 3, 10000, 2, 4, 4, 5, 3, 2};
static const int taille_du_bide[]={0, 0, 4, 3, 4, 5, 4, 8, 4, 60, 0, 0};
static const int saut_max[]={0, 0, 1, 2, 2, 0, 3, 2, 2, 2, 1, 0};
static const int metabolisme[]={0, 0, 1, 1, 1, 0, 1, 2, 2, 2, 0, 0};
static const int gestation[]={0, 2, 2, 2, 2, 0, 1, 2, 2, 10, 0, 0};
static const int frequence_reproduction[]={10000, 0, 1, 8, 51, 10000, 35, 4, 2, 25, 10000, 10000};*/



static const char *mobs_name[20] = {"Vide","Plancton","Corail","Bar","Thon","Pollution","Pyranha","Requin","Orque","Baleine","Pecheur","Pont","Ile"};

static const couleurs mobs_draw[20]={(87<<24)+(113<<16)+(144<<8), (77<<24)+(255<<16)+(84<<8), (254<<24)+(84<<16)+(6<<8), (120<<24)+(192<<16)+(168<<8), (27<<24)+(234<<16)+(255<<8), color_LIGHTGRAY, color_BLACK, color_YELLOW, color_LIGHTMAGENTA, color_MAGENTA, color_RED, color_BROWN, (241<<24)+(184<<16)+(40<<8)};

//Matrice de prédation 

/*static const int eat_mat[13][13]={{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
							   	  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							      {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
								  {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0},
								  {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0}, 
								  {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0}, 
								  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, 
								  {0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0}, 
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};*/

static const int eat_mat[13][13]={{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

/* Initialisation de la matrice de prédation 
	eat_mat[0][]={0}; //espece vide ne mange rien
	eat_mat[1]={0}; // plancton ne mange rien 
	eat_mat[2]={1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // corail
	eat_mat[3]={1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}; // bar
 	eat_mat[4]={1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //thon
	eat_mat[5]={1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //pollution
	eat_mat[6]={1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0}; //pyranha
	eat_mat[7]={1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0}; //requin
	eat_mat[8]={1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0}; //orque 
	eat_mat[9]={1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}; //baleine 
	eat_mat[10]={0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0}; //pêcheur
	eat_mat[11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //pont */ 


int rand_a_b(int a, int b);

#endif

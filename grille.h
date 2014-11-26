#ifndef __GRILLE__H
#define __GRILLE__H 
#include "libgraphique.h"

typedef struct 
{	
	int x ;
	int y ;
} Case;



typedef struct 
{
	Case cases[25];
	couleurs content;

} Grille;

//modif content = couleur
typedef struct 
{
	couleurs coul;
	Mob * mob;
} Map;



void afficher_grille(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) ;

void initialiser_grille(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

void place_liste_animal_random(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * listeAnimal );

int isPlaceFree (Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int a , int b);

int spawn_mob(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste);

void spawn_list_of_mobs(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste );

ListeCase * free_neighboor_case_list(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Mob mob);
#endif

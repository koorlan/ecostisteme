#ifndef __GRILLE__H
#define __GRILLE__H 


typedef struct 
{	
	int x ;
	int y ;
} Case;

typedef struct 
{
	Case cases[25];
	char * content;

} Grille;


#include "liste.h"

void afficher_grille(char *plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) ;

void initialiser_grille(char * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

void place_liste_animal_random(char * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * listeAnimal );

int isPlaceFree (char * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int a , int b);

int spawn_mob(char * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Mob mob);

#endif
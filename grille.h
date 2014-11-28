#ifndef __GRILLE__H
#define __GRILLE__H 
#include "libgraphique.h"


/*modif content = couleur
typedef struct 
{
	couleurs coul;
	Mob * mob;
} Map;
*/


void afficher_grille(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) ;

void initialiser_grille(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

void place_liste_animal_random(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * listeAnimal );

int isPlaceFree (Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int a , int b);

int spawn_mob(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste);

void spawn_list_of_mobs(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste );

Liste * free_neighboor_case_list(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Mob mob);
#endif

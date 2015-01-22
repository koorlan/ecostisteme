/**********************************************************************/
/***  fichier: eco.h                                                ***/
/***  en-tete de eco.c   					    ***/
/***								    ***/	
/***  gestion de l'affichage graphique                              ***/
/**********************************************************************/

#ifndef _ECO_H
#define _ECO_H

#include <stdio.h>
#include <stdlib.h>
#include "libgraphique.h"

#define M1 20	//gauche
#define M2 20	//bas
#define M3 (WINDOW_WIDTH- WINDOW_HEIGHT) //droite
#define M4 20	//haut
#define N TAILLE_PLATEAU


void affiche_grille();

void afficher_point(int x, int y, couleurs coul);

void draw_square(int x, int y, couleurs coul);

void espece_consideree(int i, couleurs coul);

int start_screen(); 


//void blind_grid();


#endif

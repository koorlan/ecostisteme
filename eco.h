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
#define M1 (WINDOW_WIDTH)/10
#define M2 (WINDOW_HEIGHT)/10
#define N TAILLE_PLATEAU


void affiche_grille();

void afficher_point(int x, int y, couleurs coul);

void espece_consideree(int i, couleurs coul);

//void blind_grid();


#endif

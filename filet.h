/**********************************************************************/
/***  fichier: filet.h                                              ***/
/***  en-tete de filet.c   					    ***/
/***								    ***/	
/***  gestion du filet de pêche                                     ***/
/**********************************************************************/

#ifndef FILET_H
#define FILET_H

#include "main.h"

void spawn_filet(int x_pecheur, int y_pecheur, int filet[][3], Mob *plateau[][TAILLE_PLATEAU]);

void draw_filet(int x_pecheur, int y_pecheur, int filet[][3]);

#endif

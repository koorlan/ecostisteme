/**********************************************************************/
/***  fichier: canne.h                                              ***/
/***  en-tete de canne.c   					    ***/
/***								    ***/	
/***  gestion de la canne à pêche                                   ***/
/**********************************************************************/

#ifndef CANNE_H
#define CANNE_H

#include "main.h"

int case_valide_peche(int x, int y, int dx, int dy, Mob * plateau[][TAILLE_PLATEAU]);

void spawn_canne(int x, int y, int *x_c, int *y_c, Mob * plateau[][TAILLE_PLATEAU]);

void draw_canne(int x_pecheur, int y_pecheur, int x_canne, int y_canne, couleurs coul);

int place_canne_a_peche(int x_pecheur, int y_pecheur, int *x_canne, int *y_canne, Mob * plateau[][TAILLE_PLATEAU],int bonus_tab[]);

#endif 

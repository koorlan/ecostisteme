/**********************************************************************/
/***  fichier: bonus.h                                              ***/
/***  en-tete de bonus.c   					    ***/
/***								    ***/	
/***  gestion des différents bonus                                  ***/
/**********************************************************************/

#ifndef BONUS_H
#define BONUS_H

#include "main.h"



int first_fish(int nv_reserves, int bonus);

int first_bridge(int bridge, int bonus);

int fish(int nv_reserves, int bonus);

int bridge(int bridge, int bonus);

int island(fisher * pecheur, Mob * plateau[][TAILLE_PLATEAU], int bonus);

int vision(fisher *pecheur, int bonus);

void afficher_bonus(int n);

void appliquer_bonus(fisher * pecheur, int bonus_tab[]);

void capitaliser_bonus(fisher * pecheur, int bonus_tab[], Mob * plateau[][TAILLE_PLATEAU]);

#endif

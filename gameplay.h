#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "main.h"



int first_fish(int nv_reserves, int bonus);

int first_bridge(int bridge, int bonus);

int fish(int nv_reserves, int bonus);

int bridge(int bridge, int bonus);

int island(fisher * pecheur);

int vision(fisher *pecheur, int bonus);

void afficher_bonus(int n);

void afficher_xp(fisher * pecheur);

void appliquer_bonus(fisher * pecheur, int bonus_tab[]);

void capitaliser_bonus(fisher * pecheur, int bonus_tab[]);

#endif

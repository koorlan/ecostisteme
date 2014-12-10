#ifndef PECHEUR_H
#define PECHEUR_H

#include "eco.h"
#include "mob.h"
#include "main.h"

int case_valide(int x, int y, Mob * plateau[][TAILLE_PLATEAU]);

void deplacement_pecheur(int *x, int *y, couleurs coul, Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

int choix_action();

int peche();

#endif 

#ifndef PECHEUR_H
#define PECHEUR_H

#include "eco.h"
#include "mob.h"
#include "main.h"
#include "mobs_ia.h"
#include "pont.h" 

#define TAILLE_CANNE 1

int case_valide(int x, int y, Mob * plateau[][TAILLE_PLATEAU]);

void deplacement_pecheur(Mob * pecheur, couleurs coul, Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

int choix_action(int n);

void spawn_canne(int x, int y, int *x_c, int *y_c);

void draw_canne(int x_pecheur, int y_pecheur, int x_canne, int y_canne, couleurs coul);

int case_valide_peche(int x, int y, int dx, int dy);

void place_canne_a_peche(int x_pecheur, int y_pecheur, int *x_canne, int *y_canne);

void afficher_munitions(Mob * pecheur);

void que_la_peche_commence(Mob * plateau_de_jeu[][TAILLE_PLATEAU], Mob * pecheur, Liste * species[]);

void plouf(Mob *pecheur);


#endif 

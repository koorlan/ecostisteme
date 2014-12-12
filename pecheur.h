/**********************************************************************/
/***  fichier: pecheur.h                                            ***/
/***  en-tete de pecheur.c   					    ***/
/***								    ***/	
/***  gestion du pecheur                                            ***/
/**********************************************************************/


#ifndef PECHEUR_H
#define PECHEUR_H

//#include "eco.h"
//#include "mob.h"
#include "main.h"
//#include "mobs_ia.h"
//#include "pont.h" 

#define TAILLE_CANNE 1

int case_valide(int x, int y, Mob * plateau[][TAILLE_PLATEAU]);

void deplacement_pecheur(Mob * pecheur, couleurs coul, Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

int choix_action(int n);

int case_valide_peche(int x, int y, int dx, int dy);

void afficher_munitions(Mob * pecheur);

void que_la_peche_commence(Mob * plateau_de_jeu[][TAILLE_PLATEAU], Mob * pecheur, Liste * species[], int type_materiel);

void plouf(Mob *pecheur);

int plouf2(Mob *pecheur, Mob * plateau[][TAILLE_PLATEAU], Liste * species[]);

//void final_screen (int a);

#endif 

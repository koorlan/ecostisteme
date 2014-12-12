/**********************************************************************/
/***  fichier: pecheur.h                                            ***/
/***  en-tete de pecheur.c   					    ***/
/***								    ***/	
/***  gestion du pecheur                                            ***/
/**********************************************************************/


#ifndef PECHEUR_H
#define PECHEUR_H

#include "main.h"


#define TAILLE_CANNE 1

int case_valide(int x, int y, Mob * plateau[][TAILLE_PLATEAU]);

void deplacement_pecheur(Mob * pecheur, couleurs coul, Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

int choix_action(int n);

int case_valide_peche(int x, int y, int dx, int dy);

void afficher_munitions(Mob * pecheur, int * reserves_gagnees);

void que_la_peche_commence(Mob * plateau_de_jeu[][TAILLE_PLATEAU], Mob * pecheur, Liste * species[], int type_materiel, int * reserves_gagnees);

void plouf_soft_version(Mob *pecheur);

int plouf_hard_version(Mob *pecheur, Mob * plateau[][TAILLE_PLATEAU], Liste * species[]);

//void final_screen (int a);

#endif 

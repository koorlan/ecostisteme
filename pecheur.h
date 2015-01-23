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

void init_fisher (fisher * pecheur, int x, int y, int id);

int case_valide(int x, int y, Mob * plateau[][TAILLE_PLATEAU]);

void deplacement_pecheur(fisher * pecheur, couleurs coul, Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

int affichage_1();

int affichage_2();

int affichage_3(); 

int choix_action(int n, fisher * pecheur);

void afficher_munitions(fisher * pecheur);

void que_la_peche_commence(Mob * plateau_de_jeu[][TAILLE_PLATEAU], fisher * pecheur, Liste * species[], int type_materiel, int bonus);

void plouf_soft_version(fisher *pecheur);

int plouf_hard_version(fisher *pecheur, Mob * plateau[][TAILLE_PLATEAU], Liste * species[]);

void deplacement_curseur(int * x, int * y, Mob * plateau[][TAILLE_PLATEAU], int bonus_tab[], couleurs coul);

void relacher_poisson(Mob * plateau_de_jeu[][TAILLE_PLATEAU], fisher * pecheur, Liste * species[], int bonus_tab[]);

void jeu_du_pecheur(fisher *pecheur, Mob * plateau_de_jeu[][TAILLE_PLATEAU], int bonus_tab[], int * mort_pecheur, Liste * species[]);


//void final_screen (int a);

#endif 

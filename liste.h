#ifndef __LISTE__H
#define __LISTE__H 


typedef struct elt_liste_mob Liste;
struct elt_liste_mob
{
	Mob mob;
	Liste *nxt;
};
typedef struct listeCase ListeCase;
struct listeCase
{
	int x;
	int y;
	ListeCase *nxt;
};

Liste * ajouterEnTete(Liste * liste, Mob newMob);

ListeCase * ajouterEnTeteCase(ListeCase * liste, int a , int b);

int nombre_elts_liste( Liste * liste);

int nombre_elts_listeCase( ListeCase * liste);
#endif
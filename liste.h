#ifndef __LISTE__H
#define __LISTE__H 


typedef struct elt_liste_mob Liste;
struct elt_liste_mob
{
	Mob  mob;
	Liste *nxt;
};

Liste * ajouterEnTete(Liste * liste, Mob newMob);

int nombre_elts_liste( Liste * liste);

Liste * init_mobs(int id, int percentage);
#endif

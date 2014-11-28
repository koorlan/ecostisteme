
#ifndef __MOB__H
#define __MOB__H


typedef struct 
{
	/**********************
	**
	** Correspondance ID - NOM
	** espece vide....0
	** plancton :.....1
	** corail :.......2
	** bar :..........3
	** thon :.........4
	** pollution :....5
	** pyranha :......6
	** requin :.......7
	** orque :........8
	** baleine :......9
	** pêcheur :......10 
	** pont :.........11
	***********************/
	int id;
	int x;
	int y;
	int dernier_repas;
	int satiete;
	int derniere_reproduction;
	/*int duree_survie;
	int taille;
	int taille_du_bide;
	int saut_max;
	int metabolisme;
	int gestation;
	int frequence_reproduction;*/
} Mob;



Mob * create_mob(int id_mob);

void print_mob_spec(Mob mob);

#endif


#ifndef __MOB__H
#define __MOB__H


typedef struct 
{
	/**********************
	**
	** Correspondance ID - NOM
	** plancton : 0
	** corail : 1
	** bar : 2
	** thon : 3
	** pollution : 4
	** pyranha : 5
	** requin : 6
	** orque : 7
	** baleine : 8
	** pêcheur : 9
	** pont 10
	***********************/
	int id;
	int x;
	int y;
	int dernier_repas;
	int satiete;
	int derniere_reproduction;
	int duree_survie;
	int taille;
	int taille_du_bide;
	int saut_max;
	int metabolisme;
	int gestation;
	int frequence_reproduction;
} Mob;



Mob * create_mob(int id_mob);

void print_mob_spec(Mob mob);

#endif
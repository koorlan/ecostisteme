#include "main.h"

/* Retourne un pointeur sur Mob avec en fonction de l'espèce voulue (id) avec ses variables caracrtéristiques initiales*/
Mob * create_mob(int id_mob)
	
{
 	Mob * mob  = malloc(sizeof(Mob));
  	mob->id = id_mob;
    	mob->dernier_repas = WORLD_TIME;
    	mob->satiete = 0;
    	mob->derniere_reproduction =  WORLD_TIME; 
	return mob;
}

/* Affichage des caractèristiques d'un Mob (ne sert plus)*/
void print_mob_spec(Mob  mob){

 	printf("ID : %d\n", mob.id );
 	printf("dernier_repas : %d\n",mob.dernier_repas );
 	printf("satiete : %d\n",mob.satiete);
 	printf("derniere_reproduction : %d\n", mob.derniere_reproduction);
 	printf("duree_survie : %d\n", duree_survie[mob.id] );
 	printf("taille : %d\n", taille[mob.id]);
 	printf("taille_du_bide : %d\n", taille_du_bide[mob.id]);
 	printf("saut_max : %d\n", saut_max[mob.id] );
 	printf("metabolisme : %d\n", metabolisme[mob.id] );
 	printf("gestation : %d\n", gestation[mob.id] );
 	printf("frequence_reproduction : %d\n", frequence_reproduction[mob.id]);

 	
}

 

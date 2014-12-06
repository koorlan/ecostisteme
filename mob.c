#include "main.h"

/* Retourne un pointeur sur Mob avec en fonction de l'espèce voule (id) avec ses variables caracrtéristiques initiales*/
Mob * create_mob(int id_mob)
	
{
 	Mob mobs_specs[12];

	/**********************
	**ID 0 -> Espece vide
	*********************/
    mobs_specs[0].dernier_repas = 0;
    mobs_specs[0].satiete = 0;
    mobs_specs[0].derniere_reproduction = 0;

 	/**********************
	**ID 1 -> Plancton
	*********************/
    mobs_specs[1].dernier_repas = 0;
    mobs_specs[1].satiete = 0;
    mobs_specs[1].derniere_reproduction = 0;

	/**********************
	**ID 2 -> Corail
	*********************/
    mobs_specs[2].dernier_repas = 0;
    mobs_specs[2].satiete = 0;
    mobs_specs[2].derniere_reproduction =  0;
 
	/**********************
	**ID 3 -> Bar
	*********************/
    mobs_specs[3].dernier_repas = 0;
    mobs_specs[3].satiete = 0;
    mobs_specs[3].derniere_reproduction = 0;
    
    /**********************
	**ID 4 -> Thon
	*********************/
    mobs_specs[4].dernier_repas = 0;
    mobs_specs[4].satiete = 0;
    mobs_specs[4].derniere_reproduction = 0;

    /**********************
	**ID 5 -> Pollution
	*********************/
    mobs_specs[5].dernier_repas = 0;
    mobs_specs[5].satiete = 0;
    mobs_specs[5].derniere_reproduction = 0;  

    /**********************
	**ID 6 -> Pyranah
	*********************/
    mobs_specs[6].dernier_repas = 0;
    mobs_specs[6].satiete = 0;
    mobs_specs[6].derniere_reproduction = 0;

    /**********************
	**ID 7 -> Requin
	*********************/
    mobs_specs[7].dernier_repas = 0;
    mobs_specs[7].satiete = 0;
    mobs_specs[7].derniere_reproduction = 0;

    /**********************
	**ID 8 -> Orque
	*********************/
    mobs_specs[8].dernier_repas = 0;
    mobs_specs[8].satiete = 0;
    mobs_specs[8].derniere_reproduction = 0;

    /**********************
	**ID 9 -> Baleine
	*********************/
    mobs_specs[9].dernier_repas = 0;
    mobs_specs[9].satiete = 0;
    mobs_specs[9].derniere_reproduction = 0;

  
    // A FOUTRE (METTRE...) DANS AUTRE STRUCTURE
   /**********************
	**ID 10 -> Pont
	*********************/
    mobs_specs[10].dernier_repas = 9;
    mobs_specs[10].satiete = 9;
    mobs_specs[10].derniere_reproduction = 9;

    /**********************
	**ID 11 -> Pecheur
	*********************/
    mobs_specs[11].dernier_repas = 10;
    mobs_specs[11].satiete = 10;
    mobs_specs[11].derniere_reproduction = 10;



 	Mob * mob  = malloc(sizeof(Mob));
	mob->id = id_mob;
	mob->dernier_repas = mobs_specs[id_mob].dernier_repas;
	mob->satiete = mobs_specs[id_mob].satiete;
	mob->derniere_reproduction =  mobs_specs[id_mob].derniere_reproduction;

	return mob;
}

/* Affichage des caractèristiques d'un Mob*/
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

 	return;
}

 

#include "main.h"

Mob * create_mob(int id_mob)
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
	** pêcheur : 9 // a pas mettre dans mob
	** pont 10  // a pas mettre dans mob
	***********************/
 {
 	Mob mobs_specs[12];

 	/**********************
	**ID 0 -> Plancton
	*********************/
    mobs_specs[0].dernier_repas = 0;
    mobs_specs[0].satiete = 3;
    mobs_specs[0].derniere_reproduction = 0;
    mobs_specs[0].duree_survie = 3;
    mobs_specs[0].taille = 5;
    mobs_specs[0].taille_du_bide = 4;
    mobs_specs[0].saut_max = 2;
    mobs_specs[0].metabolisme = 1;
    mobs_specs[0].gestation = 2;
    mobs_specs[0].frequence_reproduction =600 ;
	/**********************
	**ID 1 -> Corail
	*********************/
    mobs_specs[1].dernier_repas = 11;
    mobs_specs[1].satiete = 3;
    mobs_specs[1].derniere_reproduction = 11;
    mobs_specs[1].duree_survie = 3;
    mobs_specs[1].taille = 5;
    mobs_specs[1].taille_du_bide = 4;
    mobs_specs[1].saut_max = 2;
    mobs_specs[1].metabolisme = 1;
    mobs_specs[1].gestation = 2;
    mobs_specs[1].frequence_reproduction =61 ;

	/**********************
	**ID 2 -> Bar
	*********************/
    mobs_specs[2].dernier_repas = 2;
    mobs_specs[2].satiete = 3;
    mobs_specs[2].derniere_reproduction = 2;
    mobs_specs[2].duree_survie = 3;
    mobs_specs[2].taille = 2;
    mobs_specs[2].taille_du_bide = 4;
    mobs_specs[2].saut_max = 2;
    mobs_specs[2].metabolisme = 2;
    mobs_specs[2].gestation = 2;
    mobs_specs[2].frequence_reproduction =62 ;

    /**********************
	**ID 3 -> Thon
	*********************/
    mobs_specs[3].dernier_repas = 3;
    mobs_specs[3].satiete = 3;
    mobs_specs[3].derniere_reproduction = 3;
    mobs_specs[3].duree_survie = 3;
    mobs_specs[3].taille = 3;
    mobs_specs[3].taille_du_bide = 4;
    mobs_specs[3].saut_max = 3;
    mobs_specs[3].metabolisme = 3;
    mobs_specs[3].gestation = 3;
    mobs_specs[3].frequence_reproduction =63 ;

    /**********************
	**ID 4 -> Pollution
	*********************/
    mobs_specs[4].dernier_repas = 4;
    mobs_specs[4].satiete = 4;
    mobs_specs[4].derniere_reproduction = 4;
    mobs_specs[4].duree_survie = 4;
    mobs_specs[4].taille = 4;
    mobs_specs[4].taille_du_bide = 4;
    mobs_specs[4].saut_max = 4;
    mobs_specs[4].metabolisme = 4;
    mobs_specs[4].gestation = 4;
    mobs_specs[4].frequence_reproduction =64 ;

    /**********************
	**ID 5 -> Pyranah
	*********************/
    mobs_specs[5].dernier_repas = 5;
    mobs_specs[5].satiete = 5;
    mobs_specs[5].derniere_reproduction = 5;
    mobs_specs[5].duree_survie = 5;
    mobs_specs[5].taille = 5;
    mobs_specs[5].taille_du_bide = 5;
    mobs_specs[5].saut_max = 5;
    mobs_specs[5].metabolisme = 5;
    mobs_specs[5].gestation = 5;
    mobs_specs[5].frequence_reproduction =65 ;

    /**********************
	**ID 6 -> Requin
	*********************/
    mobs_specs[6].dernier_repas = 6;
    mobs_specs[6].satiete = 6;
    mobs_specs[6].derniere_reproduction = 6;
    mobs_specs[6].duree_survie = 6;
    mobs_specs[6].taille = 6;
    mobs_specs[6].taille_du_bide = 6;
    mobs_specs[6].saut_max = 6;
    mobs_specs[6].metabolisme = 6;
    mobs_specs[6].gestation = 6;
    mobs_specs[6].frequence_reproduction =66 ;

    /**********************
	**ID 7 -> Orque
	*********************/
    mobs_specs[7].dernier_repas = 7;
    mobs_specs[7].satiete = 7;
    mobs_specs[7].derniere_reproduction = 7;
    mobs_specs[7].duree_survie = 7;
    mobs_specs[7].taille = 7;
    mobs_specs[7].taille_du_bide = 7;
    mobs_specs[7].saut_max = 7;
    mobs_specs[7].metabolisme = 7;
    mobs_specs[7].gestation = 7;
    mobs_specs[7].frequence_reproduction =77 ;

    /**********************
	**ID 8 -> Baleine
	*********************/
    mobs_specs[8].dernier_repas = 8;
    mobs_specs[8].satiete = 8;
    mobs_specs[8].derniere_reproduction = 8;
    mobs_specs[8].duree_survie = 8;
    mobs_specs[8].taille = 8;
    mobs_specs[8].taille_du_bide = 8;
    mobs_specs[8].saut_max = 8;
    mobs_specs[8].metabolisme = 8;
    mobs_specs[8].gestation = 8;
    mobs_specs[8].frequence_reproduction =88 ;

  
    // A FOUTRE DANS AUTRE STRUCTURE
   /**********************
	**ID 9 -> Pont
	*********************/
    mobs_specs[9].dernier_repas = 9;
    mobs_specs[9].satiete = 9;
    mobs_specs[9].derniere_reproduction = 9;
    mobs_specs[9].duree_survie = 9;
    mobs_specs[9].taille = 9;
    mobs_specs[9].taille_du_bide = 9;
    mobs_specs[9].saut_max = 9;
    mobs_specs[9].metabolisme = 9;
    mobs_specs[9].gestation = 9;
    mobs_specs[9].frequence_reproduction =99 ;

    /**********************
	**ID 10 -> Pecheur
	*********************/
    mobs_specs[10].dernier_repas = 10;
    mobs_specs[10].satiete = 10;
    mobs_specs[10].derniere_reproduction = 10;
    mobs_specs[10].duree_survie = 10;
    mobs_specs[10].taille = 10;
    mobs_specs[10].taille_du_bide = 10;
    mobs_specs[10].saut_max = 10;
    mobs_specs[10].metabolisme = 10;
    mobs_specs[10].gestation = 10;
    mobs_specs[10].frequence_reproduction =1010 ;



 	Mob * mob  = malloc(sizeof(Mob));
	mob->id = id_mob;
	mob->dernier_repas = mobs_specs[id_mob].dernier_repas;
	mob->satiete = mobs_specs[id_mob].satiete;
	mob->derniere_reproduction =  mobs_specs[id_mob].derniere_reproduction;
	mob->duree_survie = mobs_specs[id_mob].duree_survie;
	mob->taille = mobs_specs[id_mob].taille;
	mob->taille_du_bide = mobs_specs[id_mob].taille_du_bide;
	mob->saut_max = mobs_specs[id_mob].saut_max;
	mob->metabolisme = mobs_specs[id_mob].metabolisme;
	mob->gestation = mobs_specs[id_mob].gestation;
	mob->frequence_reproduction = mobs_specs[id_mob].frequence_reproduction;
    
	return mob;
 }

 void print_mob_spec(Mob  mob){

 	printf("ID : %d\n", mob.id );
 	printf("dernier_repas : %d\n",mob.dernier_repas );
 	printf("satiete : %d\n",mob.satiete);
 	printf("derniere_reproduction : %d\n", mob.derniere_reproduction);
 	printf("duree_survie : %d\n",mob.duree_survie );
 	printf("taille : %d\n", mob.taille);
 	printf("taille_du_bide : %d\n", mob.taille_du_bide);
 	printf("saut_max : %d\n",mob.saut_max  );
 	printf("metabolisme : %d\n",mob.metabolisme );
 	printf("gestation : %d\n",mob.gestation );
 	printf("frequence_reproduction : %d\n", mob.frequence_reproduction);

 	return;
 }

 
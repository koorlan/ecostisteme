#include "main.h"


Liste * destroy_mob (Mob mob, Liste * list_of_specific_species )

{      
	if(list_of_specific_species ->nxt == NULL)
        	return list_of_specific_species;
    	if(list_of_specific_species->mob.x == mob.x && list_of_specific_species->mob.y == mob.y)
	{
        	Liste * tmp = list_of_specific_species->nxt;
        	//free(list_of_specific_species);
        	return tmp;
    	} 
	else 
	{
        	list_of_specific_species->nxt = destroy_mob (mob,list_of_specific_species->nxt);
        	return list_of_specific_species;
    	}    

}

/* Retourne 1 si un mob survit */
int survie(Mob * mob, Liste * species[NB_SPECIES])
{
	if(mob->satiete <= 0 && (WORLD_TIME-mob->dernier_repas)>duree_survie[mob->id]) 
  	{	
		species[mob->id] = destroy_mob(*mob, species[mob->id]);  //On passe la liste de l'espece a la fonction destroy pour le supprimer de la liste
		
        	return 0;
	} 
	return 1;
}


int reproduction(Mob * mob, Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES]){

	//printf("%d %d %d %d %d %d \n ",mob->satiete, gestation[mob->id], metabolisme[mob->id], mob->derniere_reproduction, frequence_reproduction[mob->id], WORLD_TIME);
	if(mob->satiete >= gestation[mob->id] * metabolisme[mob->id] && mob->derniere_reproduction + frequence_reproduction[mob->id] < WORLD_TIME) {
	//printf("WALAH JAI ESSAYEDE ME REPRO\n");
	Liste * free_place_list = malloc(sizeof(Liste));
	free_place_list = free_neighboor_case_list(plateau, mob);
	if (free_place_list->nxt == NULL)
	{
		//printf("Enfait javais pas dplace\n");
		
		free(free_place_list);
		return 0;
	}
	
	int randomPick = rand_a_b(0,nombre_elts_liste(free_place_list));
	
	int i = 0;
	while(i != randomPick){
		free_place_list = free_place_list->nxt;
		i++;
	} 
	//On free la ou on etait pou accueilir le mob
	//free(plateau[free_place_list->mob.x][free_place_list->mob.y]); 
	Mob * newMob = create_mob(mob->id);
	newMob->x = free_place_list->mob.x ;
	newMob->y = free_place_list->mob.y;
	newMob->satiete = 0;
	newMob->dernier_repas = WORLD_TIME;
	newMob->derniere_reproduction = WORLD_TIME;
	species[mob->id] = ajouterEnTete(species[mob->id], *newMob);
	plateau[free_place_list->mob.x][free_place_list->mob.y] = newMob;
	free(free_place_list);
    return 1;
	} else 
		return 0;

}


/*Retourne 1 si un mob effectue prédation */
int predation(Mob *mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES])
{	

	int i, j;
	i= 0;
	j= 0;
	Mob *proie ;// = malloc(sizeof(Mob));
	proie=create_mob(0);
	//afficher_point(mob->x+1, mob->y+1, mobs_draw[7]);

	Liste *a_miam = malloc(sizeof(Liste));
	a_miam->nxt = NULL;



	for(i=-1; i<=1; i++)
	{	for(j=-1; j<=1; j++)
		{	
        	if(((((mob->x)+i>=0) && ((mob->y)+j>=0))&&(((mob->x)+i<TAILLE_PLATEAU) && ((mob->y)+j<TAILLE_PLATEAU)))) //case hors champ
			{
            	if(eat_mat[mob->id][plateau_de_jeu[(mob->x)+i][(mob->y)+j]->id]==1) //si on trouve une espèce commestible dans les cases adjacentes
              	{     

	        		if((taille[plateau_de_jeu[(mob->x)+i][(mob->y)+j]->id]>=taille[proie->id])&&((mob->satiete)+taille[proie->id]<taille_du_bide[mob->id]))	//recherche de la proie de taille max
                    {      //Affichage en rose de la (les) proie(s) potentielles
						//afficher_point((mob->x)+i+1, (mob->y)+j+1, mobs_draw[8]);
	        		}
	        		proie->x=plateau_de_jeu[(mob->x)+i][(mob->y)+j]->x;
                        proie->y=plateau_de_jeu[(mob->x)+i][(mob->y)+j]->y;
                       	proie->id=plateau_de_jeu[(mob->x)+i][(mob->y)+j]->id;

                       	a_miam = ajouterEnTete(a_miam, *proie);  
        	    }      
            }
		}
	}
	if (a_miam->nxt == NULL)
	{
		
		free(a_miam);
		return 0;
	} 

	int randomPick = rand_a_b(1,nombre_elts_liste(a_miam)+1);
	//printf("%d \n", nombre_elts_liste(a_miam));
	//printf("%d\t",randomPick);

	i = 1;
	while(i != randomPick){
		//printf("%d\n",a_miam->mob.x );
		a_miam = a_miam->nxt;
		i++;
	} 
	*proie = a_miam->mob;
	free(a_miam);
   // if(proie->id!=0)
   	{	
  
 		//La case de la proie prend les caractéristiques du mob	                    
        plateau_de_jeu[proie->x][proie->y]->id=(*mob).id;
		plateau_de_jeu[proie->x][proie->y]->derniere_reproduction=(*mob).derniere_reproduction;
        plateau_de_jeu[proie->x][proie->y]->satiete=(*mob).satiete+taille[proie->id]; 
		plateau_de_jeu[proie->x][proie->y]->dernier_repas=WORLD_TIME;
		
		//La case précedente du mob est remplacée par l'espece vide                 
		plateau_de_jeu[(*mob).x][(*mob).y]=create_mob(0);
		plateau_de_jeu[(*mob).x][(*mob).y]->x = (*mob).x ;
		plateau_de_jeu[(*mob).x][(*mob).y]->y = (*mob).y ;
		
		
		//Les coordonnées et caractéristiques du mob sont changées, nb : pas dans la liste de ce mob ... 	
		//Il faut que ce mob soit passé par ADRESSE	
		mob->x=proie->x;
		mob->y=proie->y;
        mob->dernier_repas=WORLD_TIME;
		mob->satiete=plateau_de_jeu[proie->x][proie->y]->satiete;                
                	
		//On retire la proie de la liste correspondant à son espèce
		if (proie->id != 11) {
           	species[proie->id]=destroy_mob(*proie, species[proie->id]);	 
		
		free(proie);                
		}
		return 1;      
    }       	        	
	return 0;


}

int deplacement(Mob * mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES] ){
	Liste * free_place_list = malloc(sizeof(Liste));
	free_place_list = free_neighboor_case_list(plateau_de_jeu, mob);
	if (free_place_list->nxt == NULL)
	{
		free(free_place_list);
		return 0;
	}
	
	int randomPick = rand_a_b(0,nombre_elts_liste(free_place_list));
	
	int i = 0;
	while(i != randomPick){
		free_place_list = free_place_list->nxt;
		i++;
	} 


	plateau_de_jeu[free_place_list->mob.x][free_place_list->mob.y]->id=(*mob).id;
  //plateau_de_jeu[free_place_list->mob.x][free_place_list->mob.y]->derniere_reproduction=(*mob).derniere_reproduction;
  //  plateau_de_jeu[free_place_list->mob.x][free_place_list->mob.y]->satiete=(*mob).satiete+taille[proie->id]; 
  //	plateau_de_jeu[free_place_list->mob.x][free_place_list->mob.y]->dernier_repas=WORLD_TIME;
		
	//La case précedente du mob est remplacée par l'espece vide                 
	plateau_de_jeu[(*mob).x][(*mob).y]=create_mob(0);
	plateau_de_jeu[(*mob).x][(*mob).y]->x = (*mob).x ;
	plateau_de_jeu[(*mob).x][(*mob).y]->y = (*mob).y ;
	
	
	//Les coordonnées et caractéristiques du mob sont changées, nb : pas dans la liste de ce mob ... 	
	//Il faut que ce mob soit passé par ADRESSE	
	mob->x=free_place_list->mob.x;
	mob->y=free_place_list->mob.y;
   // mob->dernier_repas=WORLD_TIME;
               
               	
	//On retire la proie de la liste correspondant à son espèce
    //species[proie->id]=destroy_mob(*proie, species[proie->id]);	 
//	free(proie);                
	return 1;      
}

void tour(Mob * mob){
	//printf("Ma satiete avant %d \n" mob->satiete);
	//printf(" sat : %d \n",mob->satiete );
	mob->satiete = max(mob->satiete - metabolisme[mob->id] , 0 );
	
}

void ia_mob(Mob * mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES] ){
	if(!survie(mob, species))
	{	
		//Si l'individu ne survie pas
		plateau_de_jeu[mob->x][mob->y]=create_mob(0);
		plateau_de_jeu[mob->x][mob->y]->x = mob->x;
		plateau_de_jeu[mob->x][mob->y]->y = mob->y;	
		return;
	}	
	else{
		if(reproduction(mob, plateau_de_jeu, species))
		{	
			//L'individu c'est reproduit
			tour(mob);
			return;
		}
		else if (predation(mob, plateau_de_jeu, species))
			{	//L'individu a mangé
				tour(mob);
				return;										
			} else if (deplacement(mob, plateau_de_jeu, species)) {
				tour(mob);
				return;
			}

	//Il n'a rien put faire
	tour(mob);
	return;
	}
}


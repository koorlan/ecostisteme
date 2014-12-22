#include "main.h"


void destroy_list (Liste ** l)
{	Liste * clean=malloc(sizeof(Liste));
	if(*l==NULL)
		exit(EXIT_FAILURE);
	clean=(*l);
	
	while(clean->nxt!=NULL)
	{	*l=(*l)->nxt;
		free(clean);
		clean=NULL;
		clean=realloc(*l, sizeof(Liste));
		
	}
	
}


/*void destroy_list (Liste ** l)
{	Liste * elt =malloc(sizeof(Liste));
	if(elt==NULL)	
		exit(EXIT_FAILURE);	
	if(*l==NULL)	
	{	printf("\nDans la fonction defiler : LISTE VIDE, PAS D'ELEMENT A DEFILER\n");
		return;
	}	
	elt=(*l);
	while((*l)->nxt!=NULL)
	{	elt=realloc((*l), sizeof(Liste));
		(*l)=(*l)->nxt;
		free(elt);
		
	}	


	
}*/	
	

Liste * destroy_mob (Mob mob, Liste * list_of_specific_species )

{      
	if(list_of_specific_species ->nxt == NULL)
        	return list_of_specific_species;
    	if(list_of_specific_species->mob.x == mob.x && list_of_specific_species->mob.y == mob.y)
	{
        	Liste * tmp=malloc(sizeof(Liste));
		tmp=list_of_specific_species->nxt;
 //       	Liste * clean=malloc(sizeof(Liste));
//		clean=list_of_specific_species;
		if(tmp==NULL/*||clean==NULL*/)
			exit(EXIT_FAILURE);

		//libération mémoire 		
//		free(clean);
//		clean=NULL;
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

	
	if(mob->satiete >= gestation[mob->id] * metabolisme[mob->id] && mob->derniere_reproduction + frequence_reproduction[mob->id] < WORLD_TIME) {
	
		Liste * free_place_list = malloc(sizeof(Liste));
		if(free_place_list==NULL)
			exit(EXIT_FAILURE);
	
		free_place_list = free_neighboor_case_list(plateau, mob);
		if (free_place_list->nxt == NULL)
		{	
			free(free_place_list);
			free_place_list=NULL;
			return 0;
		}	
	
		int randomPick = rand_a_b(0,nombre_elts_liste(free_place_list));
	
		int i = 0;
		while(i != randomPick){
			free_place_list = free_place_list->nxt;
			i++;
		} 
		

		Mob * newMob = create_mob(mob->id);
		newMob->x = free_place_list->mob.x ;
		newMob->y = free_place_list->mob.y;
		newMob->satiete = 0;
		newMob->dernier_repas = WORLD_TIME;
		newMob->derniere_reproduction = WORLD_TIME;
		species[mob->id] = ajouterEnTete(species[mob->id], *newMob);

		Mob * tmp = malloc(sizeof(Mob));
		tmp=plateau[free_place_list->mob.x][free_place_list->mob.y];

		free(tmp);
		tmp=NULL;
		plateau[free_place_list->mob.x][free_place_list->mob.y] = newMob;
		
		//libération mémoire
		destroy_list(&free_place_list);
		free(free_place_list);
		free_place_list=NULL;
	
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
	Mob * proie = malloc(sizeof(Mob));
	proie=create_mob(0);
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
                    			{      	//Affichage en rose de la (les) proie(s) potentielles
						//afficher_point((mob->x)+i+1, (mob->y)+j+1, mobs_draw[8]);
	        			
	        				proie->x=plateau_de_jeu[(mob->x)+i][(mob->y)+j]->x;
                        			proie->y=plateau_de_jeu[(mob->x)+i][(mob->y)+j]->y;
                       				proie->id=plateau_de_jeu[(mob->x)+i][(mob->y)+j]->id;
	                       			a_miam = ajouterEnTete(a_miam, *proie);
					}
					 
        			}      
            		}
		}
	}
	if (a_miam->nxt == NULL)
	{
		
		free(a_miam);
		a_miam=NULL;
		return 0;
	} 

	int randomPick = rand_a_b(1,nombre_elts_liste(a_miam)+1);
	Liste * tmp=malloc(sizeof(Liste));
	if(tmp==NULL)
		exit(EXIT_FAILURE);
	tmp=a_miam;	
		
	i = 1;
	
	while(i != randomPick){
		
		tmp = a_miam->nxt;
		i++;
	} 
	*proie = tmp->mob;
//	free(tmp);
//	tmp=NULL;
	destroy_list(&a_miam);
	free(a_miam);	
//	a_miam=NULL;
    	if(proie->id!=0)
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
		
		
		//Les coordonnées et caractéristiques du mob sont changées		
		mob->x=proie->x;
		mob->y=proie->y;
        	mob->dernier_repas=WORLD_TIME;
		mob->satiete=plateau_de_jeu[proie->x][proie->y]->satiete;                
	                	
		if (proie->id ==11)
			draw_pont(proie->x+1, proie->y+1, color_WHITE);
		//On retire la proie de la liste correspondant à son espèce
		if (proie->id != 11)
		{
           		species[proie->id]=destroy_mob(*proie, species[proie->id]);	 
			              
		}
		free(proie); 
		proie=NULL;  
	//	free(tmp);
	//	tmp=NULL;		
		return 1;      
    }       
	free(proie); 
	proie=NULL; 	 
	//free(tmp);
	//tmp=NULL;       	
	return 0;


}

int deplacement(Mob * mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES] ){
	int mob_saut_max = saut_max[mob->id];
	//while(mob_saut_max < saut_max[mob->id] ){
	Liste * free_place_list = malloc(sizeof(Liste));
	free_place_list = free_neighboor_case_list(plateau_de_jeu, mob);

	if (free_place_list->nxt == NULL)
	{
		free(free_place_list);
		free_place_list=NULL;
		return 0;
	}
	
	int randomPick = rand_a_b(0,nombre_elts_liste(free_place_list));
	
	int i = 0;
	while(i != randomPick){
		free_place_list = free_place_list->nxt;
		i++;
	} 


	plateau_de_jeu[free_place_list->mob.x][free_place_list->mob.y]->id=(*mob).id;          
	plateau_de_jeu[(*mob).x][(*mob).y]=create_mob(0);
	plateau_de_jeu[(*mob).x][(*mob).y]->x = (*mob).x ;
	plateau_de_jeu[(*mob).x][(*mob).y]->y = (*mob).y ;
	mob->x=free_place_list->mob.x;
	mob->y=free_place_list->mob.y;
	mob_saut_max--;
	//}
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
			//L'individu s'est reproduit
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

	//Il n'a rien pu faire
	tour(mob);
	return;
	}
}


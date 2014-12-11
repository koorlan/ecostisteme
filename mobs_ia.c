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
int survie(Mob mob, Liste * species[NB_SPECIES])
{
	if(mob.satiete <= 0 && (WORLD_TIME-mob.dernier_repas)>duree_survie[mob.id]) 
  	{	
		species[mob.id] = destroy_mob(mob, species[mob.id]);  //On passe la liste de l'espece a la fonction destroy pour le supprimer de la liste
		
        	return 0;
	} 
	return 1;
}


int reproduction(Mob mob);


/*Retourne 1 si un mob effectue prédation */
int predation(Mob *mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES])
{	
	int i, j;
	Mob *proie = malloc(sizeof(Mob));
	proie=create_mob(0);
	afficher_point(mob->x+1, mob->y+1, mobs_draw[7]);
	for(i=-1; i<=1; i++)
	{	for(j=-1; j<=1; j++)
		{	
                        if(((((mob->x)+i>=0) && ((mob->y)+j>=0))&&(((mob->x)+i<TAILLE_PLATEAU) && ((mob->y)+j<TAILLE_PLATEAU)))) //case hors champ
			{
                                if(eat_mat[mob->id][plateau_de_jeu[(mob->x)+i][(mob->y)+j]->id]==1) //si on trouve une espèce commestible dans les cases adjacentes
                                {       
	        			if((taille[plateau_de_jeu[(mob->x)+i][(mob->y)+j]->id]>=taille[proie->id])&&(mob->satiete+taille[proie->id]<taille_du_bide[mob->id]))	//recherche de la proie de taille max
                                         {      //Affichage en rose de la (les) proie(s) potentielles
						if(plateau_de_jeu[(mob->x)+i][(mob->y)+j]->id==11)
					 		draw_pont((mob->x)+i+1, (mob->y)+j+1, mobs_draw[8]); 							else 
							afficher_point((mob->x)+i+1, (mob->y)+j+1, mobs_draw[8]);
	        				proie->x=plateau_de_jeu[(mob->x)+i][(mob->y)+j]->x;
                                                proie->y=plateau_de_jeu[(mob->x)+i][(mob->y)+j]->y;
                                                proie->id=plateau_de_jeu[(mob->x)+i][(mob->y)+j]->id;
						
                                               
                                                
	        			}
        	      	 	}      
                	 }
		}
	}
	update_graphics();
        if(proie->id!=0)
        {	
  
 		//La case de la proie prend les caractéristiques du mob	                    
                plateau_de_jeu[proie->x][proie->y]->id=(*mob).id;
		plateau_de_jeu[proie->x][proie->y]->derniere_reproduction=(*mob).derniere_reproduction;
                plateau_de_jeu[proie->x][proie->y]->satiete=(*mob).satiete+taille[proie->id]; 
		plateau_de_jeu[proie->x][proie->y]->dernier_repas=WORLD_TIME;
		
		//La case précedente du mob est remplacée par l'espece vide                 
		plateau_de_jeu[(*mob).x][(*mob).y]=create_mob(0);
		
		//Les coordonnées et caractéristiques du mob sont changées, nb : pas dans la liste de ce mob ... 	
		//Il faut que ce mob soit passé par ADRESSE	
		mob->x=proie->x;
		mob->y=proie->y;
               	mob->dernier_repas=WORLD_TIME;
		mob->satiete=plateau_de_jeu[proie->x][proie->y]->satiete;                
                
		if(proie->id!=11)	
			//On retire la proie de la liste correspondant à son espèce
           		species[proie->id]=destroy_mob(*proie, species[proie->id]);	 
//		free(proie);                
		return 1;      
        }       	        	
	return 0;
	

}

int deplacement(Mob mob);

int tour();


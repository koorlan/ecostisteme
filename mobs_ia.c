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

/*libère une liste*/
void free_list (Liste *l)
{
	Liste *tmp;

   while (l != NULL)
    {
       tmp = l;
       l = l->nxt;
       free(tmp);
    }
}
		
/*Retire un mob de sa liste*/
Liste * destroy_mob (Mob mob, Liste * list_of_specific_species )

{      
	if(list_of_specific_species->nxt == NULL)
        	return list_of_specific_species;
    	if(list_of_specific_species->mob.x == mob.x && list_of_specific_species->mob.y == mob.y)
	{
       		Liste * tmp=malloc(sizeof(Liste));
		tmp=list_of_specific_species->nxt;
		free(list_of_specific_species);
       		return tmp;
    	} 
    	list_of_specific_species->nxt = destroy_mob (mob,list_of_specific_species->nxt);
    	return list_of_specific_species;
    	    

}

/* Retourne 1 si un mob survit, 0 sinon*/
int survie(Mob * mob, Liste * species[NB_SPECIES])
{
	if(mob->satiete <= 0 && (WORLD_TIME-mob->dernier_repas)>duree_survie[mob->id]) 
  	{	
		  //On passe la liste de l'espece a la fonction destroy pour le supprimer de la liste
			
        	return 0;
	} 
	return 1;
}


int reproduction(Mob * mob, Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES]){

	
	if(mob->satiete >= gestation[mob->id] * metabolisme[mob->id] && mob->derniere_reproduction + frequence_reproduction[mob->id] < WORLD_TIME) {
	
		int randomPick = 0;
		Mob * libre[8] = { NULL } ;
		int i = 0;
		int j = 0;
		int indice = 0;

		for (i = -1; i < 1; ++i)
		{
			for (j = -1; j <1; ++j)
			{
				if( ((((mob->x)+i>=0) && ((mob->y)+j>=0))&&(((mob->x)+i<TAILLE_PLATEAU) && ((mob->y)+j<TAILLE_PLATEAU))) ){ //case hors champ
           			if( (plateau[i+mob->x][j+mob->y])->id == 0 ){
           				libre[indice] = plateau[i+mob->x][j+mob->y];
           				indice ++;
           			}

            	}
			}
		}

		if (indice  != 0)
			randomPick = rand_a_b(0,indice);
		else
			return 0;
		
		int xtemp = libre[randomPick]->x;
		int ytemp = libre[randomPick]->y;		
		free(libre[randomPick]);

		Mob * newMob = create_mob(mob->id);
		plateau[xtemp][ytemp] = newMob;
		plateau[xtemp][ytemp]->id = mob->id;
		plateau[xtemp][ytemp]->x = xtemp;
		plateau[xtemp][ytemp]->y = ytemp;
		plateau[xtemp][ytemp]->satiete = 0;
		plateau[xtemp][ytemp]->dernier_repas = WORLD_TIME;
		plateau[xtemp][ytemp]->derniere_reproduction = WORLD_TIME;
		species[mob->id] = ajouterEnTete(species[mob->id], *newMob);
		

    	return 1;
		} else 
			return 0;

}


/*Retourne 1 si un mob effectue prédation, 0 sinon */
int predation(Mob *mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES])
{	

	int i, j;
	i= 0;
	j= 0;

	int indice =0 ;
	int randomPick = 0;
	Mob * proie ;
	proie=create_mob(0);
	Mob * a_miam[8] = { NULL } ;
	int taille_max=0;

	for(i= -1; i<=1; i++)
	{	for(j=-1; j<=1; j++)
		{	

        	if( ((((mob->x)+i>=0) && ((mob->y)+j>=0))&&(((mob->x)+i<TAILLE_PLATEAU) && ((mob->y)+j<TAILLE_PLATEAU))) ){ //case hors champ
            	if(eat_mat[mob->id][plateau_de_jeu[(mob->x)+i][(mob->y)+j]->id]==1){ //si on trouve une espèce commestible dans les cases adjacentes    
					if( (mob->satiete)+taille[proie->id]<taille_du_bide[mob->id] ){
						a_miam[indice] = plateau_de_jeu[(mob->x)+i][(mob->y)+j];
						indice++;
						if (taille[ (plateau_de_jeu[(mob->x)+i][(mob->y)+j])->id ] >= taille_max)
							taille_max = taille[ (plateau_de_jeu[(mob->x)+i][(mob->y)+j])->id ];
					}
					 
        		}      
            }
		}
	}
	if (indice  != 0)
		randomPick = rand_a_b(0,indice);
	else{ 
		free(proie);
		return 0;
	}


	while ( a_miam[randomPick%8] == NULL || taille[(a_miam[randomPick%8])->id] != taille_max ){
		randomPick++;
	}

	*proie = *a_miam[randomPick%8];


    	if(proie->id!=0)
   	{	
   		//La case de la proie prend les caractéristiques du mob	                    
        plateau_de_jeu[proie->x][proie->y]->id=(*mob).id;
		plateau_de_jeu[proie->x][proie->y]->derniere_reproduction=(*mob).derniere_reproduction;
        plateau_de_jeu[proie->x][proie->y]->satiete=(*mob).satiete+taille[proie->id]; 
		plateau_de_jeu[proie->x][proie->y]->dernier_repas=WORLD_TIME;
		
		//La case précedente du mob est remplacée par l'espece vide  
		int xtmp = (*mob).x;
		int ytmp = (*mob).y;
		//free(plateau_de_jeu[xtmp][ytmp]);
		plateau_de_jeu[xtmp][ytmp]=create_mob(0);
		plateau_de_jeu[xtmp][ytmp]->x = xtmp ;
		plateau_de_jeu[xtmp][ytmp]->y = ytmp ;
		
		
		//Les coordonnées et caractéristiques du mob sont changées		
		mob->x=proie->x;
		mob->y=proie->y;
        mob->dernier_repas=WORLD_TIME;
		mob->satiete=plateau_de_jeu[proie->x][proie->y]->satiete;                
	                	
		if (proie->id ==11)
			draw_square(proie->x+1, proie->y+1, color_WHITE);
		//On retire la proie de la liste correspondant à son espèce
		if (proie->id != 11)
		{
           	species[proie->id]=destroy_mob(*proie, species[proie->id]);	               
		}
		free(proie);
		proie =NULL;

		return 1;      
    }      

	free(proie); 
	proie=NULL; 	 
   	
	return 0;


}

/*Retourne 1 si un mob se déplace, 0 sinon */
int deplacement(Mob * mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES] ){
	int mob_saut_max = saut_max[mob->id];
	
	do {
		
	int indice = 0;
	Mob * cases_libre[8] = { NULL } ;
	int i,j,randomPick;
	randomPick = 0;

	for(i= -1; i<=1; i++)
	{	for(j=-1; j<=1; j++)
		{	

        	if( ((((mob->x)+i>=0) && ((mob->y)+j>=0))&&(((mob->x)+i<TAILLE_PLATEAU) && ((mob->y)+j<TAILLE_PLATEAU))) ){ //case hors champ
            	
            	if( plateau_de_jeu[(mob->x)+i][(mob->y)+j]->id == 0){
						cases_libre[indice] = plateau_de_jeu[(mob->x)+i][(mob->y)+j];
						indice++;
					}
			}
		}
	}
	if (indice  != 0)
		randomPick = rand_a_b(0,indice);
	else{ 
		return 0;
	}


	while ( cases_libre[randomPick%8] == NULL ){
		randomPick++;
	}


    


	plateau_de_jeu[(cases_libre[randomPick%8])->x][(cases_libre[randomPick%8])->y]->id=(*mob).id; 
	
	plateau_de_jeu[(*mob).x][(*mob).y] = create_mob(0);
	plateau_de_jeu[(*mob).x][(*mob).y]->x = (*mob).x ;
	plateau_de_jeu[(*mob).x][(*mob).y]->y = (*mob).y ;
	mob->x=cases_libre[randomPick%8]->x;
	mob->y=cases_libre[randomPick%8]->y;
	mob_saut_max--;
	
	} while (mob_saut_max >0);
	
	return 1;      
}


/* Applique la règle pour la satiete*/
void tour(Mob * mob){
	mob->satiete = max(mob->satiete - metabolisme[mob->id] , 0 );
	
}

/*Coordonne les différentes fonctions relatives au jeu des mobs */
void ia_mob(Mob * mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * species[NB_SPECIES] ){
	if(!survie(mob, species))
	{	
		//Si l'individu ne survie pas
		plateau_de_jeu[mob->x][mob->y]=create_mob(0);
		plateau_de_jeu[mob->x][mob->y]->x = mob->x;
		plateau_de_jeu[mob->x][mob->y]->y = mob->y;	
		species[mob->id] = destroy_mob(*mob, species[mob->id]);
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


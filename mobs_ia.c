#include "main.h"

// problème, on passe à 12 ou 13 paramètres quand on considèrera toutes les espèces ...
void destroy_mob (Mob mob, Liste * liste_plancton, Liste * liste_corail, Liste * liste_bar, Liste * liste_thon )

{       Liste * liste_voulue=malloc(sizeof(Liste));              

        //On trouve la liste qui correspond à l'espece du mob à éliminer 
	
        if(mob.id==liste_plancton->mob.id)
                liste_voulue=liste_plancton;
        
        else if(mob.id==liste_corail->mob.id)
        {       liste_voulue= liste_corail;
        } 		       
        else if(mob.id=liste_thon->mob.id)
        {       liste_voulue= liste_thon;
        }																																																																																																																																																																																																																																																																																																																																																																																		
        else if(mob.id=liste_bar->mob.id)
        {       liste_voulue= liste_bar;
        }
        /*else if(mob.id=liste_pyranha->mob.id)
        {       liste_voulue= liste_pyranha;
        }
        else if(mob.id=liste_requin->mob.id)
        {       liste_voulue= liste_requin;
        }
        else if(mob.id=liste_baleine->mob.id)
        {       liste_voulue= liste_baleine;
        }
        else if(mob.id=liste_pont->mob.id)
        {       liste_voulue= liste_pont;
        }*/
        else return ;
	
	//On retire le mob de sa liste	
        if (liste_voulue==NULL||liste_voulue->nxt==NULL)
        {       liste_voulue==NULL;
                return ;
        }
        else
        {       Liste * elt=malloc(sizeof(Liste));
                elt=liste_voulue;      
                while(elt->nxt!=NULL)
                {
                       
                        if(elt->mob.x==mob.x && elt->mob.y==mob.y)
                        {       liste_voulue->nxt=liste_voulue->nxt->nxt;
                                return;                        
                        }
                        
 			else{	                      
                               liste_voulue=elt;       
                                elt=elt->nxt;
                        }
                        
                }
        }
              
}

	
int survie(Mob mob, Liste * liste_plancton, Liste * liste_corail, Liste * liste_bar, Liste * liste_thon )
{
	if(mob.satiete == 0 && (WORLD_TIME-mob.dernier_repas)>duree_survie[mob.id])
	{	printf("RIP petit mob\n");
		destroy_mob(mob, liste_plancton, liste_corail, liste_bar, liste_thon);
				
		return 0;
	} 
	return 1;
 
}


int reproduction(Mob mob);


void predation(Mob mob, Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste_plancton, Liste * liste_corail, Liste * liste_bar, Liste * liste_thon)
{	
	//problème: génération de la matrice à chaque appel de "prédation"
	//idée : mettre cette matrice en variable globale et l'initialiser qu'UNE seule fois au début du main, ou bien en faire un tableau constant 
	int eat_mat[12][12]={{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0}, {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	
	int i, j;
	Mob *proie = malloc(sizeof(Mob));
	proie=create_mob(0);
	
	/* Initialisation de la matrice de prédation 
	eat_mat[0][]={0}; //espece vide ne mange rien
	eat_mat[1]={0}; // plancton ne mange rien 
	eat_mat[2]={1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // corail
	eat_mat[3]={1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}; // bar
 	eat_mat[4]={1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //thon
	eat_mat[5]={1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //pollution
	eat_mat[6]={1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0}; //pyranha
	eat_mat[7]={1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0}; //requin
	eat_mat[8]={1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0}; //orque 
	eat_mat[9]={1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}; //baleine 
	eat_mat[10]={0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0}; //pêcheur
	eat_mat[11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //pont */ 
	
	for(i=-1; i<=1; i++)
	{	for(j=-1; j<=1; j++)
		{	
                        if(((((mob.x)+i>=0) && ((mob.y)+j>=0))&&(((mob.x)+i<TAILLE_PLATEAU) && ((mob.y)+j<TAILLE_PLATEAU)))) //case hors champ
			{
                                if(eat_mat[mob.id][plateau_de_jeu[(mob.x)+i][(mob.y)+j]->id]==1) //si on trouve une espèce commestible dans les cases adjacentes
                                {       
	        			if((taille[plateau_de_jeu[(mob.x)+i][(mob.y)+j]->id]>=taille[proie->id])&&(mob.satiete+taille[proie->id]<taille_du_bide[mob.id]))	//recherche de la proie de taille max
                                         {      //Affichage en rose de la (les) proie(s) potentielles
						afficher_point((mob.x)+i+1, (mob.y)+j+1, mobs_draw[5]);
	        				proie->x=plateau_de_jeu[(mob.x)+i][(mob.y)+j]->x;
                                                proie->y=plateau_de_jeu[(mob.x)+i][(mob.y)+j]->y;
                                                proie->id=plateau_de_jeu[(mob.x)+i][(mob.y)+j]->id;
						
                                               
                                                
	        			}
        	      	 	}      
                	 }
		}
	}
        if(proie->id!=0)
        {	
  
 		//La case de la proie prend les caractéristiques du mob	                    
                plateau_de_jeu[proie->x][proie->y]->id=mob.id;
		plateau_de_jeu[proie->x][proie->y]->derniere_reproduction=mob.derniere_reproduction;
                plateau_de_jeu[proie->x][proie->y]->satiete=mob.satiete+taille[proie->id]; 
		plateau_de_jeu[proie->x][proie->y]->dernier_repas=WORLD_TIME;
		
		//La case précedente du mob est remplacée par l'espece vide                 
		plateau_de_jeu[mob.x][mob.y]=create_mob(0);
		
		//Les coordonnées et caractéristiques du mob sont changées, nb : pas dans la liste de ce mob ... 	
		//Il faut que ce mob soit passé par ADRESSE	
		mob.x=proie->x;
		mob.y=proie->y;
               	mob.dernier_repas=WORLD_TIME;
		mob.satiete=plateau_de_jeu[proie->x][proie->y]->satiete;                
                	
		//On retire la proie de la liste correspondant à son espèce
           	destroy_mob(*proie, liste_plancton, liste_corail, liste_bar, liste_thon);	 
                      
        }       	        	
	


}

int deplacement(Mob mob);

int tour();

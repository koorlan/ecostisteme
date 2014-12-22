#include "main.h"


/*Retourne un entier compris entre a et b*/
int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}


int main(int argc, char const *argv[])
{
	start_graphics();
	//final_screen(6);
	//RECORD
	FILE *fPtr;
	fPtr=fopen("records.csv","w");

	if (fPtr == NULL)
	    printf("Error in opening file\n");
	
	//Variable d'arrêt de la simulation 
	int stop=key_F1;
	srand (time (NULL));
   	Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU];
	//=calloc((TAILLE_PLATEAU*TAILLE_PLATEAU), sizeof(Mob)) ;
  	
	// Compteur pour gérer les listes d'especes
  	int i = 0; 
	

	/***Initialisation du pêcheur***/
	//Variables de déplacement du pêcheur
	int x=0;
	int y=0;

	//0 pour le mode ecosysteme seul, 1 pour le mode joueur
	int mode_joueur=1;

	//Variable d'action du pêcheur
	int a;

	fisher pecheur;
	
	int mort_pecheur=0;

	//initialisation du pecheur 
	init_fisher(&pecheur, x, y, 1);

	//initialisation de la table des bonus 	
	int bonus_tab[8]={0};
	
	//1 pour la vision		
	bonus_tab[7]=1;

	init_grid(plateau_de_jeu);

	/***Initialisation des espèces***/
	//Génération des listes de mobs......................................................................................
   		
		
		/*Ordre de creation            Espece vide - Plancton -   Corail -   Bar -  Thon - Pollution
   		Correspondance des couleurs    WHITE -       LIGHTGREEN - LIGHTRED - CYAN - BLUE - RED    */
   	Liste * species[] = {NULL, init_mobs(1,10), init_mobs(2, 4), init_mobs(3,6), init_mobs(4, 5), init_mobs(5, 2), init_mobs(6, 4), init_mobs(7, 5), init_mobs(8, 2), init_mobs(9, 2)};



   	fprintf(fPtr,"%s","WORLD_TIME");

	//Génération des mobs sur le plateau de jeu..........................................................................	
	for (int i = 1; i <= NB_SPECIES; ++i)
	{
		spawn_list_animal_random(plateau_de_jeu, species[i]);
		printf("Il y a %d individus de l'espece %d \n", nombre_elts_liste(species[i]), i);
		fprintf(fPtr,",%d",i);
	}
	draw_grid(plateau_de_jeu, bonus_tab[7]);
	update_graphics(); 
	Mob * ptr=malloc(sizeof(Mob));
	Liste * elt=malloc(sizeof(Liste));
	WORLD_TIME=0;
	


	do
	{	printf("WOLRD_TIME : %d\n", WORLD_TIME);
		fprintf(fPtr,"\n%d", WORLD_TIME);

		/***Jeu du pêcheur***/		
		//Action du pêcheur.................................................................................................. 
		
	
		//Jeu du pĉheur tous les 10 tours d'écosystème
		if(WORLD_TIME % 10 == 0 && mode_joueur==1)
		{	
			//Le pecheur est tombé dans l'eau
			if(!case_valide(pecheur.x, pecheur.y, plateau_de_jeu))		
			{	
				if(plouf_hard_version(&pecheur, plateau_de_jeu, species))
				{	clear_screen();
					plouf_soft_version(&pecheur);
					draw_grid(plateau_de_jeu, bonus_tab[7]);
					stop=get_key();				
					update_graphics(); 		
									
				}		
				else
					mort_pecheur=1; 
				
			}	
			//Le pêcheur effectue un tour de jeu normal	
			else
			{	capitaliser_bonus(&pecheur, bonus_tab);
				pecheur.bridge=0;				
				clear_screen();
				draw_grid(plateau_de_jeu, bonus_tab[7]);
				afficher_point(pecheur.x, pecheur.y, color_RED);
				appliquer_bonus(&pecheur, bonus_tab);
				printf("pont construit %d\n", pecheur.bridge);				
				afficher_munitions(&pecheur);
				deplacement_pecheur(&pecheur, color_RED, plateau_de_jeu);
				//possibilité de pêcher 		
				a=choix_action(1);
				if(a=='o')
				{	//choix du materiel de peche (canne ou filet)
					//si le filet n'est pas débloqué, la canne à pêche est choisie par défaut 						
					if(bonus_tab[4]!=0)					
						a=choix_action(3);
					else
						a='c';	
					que_la_peche_commence(plateau_de_jeu, &pecheur, species, a);
				}	
				else if(pecheur.reserves!=0)
				{	//possibilité de construire le pont	
					a=choix_action(2);
					if(a=='o')
						construire_pont(plateau_de_jeu, &pecheur, species, bonus_tab);			
					
					//possibilité de rejeter un poisson dans l'eau 
					else if(pecheur.id_proie!=0)
					{	a=choix_action(4);		
						if(a=='o')
							relacher_poisson(plateau_de_jeu, &pecheur, species, bonus_tab);
					}				
				}
				
			
			}
		} 	
		
			if(!mort_pecheur)
			{
		/***Jeu de l'IA***/	
					
				draw_grid(plateau_de_jeu, bonus_tab[7]);
				
				for (int i = 1; i <= NB_SPECIES; ++i)
				{
					elt=species[i];
					while(elt->nxt !=NULL)
					{	
						ptr = &(elt->mob);
						ia_mob(ptr,plateau_de_jeu,species);
						elt = elt->nxt;							
					}	
					fprintf(fPtr,",%d",(nombre_elts_liste(species[i])*100)/(TAILLE_PLATEAU * TAILLE_PLATEAU) ) ;
				}	
				
				draw_grid(plateau_de_jeu, bonus_tab[7]);
				
				//usleep(10000);	
				
				WORLD_TIME++;
				//stop=get_key();	
			}
	
			
			}while( WORLD_TIME <= 1000 && !mort_pecheur);
	
	
		//Fermeture de la fenetre graphique	
		stop_graphics();
		//Fermeture du fichier d'acquisition des données
		fclose(fPtr);
	
		return 0;
	}			

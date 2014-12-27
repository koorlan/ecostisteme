#include "main.h"


/*Retourne un entier compris entre a et b*/
int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}


int main(int argc, char const *argv[])
{
	start_graphics();
	FILE *fPtr;
	fPtr=fopen("records.csv","w");

	if (fPtr == NULL)
	    printf("Error in opening file\n");
	
	//Variable d'arrêt de la simulation 
	int stop=key_F1;
	srand (time (NULL));
   	Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU];

  	
	// Compteur pour gérer les listes d'especes
  	int i = 0; 
	

	/***Initialisation du pêcheur***/
	//Variables de déplacement du pêcheur
	int x=0;
	int y=0;


	int x2=TAILLE_PLATEAU+1;
	int y2=TAILLE_PLATEAU+1;

	//Variable d'action du pêcheur
	//int a;

	fisher pecheur;
	fisher pecheur2;
	
	int mort_pecheur=0;
	int mort_pecheur2=0;

	//initialisation du pecheur 
	init_fisher(&pecheur, x, y, 1);
	init_fisher(&pecheur2, x2, y2, 2);
		
	//initialisation de la table des bonus 	
	int bonus_tab[8]={0};
	int bonus_tab2[8]={0};

	//1 pour la vision		
//	bonus_tab[7]=0;
//	bonus_tab2[7]=0;

	//choix du mode de jeu : 0 pour le mode ecosysteme seul, 1 pour le mode 1 joueur, 2 pour le mode 2 joueurs
	int mode_joueur=start_screen();
	clear_screen();
	if(!mode_joueur)
		bonus_tab[7]=1;
	

	init_grid(plateau_de_jeu);

	



	/***Initialisation des espèces***/
	//Génération des listes de mobs......................................................................................
   		
		
		/*Ordre de creation            Espece vide - Plancton -   Corail -   Bar -  Thon - Pollution
   		Correspondance des couleurs    WHITE -       LIGHTGREEN - LIGHTRED - CYAN - BLUE - RED    */
   	Liste * species[] = {NULL, init_mobs(1,5), init_mobs(2, 3), init_mobs(3,6), init_mobs(4, 3), init_mobs(5, 2), init_mobs(6, 4), init_mobs(7, 5), init_mobs(8, 2), init_mobs(9, 2)};



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
		
		//Jeu du pêcheur tous les 10 tours d'écosystème
		if(WORLD_TIME % 10 == 0 && mode_joueur!=0)
		{	
			jeu_du_pecheur(&pecheur, plateau_de_jeu, bonus_tab, &mort_pecheur, species);
			if(mode_joueur==2)
				jeu_du_pecheur(&pecheur2, plateau_de_jeu, bonus_tab2, &mort_pecheur2, species);	

		} 	
		
			if(!mort_pecheur&&!mort_pecheur2)
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

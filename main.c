#include "main.h"


/*Retourne un entier compris entre a et b*/
int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}


int main(int argc, char const *argv[])
{

	WORLD_TIME=2;
	start_graphics();
	//Variable d'arrêt de la simulation 
	int stop=key_F1;
	srand (time (NULL));
   	Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU] ;
  	// Compteur pour gérer les listes d'especes
  	int i = 0; 
	//Variables de déplacement du pêcheur
	int x=0;
	int y=0;
	//Variable d'action du pêcheur
	int a;
	init_grid(plateau_de_jeu);


	/***Initialisation des espèces***/
	//Génération des listes de mobs......................................................................................
   		
		
		/*Ordre de creation            Espece vide - Plancton -   Corail -   Bar -  Thon - Pollution
   		Correspondance des couleurs    WHITE -       LIGHTGREEN - LIGHTRED - CYAN - BLUE - RED    */
   	Liste * species[] = {NULL, init_mobs(1,9), init_mobs(2, 8), init_mobs(3, 5), init_mobs(4, 2), init_mobs(5, 1)};


	//Génération des mobs sur le plateau de jeu..........................................................................	
	for (int i = 1; i <= NB_SPECIES; ++i)
	{
		spawn_list_animal_random(plateau_de_jeu, species[i]);
		printf("Il y a %d individus de l'espece %d \n", nombre_elts_liste(species[i]), i);
	}
	draw_grid(plateau_de_jeu);
	Mob * ptr;
	Liste * elt;
	WORLD_TIME=1;
	do
	{	

	/***Jeu de l'IA***/		
	//Action du pêcheur.................................................................................................. 
			
		deplacement_pecheur(&x, &y, color_RED, plateau_de_jeu);
		a=choix_action();
		if(a=='o')
		{	printf("Je suis là\n");
		
		}		
		clear_screen();	
		afficher_point(x, y, color_RED);
		for (int i = 1; i <= NB_SPECIES; ++i)
		{
			elt=species[i];
			printf("%d\n", WORLD_TIME);

	//Survie.............................................................................................................
			
			while(elt->nxt !=NULL)
			{	
				
										
					
				elt->mob.satiete --;
				espece_consideree(i, mobs_draw[i]);	
				draw_grid(plateau_de_jeu);				
				stop=get_key();					
				afficher_point(elt->mob.x+1, elt->mob.y+1, mobs_draw[7]);
				//L'individu est mort				
				if(!survie(elt->mob, species)&&elt->nxt!=NULL)
				{	
					afficher_point(elt->mob.x+1, elt->mob.y+1, mobs_draw[7]);
					plateau_de_jeu[elt->mob.x][elt->mob.y]=create_mob(0);	
					draw_grid(plateau_de_jeu);
					afficher_point(x, y, color_RED);						
					//printf("L'individu est mort\n");
					stop=get_key();		
					elt=elt->nxt;	
				}
				//L'individu a survécu	
				else{
					//printf("L'individu a survécu\n");			
					draw_grid(plateau_de_jeu);
					afficher_point(x, y, color_RED);
					
					
				
	//Predation............................................................................................................ 
					if(elt->nxt!=NULL)
					{					
						ptr=&(elt->mob);
						//L'individu mange						
						if(predation(ptr, plateau_de_jeu, species))
						{	draw_grid(plateau_de_jeu);
							afficher_point(x, y,color_RED);							
							stop=get_key();
							elt=elt->nxt;
						}
					//Fin de prédation
						//l'individu n'a pas mangé						
						else
						{	//printf("L'individu n'a as mangé\n");	
							elt=elt->nxt;
												
						}
					}
				}	
			}	
			clear_screen();
			draw_grid(plateau_de_jeu);
				
		}
		WORLD_TIME++;
	
		//reproduction 

/*		spawn_list_of_mobs(plateau_de_jeu, liste_plancton);
		afficher_grille(plateau_de_jeu);
		stop=get_key();

		spawn_list_of_mobs(plateau_de_jeu, liste_corail);
		afficher_grille(plateau_de_jeu);
		stop=get_key();	
	
		spawn_list_of_mobs(plateau_de_jeu, liste_thon);
		afficher_grille(plateau_de_jeu);
		stop=get_key();		
	
		spawn_list_of_mobs(plateau_de_jeu, liste_pollution);
		afficher_grille(plateau_de_jeu);
		stop=get_key();	
	
		spawn_list_of_mobs(plateau_de_jeu, liste_bar);
		afficher_grille(plateau_de_jeu);
		stop=get_key();	
	
		afficher_grille(plateau_de_jeu);
		stop=get_key(); 						*/
		
		
		stop=get_key();	
		//clear_screen();
	
	}while(stop!=key_DOWN||WORLD_TIME<10);

	
/*	for (int i = 0; i < NB_SPECIES; ++i)
		{
			free(species[i]);
			species[i] = NULL ;
	
		}
*/
 	  //int tailleliste = nombre_elts_liste(liste_plancton);
	  //printf("taille liste : %d\n", tailleliste);
 	  //printf("Population de X = %d %% \n", (tailleliste *  100)/(TAILLE_PLATEAU * TAILLE_PLATEAU) );
	 //stop=get_key();
	
	//Fermeture de la fenetre graphique	
	stop_graphics();

	return 0;
}

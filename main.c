
#include "main.h"

/*Retourne un entier compris entre a et b*/
int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}

int main(int argc, char const *argv[])
{

	WORLD_TIME=0;
	start_graphics();
	int stop=key_F1;
	srand (time (NULL));
   	Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU] ;
  	// Compteur pour gérer les listes d'especes.
  
 	
	do
	{
	
	int i = 0; 
	
	init_grid(plateau_de_jeu);
   	Liste * species[] = {NULL, init_mobs(1,9), init_mobs(2, 8), init_mobs(3, 5), init_mobs(4, 2), init_mobs(5, 1)};

    

    //Dans l'ordre de creation      Plancton - Corail - Bar - Thon - Pollution
   	//Correspondance des couleurs LIGHTGREEN - LIGHTRED - CYAN - BLUE - MAGENTA
   	for (int i = 1; i <= NB_SPECIES; ++i)
	{
		spawn_list_animal_random(plateau_de_jeu,species[i]);
		printf("Il y a %d individus de l'espece %d \n", nombre_elts_liste(species[i]), i);
	}

	
	draw_grid(plateau_de_jeu);
	
	//Survie 
	WORLD_TIME=2; 
	
	
	for (int i = 1; i <= NB_SPECIES; ++i)
	{
		Liste * elt =species[i];
	
	while(elt->nxt !=NULL)
	{	

			afficher_point(elt->mob.x+1, elt->mob.y+1, mobs_draw[7]);	
			//if(!survie(elt->mob, liste_plancton, liste_corail, liste_bar, liste_thon));
			//printf("Il y a %d individus de l'espece corail avant survie\n", nombre_elts_liste(liste_corail));
			//printf("Je regarde le mob (main) MOB %d , %d\n",elt->mob.x,elt->mob.y ); 	
			printf("Mon mob de main id %d , coo : %d,%d \n",elt->mob.id, elt->mob.x, elt->mob.y );
			survie(elt->mob, species);
			//printf("Le premier element de ma liste corail : %d , %d \n",liste_corail->mob.x, liste_corail->mob.y );
			plateau_de_jeu[elt->mob.x][elt->mob.y]=create_mob(0);
			printf("Il reste %d elements de l'id %d \n", nombre_elts_liste(species[i]), i);	
			draw_grid(plateau_de_jeu);
			stop=get_key();
			//printf("Il y a %d individus de l'espece corail\n", nombre_elts_liste(liste_corail));		
			elt = elt->nxt;
			
	}

	}
	draw_grid(plateau_de_jeu);
			stop=get_key();

	

	//Predation pour chaque individu de la liste 
	/*Liste * elt = liste_corail;
	while(elt->nxt!=NULL)
	{	//Affichage en jaune du mob qui effectue prédation 
		afficher_point(elt->mob.x+1, elt->mob.y+1, mobs_draw[7]);	
		predation(elt->mob, plateau_de_jeu, liste_plancton, liste_corail, liste_bar, liste_thon);
		afficher_grille(plateau_de_jeu);
		
	
		stop=get_key();
		//Affichage sur le terminal de l'evolution de l'espèce plancton 			
		printf("Il y a %d individus de l'espece plancton\n", nombre_elts_liste(liste_plancton));
		elt=elt->nxt;	
	}
	
	elt= liste_bar;
	while(elt->nxt!=NULL)
	{	afficher_point(elt->mob.x+1, elt->mob.y+1, mobs_draw[7]);	
		predation(elt->mob, plateau_de_jeu, liste_plancton, liste_corail, liste_bar, liste_thon);
		afficher_grille(plateau_de_jeu);
		stop=get_key();
		elt=elt->nxt;	
	}
	*/
	
	//reproduction 

/*	spawn_list_of_mobs(plateau_de_jeu, liste_plancton);
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
	stop=get_key(); */
	
	for (int i = 0; i < NB_SPECIES; ++i)
	{
		free(species[i]);
		species[i] = NULL ;
	
	}

	stop=get_key();	
	//clear_screen();	
	}while(stop!=key_DOWN);


    	//int tailleliste = nombre_elts_liste(liste_plancton);

	   //printf("taille liste : %d\n", tailleliste);
   //printf("Population de X = %d %% \n", (tailleliste *  100)/(TAILLE_PLATEAU * TAILLE_PLATEAU) );


	//stop=get_key();
	
	stop_graphics();
	return 0;
}

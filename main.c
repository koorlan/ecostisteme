
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
  	
  
	do
	{
	clear_screen();
	initialiser_grille(plateau_de_jeu);
    	Liste * liste_plancton = init_mobs(1, 9);
    	Liste * liste_corail = init_mobs(2, 8);
    	Liste * liste_bar = init_mobs(3, 5);
	Liste * liste_thon = init_mobs(4, 2);
	Liste * liste_pollution =init_mobs(6, 1); 
    
	place_liste_animal_random(plateau_de_jeu,liste_plancton);
	place_liste_animal_random(plateau_de_jeu,liste_corail);
	place_liste_animal_random(plateau_de_jeu,liste_bar);
	place_liste_animal_random(plateau_de_jeu,liste_thon);
	place_liste_animal_random(plateau_de_jeu,liste_pollution);	
	afficher_grille(plateau_de_jeu);
	stop=get_key();	
	afficher_grille(plateau_de_jeu);
	printf("Il y a %d individus de l'espece plancton\n", nombre_elts_liste(liste_plancton));
	stop=get_key();
		
	/*Survie 
	WORLD_TIME=2; 
	Liste * elt =liste_corail;
	while(elt->nxt!=NULL)
	{	afficher_point(elt->mob.x+1, elt->mob.y+1, mobs_draw[7]);	
		if(!survie(elt->mob, liste_plancton, liste_corail, liste_bar, liste_thon));	
		{	plateau_de_jeu[elt->mob.x][elt->mob.y]=create_mob(0);	
			afficher_grille(plateau_de_jeu);
			stop=get_key();
			printf("Il y a %d individus de l'espece corail\n", nombre_elts_liste(liste_corail));		
			elt=elt->nxt;
		}
	}
	*/	

	

	//Predation pour chaque individu de la liste 
	Liste * elt = liste_corail;
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
	
	//à refaire 
/*	free(liste_plancton);
	free(liste_corail);
	free(liste_bar);
	free(liste_thon);
	free(liste_pollution); */
	}while(stop!=key_DOWN);


    	//int tailleliste = nombre_elts_liste(liste_plancton);

	   //printf("taille liste : %d\n", tailleliste);
   //printf("Population de X = %d %% \n", (tailleliste *  100)/(TAILLE_PLATEAU * TAILLE_PLATEAU) );


	//stop=get_key();
	
	stop_graphics();
	return 0;
}

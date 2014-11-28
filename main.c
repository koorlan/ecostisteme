
#include "main.h"

/*Retourne un entier compris entre a et b*/
int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}

int main(int argc, char const *argv[])
{


	start_graphics();
	int stop=key_F1;
	srand (time (NULL));
   	Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU] ;
  	
  
	do
	{
	clear_screen();
	initialiser_grille(plateau_de_jeu);
    	Liste * liste_plancton = init_mobs(1, 5);
    	Liste * liste_corail = init_mobs(2, 5);
    	Liste * liste_bar = init_mobs(3, 5);
	Liste * liste_thon = init_mobs(4, 2);
	Liste * liste_pollution =init_mobs(5, 1); 
    
	place_liste_animal_random(plateau_de_jeu,liste_plancton);
	place_liste_animal_random(plateau_de_jeu,liste_corail);
	place_liste_animal_random(plateau_de_jeu,liste_bar);
	place_liste_animal_random(plateau_de_jeu,liste_thon);
	place_liste_animal_random(plateau_de_jeu,liste_pollution);	


	spawn_list_of_mobs(plateau_de_jeu, liste_plancton);
	spawn_list_of_mobs(plateau_de_jeu, liste_corail);
	spawn_list_of_mobs(plateau_de_jeu, liste_bar);


	afficher_grille(plateau_de_jeu);
	update_graphics();
	stop=get_key();	
	free(liste_plancton);
	free(liste_corail);
	free(liste_bar);
	free(liste_thon);
	free(liste_pollution);
	}while(stop!=key_DOWN);
    	//int tailleliste = nombre_elts_liste(liste_plancton);


   //printf("taille liste : %d\n", tailleliste);
   //printf("Population de X = %d %% \n", (tailleliste *  100)/(TAILLE_PLATEAU * TAILLE_PLATEAU) );


	//stop=get_key();
	
	stop_graphics();
	return 0;
}

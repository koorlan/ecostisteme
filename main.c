
#include "main.h"

int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

int main(int argc, char const *argv[])
{
	
	srand (time (NULL));
    Map plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU] ;
    initialiser_grille(plateau_de_jeu);
    int i = 0 ;

    Liste * liste_plancton = init_mobs(0, 10);
    Liste * liste_corail = init_mobs(1, 5);
    Liste * liste_bar = init_mobs(2, 5);
    
	place_liste_animal_random(plateau_de_jeu,liste_plancton);
	place_liste_animal_random(plateau_de_jeu,liste_corail);
	place_liste_animal_random(plateau_de_jeu,liste_bar);


	spawn_list_of_mobs(plateau_de_jeu, liste_plancton);
	spawn_list_of_mobs(plateau_de_jeu, liste_corail);
	spawn_list_of_mobs(plateau_de_jeu, liste_bar);


	afficher_grille(plateau_de_jeu);
    int tailleliste = nombre_elts_liste(liste_plancton);


   //printf("taille liste : %d\n", tailleliste);
   //printf("Population de X = %d %% \n", (tailleliste *  100)/(TAILLE_PLATEAU * TAILLE_PLATEAU) );

	return 0;
}
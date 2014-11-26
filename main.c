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

    Liste * liste_thon = malloc(sizeof(Liste));
    liste_thon->nxt=NULL; 
    
    Mob * thon = malloc(sizeof(Mob));

    thon = create_mob(0);
    for (int i = 0; i < (10 * (TAILLE_PLATEAU * TAILLE_PLATEAU) / 100 ); ++i)
    {
     liste_thon = ajouterEnTete(liste_thon, *thon );     // modif le 20 pour le % age de poop
    }
   
	place_liste_animal_random(plateau_de_jeu,liste_thon);

	spawn_list_of_mobs(plateau_de_jeu, liste_thon);


	afficher_grille(plateau_de_jeu);
    int tailleliste = nombre_elts_liste(liste_thon);


   printf("taille liste : %d\n", tailleliste);
   printf("Population de X = %d %% \n", (tailleliste *  100)/(TAILLE_PLATEAU * TAILLE_PLATEAU) );

	return 0;
}
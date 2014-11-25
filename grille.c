#include "main.h"

void initialiser_grille(char * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]){
	int i=0;
	int j=0;
	for (int i = 0; i < TAILLE_PLATEAU ; i++)
	{
		for (int j = 0; j < TAILLE_PLATEAU ; j++)
		{	
			
			plateau[i][j] = ". " ;
		}

	}
	
return;
}

void afficher_grille(char *plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
   int i=0;
	int j=0;
	for (int i = 0; i < TAILLE_PLATEAU; ++i)
	{
		for (int j = 0; j < TAILLE_PLATEAU; ++j)
		{
			printf("%s",plateau[i][j]); 
		}
		printf("\n");
	}
	
return;
}

void place_liste_animal_random(char * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU],Liste * listeMob){
    int i = 0;
    int j = 0;
    int tailleliste = nombre_elts_liste(listeMob);
    while(listeMob->nxt != NULL) {
		do {
		i = rand_a_b(0,TAILLE_PLATEAU);
		j = rand_a_b(0,TAILLE_PLATEAU);

		} while( !isPlaceFree(plateau,i,j));

		listeMob->mob.x = i;
		listeMob->mob.y = j;

		plateau[i][j] = "X " ;
    	
    	
    	listeMob = listeMob->nxt;
    }
	return;
}

int isPlaceFree (char * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int a , int b){
	return (!strcmp(plateau[a][b],". ") );
}

int spawn_mob(char * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Mob mob){
	int i = 0 ;
	int j = 0 ;

	for (int i = -1; i < 1; ++i)
	{
		for (int j = -1; j < 1; ++j)
			{
				if ((mob.x + i >0 && mob.y + j >0) && (mob.x < TAILLE_PLATEAU && mob.y < TAILLE_PLATEAU) && isPlaceFree(plateau,(mob.x + i ),(mob.y + j))){
					printf("Jefais sa %d  %d  %d %d\n",i , j , mob.x +i , mob.y +j);
					plateau[mob.x +i][mob.y +j] = "X " ;

					
				}

			}	
	}

	return -1;


}
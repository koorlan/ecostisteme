#include "main.h"

char * mobs_draw[20]={"X ","O ","$ "};


void initialiser_grille(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]){
	int i=0;
	int j=0;
	for (int i = 0; i < TAILLE_PLATEAU ; i++)
	{
		for (int j = 0; j < TAILLE_PLATEAU ; j++)
		{	
			plateau[i][j].mob = NULL;
			plateau[i][j].content = ". " ;
		}

	}
	
return;
}

void afficher_grille(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    int i=0;
	int j=0;
	for (int i = 0; i < TAILLE_PLATEAU; ++i)
	{
		for (int j = 0; j < TAILLE_PLATEAU; ++j)
		{
			printf("%s",plateau[i][j].content); 
		}
		printf("\n");
	}
	
return;
}

void place_liste_animal_random(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU],Liste * listeMob){
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

		plateau[i][j].mob = &(listeMob->mob);
		plateau[i][j].content = mobs_draw[listeMob->mob.id] ;
    	
    	
    	listeMob = listeMob->nxt;
    }
	return;
}

int isPlaceFree (Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int a , int b){
	return (plateau[a][b].mob == NULL);
}

int spawn_mob(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste ){
	ListeCase *  free_place_list = malloc(sizeof(Liste));
	free_place_list = free_neighboor_case_list(plateau, liste->mob);
	if (free_place_list->nxt == NULL)
	{
		
		free(free_place_list);
		return -1;
	}
	
	int randomPick = rand_a_b(0,nombre_elts_listeCase(free_place_list));
	
	int i = 0;
	while(i != randomPick){
		free_place_list = free_place_list->nxt;
		i++;
	}
	liste = ajouterEnTete(liste, *(create_mob(liste->mob.id))) ;
	plateau[free_place_list->x][free_place_list->y].content = mobs_draw[liste->mob.id] ;
	free(free_place_list);
    return 1;
}


void spawn_list_of_mobs(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste ){
	
	while (liste->nxt != NULL)
	{	
		
		spawn_mob(plateau, liste);
		liste = liste->nxt;
	}

	
	
	return ;

}

ListeCase * free_neighboor_case_list(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Mob mob) {
	ListeCase * free_place_list = malloc(sizeof(Liste));
	free_place_list->nxt = NULL;
	//printf("Mon Mob est en %d %d \n", mob.x, mob.y );
	for (int i = -1 ; i <= 1; ++i)
	{
		
		for (int j = -1 ; j <= 1; ++j)
			{

				if ((mob.x + i >= 0 && mob.y + j >= 0) && (mob.x <= TAILLE_PLATEAU && mob.y <= TAILLE_PLATEAU) && isPlaceFree(plateau,(mob.x + i ),(mob.y + j))){
					//printf("J'ajoute en tete ! %d %d \n",i,j);
					free_place_list = ajouterEnTeteCase(free_place_list,mob.x + i,mob.y + j);
					
				}

			}	
	}
return free_place_list;
}
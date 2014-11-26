#include "main.h"
#include "eco.h"


couleurs mobs_draw[20]={color_WHITE, color_BLUE, color_MAGENTA, color_BLACK};


//Initialisation de la map vide
void initialiser_grille(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]){
	int i=0;
	int j=0;
	for (int i = 0; i < TAILLE_PLATEAU ; i++)
	{
		for (int j = 0; j < TAILLE_PLATEAU ; j++)
		{	
			plateau[i][j].mob = create_mob(0);
			plateau[i][j].mob->x = i ;
			plateau[i][j].mob->y = j ;
			plateau[i][j].coul=mobs_draw[0] ;
		}
	}
	return;
}


void afficher_grille(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) 
{
	int i=0;
	int j=0;
	affiche_grille();
	for (int i = 0; i < TAILLE_PLATEAU; ++i)
	{
		for (int j = 0; j < TAILLE_PLATEAU; ++j)
		{
			afficher_point(i+1, j+1, plateau[i][j].coul);
		}
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
		free(plateau[i][j].mob);
		plateau[i][j].mob = &(listeMob->mob);
		plateau[i][j].coul = mobs_draw[(listeMob->mob).id] ;
    	
    	
    	listeMob = listeMob->nxt;
    }
	return;
}

int isPlaceFree (Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int a , int b){
	return (plateau[a][b].mob->id == 0);
}

int spawn_mob(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste ){
	Liste *  free_place_list = malloc(sizeof(Liste));
	free_place_list = free_neighboor_case_list(plateau, liste->mob);
	if (free_place_list->nxt == NULL)
	{
		
		free(free_place_list);
		return -1;
	}
	
	int randomPick = rand_a_b(0,nombre_elts_liste(free_place_list));
	
	int i = 0;
	while(i != randomPick){
		free_place_list = free_place_list->nxt;
		i++;
	}
	//Afaire l'accrochage a la liste

	//On free la ou on etait pou accueilir le mob
	free(plateau[free_place_list->mob.x][free_place_list->mob.y].mob); 

	plateau[free_place_list->mob.x][free_place_list->mob.y].mob = create_mob(liste->mob.id);
	
	plateau[free_place_list->mob.x][free_place_list->mob.y].coul = mobs_draw[liste->mob.id] ;
	
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

Liste * free_neighboor_case_list(Map plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Mob mob) 
{
	Liste * free_place_list = malloc(sizeof(Liste));
	free_place_list->nxt = NULL;
	//printf("Mon Mob est en %d %d \n", mob.x, mob.y );
	for (int i = -1 ; i <= 1; ++i)
	{
		
		for (int j = -1 ; j <= 1; ++j)
			{

				if ((mob.x + i >= 0 && mob.y + j >= 0) && (mob.x + i < TAILLE_PLATEAU && mob.y + j < TAILLE_PLATEAU) && isPlaceFree(plateau,(mob.x + i ),(mob.y + j))){
					//printf("J'ajoute en tete ! %d %d \n",i,j);
					free_place_list = ajouterEnTete(free_place_list,*(plateau[mob.x + i][mob.y + j].mob));
				}

			}	
	}
	return free_place_list;
}

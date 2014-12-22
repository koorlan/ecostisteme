#include "main.h"
#include "eco.h"
#include "pont.h"


//Initialisation de la map vide
void init_grid(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU])
{
	int i=0;
	int j=0;
	for (int i = 0; i < TAILLE_PLATEAU ; i++)
	{
		for (int j = 0; j < TAILLE_PLATEAU ; j++)
		{	
			plateau[i][j] = create_mob(0); //Mob d'id=0 -> espece vide
			plateau[i][j]->x = i ;
			plateau[i][j]->y = j ;
		
		}
	}
	return;
}

/* Affichage de la Map dans une fenêtre graphique */
void draw_grid(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int mode)
{
	int i=0;
	int j=0;
	int a;
	if(mode!=0)
		affiche_grille();
	for (int i = 0; i < TAILLE_PLATEAU; ++i)
	{
		for (int j = 0; j < TAILLE_PLATEAU; ++j)
		{	/*if(plateau[i][j]->id==11)
				draw_pont(i+1, j+1, mobs_draw[11]);*/

			//mode aveugle
			if(mode==0)
			{	if(plateau[i][j]->id==11)
					draw_pont(i+1, j+1, mobs_draw[11]);
				else
				{	a=rand()%(2)+1;
					switch (a)
					{	case 1 : 	
							set_drawing_color(color_BLUE);
							draw_rectangle_full(M1+(i+1)*(WINDOW_WIDTH-2*M1)/N, M2+(j+1)*(WINDOW_HEIGHT-2*M2)/N, M1+(i)*(WINDOW_WIDTH-2*M1)/N, M2+(j)*(WINDOW_HEIGHT-2*M2)/N);
							break;
						case 2 : 
							set_drawing_color(color_LIGHTBLUE);
							draw_rectangle_full(M1+(i+1)*(WINDOW_WIDTH-2*M1)/N, M2+(j+1)*(WINDOW_HEIGHT-2*M2)/N, M1+(i)*(WINDOW_WIDTH-2*M1)/N, M2+(j)*(WINDOW_HEIGHT-2*M2)/N);
							break;
					}
				}
			}
			//mode vision 
			else			
			{		
				if(plateau[i][j]->id!=11)
					afficher_point(i+1, j+1, mobs_draw[plateau[i][j]->id]);
				else 
					draw_pont(i+1, j+1, mobs_draw[11]);
			}		
		}
	}
	
	return;
}

/* Reçoit une liste de Mobs déjà générés et leur attribue une place sur la Map */
void spawn_list_animal_random(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU],Liste * listeMob)
{
    int i = 0;
    int j = 0;
    int tailleliste = nombre_elts_liste(listeMob);
	    while(listeMob->nxt != NULL) {
		do {
		i = rand_a_b(0,TAILLE_PLATEAU);
		j = rand_a_b(0,TAILLE_PLATEAU);

		} while(!isPlaceFree(plateau,i,j)); //Tant que la case de coordonnées (i,j) n'est pas disponible, trouver d'autres coordonnées

		listeMob->mob.x = i;	
		listeMob->mob.y = j;
		//free(plateau[i][j]);
		//printf("Spaw: ID : %d " liste->mob.id);
		plateau[i][j] = &(listeMob->mob);
    		listeMob = listeMob->nxt;
    }
	
}


int isPlaceFree (Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int a , int b)
{
	return (plateau[a][b]->id == 0);
}


int spawn_mob(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste )
{
	Liste * free_place_list = malloc(sizeof(Liste));
	free_place_list = free_neighboor_case_list(plateau, &(liste->mob));
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
	
	free(plateau[free_place_list->mob.x][free_place_list->mob.y]); 
	plateau[free_place_list->mob.x][free_place_list->mob.y] = create_mob(liste->mob.id);
	
	//libération mémoire	
	destroy_list(&free_place_list);		
	free(free_place_list);
	free_place_list=NULL;
    return 1;
}


void spawn_list_of_mobs(Mob *  plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste ){
	
	while (liste->nxt != NULL)
	{	
		
		spawn_mob(plateau, liste);
		liste = liste->nxt;
	}

}

Liste * free_neighboor_case_list(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Mob * mob) 
{
	Liste * free_place_list = malloc(sizeof(Liste));
	free_place_list->nxt = NULL;
	//printf("Mon Mob est en %d %d \n", mob.x, mob.y );
	for (int i = -1 ; i <= 1; ++i)
	{
		
		for (int j = -1 ; j <= 1; ++j)
			{

				if ((mob->x + i >= 0 && mob->y + j >= 0) && (mob->x + i < TAILLE_PLATEAU && mob->y + j < TAILLE_PLATEAU) && isPlaceFree(plateau,(mob->x + i ),(mob->y + j))){
					free_place_list = ajouterEnTete(free_place_list,*(plateau[mob->x + i][mob->y + j]));
				}

			}	
	}
	return free_place_list;
}

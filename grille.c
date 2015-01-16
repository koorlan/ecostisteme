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
		{update_graphics();
		affiche_grille();  //uncomment for smooth grid
	}
	for (int i = 0; i < TAILLE_PLATEAU; ++i)
	{
		for (int j = 0; j < TAILLE_PLATEAU; ++j)
		{	/*if(plateau[i][j]->id==11)
				draw_square(i+1, j+1, mobs_draw[11]);*/

			//mode aveugle
			if(mode==0)
			{	if(plateau[i][j]->id==11)
					draw_square(i+1, j+1, mobs_draw[11]);
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
				switch (plateau[i][j]->id)
				{
				case 0:
						draw_square(i+1, j+1, mobs_draw[plateau[i][j]->id]);
						break;

				case 11:
						draw_square(i+1, j+1, mobs_draw[11]);
						break;
				case 12:
						draw_square(i+1, j+1, mobs_draw[11]);
						break;		
				default:
						afficher_point(i+1, j+1, mobs_draw[plateau[i][j]->id]);
						break;
				}
			}		
		}
	}
	
	return;
}

void spawn_island(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]){
	int nb_island = 3;
	int radius;
	while(nb_island != 0){
		radius = rand_a_b(2,8);
	//int a = rand_a_b(TAILLE_PLATEAU /2  - 30,TAILLE_PLATEAU /2 + 30);
	//int b = rand_a_b(TAILLE_PLATEAU /2 - 30,TAILLE_PLATEAU /2 + 30);
	//int a = rand_a_b(radius,TAILLE_PLATEAU-radius);
	//int b = rand_a_b(radius,TAILLE_PLATEAU-radius);
	int a = rand_a_b(TAILLE_PLATEAU /2 - radius,TAILLE_PLATEAU /2 + radius);
	int b = rand_a_b(TAILLE_PLATEAU /2 - radius,TAILLE_PLATEAU /2 + radius);

	for (int i = -radius; i <= radius	; ++i)
	{
		for (int j = -radius; j <= radius; ++j)
		{
			if(i*i+j*j <= radius*radius) {
			plateau[i+a][j+b] = create_mob(12);
			plateau[i+a][j+b]->x = i+a;
			plateau[i+a][j+b]->y = j+b;
			
			}
			if(rand_a_b(1,5) >= 4) {
			 plateau[i+a][j+b] = create_mob(12);
			plateau[i+a][j+b]->x = i+a;
			plateau[i+a][j+b]->y = j+b;
			
			} 
		}
	}

	nb_island--;
	}

/*	for (int i = 0; i < TAILLE_PLATEAU; i+=3)
	{
		radius = 3;
		
		for (int j = -radius; j <= radius	; ++j)
		{
		for (int k = -radius; k <= radius; ++k)
			{
			if(k*k+j*j <= radius*radius ) {
			/*plateau[i+j][k] = create_mob(12);
			plateau[i+j][k]->x = i+j;
			plateau[i+j][k]->y = k; */

/*			plateau[j][i+k] = create_mob(12);
			plateau[j][i+k]->x = j;
			plateau[j][i+k]->y = i+k; 

			}
			
			}
		}  */


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

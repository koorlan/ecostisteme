#include "main.h"
#include "eco.h"
#include "pont.h"


//Initialisation de la map vide
void init_grid(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU])
{
	int i=0;
	int j=0;
	for (i = 0; i < TAILLE_PLATEAU ; i++)
	{
		for (j = 0; j < TAILLE_PLATEAU ; j++)
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
	if(mode!=0)
		{//update_graphics();
		set_drawing_color(mobs_draw[0]); 
		affiche_grille(); 
	}
	for (i = 0; i < TAILLE_PLATEAU; ++i)
	{
		for (j = 0; j < TAILLE_PLATEAU; ++j)
		{	
			//mode aveugle
			if(mode==0)
			{	if((plateau[i][j]->id==11)||(plateau[i][j]->id==12))
					draw_square(i+1, j+1, mobs_draw[plateau[i][j]->id]);
				else
				{	
					draw_square(i+1,j+1, (rand_a_b(30,47)<<24)+(rand_a_b(27,72)<<16)+(rand_a_b(139,206)<<8));
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
						draw_square(i+1, j+1, mobs_draw[12]);
						break;		
				default:
						draw_square(i+1, j+1, mobs_draw[0]);
						afficher_point(i+1, j+1, mobs_draw[plateau[i][j]->id]);
						break;
				}
			}		
		}
	}
	
	return;
}

/*Affichage de l'île sur le plateau de jeu*/
void spawn_island(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]){
	int nb_island = 3;
	int radius;
	while(nb_island != 0){
		radius = rand_a_b(2,8);
	int a = rand_a_b(TAILLE_PLATEAU /2 - radius,TAILLE_PLATEAU /2 + radius);
	int b = rand_a_b(TAILLE_PLATEAU /2 - radius,TAILLE_PLATEAU /2 + radius);

	for (int i = -radius; i <= radius	; ++i)
	{
		for (int j = -radius; j <= radius; ++j)
		{
			if(i*i+j*j <= radius*radius) {
			plateau[i+a][j+b] = create_mob(12);
			plateau[i+a][j+b]->id = 12;
			plateau[i+a][j+b]->x = i+a;
			plateau[i+a][j+b]->y = j+b;
			
			}
			if(rand_a_b(1,5) >= 4) {
			plateau[i+a][j+b] = create_mob(12);
			plateau[i+a][j+b]->id = 12;
			plateau[i+a][j+b]->x = i+a;
			plateau[i+a][j+b]->y = j+b;
			
			} 
		}
	}

	nb_island--;
	}

}


/* Reçoit une liste de Mobs déjà générés et leur attribue une place sur la Map */
void spawn_list_animal_random(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU],Liste * listeMob)
{
    int i = 0;
    int j = 0;
	    while(listeMob->nxt != NULL) {
		do {
		i = rand_a_b(0,TAILLE_PLATEAU);
		j = rand_a_b(0,TAILLE_PLATEAU);

		} while(!isPlaceFree(plateau,i,j)); //Tant que la case de coordonnées (i,j) n'est pas disponible, trouver d'autres coordonnées

		listeMob->mob.x = i;	
		listeMob->mob.y = j;
		plateau[i][j]->x = i;
		plateau[i][j]->y = j;
		plateau[i][j] = &(listeMob->mob);
		plateau[i][j]->id = listeMob->mob.id;
    	listeMob = listeMob->nxt;
    }
	
}

/*Retourne 1 sur la case de coordonnées (a, b) est libre*/
int isPlaceFree (Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int a , int b)
{
	return (plateau[a][b]->id == 0);
}


/*Retourne une liste de cases disponibles adjacentes à un Mob*/
Liste * free_neighboor_case_list(Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Mob * mob) 
{
	Liste * free_place_list = malloc(sizeof(Liste));
	free_place_list->nxt = NULL;
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

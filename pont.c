#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "pont.h"



/*Selection de coordonnées valides (où il est possible de construire le pont) pour l'apparition du pont (cas où la pos du pecheur rend la construction du pont impossible non géré)*/
void spawn_pont(int x_pecheur, int y_pecheur, int *x_pont, int *y_pont, Mob * plateau[][TAILLE_PLATEAU])
{	int i, j;
	for(i=-1; i<=1; i++)
	{	for(j=-1;j<=1;j++)
		{	if( ((x_pecheur+i>=1 && x_pecheur+i<=TAILLE_PLATEAU) && (y_pecheur+j>=1 && y_pecheur+j<=TAILLE_PLATEAU)) && (plateau[x_pecheur+i-1][y_pecheur+j-1]->id != 11))
			{	*x_pont=x_pecheur+i;
				*y_pont=y_pecheur+j;
				return;			
			}
		}
	}
}


/*Atteste de la validité d'une case lors du déplacement du pont*/
int case_valide_pont(int x_pont, int y_pont, int x_pecheur, int y_pecheur, Mob * plateau[][TAILLE_PLATEAU])
{	return (case_valide_peche(x_pont, y_pont, x_pecheur, y_pecheur,plateau) && (plateau[x_pont-1][y_pont-1]->id != 11));
		
}


/*Selection par le joueur de la position du pont*/
void place_pont (int x_pecheur, int y_pecheur, int *x_pont, int *y_pont, Mob * plateau[][TAILLE_PLATEAU], int bonus_tab[], couleurs coul)
{	int pont=0;
	while(pont!=key_ENTER)
	{	switch (pont)
		{	case key_RIGHT:						
				if(case_valide_pont(*x_pont+1, *y_pont, x_pecheur, y_pecheur, plateau))
				{	
					if(bonus_tab[7]==1)
					{	draw_square(*x_pont, *y_pont, color_WHITE);
						afficher_point(*x_pont, *y_pont,  mobs_draw[plateau[*x_pont-1][*y_pont-1]->id]);					}					
					else
						draw_square(*x_pont, *y_pont, color_BLUE);
									
					(*x_pont)++;
				}				
				break;
		
			case key_LEFT : 
				if(case_valide_pont(*x_pont-1, *y_pont, x_pecheur, y_pecheur, plateau))
				{	if(bonus_tab[7]==1)
					{	draw_square(*x_pont, *y_pont, color_WHITE);
						afficher_point(*x_pont, *y_pont,  mobs_draw[plateau[*x_pont-1][*y_pont-1]->id]);					}
					else
					{	
						draw_square(*x_pont, *y_pont, color_BLUE);
					}
					
					(*x_pont)--;
				}			
				break;
			case key_UP :
				if(case_valide_pont(*x_pont, *y_pont+1, x_pecheur, y_pecheur, plateau))				
				{	if(bonus_tab[7]==1)
					{	draw_square(*x_pont, *y_pont, color_WHITE);
						afficher_point(*x_pont, *y_pont,  mobs_draw[plateau[*x_pont-1][*y_pont-1]->id]);					}
					else
						draw_square(*x_pont, *y_pont, color_BLUE);
					
					(*y_pont)++;
				}				
				break;
			case key_DOWN :
				if(case_valide_pont(*x_pont, *y_pont-1, x_pecheur, y_pecheur, plateau))				
				{	if(bonus_tab[7]==1)
					{	draw_square(*x_pont, *y_pont, color_WHITE);
						afficher_point(*x_pont, *y_pont,  mobs_draw[plateau[*x_pont-1][*y_pont-1]->id]);					}
					else
						draw_square(*x_pont, *y_pont, color_BLUE);
				
					(*y_pont)--;
				}				
				break;
			default :
				break;
		}
		draw_square(*x_pont, *y_pont, mobs_draw[11]); 
		update_graphics();
		pont=get_key();		
	}
}



/*Gestion des fonctions relatives à la construction du pont*/
void construire_pont(Mob * plateau[][TAILLE_PLATEAU], fisher * pecheur, Liste * species[], int bonus_tab[])
{	int x_pont=0, y_pont=0;
	int stop;	
	Mob pont ;
	set_drawing_color(color_WHITE);
	draw_string(M1, M2/2, "Voulez-vous construire le pont? (o)ui (n)on\n");
	spawn_pont(pecheur->x, pecheur->y, &x_pont, &y_pont, plateau);
	draw_square(x_pont, y_pont, mobs_draw[11]);
	place_pont(pecheur->x, pecheur->y, &x_pont, &y_pont, plateau, bonus_tab, mobs_draw[11]);
	update_graphics();
	
	//On détruit l'éspèce présente dans la case ou le pont a été construit	
	if(plateau[x_pont-1][y_pont-1]->id!=0)
	{	species[plateau[x_pont-1][y_pont-1]->id] = destroy_mob(*plateau[x_pont-1][y_pont-1], species[plateau[x_pont-1][y_pont-1]->id]);
	}	
	plateau[x_pont-1][y_pont-1]->id=11;
	plateau[x_pont-1][y_pont-1]->x=x_pont-1;
	plateau[x_pont-1][y_pont-1]->y=y_pont-1;
	plateau[x_pont-1][y_pont-1]->satiete=0;
	plateau[x_pont-1][y_pont-1]->dernier_repas=0;
	plateau[x_pont-1][y_pont-1]->derniere_reproduction=0;
	pecheur->reserves--;
	pecheur->bridge++;	
}

 	

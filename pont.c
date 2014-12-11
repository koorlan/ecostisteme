#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "pont.h"



/*Selection de coordonnées valides (où il est possible de construire le pont) pour l'apparition du pont (cas où la pos du pecheur rend la construction du pont impossible non géré)*/
void spawn_pont(int x_pecheur, int y_pecheur, int *x_pont, int *y_pont, Mob * plateau[][TAILLE_PLATEAU])
{	int i, j;
	for(i=-1; i<=1; i++)
	{	for(j=-1;j<=1;j++)
		{	if( ((x_pecheur+i>=1 && x_pecheur+i<=30) && (y_pecheur+j>=1 && y_pecheur+j<=30)) && (plateau[x_pecheur+i-1][y_pecheur+i-1]->id != 11))
			{	*x_pont=x_pecheur+i;
				*y_pont=y_pecheur+j;
				return;			
			}
		}
	}
}

/*Affichage du pont*/
void draw_pont(int x, int y, couleurs coul)
{		
	set_drawing_color(coul);
	set_fill_color(coul);
	draw_rectangle_full(M1+x*(639-2*M1)/N-1, M2+y*(479-2*M2)/N-1, M1+(x-1)*(639-2*M1)/N+1, M2+(y-1)*(479-2*M2)/N+1);

}

/*Atteste de la validité d'une case lors du déplacement du pont*/
int case_valide_pont(int x_pont, int y_pont, int x_pecheur, int y_pecheur, Mob * plateau[][TAILLE_PLATEAU])
{	return (case_valide_peche(x_pont, y_pont, x_pecheur, y_pecheur) && (plateau[x_pont-1][y_pont-1]->id != 11));
		
}


/*Selection par le joueur de la position du pont*/
void place_pont (int x_pecheur, int y_pecheur, int *x_pont, int *y_pont, Mob * plateau[][TAILLE_PLATEAU])
{	int pont=0;
	while(pont!=key_ENTER)
	{	switch (pont)
		{	case key_RIGHT:						
				if(case_valide_pont(*x_pont+1, *y_pont, x_pecheur, y_pecheur, plateau))
				{	draw_pont(*x_pont, *y_pont, color_WHITE);
					afficher_point(*x_pont, *y_pont,  mobs_draw[plateau[*x_pont-1][*y_pont-1]->id]);
									
					(*x_pont)++;
				}				
				break;
		
			case key_LEFT : 
				if(case_valide_pont(*x_pont-1, *y_pont, x_pecheur, y_pecheur, plateau))
				{	draw_pont(*x_pont, *y_pont, color_WHITE);
					afficher_point(*x_pont, *y_pont, mobs_draw[plateau[*x_pont-1][*y_pont-1]->id]);
					(*x_pont)--;
				}			
				break;
			case key_UP :
				if(case_valide_pont(*x_pont, *y_pont+1, x_pecheur, y_pecheur, plateau))				
				{	draw_pont(*x_pont, *y_pont, color_WHITE);
					afficher_point(*x_pont, *y_pont,  mobs_draw[plateau[*x_pont-1][*y_pont-1]->id]);
					(*y_pont)++;
				}				
				break;
			case key_DOWN :
				if(case_valide_pont(*x_pont, *y_pont-1, x_pecheur, y_pecheur, plateau))				
				{	draw_pont(*x_pont, *y_pont, color_WHITE);
					afficher_point(*x_pont, *y_pont,  mobs_draw[plateau[*x_pont-1][*y_pont-1]->id]);
					(*y_pont)--;
				}				
				break;
			default :
				break;
		}
		draw_pont(*x_pont, *y_pont, color_LIGHTBLUE); 
		update_graphics();
		pont=get_key();		
	}
}


/*Gestion des fonctions relatives à la construction du pont*/
void construire_pont(int x_pecheur, int y_pecheur, Mob * plateau[][TAILLE_PLATEAU], Mob * pecheur, Liste * species[])
{	int x_pont=0, y_pont=0;
	int stop;	
	Mob pont;
	spawn_pont(x_pecheur, y_pecheur, &x_pont, &y_pont, plateau);
	draw_pont(x_pont, y_pont, color_LIGHTBLUE);
	place_pont(x_pecheur, y_pecheur, &x_pont, &y_pont, plateau);
	update_graphics();
	
	//On détruit l'éspèce présente dans la case ou le pont a été construit	
	if(plateau[x_pont-1][y_pont-1]->id!=0)
	{	destroy_mob(*plateau[x_pont-1][y_pont-1], species[plateau[x_pont-1][y_pont-1]->id]);
	}	
	plateau[x_pont-1][y_pont-1]->id=11;
	plateau[x_pont-1][y_pont-1]->x=x_pont-1;
	plateau[x_pont-1][y_pont-1]->y=y_pont-1;
	plateau[x_pont-1][y_pont-1]->satiete=0;
	plateau[x_pont-1][y_pont-1]->dernier_repas=0;
	plateau[x_pont-1][y_pont-1]->derniere_reproduction=0;

	
		
	stop=get_key();
}



#include "canne.h"


/*Atteste de la validité d'une case lors du déplacement de la canne à pêche*/
int case_valide_peche(int x_canne, int y_canne, int x2, int y2,Mob * plateau[][TAILLE_PLATEAU])
{	int dx = x_canne-x2;
	int dy = y_canne-y2;
	return ( ( (x_canne>=1 && x_canne<=TAILLE_PLATEAU) && (y_canne>=1 && y_canne<=TAILLE_PLATEAU) ) && ( sqrtf(dx*dx + dy*dy)<= sqrt(2) ) && (plateau[x_canne-1][y_canne-1]->id != 11) );
}

/*Selection de coordonnées valides (où il est possible de pêcher) pour l'apparition de la canne à pêche*/
void spawn_canne(int x_pecheur, int y_pecheur, int *x_canne, int *y_canne, Mob * plateau[][TAILLE_PLATEAU])
{	int i, j;
	for(i=-TAILLE_CANNE; i<=TAILLE_CANNE; i++)
	{	for(j=-TAILLE_CANNE;j<=TAILLE_CANNE;j++)
		{	if( (x_pecheur+i>=1 && x_pecheur+i<=TAILLE_PLATEAU) && (y_pecheur+j>=1 && y_pecheur+j<=TAILLE_PLATEAU) && (plateau[x_pecheur+i-1][y_pecheur+j-1]->id != 11))
			{	*x_canne=x_pecheur+i;
				*y_canne=y_pecheur+j;
				return;			
			}
		}
	}
}


/*Affichage de la canne à pêche sur le plateau de jeu*/
void draw_canne(int x_pecheur, int y_pecheur, int x_canne, int y_canne, couleurs coul)
{	set_drawing_color(coul);
	draw_line(M1+(x_pecheur-0.5)*(WINDOW_WIDTH-M3)/(N), M2+(y_pecheur-0.5)*(WINDOW_HEIGHT-2*M4)/(N), M1+(x_canne-0.5)*(WINDOW_WIDTH-M3)/(N), M2+(y_canne-0.5)*(WINDOW_HEIGHT-2*M4)/(N));
}	

/*Déplacement de la canne à pêche*/
void place_canne_a_peche(int x_pecheur, int y_pecheur, int *x_canne, int *y_canne, Mob * plateau[][TAILLE_PLATEAU])
{	int peche=0;
	while(peche!=key_ENTER)
	{	switch (peche)
		{	case key_RIGHT:						
				if(case_valide_peche(*x_canne+1, *y_canne, x_pecheur, y_pecheur,plateau))
				{	draw_canne(x_pecheur, y_pecheur, *x_canne, *y_canne, color_WHITE);				
					(*x_canne)++;
				}				
				break;
		
			case key_LEFT : 
				if(case_valide_peche(*x_canne-1, *y_canne, x_pecheur, y_pecheur, plateau))
				{	draw_canne(x_pecheur, y_pecheur, *x_canne, *y_canne, color_WHITE);
					(*x_canne)--;
				}			
				break;
			case key_UP :
				if(case_valide_peche(*x_canne, *y_canne+1, x_pecheur, y_pecheur, plateau))				
				{	draw_canne(x_pecheur, y_pecheur, *x_canne, *y_canne, color_WHITE);
					(*y_canne)++;
				}				
				break;
			case key_DOWN :
				if(case_valide_peche(*x_canne, *y_canne-1, x_pecheur, y_pecheur, plateau))				
				{	draw_canne(x_pecheur, y_pecheur, *x_canne, *y_canne, color_WHITE);
					(*y_canne)--;
				}				
				break;
			default :
				break;
		}
		draw_canne(x_pecheur, y_pecheur, *x_canne, *y_canne, color_BLACK); 
		update_graphics();
		peche=get_key();		
	}
}

#include "filet.h"


/*Selection de coordonnées valides (où il est possible de pêcher) pour l'apparition du filet*/
void spawn_filet(int x_pecheur, int y_pecheur, int filet[][3], Mob *plateau[][TAILLE_PLATEAU])
{	int i, j;
	for(i=-1; i<=1; i++)
	{	for(j=-1;j<=1;j++)
		{	if( case_valide_pont(x_pecheur+i, y_pecheur+j, x_pecheur, y_pecheur, plateau) )
			{	
				filet[i+1][j+1]=1;			
			}
		}
	}
}

/*Affichage du filet sur le plateau de jeu*/
void draw_filet(int x_pecheur, int y_pecheur, int filet[][3])
{	int i, j;
	int sup, inf;
	int decal=(M1+((WINDOW_WIDTH-(M1+M3))/N));	
	set_drawing_color(color_BLACK);
	for(i=0;i<3;i++)
	{	for(j=0;j<3;j++)
		{	if(filet[i][j]==1)
				{	draw_square(x_pecheur+i-1, y_pecheur+j-1, color_BACKGROUND);
						
				}
		}
	}					
								
}	


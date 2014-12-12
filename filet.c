#include "filet.h"


/*Selection de coordonnées valides (où il est possible de pêcher) pour l'apparition du filet*/
void spawn_filet(int x_pecheur, int y_pecheur, int filet[][3], Mob *plateau[][TAILLE_PLATEAU])
{	int i, j;
	for(i=-1; i<=1; i++)
	{	for(j=-1;j<=1;j++)
		{	if( case_valide_pont(x_pecheur+i, y_pecheur+j, x_pecheur, y_pecheur, plateau) )
			{	
				filet[i+1][j+1]=1;			
				//printf("dans spawn :\nfilet %d %d = %d\n", i+1, j+1, filet[i+1][j+1]);
			}
		}
	}
}

/*Affichage du filet sur le plateau de jeu*/
void draw_filet(int x_pecheur, int y_pecheur, int filet[][3])
{	int i, j;
	int sup, inf;	
	set_drawing_color(color_BLACK);
	for(i=0;i<3;i++)
	{	for(j=0;j<3;j++)
		{	if(filet[i][j]==1)
				{	//case x_pecheur+i-1 y_pecheur+j-1
					for (sup=-1;sup<=1;sup++)
					{ 	draw_line(M1+(x_pecheur+i-2)*(639-2*M1)/(N), M2+(y_pecheur+j-1.5+sup*0.25)*(479-2*M2)/(N), M1+(x_pecheur+i-1.5-sup*0.25)*(639-2*M1)/(N), M2+(y_pecheur+j-1)*(479-2*M2)/(N));
						draw_line(M1+(x_pecheur+i-1)*(639-2*M1)/(N), M2+(y_pecheur+j-1.5+sup*0.25)*(479-2*M2)/(N), M1+(x_pecheur+i-1.5+sup*0.25)*(639-2*M1)/(N), M2+(y_pecheur+j-1)*(479-2*M2)/(N)) ;
					}
					for (inf=-2;inf<=1;inf++)	
					{	draw_line(M1+(x_pecheur+i-1.5+inf*0.25)*(639-2*M1)/(N), M2+(y_pecheur+j-2)*(479-2*M2)/(N), M1+(x_pecheur+i-1)*(639-2*M1)/(N), M2+(y_pecheur+j-1.5-inf*0.25)*(479-2*M2)/(N));
												
						draw_line(M1+(x_pecheur+i-1.5-inf*0.25)*(639-2*M1)/(N), M2+(y_pecheur+j-2)*(479-2*M2)/(N), M1+(x_pecheur+i+-1-1)*(639-2*M1)/(N), M2+(y_pecheur+j-1.5-inf*0.25)*(479-2*M2)/(N));
					}
						
				}
		}
	}					
								
				
//		draw_line(M1+(x_pecheur-0.5)*(639-2*M1)/(N), M2+(y_pecheur-0.5)*(479-2*M2)/(N), M1+(x_canne-0.5)*(639-2*M1)/(N), M2+(y_canne-0.5)*(479-2*M2)/(N));
}	


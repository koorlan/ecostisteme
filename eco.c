#include "eco.h"
#include "main.h" 

/**********************************************************************/
/*** 		NB, à propos des systèmes de coordonnées            ***/
/***								    ***/
/*** Travail avec l'affichage graphique :		            ***/
/*** 1 à TAILLE_PLATEAU						    ***/
/***								    ***/
/*** Travail avec le plateau effectif (tableau) :		    ***/	
/*** 0 à TAILLE_PLATEAU-1 					    ***/
/***								    ***/						
/**********************************************************************/



void affiche_grille()
/*affichage d'une grille n*n cases*/
{	int i;
	set_drawing_color(color_BLACK);
	for(i=0;i<=N;i++)
	{	draw_line(M1+i*(WINDOW_WIDTH-2*M1)/N, M2, M1+i*(WINDOW_WIDTH-2*M1)/N, WINDOW_HEIGHT-M2);
		draw_line(M1, M2+i*(WINDOW_HEIGHT-2*M2)/N, WINDOW_WIDTH-M1, M2+i*(WINDOW_HEIGHT-2*M2)/N);
	}		
	update_graphics();	
}

void afficher_point(int x, int y, couleurs coul)
/*affichage d'un individu sur la grille en fonction de son espèce*/
{	set_drawing_color(coul);
	draw_circle_full(M1+(x-0.5)*(WINDOW_WIDTH-2*M1)/(N), M2+(y-0.5)*(WINDOW_HEIGHT-2*M2)/(N), 4.5);
}
 
/*void blind_grid()
{	int i,j,a;
	for(j=1; j<=TAILLE_PLATEAU;j++)
	{	for(i=1;i<=TAILLE_PLATEAU;i++)
		{	
				a=rand()%(2)+1;
				switch (a)
				{	case 1 : 	
						set_drawing_color(color_BLUE);
						draw_rectangle_full(M1+i*(WINDOW_WIDTH-2*M1)/N, M2+j*(WINDOW_HEIGHT-2*M2)/N, M1+(i-1)*(WINDOW_WIDTH-2*M1)/N, M2+(j-1)*(WINDOW_HEIGHT-2*M2)/N);
						break;
					case 2 : 
						set_drawing_color(color_LIGHTBLUE);
						draw_rectangle_full(M1+i*(WINDOW_WIDTH-2*M1)/N, M2+j*(WINDOW_HEIGHT-2*M2)/N, M1+(i-1)*(WINDOW_WIDTH-2*M1)/N, M2+(j-1)*(WINDOW_HEIGHT-2*M2)/N);
						break;
				}
			
		}
	}
	update_graphics();
}	
*/

void espece_consideree(int i, couleurs coul)
{	switch (i)
	{case 1 :
		set_drawing_color(color_BLACK);
		set_font(font_HELVETICA_12);
		draw_string(M1, M2/2, "On considere l'espece plancton\n");
		afficher_point(12, -1, mobs_draw[i]); 
		break;
	
	case 2 :
		set_drawing_color(color_BLACK);
		set_font(font_HELVETICA_12);
		draw_string(M1, M2/2, "On considere l'espece corail\n");
		afficher_point(11, -1, mobs_draw[i]); 
		break;
	
	case 3 :
		set_drawing_color(color_BLACK);
		set_font(font_HELVETICA_12);
		draw_string(M1, M2/2, "On considere l'espece bar\n");
		afficher_point(10, -1, mobs_draw[i]); 
		break;
	 
	case 4 :
		set_drawing_color(color_BLACK);
		set_font(font_HELVETICA_12);
		draw_string(M1, M2/2, "On considere l'espece thon\n");
		afficher_point(10, -1, mobs_draw[i]); 
		break;
	
	case 5 :
		set_drawing_color(color_BLACK);
		set_font(font_HELVETICA_12);
		draw_string(M1, M2/2, "On considere l'espece pollution\n");
		afficher_point(12, -1, mobs_draw[i]); 
		break;
	
	default :
		break;
	}
	update_graphics();
}



#include <stdio.h>
#include <stdlib.h>
#include "libgraphique.h"
#define M1 63.9
#define M2 47.9
#define N 25

typedef struct coord {int x;
			int y;} coord;
				

void affiche_grille()
/*affichage d'une grille n*n cases*/
{	int i;
	for(i=0;i<=N;i++)
	{	draw_line(M1+i*(639-2*M1)/N, M2, M1+i*(639-2*M1)/N, 479-M2);
		draw_line(M1, M2+i*(479-2*M2)/N, 639-M1, M2+i*(479-2*M2)/N);
	}		
	
}

void afficher_point(coord c, couleurs coul)
/*affichage d'un individu sur la grille en fonction de son espèce*/
{	set_drawing_color(coul);
	draw_circle_full(M1+(c.x-0.5)*(639-2*M1)/(N), M2+(c.y-0.5)*(479-2*M2)/(N), 6);
}
 



int main (void)

{	int stop;
	coord p1={1, 1};
	coord p2={1, 2};
	coord p3={10, 1};
	start_graphics();	
	update_graphics();
	affiche_grille();
	update_graphics();
	afficher_point(p1, color_LIGHTBLUE);
	afficher_point(p2, color_LIGHTCYAN);
	afficher_point(p3, color_MAGENTA);		
	update_graphics();
	stop=get_key();
	stop_graphics();
	return 0;
}

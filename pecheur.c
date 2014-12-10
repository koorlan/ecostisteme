#include<stdio.h>
#include<stdlib.h>

#include "pecheur.h"


/*Teste la validité d'une case sélectionnée par un joueur*/
int case_valide(int x, int y, Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU])
{	if((y==0 || y==31) && (x>=0 && x<= 31))
		return 1;
	else if ((x==0 || x==31) && (y>=0 && y<=31))
		return 1;
	else if(((x>=1 && x<=30) && (y>=1 && y<=30)) && plateau[x-1][y-1]->id==11) 
		return 1;
	return 0;
}

/*Permet le déplacement du pêcher sur le plateau de jeu*/
void deplacement_pecheur(int *x, int *y, couleurs coul, Mob * plateau[][TAILLE_PLATEAU])
{	int a=0;	
	
	afficher_point(*x, *y, coul);	
	while(a!=key_ENTER)
	{	a=get_key();
		switch(a)
		{	case key_RIGHT:						
				if(case_valide(*x+1, *y, plateau))
				{	afficher_point(*x,*y,color_WHITE);				
					(*x)++;
				}				
				break;
		
			case key_LEFT : 
				if(case_valide(*x-1, *y, plateau))
				{	afficher_point(*x,*y,color_WHITE);
					(*x)--;
				}			
				break;
			case key_UP :
				if(case_valide(*x, *y+1, plateau))				
				{	afficher_point(*x,*y,color_WHITE);
					(*y)++;
				}				
				break;
			case key_DOWN :
				if(case_valide(*x, *y-1, plateau))				
				{	afficher_point(*x,*y,color_WHITE);
					(*y)--;
				}				
				break;
			default :
				break;
		
		}
		afficher_point(*x,*y,coul);						
		update_graphics();
			
	}
	//set_drawing_color(color_WHITE);
	//Effacer ancien point
	update_graphics();

}

/*Determine l'action du pecheur après son déplacement*/
int choix_action()
{	int a=0;
	set_font(font_HELVETICA_12);
	set_drawing_color(color_BLACK);
	draw_string(M1, M2/2, "Voulez-vous pecher? (o)ui (n)on\n");
	update_graphics();
	a=get_key();
	return a;
}
	

int peche();

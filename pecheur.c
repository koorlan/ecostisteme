#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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

/*Permet le déplacement du pecheur sur le plateau de jeu*/
void deplacement_pecheur(Mob *p, couleurs coul, Mob * plateau[][TAILLE_PLATEAU])
{	int a=0;	
	
	afficher_point(p->x, p->y, coul);	
	while(a!=key_ENTER)
	{	a=get_key();
		switch(a)
		{	case key_RIGHT:						
				if(case_valide(p->x+1, p->y, plateau)||p->derniere_reproduction==1)
				{	afficher_point(p->x,p->y,color_WHITE);				
					(p->x)++;
				}				
				break;
		
			case key_LEFT : 
				if(case_valide(p->x-1, p->y, plateau)||p->derniere_reproduction==1)
				{	afficher_point(p->x,p->y,color_WHITE);
					(p->x)--;
				}			
				break;
			case key_UP :
				if(case_valide(p->x, p->y+1, plateau)||p->derniere_reproduction==1)				
				{	afficher_point(p->x,p->y,color_WHITE);
					(p->y)++;
				}				
				break;
			case key_DOWN :
				if(case_valide(p->x, p->y-1, plateau)||p->derniere_reproduction==1)				
				{	afficher_point(p->x,p->y,color_WHITE);
					(p->y)--;
				}				
				break;
			default :
				break;
		
		}
		afficher_point(p->x,p->y,coul);						
		update_graphics();
		/***Conditions d'arrêt pour le cas du pêcheur dans l'eau***/

		//soit il regagne le rivage sain et sauf 
		if(p->derniere_reproduction==1 && case_valide(p->x, p->y, plateau))
		{	set_drawing_color(color_WHITE);
			//set_font(font_HELVETICA_14);
			draw_printf(M1, 479-M2/2, "Vous etes tombe a l'eau, sortez de l'eau");
			set_drawing_color(color_BLACK);
			draw_printf(M1, 479-M2/2, "Vous avez rejoint la terre ferme!\n");
			update_graphics();			
			return;
					
		}

		//soit il se déplace sur une case qui contient un prédateur 
		else if(p->derniere_reproduction==1 && eat_mat[plateau[p->x-1][p->y-1]->id][10]==1)
		{	//on indique à la fonction plouf_hard_version que le pêcheur a rencontré un prédateur
			p->derniere_reproduction=0;
			return;
		}	
	}
	
	update_graphics();

}


/*Determine l'action du pecheur après son déplacement*/
/**********************************************************/
/*** valeurs de n -> action				***/
/*** 1 -> le pecheur veut-il pecher?			***/
/*** 2 -> le pecheur veut-il construire le pont?	***/
/*** 3 -> avec quel materiel le pecheur veut-il pecher? ***/
/**********************************************************/
int choix_action(int n)
{	int a=0;
	set_font(font_HELVETICA_12);
	set_drawing_color(color_BLACK);
	if (n==2||n==3)
	{	set_drawing_color(color_WHITE);
	}
	draw_string(M1, M2/2, "Voulez-vous pecher? (o)ui (n)on\n");
	if(n==2)
	{	set_drawing_color(color_BLACK);
		draw_string(M1, M2/2, "Voulez-vous construire le pont? (o)ui (n)on\n");
	}
	if(n==3)
	{	set_drawing_color(color_BLACK);
		draw_string(M1, M2/2, "Choisissez votre materiel de peche? (c)anne a peche (f)ilet\n");
	}	
	
	update_graphics();
	a=get_key();
	return a;
}
		
/*Atteste de la validité d'une case lors du déplacement de la canne à pêche*/
int case_valide_peche(int x_canne, int y_canne, int x2, int y2,Mob * plateau[][TAILLE_PLATEAU])
{	int dx = x_canne-x2;
	int dy = y_canne-y2;
	return ( ( (x_canne>=1 && x_canne<=30) && (y_canne>=1 && y_canne<=30) ) && ( sqrtf(dx*dx + dy*dy)<= sqrt(2) ) && (plateau[x_canne-1][y_canne-1]->id != 11) );
}

/*Affichage des réserves du pêcheur*/
void afficher_munitions (Mob * pecheur, int *reserves_gagnees)
{	set_drawing_color(color_BLACK);	
	set_font(font_HELVETICA_12);
	if(pecheur->dernier_repas==1)
	{	draw_printf(M1+150, WINDOW_HEIGHT-M2/2, "Vos derniers exploits a la peche a la ligne vous rapportent %d munitions", *reserves_gagnees);
		*reserves_gagnees=0;
	}
	//set_drawing_color(color_LIGHTBLUE);	
	draw_printf(M1-30, WINDOW_HEIGHT-M2/2, "RESERVES DISPONIBLES : %d\n", pecheur->satiete);
	pecheur->dernier_repas=0; 
	update_graphics();
}

/*Gestion des fonctions relatives à la pêche*/
void que_la_peche_commence (Mob * plateau_de_jeu[][TAILLE_PLATEAU], Mob * pecheur, Liste * species[], int type_materiel, int * reserves_gagnees) 
{
	int x_canne=0, y_canne=0;
	int peche;	
	if(type_materiel=='c')
	{	spawn_canne(pecheur->x, pecheur->y, &x_canne, &y_canne, plateau_de_jeu);
		printf("%d, %d\n", x_canne, y_canne);
		draw_canne((pecheur->x), (pecheur->y), x_canne, y_canne, color_BLACK);	
		update_graphics();		
		place_canne_a_peche((pecheur->x), (pecheur->y), &x_canne, &y_canne,plateau_de_jeu);	
		if(eat_mat[10][plateau_de_jeu[x_canne-1][y_canne-1]->id]==1)
		{	pecheur->satiete = pecheur->satiete + taille[plateau_de_jeu[x_canne-1][y_canne-1]->id];		
			pecheur->dernier_repas=1;
			*reserves_gagnees=taille[plateau_de_jeu[x_canne-1][y_canne-1]->id];
			destroy_mob(*plateau_de_jeu[x_canne-1][y_canne-1], species[plateau_de_jeu[x_canne-1][y_canne-1]->id]);
			plateau_de_jeu[x_canne-1][y_canne-1]=create_mob(0);
			plateau_de_jeu[x_canne-1][y_canne-1]->x= x_canne-1;
			plateau_de_jeu[x_canne-1][y_canne-1]->y= y_canne-1;

		}
			printf("Les munitions du pêcheur sont : %d\nA-t-il peché (0 : non , 1 : oui)? %d\n", pecheur->satiete, pecheur->dernier_repas); 
		update_graphics();
	}
	else if(type_materiel=='f')
	{	int filet[3][3]={0};
		printf("peche au filet\n");
		spawn_filet(pecheur->x, pecheur->y, filet, plateau_de_jeu);
		draw_filet(pecheur->x, pecheur->y, filet);
		update_graphics();
		for(int i=0;i<3;i++)
		{	for(int j=0;j<3;j++)
			{	
				if(filet[i][j]==1)
					
				{	printf("id : %d\n", plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->id);	
					if(eat_mat[10][plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->id]==1)
					{	
						pecheur->satiete=pecheur->satiete+taille[plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->id];						
						pecheur->dernier_repas=1;
						*reserves_gagnees=(*reserves_gagnees)+taille[plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->id];
						
						destroy_mob(*plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2], species[plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->id]);
						plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]=create_mob(0);
						plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->x = pecheur->x+i-2;
						plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->y = pecheur->y+j-2;
					 }
				}
			}
		}
		peche=get_key();
	}
	
}

void plouf_soft_version(Mob *pecheur)	
{	set_drawing_color(color_BLACK);	
	pecheur->satiete=0;
	pecheur->dernier_repas=0;
	pecheur->x=0;
	pecheur->y=0;	
	set_font(font_HELVETICA_12);
	draw_printf(M1+150, 479-M2/2, "Vous etes tombe a l'eau au tour precedent, vos munitions sont perdues");
	afficher_munitions(pecheur, 0); 
	update_graphics();

}

int plouf_hard_version(Mob *pecheur, Mob * plateau[][TAILLE_PLATEAU], Liste * species[])	
{	int stop;	
	char * nom;
	set_drawing_color(color_LIGHTRED);	
	pecheur->dernier_repas=0;	
	pecheur->derniere_reproduction=1; //le pêcheur est dans l'eau 
	set_font(font_HELVETICA_18);	
	draw_printf(M1, 479-M2/2, "Vous etes tombe a l'eau, sortez de l'eau");
	afficher_point(pecheur->x, pecheur->y, color_RED);	
	
	deplacement_pecheur(pecheur, color_RED, plateau);
	//stop=get_key();
		
	//si le pecheur a rencontré un prédateur pendant qu'il tentait en vain de sortir de l'eau 	
		if(pecheur->derniere_reproduction==0)
		{	printf("der_repro : %d\n", pecheur->derniere_reproduction);
			clear_screen();
			set_drawing_color(color_BLACK);
			set_font(font_HELVETICA_18);
			switch (plateau[pecheur->x][pecheur->y]->id)
			{	case 6 :
				{	nom="pyranha";
					break;
				}
				case 7 :
				{	nom="requin";
					break;
				}
				case 8 :
				{	nom="orque";
					break;
				}
				default :	
				{	nom="inattendu";
					break;
				}
			
			}
			draw_printf(M1-20, 280, "Vous venez de vous faire manger par une espece de type %s\n", nom);
			set_font(font_HELVETICA_12);			
			draw_printf(M1+180, 240, "Voulez-vous continuer?\n");
			set_font(font_HELVETICA_18);			
			draw_printf(M1+200, 200, "(o)ui / (n)on\n");
			update_graphics();
			stop=get_key();
		}
		else 
			return 1;
		return (stop=='o');
	 
	update_graphics();
	
}


/*void final_screen (int a)
{	set_drawing_color(color_BLACK);	
	set_font(font_HELVETICA_18);
	char * nom;
	int stop;	
	switch (a)
	{		case 6 :
			{	nom="pyranha";
				break;
			}
			case 7 :
			{	nom="requin";
				break;
			}
			case 8 :
			{	nom="orque";
				break;
			}
			default :	
			{	nom="inattendu";
				break;
			}
			
	}
		draw_printf(M1-20, 280, "Vous venez de vous faire manger par une espece de type %s\n", nom);
		set_font(font_HELVETICA_12);			
		draw_printf(M1+180, 240, "Voulez-vous continuer?\n");
		set_font(font_HELVETICA_18);			
		draw_printf(M1+200, 200, "(o)ui / (n)on\n");
		update_graphics();		
		stop=get_key();	
		stop=get_key();
}

*/


#include "pecheur.h"




/*Initialisation du pecheur*/
void init_fisher(fisher * pecheur, int x, int y, int id)
{	
	pecheur->id_proie=0;	
	pecheur->reserves=0; //représente les "réserves" du pecheur
	pecheur->nv_reserves=0; //les reserves pechees au tour precedent
	pecheur->allo=0; //vaut 1 quand le pêcheur est dans l'eau	
	pecheur->xp=0;	
	pecheur->bridge=0;
	pecheur->x=x;
	pecheur->y=y;
	pecheur->id=id;
	pecheur->ecolo=0;
}

/*Teste la validité d'une case sélectionnée par un joueur*/
int case_valide(int x, int y, Mob * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU])
{	if((y==0 || y==TAILLE_PLATEAU+1) && (x>=0 && x<= TAILLE_PLATEAU+1))
		return 1;
	else if ((x==0 || x==TAILLE_PLATEAU+1) && (y>=0 && y<=TAILLE_PLATEAU+1))
		return 1;
	else if(((x>=1 && x<=TAILLE_PLATEAU) && (y>=1 && y<=TAILLE_PLATEAU)) && (plateau[x-1][y-1]->id==11 || plateau[x-1][y-1]->id==12)) 
		return 2;
	return 0;
}

/*Permet le déplacement du pecheur sur le plateau de jeu*/
void deplacement_pecheur(fisher *p, couleurs coul, Mob * plateau[][TAILLE_PLATEAU])
{	int a=0;	
	afficher_point(p->x, p->y, coul);	
	while(a!=key_ENTER)
	{	a=get_key();
		switch(a)
		{	case key_RIGHT:						
				if(case_valide(p->x+1, p->y, plateau)||p->allo==1)
				{	//Si le pêcheur était sur le pont ou sur l'île
					if((p->x>=1 && p->x<=TAILLE_PLATEAU) && (p->y>=1 && p->y<=TAILLE_PLATEAU) && (plateau[p->x-1][p->y-1]->id==11 || plateau[p->x-1][p->y-1]->id==12 || p->allo==1))
						afficher_point(p->x,p->y,mobs_draw[plateau[p->x-1][p->y-1]->id]);
					//Si le pecheur était sur le rivage						
					else 
						afficher_point(p->x,p->y,color_BACKGROUND);				
					(p->x)++;
				}				
				break;
		
			case key_LEFT : 
				if(case_valide(p->x-1, p->y, plateau)||p->allo==1)
				{	
					if((p->x>=1 && p->x<=TAILLE_PLATEAU) && (p->y>=1 && p->y<=TAILLE_PLATEAU) && (plateau[p->x-1][p->y-1]->id==11 || plateau[p->x-1][p->y-1]->id==12 || p->allo==1))					

						afficher_point(p->x,p->y,mobs_draw[plateau[p->x-1][p->y-1]->id]);
					else
						afficher_point(p->x,p->y,color_BACKGROUND);
					(p->x)--;
				}			
				break;
			case key_UP :
				if(case_valide(p->x, p->y+1, plateau)||p->allo==1)				
				{	
					if((p->x>=1 && p->x<=TAILLE_PLATEAU) && (p->y>=1 && p->y<=TAILLE_PLATEAU) && (plateau[p->x-1][p->y-1]->id==11 || plateau[p->x-1][p->y-1]->id==12 || p->allo==1))
						afficher_point(p->x,p->y,mobs_draw[plateau[p->x-1][p->y-1]->id]);

					else
						afficher_point(p->x,p->y,color_BACKGROUND);
					(p->y)++;
				}				
				break;
			case key_DOWN :
				if(case_valide(p->x, p->y-1, plateau)||p->allo==1)				
				{	
					if((p->x>=1 && p->x<=TAILLE_PLATEAU) && (p->y>=1 && p->y<=TAILLE_PLATEAU) && (plateau[p->x-1][p->y-1]->id==11 || plateau[p->x-1][p->y-1]->id==12 || p->allo==1))
						afficher_point(p->x,p->y,mobs_draw[plateau[p->x-1][p->y-1]->id]);
					else
						afficher_point(p->x,p->y,color_BACKGROUND);
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
		if(p->allo==1 && case_valide(p->x, p->y, plateau))
		{		
			return;
					
		}

		//soit il se déplace sur une case qui contient un prédateur 
		else if(p->allo==1 && eat_mat[plateau[p->x-1][p->y-1]->id][10]==1)
		{	//on indique à la fonction plouf_hard_version que le pêcheur a rencontré un prédateur
			p->allo=0;
			return;
		}	
	}
	
	update_graphics();

}




//Actions possibles : pêcher et consulter aide		
int affichage_1()
{	int k=20;
	int current=1;
	int select=0;

	set_font(font_HELVETICA_12);	
	set_drawing_color(color_LIGHTRED);	
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Pecher");
	set_drawing_color(color_WHITE);		
	
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-k, "Aide");
	update_graphics();

	while(select!=key_ENTER){
		select=get_key();
		set_drawing_color(color_WHITE);
		switch (select)	
		{	case key_DOWN:
					
					if (current==1)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Pecher");	
						set_drawing_color(color_LIGHTRED); 
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Aide");
						current ++;
					}
					break;	
			case key_UP:	
					if (current==2)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Aide");
						set_drawing_color(color_LIGHTRED);		
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Pecher");
						current--;
					}
					break;
			case key_ENTER :
					break;
			default :		
					set_drawing_color(color_LIGHTGREEN);	
					draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-80, "Utilisez les fleches puis");
					draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-100, "ENTREE pour selectionner");
					break;
				
			}
			update_graphics();
		}

	
	return current;
}

//Actions possibles : pêcher, construire pont, consulter aide
int affichage_2()
{	int current=1;
	int select=0;
	int k=20;

	set_font(font_HELVETICA_12);
	set_drawing_color(color_LIGHTRED);	
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Pecher");
	set_drawing_color(color_WHITE);		
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-k, "Construire le pont");
	k+=20;
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-k, "Aide");
	update_graphics();
		
	
	while(select!=key_ENTER){
		select=get_key();
		switch (select)	
		{	set_drawing_color(color_WHITE);
			case key_DOWN:
					if (current==1)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Pecher");	
						set_drawing_color(color_LIGHTRED); 
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Construire le pont");
						current ++;
					}	
					else if (current==2)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Construire le pont");	
						set_drawing_color(color_LIGHTRED);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-40, "Aide");	
						current ++;
					}
					break;	
				case key_UP:	
					set_drawing_color(color_WHITE);
					if (current==3)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-40, "Aide");	
						set_drawing_color(color_LIGHTRED);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Construire le pont");
						current --;
					}
					else if (current==2)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Construire le pont");
						set_drawing_color(color_LIGHTRED);		
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Pecher");
						current--;
					}
					break;
				case key_ENTER:
					break;
				default :
							
					set_drawing_color(color_LIGHTGREEN);	
					draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-80, "Utilisez les fleches puis");
					draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-100, "ENTREE pour selectionner");
					break;
				
			}
			update_graphics();
		}

	
	return current;
}

//Actions possibles : pecher, construire pont, relacher poisson, aide	
int affichage_3()
{	int current=1;
	int select=0;
	int k=20;

	set_font(font_HELVETICA_12);	
	set_drawing_color(color_LIGHTRED);	
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Pecher");
	set_drawing_color(color_WHITE);		
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-k, "Construire le pont");
	k+=20;
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-k, "Relacher un poisson");
	k+=20;
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-k, "Aide");
	update_graphics();
		
	while(select!=key_ENTER){
		select=get_key();
		set_drawing_color(color_WHITE);	
		switch (select)	
		{	case key_DOWN:
					if (current==1)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Pecher");	
						set_drawing_color(color_LIGHTRED); 
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Construire le pont");
						current ++;
					}	
					else if (current==2)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Construire le pont");	
						set_drawing_color(color_LIGHTRED);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-40, "Relacher un poisson");
						current ++;
					}
				
					else if (current==3)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-40, "Relacher un poisson");
						set_drawing_color(color_LIGHTRED);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-60, "Aide");
						current ++;
					}
					break;	
				case key_UP:	
					if (current==4)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-60, "Aide");	
						set_drawing_color(color_LIGHTRED); 
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-40, "Relacher un poisson");
						current --;
					}
					else if (current==3)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-40, "Relacher un poisson");
						set_drawing_color(color_LIGHTRED);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Construire le pont");
						current --;
					}
					else if (current==2)
					{	set_drawing_color(color_WHITE);	
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Construire le pont");
						set_drawing_color(color_LIGHTRED);		
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Pecher");
						current--;
					}
					break;
				case key_ENTER:	
					break;
				default :			
					set_drawing_color(color_LIGHTGREEN);	
					draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-80, "Utilisez les fleches puis");
					draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-100, "ENTREE pour selectionner");
					break;
				
			}
			update_graphics();
		}

	
	return current;
}

// Actions possibles : pêcher à la canne ou au filet
int affichage_4()
{	int k=20;
	int current=1;
	int select=0;

	set_font(font_HELVETICA_12);	
	set_drawing_color(color_LIGHTRED);	
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Canne a peche");
	set_drawing_color(color_WHITE);		

	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-k, "Filet");
	update_graphics();

	while(select!=key_ENTER){
		select=get_key();
		set_drawing_color(color_WHITE);
		switch (select)	
		{	case key_DOWN:
					
					if (current==1)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Canne a peche");	
						set_drawing_color(color_LIGHTRED); 
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Filet");
						current ++;
					}
					break;	
			case key_UP:	
					if (current==2)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-20, "Filet");
						set_drawing_color(color_LIGHTRED);		
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Canne a peche");
						current--;
					}
					break;
			case key_ENTER :
					break;
			default :		
					set_drawing_color(color_LIGHTGREEN);	
					draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-80, "Utilisez les fleches puis");
					draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-100, "ENTREE pour selectionner");
					break;
				
			}
			update_graphics();
		}

	
	return current;
}

//Actions possibles : participer au troc de l'île	
int affichage_5()
{	int k=20;
	int current=1;
	int select=0;
	set_drawing_color(color_BACKGROUND);
	draw_rectangle_full(WINDOW_WIDTH-M3+M1+22,131,WINDOW_WIDTH, 0);
	set_font(font_HELVETICA_12);	
	set_drawing_color(color_LIGHTRED);	
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+70, "Oui");
	set_drawing_color(color_WHITE);		

	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90, "Voulez-vous participer au troc de l'ile ?");
	draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+70-k, "Non");
	update_graphics();

	while(select!=key_ENTER){
		select=get_key();
		set_drawing_color(color_WHITE);
		switch (select)	
		{	case key_DOWN:
					
					if (current==1)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+70, "Oui");	
						set_drawing_color(color_LIGHTRED); 
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+70-20, "Non");
						current ++;
					}
					break;	
			case key_UP:	
					if (current==2)
					{	set_drawing_color(color_WHITE);
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+70-20, "Non");
						set_drawing_color(color_LIGHTRED);		
						draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+70, "Oui");
						current--;
					}
					break;
			case key_ENTER :
					break;
			default :		
					set_drawing_color(color_LIGHTGREEN);	
					draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-80, "Utilisez les fleches puis");
					draw_string(WINDOW_WIDTH-M3+M1+20+2, M2+90-100, "ENTREE pour selectionner");
					break;
				
			}
			update_graphics();
		}

	
	return current;
}

/* Determine l'action du pêcheur */
int choix_action(int n, fisher * pecheur)
{	
	int current=1;
	if(n==0)
	{	if(pecheur->reserves>=8)
		{	current=affichage_5();
			set_drawing_color(color_BACKGROUND);
			draw_rectangle_full(WINDOW_WIDTH-M3+M1+22,131,WINDOW_WIDTH, 0);
			if(current==1)
				return 'o';
		}
		return 'n';
			
	}			
	else if(n==1)	
	{	if(pecheur->reserves==0)
		{	current=affichage_1();
			if(current==2)
				return 'a'; //aide 
		}	
		else if(pecheur->nv_reserves==0)	
		{	current=affichage_2();
			if (current==2)	
				return 'b'; //pont (bridge)
			else if (current==3)
				return 'a'; //aide 
		}		
		else
		{	current=affichage_3();
			if(current==3)
				return 'r'; //relacher poisson
			if(current==4)
				return 'a'; //aide
		}
		if(current==2)
			return 'b'; //construction du pont
		return'c'; //pêche à la canne 
	}
	else if(n==2)
	{	set_drawing_color(color_BACKGROUND);
		draw_rectangle_full(WINDOW_WIDTH-M3+M1+22,131,WINDOW_WIDTH, 0);
		current=affichage_4();
		if(current==2)
			return 'f';
		return 'c';
	}		

}
		

/*Gestion des fonctions relatives à la pêche*/
void que_la_peche_commence (Mob * plateau_de_jeu[][TAILLE_PLATEAU], fisher * pecheur, Liste * species[], int type_materiel, int bonus_tab[]) 
{
	int x_canne=0, y_canne=0;
	int peche;
	pecheur->nv_reserves=0;	
	set_drawing_color(color_WHITE);
	
	if(type_materiel=='c')
	{		
		update_graphics();		
		place_canne_a_peche((pecheur->x), (pecheur->y), &x_canne, &y_canne,plateau_de_jeu,bonus_tab);	
		if(eat_mat[10][plateau_de_jeu[x_canne][y_canne]->id]==1||(plateau_de_jeu[x_canne][y_canne]->id==5 && bonus_tab[4]==2))
		{	pecheur->id_proie=plateau_de_jeu[x_canne][y_canne]->id;
			pecheur->reserves = pecheur->reserves + taille[plateau_de_jeu[x_canne][y_canne]->id];		
			pecheur->nv_reserves=taille[plateau_de_jeu[x_canne][y_canne]->id];
			destroy_mob(*plateau_de_jeu[x_canne][y_canne], species[plateau_de_jeu[x_canne][y_canne]->id]);
			plateau_de_jeu[x_canne][y_canne]=create_mob(0);
			plateau_de_jeu[x_canne][y_canne]->x= x_canne;
			plateau_de_jeu[x_canne][y_canne]->y= y_canne;

		}
	
		update_graphics();
	}
	else if(type_materiel=='f')
	{	
		int filet[3][3] = {0} ;
		
		spawn_filet(pecheur->x, pecheur->y, filet, plateau_de_jeu);
		draw_filet(pecheur->x, pecheur->y, filet);
		update_graphics();
		for(int i=0;i<3;i++)
		{	for(int j=0;j<3;j++)
			{	
				if(filet[i][j]==1)
					
				{		
					if(eat_mat[10][plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->id]==1)
					{	if(taille[plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->id]>taille[pecheur->id_proie])
							pecheur->id_proie=plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->id;
						pecheur->reserves=pecheur->reserves+taille[plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->id];
						pecheur->nv_reserves=pecheur->nv_reserves+taille[plateau_de_jeu[pecheur->x+i-2][pecheur->y+j-2]->id];  

						
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

/*Le pecheur respawn sur le rivage, il perd ses munitions*/
void plouf_soft_version(fisher *pecheur)	
{	
	pecheur->reserves=0;
	pecheur->nv_reserves=0;
	pecheur->allo=0;	


}


/*Le pecheur doit nager jusqu'au rivage, il peut rencontrer un prédateur*/
int plouf_hard_version(fisher *pecheur, Mob * plateau[][TAILLE_PLATEAU], Liste * species[])	
{	int stop=0;	
	char * nom;

	set_drawing_color(color_BACKGROUND);
	draw_rectangle_full(WINDOW_WIDTH-M3+M1+22,131,WINDOW_WIDTH, 0);
	set_font(font_HELVETICA_18);	
	set_drawing_color(color_LIGHTRED);	
	draw_string(WINDOW_WIDTH-M3+M1+40+2, M2+70, "SORTEZ VITE DE L'EAU");
		
	pecheur->nv_reserves=0;	
	pecheur->bridge=0;
	pecheur->allo=1; //le pêcheur est dans l'eau 
	
	afficher_point(pecheur->x, pecheur->y, color_RED);	
	deplacement_pecheur(pecheur, color_RED, plateau);
	
		
	//si le pecheur a rencontré un prédateur pendant qu'il tentait en vain de sortir de l'eau 	
		if(pecheur->allo==0)
		{	
			clear_screen();
			set_background_color(color_BACKGROUND);
			set_drawing_color(color_WHITE);
			set_font(font_HELVETICA_18);
			
			switch (plateau[pecheur->x-1][pecheur->y-1]->id)
			{	case 6 :
				{	nom="piranha";
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
			draw_printf(WINDOW_WIDTH/2-250, WINDOW_HEIGHT/2+40, "Vous venez de vous faire manger par une espece de type %s\n", nom);
			draw_printf(WINDOW_WIDTH/2-100, WINDOW_HEIGHT/2, "Voulez-vous continuer ?\n");
			set_font(font_HELVETICA_18);			
			set_drawing_color(color_LIGHTRED);
			draw_printf(WINDOW_WIDTH/2-50, WINDOW_HEIGHT/2-40, "(O)");
			set_drawing_color(color_WHITE);
			draw_printf(WINDOW_WIDTH/2-22, WINDOW_HEIGHT/2-40, "ui / ");
			set_drawing_color(color_LIGHTRED);
			draw_printf(WINDOW_WIDTH/2+5, WINDOW_HEIGHT/2-40, "(N)"); 
			set_drawing_color(color_WHITE);
			draw_printf(WINDOW_WIDTH/2+31, WINDOW_HEIGHT/2-40, "on");
			if(pecheur->xp >= 50)
				pecheur->xp-=50;
			else
				pecheur->xp=0;
			update_graphics();	
			pecheur->x=0;
			pecheur->y=0;
			
			while(stop!='o'&& stop!='n')
				stop=get_key();
		}
		else 
			return 1;
		return (stop=='o');
	 
	update_graphics();
	
}

/* Déplacement du curseur pour relacher poisson*/
void deplacement_curseur(int * x, int * y, Mob * plateau[][TAILLE_PLATEAU], int bonus_tab[], couleurs coul)
{	int a=0;	
	
	draw_square(*x, *y, coul);	
	while(a!=key_ENTER)
	{	a=get_key();
		switch(a)
		{	case key_RIGHT:						
				if(!case_valide((*x)+1, *y, plateau))
				{	if(bonus_tab[6]==0)
						draw_square(*x, *y,  (rand_a_b(30,47)<<24)+(rand_a_b(27,72)<<16)+(rand_a_b(139,206)<<8));
											
					else
					{	draw_square(*x, *y, mobs_draw[0]);
						afficher_point(*x, *y,  mobs_draw[plateau[*x-1][*y-1]->id]);
					}				
					(*x)++;

				}				
				break;
		
			case key_LEFT : 
				if(!case_valide((*x)-1, (*y), plateau))
				{	
					if(bonus_tab[6]==0)
						draw_square(*x, *y,  (rand_a_b(30,47)<<24)+(rand_a_b(27,72)<<16)+(rand_a_b(139,206)<<8));
											
					else
					{	draw_square(*x, *y, mobs_draw[0]);
						afficher_point(*x, *y,  mobs_draw[plateau[*x-1][*y-1]->id]);
					}
					(*x)--;
				}			
				break;
			case key_UP :
				if(!case_valide((*x), (*y)+1, plateau))				
				{	if(bonus_tab[6]==0)
						draw_square(*x, *y,  (rand_a_b(30,47)<<24)+(rand_a_b(27,72)<<16)+(rand_a_b(139,206)<<8));
											
					else
					{	draw_square(*x, *y, mobs_draw[0]);
						afficher_point(*x, *y,  mobs_draw[plateau[*x-1][*y-1]->id]);
					}
					(*y)++;
				}				
				break;
			case key_DOWN :
				if(!case_valide((*x), (*y)-1, plateau))				
				{	
					if(bonus_tab[6]==0)
						draw_square(*x, *y,  (rand_a_b(30,47)<<24)+(rand_a_b(27,72)<<16)+(rand_a_b(139,206)<<8));
											
					else
					{	draw_square(*x, *y, mobs_draw[0]);
						afficher_point(*x, *y,  mobs_draw[plateau[*x-1][*y-1]->id]);
					}
					(*y)--;
				}				
				break;
			default :
				break;
		
		}
		draw_square(*x, *y,coul);						
		update_graphics();	
	}
	
	update_graphics();
	
}

/*Relacher poisson dans l'eau */
void relacher_poisson(Mob * plateau_de_jeu[][TAILLE_PLATEAU], fisher * pecheur, Liste * species[], int bonus_tab[])
{	int x_curseur=-1;
	int y_curseur=-1;
	spawn_pont(pecheur->x, pecheur->y, &x_curseur, &y_curseur, plateau_de_jeu);
	if(x_curseur!=-1)
	{draw_square(x_curseur, y_curseur, color_LIGHTGREEN);
	update_graphics();
	deplacement_curseur(&x_curseur, &y_curseur, plateau_de_jeu, bonus_tab, color_LIGHTGREEN);

	if(plateau_de_jeu[x_curseur-1][y_curseur-1]->id!=0)
		destroy_mob(*plateau_de_jeu[x_curseur-1][y_curseur-1], species[plateau_de_jeu[x_curseur-1][y_curseur-1]->id]);
	Mob * newMob = create_mob(pecheur->id_proie);
	newMob->id=pecheur->id_proie;
	newMob->x = x_curseur-1;
	newMob->y = y_curseur-1;

	//création d'un supermob
	newMob->satiete=100;
	newMob->dernier_repas=WORLD_TIME;
	newMob->derniere_reproduction=WORLD_TIME;	
	pecheur->reserves=pecheur->reserves-taille[pecheur->id_proie];
	species[pecheur->id_proie] = ajouterEnTete(species[pecheur->id_proie], *newMob);
	plateau_de_jeu[x_curseur-1][y_curseur-1] = newMob;
	pecheur->id_proie=0;
	pecheur->ecolo++;
	pecheur->nv_reserves=0;	
	}

}

		

void jeu_du_pecheur(fisher *pecheur, Mob * plateau_de_jeu[][TAILLE_PLATEAU], int bonus_tab[], int * mort_pecheur, Liste * species[])
{	int stop=0;
	int a='n';
	if (pecheur->xp >= 10000)
		bonus_tab[7]=1;	
	//Le pecheur est tombé dans l'eau

	if(!case_valide(pecheur->x, pecheur->y, plateau_de_jeu))		
	{	
		if(plouf_hard_version(pecheur, plateau_de_jeu, species))
		{	clear_screen();
			plouf_soft_version(pecheur);
			draw_grid(plateau_de_jeu, bonus_tab[6]);				
			update_graphics(); 		
									
		}		
		else
			*mort_pecheur=1; 
				
	}		
	
	//Le pêcheur effectue un tour de jeu normal	
	else if (!bonus_tab[7])
	{	

		draw_grid(plateau_de_jeu, bonus_tab[6]);
		afficher_point(pecheur->x,pecheur->y,color_RED);
		update_graphics(),
		deplacement_pecheur(pecheur, color_RED, plateau_de_jeu);
//	

	/***début action pecheur***/
		do{	a='n';	
			if(((pecheur->x>=1 && pecheur->x<=TAILLE_PLATEAU) && (pecheur->y>=1 && pecheur->y<=TAILLE_PLATEAU)) && (plateau_de_jeu[pecheur->x-1][pecheur->y-1]->id==12))	
			{	a=choix_action(0, pecheur);
			}
			if(a=='n')
			{	a=choix_action(1, pecheur);				
				if(a=='c') //peche
				{		
					if(bonus_tab[5]) //filet
						a=choix_action(2, pecheur);
					que_la_peche_commence(plateau_de_jeu, pecheur, species, a, bonus_tab);
	
				}
				else if(a=='b') //pont
				{	
					pecheur->nv_reserves=0;			
					construire_pont(plateau_de_jeu, pecheur, species, bonus_tab);			
				}			
				else if (a=='a') //aide 
				{	
					aide();
					set_drawing_color(color_BACKGROUND);
					draw_rectangle_full(0,0,WINDOW_WIDTH-M3+M1+18,WINDOW_HEIGHT);	
					draw_grid(plateau_de_jeu, bonus_tab[6]);
					afficher_point(pecheur->x,pecheur->y,color_RED);
	
				}	
				else if (a=='r') //relacher poisson
				{
					relacher_poisson(plateau_de_jeu, pecheur, species, bonus_tab);
					pecheur->nv_reserves=0;
				}
			}
			if (a=='o')  // troc de l'île
			{	int gain =troc(pecheur);
				set_drawing_color(color_BACKGROUND);
				draw_rectangle_full(0,0,WINDOW_WIDTH-M3+M1+18,WINDOW_HEIGHT);
				draw_grid(plateau_de_jeu, bonus_tab[6]);
				afficher_point(pecheur->x,pecheur->y,color_RED);
				pecheur->xp+=gain;
				pecheur->reserves-=8;
				pecheur->nv_reserves=0;
			}
		} while(a=='a')	;
	/***fin ici***/
	
	}
		
}


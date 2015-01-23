#include "bonus.h" 

/***bonus_tab : 
	indice		0		1		2	3		4		5		6		7	
	sens		first_fish	first_bridge	fish	bridge		écolo		filet		vision		victoire
	valeur		0;1;2		0;1;2		0;1	0;1		0;1		0;1;2		0;1;2 		0;1 	
***/

/*Bonus premier poisson*/
int first_fish(int nv_reserves, int bonus)
{	return(nv_reserves!=0 && bonus==0);
}

/*Bonus première case de pont consruite*/
int first_bridge(int bridge, int bonus)
{	return(bridge!=0 && bonus==0);
}

/*Bonus poisson pêché au dernier tour*/
int fish(int nv_reserves, int bonus)
{	return (nv_reserves!=0 && bonus==2);
}

/*Bonus pont construit au dernier tour*/
int bridge(int bridge, int bonus)
{	return (bridge!=0 && bonus==2);
}

/*Bonus découverte de l'île*/
int island(fisher * pecheur)
{	return (pecheur->x==34 && pecheur->y==34);
}

/*Bonus 300 xp*/ 
int vision(fisher *pecheur, int bonus)
{	return (pecheur->xp>=300 && bonus==0);
}

/*Bonus ecolo*/
int ecolo(int ecolo, int bonus)
{	return (ecolo>=3 && bonus==0);	
}


/*Affichage des différents bonus sur la fenêtre graphique*/
void afficher_bonus(int n)
{	set_drawing_color(color_LIGHTRED);
	switch (n)
	{	case 0 :
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M3+M1+20+2, M2+200, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M3+M1+20+2, M2+183, "1er poisson");
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M3+M1+20+2, M2+160, "+50 XP");
			break;

		case 1 : 
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M3+M1+20, M2+200, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M3+M1+20+2, M2+183, "1er pont");
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M3+M1+20, M2+160, "+50 XP");
			break;
		case 2 : 
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M3+M1+20, M2+200, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M3+M1+20, M2+183, "poisson");
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M3+M1+20, M2+160, "+25 XP");
			break;
		case 3 : 
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M3+M1+20, M2+200, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M3+M1+20, M2+183, "pont");
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M3+M1+20,M2+160, "+25 XP");
			break;
		case 4 :
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M3+M1+20, M2+200, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M3+M1+20, M2+183, "ecolo");
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M3+M1+20, M2+160, "+50 XP");
			break;
	
		case 5 : //Affichage a fix !
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+100, M2+200, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M1+104, M2+183, "ile deserte");
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+113, M2+160, "Filet");
			draw_printf(WINDOW_WIDTH-M3+M1+102, M2+145, "+200 XP");
			break;
		case 6 : 
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M3+M1+120, M2+200, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M3+M1+135, M2+183, "vision");
			break;
	}

}

/*Affiche l'xp d'un joueur sur la fenêtre graphique
void afficher_xp(fisher * pecheur)
{	set_font(font_HELVETICA_18);
	set_drawing_color(color_BLACK);
	draw_printf(WINDOW_WIDTH/2-70, M2/2-5, "VOTRE XP : %d", pecheur->xp);
}
*/

/*Applique les bonus des joueurs*/
void appliquer_bonus(fisher * pecheur, int bonus_tab[])
{	/*1er poisson*/	
	if(bonus_tab[0]==1)
	{	pecheur->xp=pecheur->xp+50;
		bonus_tab[0]=2;
		afficher_bonus(0);
	}
	printf("bonus 1 (pont) vaut %d\npehcuer->bridge vaut %d\n", bonus_tab[1], pecheur->bridge);
	
	/*1er pont*/
	if(bonus_tab[1]==1)
	{	pecheur->xp=pecheur->xp+50;
		bonus_tab[1]=2;
		afficher_bonus(1);
	}	
	/*poisson*/
	if(bonus_tab[2]==1)
	{	pecheur->xp=pecheur->xp+25;
		bonus_tab[2]=0;
		afficher_bonus(2);
	}
	/*pont*/
	if(bonus_tab[3]==1)
	{	pecheur->xp=pecheur->xp+25;
		bonus_tab[3]=0;
		afficher_bonus(3);
	}
	
	/*ecolo*/
	if(bonus_tab[4]==1)
	{	pecheur->xp=pecheur->xp+50;
		bonus_tab[4]=2;
		afficher_bonus(4);
	}

	/*island*/
	if(bonus_tab[5]==1)
	{	pecheur->xp=pecheur->xp+200;
		afficher_bonus(5);
		bonus_tab[5]=2;
	}
	/*vision*/
	if(bonus_tab[6]==1)
	{	afficher_bonus(6);
		bonus_tab[6]=2;
	}
	//afficher_xp(pecheur);
}

/*Capitalise bonus des joueurs*/
void capitaliser_bonus(fisher * pecheur, int bonus_tab[])
{	printf("dans bonus nv res %d\n", pecheur->nv_reserves);
	/*bonus premier poisson*/
	if(first_fish(pecheur->nv_reserves, bonus_tab[0]))
		bonus_tab[0]=1;
	
	/*bonus premier morceau de pont*/
	if(first_bridge(pecheur->bridge, bonus_tab[1]))
		bonus_tab[1]=1;

	/*bonus poisson*/
	if(fish(pecheur->nv_reserves, bonus_tab[0]))
		bonus_tab[2]=1;

	/*bonus pont*/
	if(bridge(pecheur->bridge, bonus_tab[1]))
		bonus_tab[3]=1;
	
	/*bonus ecolo*/
	if(ecolo(pecheur->ecolo, bonus_tab[4]))
		bonus_tab[4]=1;
	
	/*bonus île, débloque filet*/
	if(island(pecheur))
		bonus_tab[5]=1;

	/*bonus vision*/
	if(vision(pecheur, bonus_tab[6]))
		bonus_tab[6]=1;
	

}
	




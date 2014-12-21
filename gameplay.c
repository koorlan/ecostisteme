#include "gameplay.h" 

/***bonus_tab : 
	indice		0		1		2	3		4		5		6		7	
	sens		first_fish	first_bridge	fish	bridge		écolo		life bonus	filet		vision
	valeur		0;1;2		0;1;2		0;1	0;1		0;1		0;1;0		0;1 		0;1 	
***/


int first_fish(int nv_reserves, int bonus)
{	return(nv_reserves!=0 && bonus==0);
}

int first_bridge(int bridge, int bonus)
{	return(bridge!=0 && bonus==0);
}

int fish(int nv_reserves, int bonus)
{	return (nv_reserves!=0 && bonus==2);
}

int bridge(int bridge, int bonus)
{	return (bridge!=0 && bonus==2);
}

int island(fisher * pecheur)
{	return (pecheur->x==TAILLE_PLATEAU/2-1 && pecheur->y==TAILLE_PLATEAU/2-1);
}

int vision(fisher *pecheur, int bonus)
{	return (pecheur->xp>=300 && bonus==0);
}

void afficher_bonus(int n)
{	set_drawing_color(color_LIGHTRED);
	switch (n)
	{	case 0 :
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+10, M2+45, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M1+10, M2+28, "1er poisson");
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+10, M2, "+50 XP");
			break;
		case 1 : 
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+10, M2+45, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M1+15, M2+28, "1er pont");
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+10, M2, "+50 XP");
			break;
		case 2 : 
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+10, M2+45, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M1+10, M2+28, "poisson");
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+10, M2, "+25 XP");
			break;
		case 3 : 
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+10, M2+45, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M1+10, M2+28, "pont");
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+10, M2, "+25 XP");
			break;
	
		case 6 : 
			
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+10, M2+120, "BONUS");
			set_font(font_HELVETICA_12);
			draw_printf(WINDOW_WIDTH-M1+10, M2+103, "ile deserte");
			set_font(font_HELVETICA_18);
			draw_printf(WINDOW_WIDTH-M1+10, M2+75, "+200 XP");
			break;
	}

}


void afficher_xp(fisher * pecheur)
{	set_font(font_HELVETICA_18);
	set_drawing_color(color_BLACK);
	draw_printf(WINDOW_WIDTH/2-70, M2/2-5, "VOTRE XP : %d", pecheur->xp);
}

void appliquer_bonus(fisher * pecheur, int bonus_tab[])
{	/*1er poisson*/	
	if(bonus_tab[0]==1)
	{	pecheur->xp=pecheur->xp+50;
		bonus_tab[0]=2;
		afficher_bonus(0);
	}
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
	/*island*/
	if(bonus_tab[6]==1)
	{	pecheur->xp=pecheur->xp+200;
		afficher_bonus(6);
	}
	if(bonus_tab[7]==1)
	{	afficher_bonus(7);
	}
	afficher_xp(pecheur);
}

void capitaliser_bonus(fisher * pecheur, int bonus_tab[])
{	/*bonus premier poisson*/
	if(first_fish(pecheur->nv_reserves, bonus_tab[0]))
		bonus_tab[0]=1;

	/*bonus poisson*/
	if(fish(pecheur->nv_reserves, bonus_tab[0]))
		bonus_tab[2]=1;

	/*bonus premier morceau de pont*/
	if(first_bridge(pecheur->bridge, bonus_tab[1]))
		bonus_tab[1]=1;

	/*bonus pont*/
	if(bridge(pecheur->bridge, bonus_tab[1]))
		bonus_tab[3]=1;
	
	/*bonus île, bébloque filet*/
	if(island(pecheur))
		bonus_tab[6]=1;

	/*bonus vision*/
	if(vision(pecheur, bonus_tab[7]))
		bonus_tab[7]=1;
	

}
	




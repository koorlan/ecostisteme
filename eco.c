#include "eco.h"


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
	
	for(i=0;i<=N;i++)
	{	draw_line(M1+i*(WINDOW_WIDTH-M3)/N, M2, M1+i*(WINDOW_WIDTH-M3)/N, WINDOW_HEIGHT-M4);
		draw_line(M1, M2+i*(WINDOW_HEIGHT-2*M4)/N, (WINDOW_WIDTH-M3)+M1, M2+i*(WINDOW_HEIGHT-2*M4)/N);
	}		
	update_graphics();	
}

void afficher_point(int x, int y, couleurs coul)
/*affichage d'un individu sur la grille en fonction de son espèce*/
{	set_drawing_color(coul);
	draw_circle_full(M1+(x-0.5)*(WINDOW_WIDTH-M3)/(N), M2+(y-0.5)*(WINDOW_HEIGHT-2*M4)/(N), 4.5);
}

void draw_square(int x, int y, couleurs coul)
{		
	set_drawing_color(coul);
	set_fill_color(coul);
	draw_rectangle_full(M1+x*(WINDOW_WIDTH-M3)/N-1, M2+y*(WINDOW_HEIGHT-2*M4)/N -1, M1+(x-1)*(WINDOW_WIDTH-M3)/N+1, M2+(y-1)*(WINDOW_HEIGHT-2*M4)/N +1);

}

//useless
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


int start_screen ()
{	int select=0;
	int current=1;	
	set_drawing_color(color_WHITE);
	set_font(font_HELVETICA_18);
	draw_printf(WINDOW_WIDTH/2-160, WINDOW_HEIGHT/2+40, "CHOIX DU MODE DE JEU\n");
	set_font(font_HELVETICA_12);
	
	draw_printf(WINDOW_WIDTH/2-190, WINDOW_HEIGHT/2-40, "Appuyez sur la touche ENTREE pour selectionner\n");
	set_font(font_HELVETICA_18);			
	set_drawing_color(color_LIGHTRED);
	draw_printf(WINDOW_WIDTH/2-280, WINDOW_HEIGHT/2, "Ecosysteme seul");
	set_drawing_color(color_WHITE);
	draw_printf(WINDOW_WIDTH/2-105, WINDOW_HEIGHT/2, "Mode 1 joueur");
	draw_printf(WINDOW_WIDTH/2+55, WINDOW_HEIGHT/2, "Mode 2 joueurs");
	update_graphics();
	while(select!=key_ENTER){
	select=get_key();
	switch (select)	
	{	case key_RIGHT:
				set_font(font_HELVETICA_18);			
				set_drawing_color(color_WHITE);
				if (current==1)
				{	draw_printf(WINDOW_WIDTH/2-280, WINDOW_HEIGHT/2, "Ecosysteme seul");	
					set_drawing_color(color_LIGHTRED); 
					draw_printf(WINDOW_WIDTH/2-105, WINDOW_HEIGHT/2, "Mode 1 joueur");
					current ++;
					
				}	
				else if (current==2)
				{	draw_printf(WINDOW_WIDTH/2-105, WINDOW_HEIGHT/2, "Mode 1 joueur");	
					set_drawing_color(color_LIGHTRED);
					draw_printf(WINDOW_WIDTH/2+55, WINDOW_HEIGHT/2, "Mode 2 joueurs");
					current ++;
				
				}
				break;
		case key_LEFT:	
				set_font(font_HELVETICA_18);	

				set_drawing_color(color_WHITE);
				if (current==3)
				{	draw_printf(WINDOW_WIDTH/2+55, WINDOW_HEIGHT/2, "Mode 2 joueurs");	
					set_drawing_color(color_LIGHTRED); 
					draw_printf(WINDOW_WIDTH/2-105, WINDOW_HEIGHT/2, "Mode 1 joueur");
					current --;
				}
				else if (current==2)
				{	draw_printf(WINDOW_WIDTH/2-105, WINDOW_HEIGHT/2, "Mode 1 joueur");
					set_drawing_color(color_LIGHTRED);
					draw_printf(WINDOW_WIDTH/2-280, WINDOW_HEIGHT/2, "Ecosysteme seul");	
					current --;
				}
				break;
		default :
				set_font(font_HELVETICA_12);			
				set_drawing_color(color_LIGHTRED);	
				draw_printf(150, M4, "Utiliser les fleches pour changer de selection");
				break;
		}
		update_graphics();
			
	}
	return current-1;
}
void titre()
{	set_font(font_HELVETICA_18);
	set_drawing_color(mobs_draw[0]);
}

void sous_titre()
{	set_font(font_HELVETICA_18);
	set_drawing_color(mobs_draw[12]);
}

void texte()
{	set_drawing_color(color_WHITE);
	set_font(font_HELVETICA_12);
}

void aide()
{	int stop;
	set_drawing_color(color_BACKGROUND);
	draw_rectangle_full(0,0,WINDOW_WIDTH-M3+M1+18,WINDOW_HEIGHT);


	titre();	
	draw_printf(280, 650, "Besoin d'un peu d'aide ?");
	sous_titre();	
	draw_printf(20, 610, "Deplacement hors de l'eau");	
	texte();	
	draw_printf(20, 590, "Le deplacement s'effectue avec les fleches (H, B, G, D). Pour finir le deplacement appuyez sur ENTREE. Vous pouvez vous");
	draw_printf(20, 570, "deplacer autour du lac, sur le pont et sur l'ile.");
	sous_titre();	
	draw_printf(20, 530, "Deplacement dans l'eau");
	texte();
	draw_printf(20, 510, "Lorsque vous tombez dans l'eau il faut rejoindre le rivage, le pont ou l'ile. Vous perdrez toutes vos reserves. Attention, si vous");
	draw_printf(20, 490, "croisez un predateur vous mourrez.");
	sous_titre();
	draw_printf(20, 450, "Actions possibles");
	texte();
	draw_printf(20, 430, "Apres le deplacement, l'onglet 'actions disponibles' du menu vous indique ce que vous pouvez faire (peche, construction du");
	draw_printf(20, 410, "pont...). Utilisez les fleches (H, B) pour naviguer entre les differents choix puis tapez ENTREE pour valider."); 
	sous_titre();	
	draw_printf(20, 370, "Experience et bonus");
	texte();
	draw_printf(20, 350, "Au cours de la partie vous devrez capitaliser de l'experience, vous la gagnerez en debloquant les bonus suivants :");
	draw_printf(50, 330, "- Bonus 1er poisson peche / Bonus 1er pont construit : 50 XP chacun");
	draw_printf(50, 310, "- Bonus poisson peche / Bonus pont construit : 25 XP chacun");
	draw_printf(50, 290, "- Bonus ile deserte : 200 XP attribues si vous atteignez l'ile");
	draw_printf(20, 270, "Il existe aussi des bonus qui rapportent d'autres avantages que des points d'experience :");
	draw_printf(50, 250, "- Bonus vision : la carte se decouvre pour chaque joueur ayant au moins 300 XP");
	draw_printf(50, 230, "- Bonus ile deserte : debloque un filet de peche");	
	draw_printf(50, 210, "- Bonus ecolo : relachez 3 poissons dans l'eau pour pouvoir pecher la pollution. Celle-ci vous rapportera 10 munitions.");
	sous_titre();
	draw_printf(20, 170, "Victoire");
	texte();
	draw_printf(20, 150, "En mode 2 joueurs, le gagnant est celui qui atteint 10 000 XP en premier. En mode 1 joueur, il faut atteindre 10 000 XP le plus");
	draw_printf(20, 130, "vite possible pour entrer dans le classement des 3 meilleurs scores. Votre score final correspondra au nombre de tours qu'il");
	draw_printf(20, 110, "vous aura fallu pour terminer la partie. Les scores les plus faibles sont donc les meilleurs!");
	sous_titre();
	draw_printf(20, 70, "Quitter cette page");
	texte();
	draw_printf(20, 50, "Il suffit d'appuyer sur la touche q."); 
	update_graphics();
	while(stop!='q')	
		stop=get_key();	
	
	
}

int troc(fisher * pecheur)	
{	int go=0;
	int gain =0;
	srand(time(0));
	set_drawing_color(color_BACKGROUND);
	draw_rectangle_full(0,0,WINDOW_WIDTH-M3+M1+18,WINDOW_HEIGHT);
	sous_titre();
	draw_printf(250, 650, "Bienvenue au troc de l'ile !");
	texte();
	draw_printf(20, 610, "C'est ici que pirates et nauffrages echangent leurs marchandises. En plein rush vers la victoire peut-etre aurez vous besoin de");
	draw_printf(20, 590,"troquer vos propres reserves de poisson contre de precieux points d'experience.");
	draw_printf(20, 570, "Si la chance est avec vous, cela pourrait vous rapporter gros. Cependant prenez garde, il vous est impossible de discerner les");
	draw_printf(20, 550,"filous des honnetes gens parmi les acheteurs. Et des vendeurs novices tels que vous ne peuvent se permettre de refuser une"); 
	draw_printf(20, 530, "offre. Donc une seule regle s'applique: si vous choisisssez de leguer vos reserves cela est irreversible, et SANS"); 
	draw_printf(20, 510, "GARANTIE ...");
	draw_printf(20, 470, "Vous etes sur le point de troquer 8 reserves, appuyez sur ENTREE pour commencer");
	update_graphics();	
	while(go!=key_ENTER)
		go=get_key();
	set_drawing_color(color_BACKGROUND);
	draw_printf(20, 470, "Vous etes sur le point de troquer 8 reserves, appuyez sur ENTREE pour commencer");
	gain = rand()%(450-1)+1;
	sous_titre();
	draw_printf(245, 400, "Ce troc vous a rapporté %d XP", gain);
	texte();
	draw_printf(265, 380, "Appuyez sur une touche pour quitter");
	update_graphics();
	go=get_key();
	return gain;
}


int final_screen(FILE *fscore, char name [8])
{	int select=0;
	int current=1;
	int score[3]={0};
	int i=0, k=0;
	int res=WORLD_TIME/10;

	clear_screen();
	set_background_color(color_BACKGROUND);
	set_drawing_color(color_WHITE);
	set_font(font_HELVETICA_18);
	set_drawing_color(color_WHITE);

	fscanf(fscore, "%d %d %d", &score[0], &score[1], &score[2]);
 	fseek(fscore, 0, SEEK_SET);
	
	    	
	draw_printf(WINDOW_WIDTH/2-150, WINDOW_HEIGHT/2+40, "Le gagnant est :");
	//Affichage du nom du gagnant
	while(name[i]!='\0')
	{	draw_printf(WINDOW_WIDTH/2+5+k, WINDOW_HEIGHT/2+40, "%c", name[i]);
		if(name[i]=='l'||name[i]=='r'||name[i]=='i')
			k+=8;
		else
			k+=12;
		i++;
	}

	//draw_printf(WINDOW_WIDTH/2-130, WINDOW_HEIGHT/2+20, "Le gagnant est :");
	set_font(font_HELVETICA_12);
	draw_printf(WINDOW_WIDTH/2-170, WINDOW_HEIGHT/2-60, "Appuyez sur la touche ENTREE pour quitter\n");
	set_font(font_HELVETICA_18);
	set_drawing_color(mobs_draw[0]);
	draw_printf(WINDOW_WIDTH/2-120, WINDOW_HEIGHT/2-10, "Votre score : %d", res);			
	//if(score==0 || res<=score)
	//{	
		//draw_printf(WINDOW_WIDTH/2-180, WINDOW_HEIGHT/2-40, "Les 3 meilleurs scores sont ");
		//fseek(fscore, 0, SEEK_SET);
		//fprintf(fscore, "%d", res);	
	//}	
	if(res<=score[0])
	{
		fprintf(fscore, "%d %d %d", res, score[0], score[1]);
		score[2]=score[1];
		score[1]=score[0];
		score[0]=res;
	}	
	else if(res<=score[1])
	{	
		fprintf(fscore, "%d %d %d", score[0], res, score[1]);
		score[2]=score[1];
		score[1]=res;	
	}

	else if(res<=score[2])
	{
		fprintf(fscore, "%d %d %d", score[0], score[1], res);
		score[2]=res;
	}	
	
	draw_printf(WINDOW_WIDTH/2-190, WINDOW_HEIGHT/2-40, "Les 3 meilleurs scores sont [%d] [%d] [%d]", score[0], score[1], score[2]);
	//else if((WORLD_TIME/10)>score)
	//	draw_printf(WINDOW_WIDTH/2-180, WINDOW_HEIGHT/2-40, "Le meilleur score enregistre est : %d", score);
		
	
	update_graphics();
	
	while(select!=key_ENTER)
		select=get_key();
	return 1;
}


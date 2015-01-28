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


/*affichage d'une grille n*n cases*/
void affiche_grille()
{	int i;
	
	for(i=0;i<=N;i++)
	{	draw_line(M1+i*(WINDOW_WIDTH-M3)/N, M2, M1+i*(WINDOW_WIDTH-M3)/N, WINDOW_HEIGHT-M4);
		draw_line(M1, M2+i*(WINDOW_HEIGHT-2*M4)/N, (WINDOW_WIDTH-M3)+M1, M2+i*(WINDOW_HEIGHT-2*M4)/N);
	}		
	update_graphics();	
}


/*Affichage d'un individu sur la grille en fonction de son espèce*/
void afficher_point(int x, int y, couleurs coul)
{	set_drawing_color(coul);
	draw_circle_full(M1+(x-0.5)*(WINDOW_WIDTH-M3)/(N), M2+(y-0.5)*(WINDOW_HEIGHT-2*M4)/(N), 4.5);
}


/*Affichage d'un élément de forme carrée sur la grille de jeu (pont, ile, curseur)*/
void draw_square(int x, int y, couleurs coul)
{		
	set_drawing_color(coul);
	set_fill_color(coul);
	draw_rectangle_full(M1+x*(WINDOW_WIDTH-M3)/N-1, M2+y*(WINDOW_HEIGHT-2*M4)/N -1, M1+(x-1)*(WINDOW_WIDTH-M3)/N+1, M2+(y-1)*(WINDOW_HEIGHT-2*M4)/N +1);

}

//Cette fonction n'est plus utilisée
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


/*Ecran d'acceuil -> choix du mode de jeu*/
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

/******Petite charte graphique***********/
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
/*****************************************/


/*Affichage de la page d'aide*/
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
	draw_printf(20, 490, "croisez un predateur vous mourrez et 50 points d'experience vous seront retires.");
	sous_titre();
	draw_printf(20, 450, "Actions possibles");
	texte();
	draw_printf(20, 430, "Apres le deplacement, l'onglet 'Actions' du menu vous indique ce que vous pouvez faire (peche, construction du pont, etc...).");
	draw_printf(20, 410, "Utilisez les fleches (H, B) pour naviguer entre les differents choix puis tapez sur ENTREE pour valider."); 
	sous_titre();	
	draw_printf(20, 370, "Experience et bonus");
	texte();
	draw_printf(20, 350, "Au cours de la partie vous devrez capitaliser de l'experience, vous la gagnerez en debloquant les bonus suivants :");
	draw_printf(50, 330, "- Bonus 1er poisson peche / Bonus 1er pont construit : 50 XP chacun");
	draw_printf(50, 310, "- Bonus poisson peche / Bonus pont construit : 25 XP chacun");
	draw_printf(50, 290, "- Bonus ile deserte : 200 XP attribues si vous atteignez l'ile");
	draw_printf(20, 270, "Il existe aussi des bonus qui rapportent d'autres avantages que des points d'experience :");
	draw_printf(50, 250, "- Bonus vision : la carte se decouvre pour chaque joueur ayant au moins 300 XP");
	draw_printf(50, 230, "- Bonus ile deserte : debloque un filet de peche. Aussi vous pourrez troquer vos reserves contre des points d'experience.");	
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

/*Page du troc de l'île*/
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

/*Ecran final : nom et score du gagnant + 3 meilleurs score*/
int final_screen(FILE *fscore, char name [8])
{	int select=0;
	int score[3]={0};
	int i=0, k=0;
	int res=(WORLD_TIME/2);
	char * name0;
	char * name1;
	char * name2;
	name0=calloc(8, sizeof(char));
	name1=calloc(8, sizeof(char));
	name2=calloc(8, sizeof(char));
	
	clear_screen();

	set_background_color(color_BACKGROUND);
	set_drawing_color(color_WHITE);
	set_font(font_HELVETICA_18);
	set_drawing_color(color_WHITE);
	fseek(fscore, 0, SEEK_SET);
	
	//Lecture des 3 meilleurs scores dans le fichier "scores.txt"
	fscanf(fscore, "%d %d %d\n", &score[0], &score[1], &score[2]);
	
	//Lecture des noms des 3 meilleurs joueurs
	fscanf(fscore, "%s\n", name0);
	fscanf(fscore, "%s\n", name1);
	fscanf(fscore, "%s\n", name2);

	fseek(fscore, 0, SEEK_SET);
	
	
	
	//Affichage du nom du gagnant
	set_drawing_color(mobs_draw[0]); 	
	draw_printf(WINDOW_WIDTH/2-100, WINDOW_HEIGHT/2+50, "Le gagnant est : ");
	set_drawing_color(color_WHITE);
	draw_printf(WINDOW_WIDTH/2+38, WINDOW_HEIGHT/2+50,"%s", name);
	
	set_font(font_HELVETICA_12);
	draw_printf(WINDOW_WIDTH/2-135, WINDOW_HEIGHT/8+70, "Appuyez sur la touche ENTREE pour quitter\n");
	set_font(font_HELVETICA_18);

	//Affichage du score du gagnant
	set_drawing_color(mobs_draw[0]);
	draw_printf(WINDOW_WIDTH/2-145, WINDOW_HEIGHT/2+20, "Votre score : ", res);	
	set_drawing_color(color_WHITE);
	draw_printf(WINDOW_WIDTH/2-35, WINDOW_HEIGHT/2+20, "%d tours pour gagner", res);
	set_drawing_color(mobs_draw[0]);
	
	//enregistrement du score du joueur s'il fait partie des 3 meilleurs scores 
	if(res<=score[0])
	{	
		fprintf(fscore, "%d %d %d\n", res, score[0], score[1]);
		fprintf(fscore, "%s\n%s\n%s\n", name, name0, name1);
		fseek(fscore, 0, SEEK_SET);		
		fscanf(fscore, "%d %d %d\n", &score[0], &score[1], &score[2]);
		fscanf(fscore, "%s\n%s\n%s\n", name0, name1, name2);		
	
	}	
	else if(res<=score[1])
	{	
		fprintf(fscore, "%d %d %d\n", score[0], res, score[1]);
		fprintf(fscore, "%s\n%s\n%s\n",name0, name, name1);
		fseek(fscore, 0, SEEK_SET);		
		fscanf(fscore, "%d %d %d\n", &score[0], &score[1], &score[2]);
		fscanf(fscore, "%s\n%s\n%s\n", name0, name1, name2);	
			
	}

	else if(res<=score[2])
	{
		fprintf(fscore, "%d %d %d\n", score[0], score[1], res);
		fprintf(fscore, "%s\n%s\n%s\n",name0, name1, name);
		fseek(fscore, 0, SEEK_SET);		
		fscanf(fscore, "%d %d %d\n", &score[0], &score[1], &score[2]);
		fscanf(fscore, "%s\n%s\n%s\n", name0, name1, name2);	
	}
	
	/***Tableau des 3 meilleurs scores enregistrés***/	
	draw_printf(WINDOW_WIDTH/4, WINDOW_HEIGHT/2-40, "3 meilleurs scores");	
	//vertical
	draw_line(WINDOW_WIDTH/4, WINDOW_HEIGHT/4, WINDOW_WIDTH/4, (7*WINDOW_HEIGHT)/16);
	draw_line((3*WINDOW_WIDTH)/4, WINDOW_HEIGHT/4, (3*WINDOW_WIDTH)/4, (7*WINDOW_HEIGHT)/16);

	//horizontal 
	draw_line(WINDOW_WIDTH/4, WINDOW_HEIGHT/4, (3*WINDOW_WIDTH)/4, WINDOW_HEIGHT/4);
	draw_line(WINDOW_WIDTH/4, (5*WINDOW_HEIGHT)/16, (3*WINDOW_WIDTH)/4, (5*WINDOW_HEIGHT)/16);
	draw_line(WINDOW_WIDTH/4, (3*WINDOW_HEIGHT)/8, (3*WINDOW_WIDTH)/4, (3*WINDOW_HEIGHT)/8);
	draw_line(WINDOW_WIDTH/4, (7*WINDOW_HEIGHT)/16, (3*WINDOW_WIDTH)/4, (7*WINDOW_HEIGHT)/16);
	
	//remplissage du tableau
	set_drawing_color(color_WHITE);
	draw_printf(WINDOW_WIDTH/4+10, (3*WINDOW_HEIGHT)/8+((7*WINDOW_HEIGHT)/16-(3*WINDOW_HEIGHT)/8)/4, "joueur %s", name0);
	draw_printf(WINDOW_WIDTH/4+390, (3*WINDOW_HEIGHT)/8+((7*WINDOW_HEIGHT)/16-(3*WINDOW_HEIGHT)/8)/4, "score %d", score[0]);
	draw_printf(WINDOW_WIDTH/4+10, (5*WINDOW_HEIGHT)/16+((3*WINDOW_HEIGHT)/8-(5*WINDOW_HEIGHT)/16)/4, "joueur %s", name1); 
	draw_printf(WINDOW_WIDTH/4+390, (5*WINDOW_HEIGHT)/16+((3*WINDOW_HEIGHT)/8-(5*WINDOW_HEIGHT)/16)/4, "score %d", score[1]);
	draw_printf(WINDOW_WIDTH/4+10, (WINDOW_HEIGHT)/4+((5*WINDOW_HEIGHT)/16-(WINDOW_HEIGHT)/4)/4, "joueur %s", name2);
	draw_printf(WINDOW_WIDTH/4+390, (WINDOW_HEIGHT)/4+((5*WINDOW_HEIGHT)/16-(WINDOW_HEIGHT)/4)/4, "score %d", score[2]);
	update_graphics();
	
	while(select!=key_ENTER)
		select=get_key();
	return 1;
}


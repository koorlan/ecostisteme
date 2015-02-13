//somecommentary

#include "main.h"


/*Affiche un menu à droite du plateau de jeu*/
void menu(Liste * species[],fisher *pecheur, int bonus_tab[], Mob *plateau[][TAILLE_PLATEAU]);

/*Ecran de saisie du mon des joueurs*/
void saisi_nom_screen(fisher *pecheur);

/*Retourne un entier compris entre a et b*/
int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}


int main(int argc, char const *argv[])
{	
	start_graphics(); //ouverture de la fenêtre graphique
	
	//initialisation des descripteurs de fichiers (acquisition écolution de l'ecosysteme + scores)
	FILE *fPtr;	
	FILE *gnuplot = popen("gnuplot", "w");
	FILE *fscore;
	fPtr=fopen("records.csv","w+");
	if (fPtr == NULL)
	    printf("Error in opening file\n");

	srand (time (NULL));
	
   	Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU];
	
  	int i = 0; // Compteur pour gérer les listes d'especes
	
	/***Initialisation du pêcheur***/
	
	fisher pecheur;
	fisher pecheur2;

	//Variables de déplacement du (des) pêcheur(s)	
	int x=0;
	int y=0;

	int x2=TAILLE_PLATEAU+1;
	int y2=TAILLE_PLATEAU+1;
	
	int mort_pecheur=0;
	int mort_pecheur2=0;

	//initialisation du (des) pecheur(s) 
	init_fisher(&pecheur, x, y, 1);
	init_fisher(&pecheur2, x2, y2, 2);	
	
	/*troc(&pecheur);
	update_graphics();
	x=get_key();*/	

	//initialisation de la table des bonus (voir dans bonus.c)
	int bonus_tab[8]={0};
	int bonus_tab2[8]={0};

// Pour tester le jeu en mode triche : 
	pecheur.reserves = 5000; 	// reserves illimitees 
//	pecheur.xp =9999;		//tester la fin du jeu
	bonus_tab[6]=1; 		//vision pour le joueur 1
//	bonus_tab2[6]=1;		//vision pour le joueur 2  
//	bonus_tab[5]=1; 		//filet débloqué
// Attention, si vous combinez cheat xp + cheat filet le jeu s'arrete immédiatement (xp > 10 000)*/

	//choix du mode de jeu : 0 pour le mode ecosysteme seul, 1 pour le mode 1 joueur, 2 pour le mode 2 joueurs
	int mode_joueur=start_screen();
	clear_screen();
	switch (mode_joueur){
		case 0:	bonus_tab[6]=1;				//ecosysteme seul
			pecheur.nom_joueur[0]='\0';
				break;
		case 1: saisi_nom_screen(&pecheur);		//mode 1 joueur
				break;
		case 2: saisi_nom_screen(&pecheur);
				saisi_nom_screen(&pecheur2);	//mode 2 joueurs
				break;

		default: printf("Un erreur s'est produite lors de la selection du mode\n");
			stop_graphics();			 
			exit(-1);
	}

	init_grid(plateau_de_jeu);

	
	if(mode_joueur)		//génération de l'île 
	{	spawn_island(plateau_de_jeu);
		fscore=NULL;
		fscore = fopen("scores.txt", "r+");
		if(fscore==NULL)
		{	printf("Erreur lors de l'ouverture du fichier scores.txt\n");
			stop_graphics();	
			exit(EXIT_FAILURE);
		}
	}



	/***Initialisation des espèces***/
	//Génération des listes de mobs......................................................................................
   		
	Liste * species[] = {NULL, init_mobs(1,5), init_mobs(2, 3), init_mobs(3,6), init_mobs(4, 3), init_mobs(5, 2), init_mobs(6, 4), init_mobs(7, 5), init_mobs(8, 2), init_mobs(9, 2)};

   	fprintf(fPtr,"%s","WORLD_TIME");

	//Génération des mobs sur le plateau de jeu..........................................................................	
	for ( i = 1; i <= NB_SPECIES; ++i)
	{
		spawn_list_animal_random(plateau_de_jeu, species[i]);
		fprintf(fPtr,",%d",i);
	}

	draw_grid(plateau_de_jeu, bonus_tab[6]);
	update_graphics(); 
	Mob * ptr=malloc(sizeof(Mob));
	Liste * elt=malloc(sizeof(Liste));
	WORLD_TIME=0;

	do
	{	fprintf(fPtr,"\n%d", WORLD_TIME);
		
		/***Jeu du pêcheur***/
		if(!mode_joueur) 
		{
			menu(species,&pecheur,bonus_tab, plateau_de_jeu);
			fprintf(gnuplot, "%s \n", " load 'draw_graph.gnuplot'");
			fflush(gnuplot);

		}

		//Jeu du pêcheur tous les 10 tours d'écosystème...............................................................
		if(WORLD_TIME % 2 == 0 && mode_joueur!=0)
		{	
			menu(species,&pecheur,bonus_tab, plateau_de_jeu);	//affichage du menu
			update_graphics();
			jeu_du_pecheur(&pecheur, plateau_de_jeu, bonus_tab, &mort_pecheur, species);	//jeu du pecheur 1
			if(mode_joueur==2 && !mort_pecheur){
				menu(species,&pecheur2,bonus_tab2, plateau_de_jeu);	
				draw_grid(plateau_de_jeu, bonus_tab2[6]);
				update_graphics();
				draw_grid(plateau_de_jeu, bonus_tab2[6]);				
				jeu_du_pecheur(&pecheur2, plateau_de_jeu, bonus_tab2, &mort_pecheur2, species);	
				update_graphics();
			}
		} 	
		
		/***Jeu de l'IA***/	
		if(!mort_pecheur&&!mort_pecheur2)
		{	
			draw_grid(plateau_de_jeu, bonus_tab[6]);
			for (int i = 1; i <= NB_SPECIES; ++i)
			{
				elt=species[i];
				while(elt->nxt !=NULL)
				{	
					ptr = &(elt->mob);
					ia_mob(ptr,plateau_de_jeu,species);
					elt = elt->nxt;							
				}	
				fprintf(fPtr,",%d",(nombre_elts_liste(species[i])*100)/(TAILLE_PLATEAU * TAILLE_PLATEAU) ) ;
			}	
			draw_grid(plateau_de_jeu, bonus_tab[6]);
			fflush(fPtr);	
			WORLD_TIME++;
		}
	
			
	}while( WORLD_TIME <= 1000 && !mort_pecheur && !mort_pecheur2 && pecheur.xp<10000 && pecheur2.xp<10000);
	
	

	if(bonus_tab[7])
		final_screen(fscore, pecheur.nom_joueur);	//joueur 1 a gagné
		
	else if(bonus_tab2[7])
		final_screen(fscore, pecheur2.nom_joueur);	//joueur 2 a gagné
		
	//Fermeture des fichiers d'acquisition de données / scores
	if(fPtr!=NULL)
		fclose(fPtr);
	if(mode_joueur && fscore!=NULL)
		fclose(fscore);
	
	//Fermeture de la fenetre graphique
	stop_graphics();
	
	return 0;
}			


//gestion de l'affichage d'un menu informatif 
void menu(Liste * species[], fisher *pecheur, int bonus_tab[], Mob *plateau[][TAILLE_PLATEAU])
{
	set_drawing_color(color_WHITE);
	int i = 0 ;
	int x_menu = WINDOW_WIDTH-M3+M1+20;
	int y_menu = WINDOW_HEIGHT ; // x et y serviront de curseurs pour se deplacer dans la fenêtre du menu 
	
	//refresh 
	set_drawing_color(color_BACKGROUND);
	draw_rectangle_full(x_menu,y_menu-450, WINDOW_WIDTH, y_menu-540);
	
	//mise à jour des bonus des joueurs 
	capitaliser_bonus(pecheur, bonus_tab, plateau);
	pecheur->bridge=0;
	afficher_point(pecheur->x, pecheur->y, mobs_draw[10]);
	appliquer_bonus(pecheur, bonus_tab);

	set_drawing_color(color_WHITE);

	//ligne verticale séparation menu / plateau
	draw_line(x_menu,0,x_menu,y_menu);
	
	//**En-tete
	set_font(font_HELVETICA_18);
	x_menu += 2;
	y_menu -= 18+20;
	draw_printf(x_menu, y_menu, "Jeu de la VIE");
	set_font(font_HELVETICA_12);
	y_menu -= 12+5;
	draw_printf(x_menu, y_menu, "3A-STI 2014/2015");

	//**Informations Plateau
	y_menu -= 12+5;
	x_menu -=2; 
	draw_line(x_menu,y_menu,WINDOW_WIDTH,y_menu);
	y_menu -= 12+5;
	x_menu +=2;
	draw_printf(x_menu, y_menu, "Informations sur l'ecosysteme ");
	
	set_font(font_HELVETICA_18);
	y_menu -= 18+5;
	set_drawing_color(color_BACKGROUND);
	draw_rectangle_full(x_menu,y_menu,WINDOW_WIDTH,y_menu+18);
	set_drawing_color(color_LIGHTRED);
	draw_printf(x_menu, y_menu, "TOUR : %d",WORLD_TIME);
	set_font(font_HELVETICA_12);
	y_menu -= 12+5;
	for (i = 1; i <= NB_SPECIES; ++i)
	{
		set_drawing_color(color_BACKGROUND);
		draw_rectangle_full(x_menu,y_menu,WINDOW_WIDTH,y_menu+12); //clear previous type
		set_drawing_color(mobs_draw[i]);
		draw_printf(x_menu,y_menu,"%s : %d ",mobs_name[i],(nombre_elts_liste(species[i])*100)/(TAILLE_PLATEAU * TAILLE_PLATEAU));
		y_menu -= 12+5;
	}
	set_drawing_color(color_WHITE);

	//**Informations Joueur
	draw_line(x_menu,y_menu,WINDOW_WIDTH,y_menu);
	y_menu -= 12+5;
	draw_printf(x_menu, y_menu, "Informations sur le joueur ");
	y_menu -= 12+5;
	//***Nom, réserves, xp
	set_drawing_color(color_BACKGROUND);
	draw_rectangle_full(x_menu,y_menu+12+5,WINDOW_WIDTH,y_menu-((12+5)*4)); 
	
	set_drawing_color(color_LIGHTRED);
	draw_printf(x_menu, y_menu, "%s joue !",pecheur->nom_joueur);
	set_drawing_color(color_WHITE);
	y_menu -= 12+5;
	draw_printf(x_menu, y_menu, "Reserves : %d (+%d)",pecheur->reserves,pecheur->nv_reserves);
	y_menu -= 12+5;
	draw_printf(x_menu, y_menu, "Xp : %d ",pecheur->xp);
	y_menu -= 12+5;
	
	//**Compétences 
	if (bonus_tab[4]){
		set_drawing_color(color_LIGHTGREEN);
		draw_printf(x_menu, y_menu, "Bravo l'ecolo !");
	} else{	
		set_drawing_color(color_LIGHTRED);
		draw_printf(x_menu, y_menu, "Tu n'es pas tres ecolo");
	}

	y_menu -= 12+5;
	if (bonus_tab[6])
	{
		set_drawing_color(color_LIGHTMAGENTA);
		draw_printf(x_menu, y_menu, "Tu es voyant :)");
	} 
	else {
		set_drawing_color(color_LIGHTMAGENTA);
		draw_printf(x_menu, y_menu, "Aveugle...");
	}
	y_menu -= 12+5;
	set_drawing_color(color_WHITE);
	draw_printf(x_menu, y_menu, "Peche possible : ");
	y_menu -= 12+5;
	set_drawing_color(color_BACKGROUND);
	draw_rectangle_full(x_menu,y_menu,WINDOW_WIDTH,y_menu+12); //clear previous type
	for (i = 1; i <= NB_SPECIES; ++i)
	{
		if (eat_mat[10][i] && nombre_elts_liste(species[i])!=0){
			set_drawing_color(mobs_draw[i]);
			draw_circle_full(x_menu+((i-1)*12),y_menu+6, 4.5);
		}
	}
	if(bonus_tab[4]==2 && nombre_elts_liste(species[4]))		
	{	set_drawing_color(mobs_draw[5]);
		draw_circle_full(x_menu+((5-1)*12), y_menu+6, 4.5);
	}
	y_menu -= 12+5;
	set_drawing_color(color_WHITE);

	//**Evénement
	draw_line(x_menu,y_menu,WINDOW_WIDTH,y_menu);
	y_menu -= 12+5;
	draw_printf(x_menu, y_menu, "Evenement : ");
	y_menu -= 100;
	
	set_drawing_color(color_WHITE);

	//**Actions_dispo
	draw_line(x_menu,y_menu,WINDOW_WIDTH,y_menu);
	y_menu -= 12+5;
	draw_printf(x_menu, y_menu, "Actions : ");
	set_drawing_color(color_BACKGROUND);
	draw_rectangle_full(x_menu,y_menu,WINDOW_WIDTH, 0); //refresh


}

//Saisie au clavier du nom du (des) joueur(s) au début de la partie
void saisi_nom_screen(fisher *pecheur){
	clear_screen();
	set_font(font_HELVETICA_18);
	set_drawing_color(color_WHITE);
	int x_menu = 10;
	int y_menu = WINDOW_HEIGHT-18-10 ;
	int pas = 12; //pas de decalage entre affichage des lettres.
	draw_printf(x_menu, y_menu, "Bonjour pecheur %d , saisissez donc votre nom et entrez dans la legende : ",pecheur->id);
	update_graphics();
	y_menu -= 25;
	int c = 0;  //Pour eviter de traverser au cas ou.
	unsigned int i = 0;
	while(c!=key_ENTER){
		c=get_key(); // lecture au clavier lettre par lettre

		//reste le cas des touches non valides à traiter, <32 et >126 ne sont pas valides à la saisie
		if (i >= 8)
				draw_printf(10, 10, "Taille max_nom = 9"); 

		if(c == 8){		 //cas du backspace
			set_drawing_color(color_BACKGROUND);
			if(i>0 && (pecheur->nom_joueur[i-1]=='l'||pecheur->nom_joueur[i-1]=='r'||pecheur->nom_joueur[i-1]=='i'||pecheur->nom_joueur[i-1]=='t' || pecheur->nom_joueur[i-1]=='j'))
			{	pas=7;
			}
			else if(i>0 && (pecheur->nom_joueur[i-1]=='m' ||pecheur->nom_joueur[i-1]=='w'))
			{	pas=15;
				
			}
			else
			{	pas=12;	
				
			}			
			draw_rectangle_full(x_menu,y_menu,x_menu-pas,y_menu+18); 
			set_drawing_color(color_WHITE);
			if (i<=0){
				x_menu = 10 ;
				i=0;
			}
			else{
				x_menu -= pas ;
				i--;
			}
			update_graphics();
		}  
		else if(i <= 8 ) 
		{
			draw_printf(x_menu, y_menu, "%c",c); //affichage à l'écran lettre par lettre
			if(c=='l'||c=='r'||c=='i'||c=='t'||c=='j')
			{	pas=7;
				x_menu+=7;
			}
			else if(c=='m' ||c=='w')
			{	pas=15;
				x_menu+=15;
			}
			else
			{	pas=12;	
				x_menu+=12;
			}
			pecheur->nom_joueur[i] = (char) c;
			i++;
			update_graphics();
		}
	}
	for (c = i; c <= 9; ++c)
	{
		pecheur->nom_joueur[c] = 0;
	}
	
	clear_screen();
}

#include "main.h"

void menu(Liste * species[],fisher pecheur, int bonus_tab[]);
void saisi_nom_screen(fisher *pecheur);
/*Retourne un entier compris entre a et b*/
int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}


int main(int argc, char const *argv[])
{
	start_graphics();
	FILE *fPtr;
	fPtr=fopen("records.csv","w");
	FILE *gnuplot = popen("gnuplot -persistent", "w");
	if (fPtr == NULL)
	    printf("Error in opening file\n");
	
	//Variable d'arrêt de la simulation 
	int stop=key_F1;
	srand (time (NULL));
   	Mob * plateau_de_jeu[TAILLE_PLATEAU][TAILLE_PLATEAU];

  	
	// Compteur pour gérer les listes d'especes
  	int i = 0; 
	

	/***Initialisation du pêcheur***/
	//Variables de déplacement du pêcheur
	int x=0;
	int y=0;


	int x2=TAILLE_PLATEAU+1;
	int y2=TAILLE_PLATEAU+1;

	//Variable d'action du pêcheur
	//int a;

	fisher pecheur;
	fisher pecheur2;
	
	int mort_pecheur=0;
	int mort_pecheur2=0;

	//initialisation du pecheur 
	init_fisher(&pecheur, x, y, 1);
	init_fisher(&pecheur2, x2, y2, 2);
	
		pecheur.reserves = 5000;	
	//initialisation de la table des bonus 	
	int bonus_tab[8]={0};
	int bonus_tab2[8]={0};
	
	bonus_tab[7]=1;
	bonus_tab2[7]=0;
	//1 pour la vision		
//	bonus_tab[7]=0;
//	bonus_tab2[7]=0;

	//choix du mode de jeu : 0 pour le mode ecosysteme seul, 1 pour le mode 1 joueur, 2 pour le mode 2 joueurs
	int mode_joueur=start_screen();
	clear_screen();
	switch (mode_joueur){
		case 0:	bonus_tab[7]=1;
				break;
		case 1: saisi_nom_screen(&pecheur);				//mode 1 joueur
				break;
		case 2: saisi_nom_screen(&pecheur);
				saisi_nom_screen(&pecheur2);				//mode 2 joueurs
				break;

		default: printf("Un erreur c'est produite lors de la selection du mode\n");
				 exit(-1);
	}

	init_grid(plateau_de_jeu);
	spawn_island(plateau_de_jeu);

	



	/***Initialisation des espèces***/
	//Génération des listes de mobs......................................................................................
   		
		
		/*Ordre de creation            Espece vide - Plancton -   Corail -   Bar -  Thon - Pollution
   		Correspondance des couleurs    WHITE -       LIGHTGREEN - LIGHTRED - CYAN - BLUE - RED    */
 Liste * species[] = {NULL, init_mobs(1,5), init_mobs(2, 3), init_mobs(3,6), init_mobs(4, 3), init_mobs(5, 2), init_mobs(6, 4), init_mobs(7, 5), init_mobs(8, 2), init_mobs(9, 2)};

 
   	//Liste * species[] = {NULL, init_mobs(1,0), init_mobs(2, 0), init_mobs(3,0), init_mobs(4, 0), init_mobs(5, 0), init_mobs(6, 0), init_mobs(7, 0), init_mobs(8, 0), init_mobs(9, 3)};
   	fprintf(fPtr,"%s","WORLD_TIME");

	//Génération des mobs sur le plateau de jeu..........................................................................	
	for (int i = 1; i <= NB_SPECIES; ++i)
	{
		spawn_list_animal_random(plateau_de_jeu, species[i]);
		printf("Il y a %d individus de l'espece %d \n", nombre_elts_liste(species[i]), i);
		fprintf(fPtr,",%d",i);
	}
	draw_grid(plateau_de_jeu, bonus_tab[7]);
	update_graphics(); 
	Mob * ptr=malloc(sizeof(Mob));
	Liste * elt=malloc(sizeof(Liste));
	WORLD_TIME=0;
	


	do
	{	printf("WORLD_TIME : %d\n", WORLD_TIME);
		fprintf(fPtr,"\n%d", WORLD_TIME);
		fprintf(gnuplot, "%s \n", " load 'draw_graph.gnuplot'");
		fflush(gnuplot);
		/***Jeu du pêcheur***/
		menu(species,pecheur,bonus_tab);
		//Jeu du pêcheur tous les 10 tours d'écosystème
		if(WORLD_TIME % 10 == 0 && mode_joueur!=0)
		{	
			menu(species,pecheur,bonus_tab);
			jeu_du_pecheur(&pecheur, plateau_de_jeu, bonus_tab, &mort_pecheur, species);
			if(mode_joueur==2){
			menu(species,pecheur2,bonus_tab2);	
			jeu_du_pecheur(&pecheur2, plateau_de_jeu, bonus_tab2, &mort_pecheur2, species);	
			}
		} 	
		
			if(!mort_pecheur&&!mort_pecheur2)
			{
		



		/***Jeu de l'IA***/	
					
				draw_grid(plateau_de_jeu, bonus_tab[7]);
				
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
				
				draw_grid(plateau_de_jeu, bonus_tab[7]);
				
				fflush(fPtr);	
				
				WORLD_TIME++;
				//stop=get_key();	
			}
	
			
			}while( WORLD_TIME <= 1000 && !mort_pecheur);
	
	
		//Fermeture de la fenetre graphique	
		stop_graphics();
		//Fermeture du fichier d'acquisition des données
		fclose(fPtr);
	
		return 0;
	}			


void menu(Liste * species[], fisher pecheur, int bonus_tab[]){
	set_drawing_color(color_WHITE);
	//draw_line(0,(WINDOW_WIDTH-M3)+M1+20,WINDOW_WIDTH,(WINDOW_WIDTH-M3)+M1);
	int i,j = 0 ;
	int x_menu = WINDOW_WIDTH-M3+M1+20;
	int y_menu = WINDOW_HEIGHT ; // x et y nous servirons de curseur pour se deplacer dans la fentre du menu afin de realiser l'affichage correctement et compréhensible
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

	//**Information Joueur
	draw_line(x_menu,y_menu,WINDOW_WIDTH,y_menu);
	y_menu -= 12+5;
	draw_printf(x_menu, y_menu, "Informations sur le joueur ");
	y_menu -= 12+5;
	//***Nom
	set_drawing_color(color_BACKGROUND);
	draw_rectangle_full(x_menu,y_menu+12+5,WINDOW_WIDTH,y_menu-((12+5)*4));   //On va surement dessiner une grosse surface sur tout les info du joeur qu'on blittera de color_background
	
	set_drawing_color(color_LIGHTRED);
	draw_printf(x_menu, y_menu, "%s joue !",pecheur.nom_joueur);
	set_drawing_color(color_WHITE);
	y_menu -= 12+5;
	draw_printf(x_menu, y_menu, "Reserves : %d (+%d)",pecheur.reserves,pecheur.nv_reserves);
	y_menu -= 12+5;
	draw_printf(x_menu, y_menu, "Xp : %d ",pecheur.xp);
	y_menu -= 12+5;
	
	
	if (pecheur.ecolo){
		set_drawing_color(color_LIGHTGREEN);
		draw_printf(x_menu, y_menu, "Bravo l'ecolo !");
	} else{	
		set_drawing_color(color_LIGHTRED);
		draw_printf(x_menu, y_menu, "Tu n'es pas tres ecolo");
	}

	y_menu -= 12+5;
	if (bonus_tab[7])
	{
		set_drawing_color(color_LIGHTMAGENTA);
		draw_printf(x_menu, y_menu, "Tu es voyant :)");
	} else {
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
		if (eat_mat[10][i]){
			set_drawing_color(mobs_draw[i]);
			draw_circle_full(x_menu+((i-1)*12),y_menu+6, 4.5);
		}
	}
	y_menu -= 12+5;
	set_drawing_color(color_WHITE);

	//**Evénement
	draw_line(x_menu,y_menu,WINDOW_WIDTH,y_menu);
	y_menu -= 12+5;
	draw_printf(x_menu, y_menu, "Evenement : ");
	y_menu -= 100;
	/*for (i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			if (tab_pop[i][j] != 0)
			{
				set_pixel(x_menu+i,y_menu+j,color_WHITE);
			}
		}
	}*/
	
	set_drawing_color(color_WHITE);

	//**Actions_dispo
	draw_line(x_menu,y_menu,WINDOW_WIDTH,y_menu);
	y_menu -= 12+5;
	draw_printf(x_menu, y_menu, "Actions : ");
	//afficher_bonus

}

void saisi_nom_screen(fisher *pecheur){
	clear_screen();
	set_font(font_HELVETICA_18);
	set_drawing_color(color_WHITE);
	int x_menu = 10;
	int y_menu = WINDOW_HEIGHT-18-10 ;
	int pas = 12; //pas de decalage entre afficahge des lettres.
	draw_printf(x_menu, y_menu, "Bonjour pecheur %d , entrez donc votre nom et entrez dans la legende : ",pecheur->id);
	update_graphics();
	y_menu -= 25;
	int c = 0;  //Pour eviter de traverser au cas ou.
	unsigned int i = 0;
	while(c!=key_ENTER){
		c=get_key();
		//reste le cas des touches novalide a traiter de <32 et >126 ne sont pas valide a la saisi.
		if (i >= 8)
				draw_printf(10, 10, "Taille max_nom = 8"); 

		if(c == 8){		 // Cas du backspace
			set_drawing_color(color_BACKGROUND);
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
		else if(i <= 8 ) {

 		draw_printf(x_menu, y_menu, "%c",c);
		x_menu += pas;
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
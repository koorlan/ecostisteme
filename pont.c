#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "pont.h"



/*Selection de coordonnées valides (où il est possible de construire le pont) pour l'apparition du pont (cas où la pos du pecheur rend la construction du pont impossible non géré)*/
void spawn_pont(int x_pecheur, int y_pecheur, int *x_pont, int *y_pont, Mob * plateau[][TAILLE_PLATEAU])
{	int i, j;
	for(i=-1; i<=1; i++)
	{	for(j=-1;j<=1;j++)
		{	if( ((x_pecheur+i>=1 && x_pecheur+i<=TAILLE_PLATEAU) && (y_pecheur+j>=1 && y_pecheur+j<=TAILLE_PLATEAU)) && (plateau[x_pecheur+i-1][y_pecheur+j-1]->id != 11))
			{	*x_pont=x_pecheur+i;
				*y_pont=y_pecheur+j;
				return;			
			}
		}
	}
}


/*Atteste de la validité d'une case lors du déplacement du pont*/
int case_valide_pont(int x_pont, int y_pont, int x_pecheur, int y_pecheur, Mob * plateau[][TAILLE_PLATEAU])
{	return (case_valide_peche(x_pont, y_pont, x_pecheur, y_pecheur,plateau) && (plateau[x_pont-1][y_pont-1]->id != 11) && (plateau[x_pont-1][y_pont-1]->id!=12));
		
}

//Selection par le joueur de la position du pont
int place_pont (int x_pecheur, int y_pecheur, int *x_pont, int *y_pont, Mob * plateau[][TAILLE_PLATEAU], int bonus_tab[], couleurs coul)

{		
	int indice = 0;
	Mob * cases_libre[8] = { NULL } ;
	int run_cell_in_order[2][8] ={ {-1,-1,0,1,1,1,0,-1},
								   {0,1,1,1,0,-1,-1,-1} };	//remplissage en sens horaire										
	int i;
	for(i= 0; i<8; i++)
	{
        	if( (((x_pecheur+run_cell_in_order[0][i]>0) && (y_pecheur+run_cell_in_order[1][i]>0))&&((x_pecheur+run_cell_in_order[0][i]<=TAILLE_PLATEAU) && (y_pecheur+run_cell_in_order[1][i]<=TAILLE_PLATEAU))) ){ //case hors champ	
            	if( plateau[x_pecheur+run_cell_in_order[0][i]-1][y_pecheur+run_cell_in_order[1][i]-1]->id < 10){
						cases_libre[indice] = plateau[x_pecheur+run_cell_in_order[0][i]-1][y_pecheur+run_cell_in_order[1][i]-1];
						indice++;
					}
			}
	}
	
	if (indice == 0)
		return 0;
	int curseur = 0;
	int pont=0;
	while(pont!=key_ENTER)
	{	
		switch (pont)
		{	case key_RIGHT:										
					curseur++;
					if(bonus_tab[6]==0)
						draw_square(*x_pont+1, *y_pont+1, (rand_a_b(30,47)<<24)+(rand_a_b(27,72)<<16)+(rand_a_b(139,206)<<8) );
											
					else{
						draw_square(*x_pont+1, *y_pont+1, mobs_draw[0]);
						afficher_point(*x_pont+1, *y_pont+1,  mobs_draw[plateau[*x_pont][*y_pont]->id]);
					}	
				break;
			case key_LEFT : 
					curseur--;
					if(bonus_tab[6]==0)
						draw_square(*x_pont+1, *y_pont+1, (rand_a_b(30,47)<<24)+(rand_a_b(27,72)<<16)+(rand_a_b(139,206)<<8) );
											
					else{
						draw_square(*x_pont+1, *y_pont+1, mobs_draw[0]);
						afficher_point(*x_pont+1, *y_pont+1,  mobs_draw[plateau[*x_pont][*y_pont]->id]);
					}	

				break;		
			default :
				break;
		}
		*x_pont = cases_libre[abs(curseur%indice)]->x;
		*y_pont = cases_libre[abs(curseur%indice)]->y;
		

		draw_square(*x_pont+1, *y_pont+1, coul); 
		update_graphics();
		pont=get_key();		
	}
	
	return 1;
}


/*Gestion des fonctions relatives à la construction du pont*/
void construire_pont(Mob * plateau[][TAILLE_PLATEAU], fisher * pecheur, Liste * species[], int bonus_tab[])
{	int x_pont=0, y_pont=0;
	int stop;	
	Mob pont ;
	if (place_pont(pecheur->x, pecheur->y, &x_pont, &y_pont, plateau, bonus_tab, mobs_draw[11]) ){
	update_graphics();
	
	//On détruit l'éspèce présente dans la case ou le pont a été construit	
	if(plateau[x_pont][y_pont]->id!=0)
	{	species[plateau[x_pont][y_pont]->id] = destroy_mob(*plateau[x_pont][y_pont], species[plateau[x_pont][y_pont]->id]);
	}	
	plateau[x_pont][y_pont] = create_mob(0);
	plateau[x_pont][y_pont]->id=11;
	plateau[x_pont][y_pont]->x=x_pont;
	plateau[x_pont][y_pont]->y=y_pont;
	plateau[x_pont][y_pont]->satiete=0;
	plateau[x_pont][y_pont]->dernier_repas=0;
	plateau[x_pont][y_pont]->derniere_reproduction=0;
	pecheur->reserves--;
	pecheur->bridge++;
	}	
}


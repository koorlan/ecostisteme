#include "main.h"

Liste * ajouterEnTete(Liste * liste, Mob newMob)
{
    /* On crée un nouvel élément */
    Liste * nouvelElement = malloc(sizeof(Liste));
 
    /* On assigne la valeur au nouvel élément */
    nouvelElement->mob =  newMob;
 
    /* On assigne l'adresse de l'élément suivant au nouvel élément */
    nouvelElement->nxt = liste;
 
    /* On retourne la nouvelle liste, i.e. le pointeur sur le premier élément */
    return  nouvelElement;
}

int nombre_elts_liste( Liste * liste){
	if (liste->nxt == NULL)
		return 0;
	return 1+ nombre_elts_liste( liste->nxt);
}

int spawn_list_of_mobs(char * plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Liste * liste ){
	if (liste->nxt == NULL)
	{	
		printf("Je vais spawn l'enfant de X : %d Y: %d \n", liste->mob.x, liste->mob.y);
		return 1;
	}

	
	//printf("J'ai spawn l'enfant de X : %d Y: %d \n", liste->mob.x, liste->mob.y);
	return spawn_list_of_mobs(plateau,liste->nxt) & spawn_mob(plateau, liste->mob)  ;

}
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

ListeCase * ajouterEnTeteCase(ListeCase * liste, int a , int b){

    /* On crée un nouvel élément */
    ListeCase * nouvelElement = malloc(sizeof(Liste));
 
    /* On assigne la valeur au nouvel élément */
    nouvelElement->x = a;
    nouvelElement->y = b;
 
    /* On assigne l'adresse de l'élément suivant au nouvel élément */
    nouvelElement->nxt = liste;
 
    /* On retourne la nouvelle liste, i.e. le pointeur sur le premier élément */
    return nouvelElement;
}

int nombre_elts_listeCase( ListeCase * liste){
	if (liste->nxt == NULL)
		return 0;
	return 1+ nombre_elts_listeCase( liste->nxt);	
}

Liste * init_mobs(int id, int percentage) {   
	Liste * list_of_mobs = malloc(sizeof(Liste));
	list_of_mobs->nxt = NULL ;

	
    for (int i = 0; i < (percentage * (TAILLE_PLATEAU * TAILLE_PLATEAU) / 100 ); ++i)
    {
     list_of_mobs = ajouterEnTete(list_of_mobs, *(create_mob(id)) );     
    }
 
return list_of_mobs;

}
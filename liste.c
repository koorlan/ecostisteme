#include "main.h"

/*Insertion en tête dans une liste chaînée d'elt de type Mob*/
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


/*Retourne le nombre d'éléments d'une liste*/
int nombre_elts_liste(Liste * liste){
	if (liste->nxt == NULL)
		return 0;
	return 1+ nombre_elts_liste( liste->nxt);
}

/*Retourne une liste de Mobs de la même espece (id) selon un pourcentage d'occupation de la carte (percentage)*/ 
Liste * init_mobs(int id, int percentage) 
{   
	Liste * list_of_mobs = malloc(sizeof(Liste));
	list_of_mobs->nxt = NULL ;

	
    for (int i=0; i < (percentage * (TAILLE_PLATEAU * TAILLE_PLATEAU) / 100 ); ++i)
    {     
	list_of_mobs = ajouterEnTete(list_of_mobs, *(create_mob(id)) );     
    }
 
	return list_of_mobs;

}

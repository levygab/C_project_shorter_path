#include "structure.h"
#include "list.h"
#include "pile.h"

#ifndef _FONCTION_COMMUNE_H
#define _FONCTION_COMMUNE_H


/*
fonction permettant de creer des arc a de cout 0 entre tous
les somets presents dans liste.
Ces arc sont cree (et ajoutes) dans graf
*/
void creation_arc(list_t liste,int nb_sommet, graph* graf ) ;


/*
fonction qui renvoie tous les potentiels sommet de depart ou d'arrivee.
le renvoie correspond au nb de sommets de depart, tandis que liste_sommet est une
liste chaine contenant les adresses des sommets portant le nom de la station de depart :
cette station est dans le char* station.
*/
int sommet_depart(list_t* liste_sommet, char* station , graph graf) ;

/*
recuperation chemin permet de retrouver renvoyer dans une liste le plus court
chemin entre les sommets depart et arrivee
elle a un option qui print egalement le chemin ;
si print est a 1 on prend le chemin, si print != 1 on ne print pas le chemin
*/
int* recuperation_chemin(int depart , int arrivee , graph graf , int print , int* longueur) ;

/* fonctions ervant a ajouter a la fin de la liste des arcs mail le
maillon ajout */
maillon_arc maillon_ajout_fin(maillon_arc mail , maillon_arc ajout) ;

void simpli_ligne (char* ligne, char* retour) ;

void liberation_arc(maillon_arc arcs) ;

#endif

#include "structure.h"
#ifndef _LIST_H
#define _LIST_H
// Crée une liste vide
list_t list_new() ;

// Retourne VRAI si l est une liste vide
int list_is_empty(list_t l);

// Ajoute en fin de liste
list_t list_add_last(sommet* e, list_t l) ;

list_t list_add_first( sommet* e, list_t l ) ;

// Supprime l'element en position n et retourne la nouvelle liste
list_t list_remove_n(int n, list_t l) ;

//renvoie le numero du sommet avec le pcc minimum
int list_find_min(list_t l) ;

//fonction affichant tous les sommet d'une liste
void list_print(list_t l) ;

int list_length(list_t l) ;

void print_arcs (maillon_arc arcs) ;

list_t list_del_first( list_t l ) ;

list_t list_delete(list_t l) ;
#endif

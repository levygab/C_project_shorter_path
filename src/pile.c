#include "../include/pile.h"


lifo_t lifo_new(void) {	return NULL; }

lifo_t lifo_del_first(lifo_t l) {

  lifo_t p = l->next;
  free( l );
  return p;
}

int lifo_is_empty(lifo_t p) {
  return NULL == p;
}

lifo_t lifo_push (int e , lifo_t p){
  //creation lifo a ajouter
  lifo_t ajout ;
  ajout = calloc (1,sizeof(*ajout)) ;

  //on lui attribue les valeurs
  ajout -> val = e ;
  ajout -> next = p  ; //il prend la tete de pile donc pointe sur p le deuxieme lifo

  return ajout ;
}

int lifo_peek(lifo_t p){
  return p->val; ;
}

int lifo_pop(lifo_t * p_stack) {
  int elem = lifo_peek(*p_stack) ;
  *p_stack = lifo_del_first(*p_stack) ;

  return elem ;
}

lifo_t lifo_delete(lifo_t p) {
  //on balaye la liste et on libre avec list_del_first
  while (p != NULL) {
    p = lifo_del_first (p) ;
  }
  return p ;
}

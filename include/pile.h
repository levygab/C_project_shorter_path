#include "structure.h"
#ifndef _PILE_H
#define _PILE_H

// Crée et retourne un pile vide ou NULL en cas d'erreur
lifo_t lifo_new();

// Supprime le premier element de la pile
lifo_t lifo_del_first(lifo_t p);

// Retourne 1 si la pile  stack   est vide, 0 sinon
int lifo_is_empty(lifo_t stack);

// Ajoute l'élément e à la pile  stack  et retourne la nouvelle pile
lifo_t lifo_push(int e, lifo_t stack);

// Retourne l'élément en tête de pile (sans l'enlever de la pile)
int lifo_peek(lifo_t stack);

// Enlève l'élément en tête de la pile, et retourne cet élément
int lifo_pop(lifo_t * p_stack);

// Détruit la pile et retourne une pile vide
lifo_t lifo_delete(lifo_t stack);

#endif

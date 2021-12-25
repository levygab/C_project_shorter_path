#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <SDL2/SDL_phelma.h>


#ifndef _STRUCTURE_H
#define _STRUCTURE_H
typedef struct {
  int arrivee ; //indice sommet
  double cout ; //cout de l'arc
} arc ; //un arc

typedef struct mail_arc {
  arc val ; // l'arc
  struct mail_arc* next; //pointeur sur l'arc suivant
} *maillon_arc ; //liste d'arc

typedef struct {
  int numero ; //numero sommet
  char nom[512] ; //nom sommet
  char ligne[512] ; //nom de la ligne pour le metro
  double x,y ; //coordonnees du sommet
  maillon_arc arcs ; //liste des arcs liees a ce sommet
  double pcc ; //plus court chemin : pour la fin de l'algorithme je crois
  double cout ; //cout du plus court chemin
  int precedent ; //numero du sommet precedent
} sommet ;

typedef struct {
  int nb_sommets ;
  int nb_arc ;
  sommet* data ; //tableau des sommets
} graph ;

typedef struct _link {
  sommet* som ; /* un élément de la liste*/
  struct _link *next ; /* l'adresse du maillon suivant */
} *list_t, List ;

typedef struct _link2 {
  int val; /* un élément de la liste*/
  struct _link2 *next ; /* l'adresse du maillon suivant */
} *lifo_t ;

#endif

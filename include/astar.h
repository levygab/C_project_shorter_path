#include "structure.h"
#include "list.h"
#include "ouverture.h"
#include "pile.h"
#include "fonction_commune.h"

#ifndef _ASTAR_H
#define _ASTAR_H

/*
fonction heuristique permettant de calculer les ditances pour la fonctions Astar
*/
float heuristique(sommet sommet1 , sommet sommet2 ) ;


/*
Astar permet de trouver un plus court chemin
*/
int Astar(int depart , int arrivee , graph* graf ) ;








#endif

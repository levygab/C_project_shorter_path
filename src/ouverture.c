#include "../include/ouverture.h"

//fichier d'ouverture des fichier

void ouverture(char* nom , graph* graf) {
  /* fonction permettant d'ouvrir le fichier nom
  elle prend en entree le nom du fichier a ouvrir et
  rempli graf donne en entree
  */
  //pointeur d'entree
  FILE* entree ; entree = NULL ;
  int nb_elem_lus = 0 ;
  char stock[500] ;
  //ouverture du fichier
  entree = fopen (nom, "rt") ;
  if (entree == NULL) {
    printf("mauvaise lecture 1 du fichier : fonction ouverture, fichier ouverture.c\n" );
    EXIT_FAILURE ;
  }

  //lecture premiere ligne
  nb_elem_lus = fscanf(entree , "%d  %d" , & (graf -> nb_sommets), & (graf -> nb_arc) ) ;
  //on finit la ligne puis on saute la deuxieme ligne
  fgets(stock, 500, entree) ;
  fgets(stock, 500, entree) ;
  //remplissage des sommets
  // allocution dyanmique du tableau de sommet
  graf -> data = calloc ( graf -> nb_sommets , sizeof(sommet) ) ;
  int i ;
  for (i=0 ; i < graf -> nb_sommets ; i++ ) {
    //lecture numero sommet, sa position et le nom de la ligne si metro
    nb_elem_lus = fscanf( entree , "%d %lf %lf %s" , & (graf ->  data)[i].numero  , &(graf ->  data)[i].x  , &(graf ->  data)[i].y  , stock) ;
    //printf("la ligne est : %s\n", stock);
    strcpy( (graf -> data)[i].ligne, stock) ;
    //lecture ligne du sommet
    fgets(stock , 511 , entree ) ;
    //graf -> data)[i].nom
    simpli_ligne(stock,(graf -> data)[i].nom) ;
    //suppression de \n
    //if (stock[strlen(graf -> data -> ligne)-1]<32) stock[strlen(graf -> data -> ligne)-1]=0 ;

  }

  //les sommets sont remplis, on saute la ligne suivante
  fgets(stock, 500, entree) ;
  //remplissage des arcs
  //on a besoin de 3 varaibles
  int debut, fin ;
  float valeur ;
  for (i=0 ; i< graf -> nb_arc ; i++ ) {
    //lecture de la ligne
    fscanf(entree , "%d %d %f" , &debut , &fin , &valeur) ;

    //creation d'un nouveau maillon pour le noeud debut : allocution dynamique
    maillon_arc ajout ; ajout = calloc(1, sizeof(*ajout)) ;
    (ajout -> val).arrivee = fin ;
    (ajout ->val).cout = valeur ;

    //creation d'un nouveau maillon pour le noeud fin : allocution dynamique
    //on ajoute ces maillons a leur place (dans les noeuds debut et fin)
    //cas NULL
    if ((graf -> data[debut]).arcs == NULL ) {
      (graf -> data[debut]).arcs  = ajout ;
    }
    //cas non NULL
    else {
      maillon_ajout_fin( (graf -> data[debut]).arcs ,ajout ) ;
    }
  }
  fclose(entree);
}


/*
int main() {
  char tab[512] = {"     Bonjour La Vie Est belle   a"} ;
  char tab2[512] ;
  printf("tab = %s\n", tab) ;
  simpli_ligne(tab, tab2) ;
  //printf("tab2 = %s\n",tab2 );
}
*/

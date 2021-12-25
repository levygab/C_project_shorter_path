#include "../include/fonction_commune.h"
#include <SDL2/SDL_phelma.h>

void graph_print(graph graphe) {
  //pour print le graphque
  printf("il y a %d sommets et %d arcs\n",graphe.nb_sommets, graphe.nb_arc );
  int i ;
  for (i=0 ; i < graphe.nb_sommets ; i++ ) {
    printf("sommet : %d , ",graphe.data[i].numero );
    printf(" ligne : %s , coor : x=%f, y=%f ,son som est :%s, son pcc est %f ",  ((graphe .data)[i]).ligne , ((graphe .data)[i]).x , ((graphe .data)[i]).y , ((graphe .data)[i]).nom , ((graphe .data)[i]).pcc);
    print_arcs( (graphe.data[i]).arcs ) ;
    printf("\n" );
  }
}

int* recuperation_chemin(int depart , int arrivee , graph graf ,int print , int* longueur) {
  //pile de recuperation de chemin : elle est à l'envers
  lifo_t pile = lifo_new () ;
  //varibale servant a balayer le graf
  int numero = arrivee ;
  int compteur = 0 ; //variable servant a compter le nombre de sommet traverse
  while (numero !=depart) {
    pile = lifo_push(numero , pile) ;
    numero = graf.data[numero].precedent ;
    compteur ++ ;
  }
  //on ajoute le depart et on incremente compteur
  pile = lifo_push(depart , pile) ;
  compteur ++ ;

  //liste que l'on va renvoyer : elle est dans le bon sens
  int* renvoie = calloc(compteur, sizeof(renvoie)) ;
  int i ;

  for (i=0 ; i < compteur ; i++ ) {
    renvoie[i] = lifo_pop(&pile) ;
  }
  //on libere
  pile = lifo_delete(pile) ;

  //impression en cas de besoin
  if (print == 1){
    for (i=0 ; i< compteur ; i++) {
      //prise en compte de la correspondance
      if (i<compteur-1 && strcmp(graf.data[renvoie[i]].nom,graf.data[renvoie[i+1]].nom)==0 && strcmp(graf.data[renvoie[i]].ligne,graf.data[renvoie[i+1]].ligne) != 0) {
        //printf("nom1 : %s , nom 2 %s:\n", graf.data[renvoie[i]].nom,graf.data[renvoie[i+1]].nom);
        printf("c'est un correpondance à la station %s, entre les lignes %s et %s  : ",graf.data[renvoie[i]].nom , graf.data[renvoie[i]].ligne , graf.data[renvoie[i+1]].ligne);
      }
      printf("sommet %d : ",renvoie[i] ); printf("nom de la station : %s", graf.data[renvoie[i]].nom ); printf(" vers\n" );
    }
    printf("vous etes arrivee a destination ; le cout du pcc est de %f\n", graf.data[arrivee].pcc );
  }
  *longueur = compteur ;
  return renvoie ;
}

int sommet_depart(list_t* liste_sommet, char* station, graph graf) {
  int nb_depart = 0  ;
  int i;
  //balayge de la liste des sommets pour trouver tous ceux avec le meme nom
  for (i=0 ; i< graf.nb_sommets ; i++ ) {
    if (strcmp(station , graf.data[i].nom) == 0 ){
      //dans le cas ou on a trouve le sommet
      //on incremente le nb de sommet de depart
      nb_depart ++ ;
      //on ajoute le sommet a la liste
      *liste_sommet = list_add_last(graf.data + i , *liste_sommet) ;
    }
  }
  return nb_depart ;
}

void creation_arc(list_t liste,int nb_sommet, graph* graf ){
  //2 variables de balayages
  int i = 0 ;
  int j ;
  //une liste de numero
  int* liste_numero ; liste_numero = calloc(nb_sommet, sizeof(liste_numero)) ;
  list_t p ;
  for (p = liste ; p != NULL ; p = p -> next ) {
    liste_numero[i] = (p -> som) -> numero ;
    i++ ;
  }
  //liste_numero contient les numeros de chaque sommet
  for (i=0 ; i< nb_sommet ; i ++ ) {
    for (j=0 ; j < nb_sommet ; j++ ) {
      if (j != i ) {
        //creation de l'arc que l'on va ajouter a la fin
        maillon_arc ajout ; ajout = calloc(1, sizeof(*ajout)) ;
        (ajout -> val).arrivee = liste_numero[j] ;
        (ajout -> val).cout = 0 ;

        //on ajoute le maillon
        //premier cas
        if ((graf -> data[liste_numero[i]]).arcs == NULL ) {
          (graf -> data[liste_numero[i]]).arcs  = ajout ;
        }
        //deuxieme cas
        else {

          maillon_ajout_fin( (graf -> data[liste_numero[i]]).arcs ,ajout ) ;
        }
      }
    }
  }
}

maillon_arc maillon_ajout_fin(maillon_arc mail , maillon_arc ajout) {
  //parcours de la liste des arcs : on s'arrete quand l'arc suivant est NULL
  maillon_arc p ;
  int i =0;
  for (p=mail ; p -> next != NULL ; p = p-> next) {
    i ++ ;
  }

  //on est a la fin, on ajoute ajout
  p -> next = ajout ;

  return mail ;
}

void simpli_ligne (char* ligne, char* retour) {

  int validation_retour = 0 ;
  //on balaie les premiers espaces
  int longueur = 0 ;
  while (tolower(*ligne) < 'a' && tolower(*ligne) < 'z' ) {
    ligne ++ ;
    //longueur ++ ;
  }
  strcpy(retour , ligne) ;
  //printf("retour1 = %s\n",retour );
  //on a enleve le premier paquet d'espace

  //on considere maintenant que s'il y a deux espaces a la suite, on est en bout de nom de ligne
  while (validation_retour == 0 && *ligne != '\0') {
    if (*ligne == ' ' && (*(ligne+1) == ' ' ||*(ligne+1) == '\n') ) {
      validation_retour = 1 ;
    }
    else {
      longueur ++ ;
      ligne ++ ;
      /*
      printf("ligne = %c\n",*ligne );
      printf("ligne + 1 = %c\n",*(ligne+1) );
      */
    }
  }
  //on enleve tous les termes en trop de retour
  retour[longueur-1] = '\0' ;
  //printf("retour2 = %s\n",retour );
}

void liberation_arc(maillon_arc arcs) {
  maillon_arc p = arcs ;
  while(p != NULL) {
    p = arcs -> next ;
    //printf("%p\n",p );
    free (arcs) ;
    arcs = p ;
  }
}
/*
void tracer_chemin(int* tab , int longueur , graph graf) {
  //definition des variables utiles
  SDL_PHWindow*  ecran;
  int size = 30 ;
  unsigned int couleur =SDL_PH_RED ;
  double x1,y1,x2,y2;

  ecran=SDL_PH_CreateWindow(size,size);

  int i ;
  for (i=1 ; i< longueur ; i++) {
    //recuperation des x et y
    x1 = graf.data[tab[i-1]].x ;
    y1 = graf.data[tab[i-1]].y ;
    x2 = graf.data[tab[i]].x ;
    y2 = graf.data[tab[i]].y ;

    //traces
    lineColor(ecran->rendu , x1, y1 ,x2 , y2 , couleur) ;
  }
  puts("taper une touche pour continuer") ; getchar() ;
  SDL_PH_DestroyWindow(ecran); SDL_Quit(); return EXIT_SUCCESS;
}
*/

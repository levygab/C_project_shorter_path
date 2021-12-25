#include "../include/astar.h"


float heuristique(sommet sommet1 , sommet sommet2 ) {
  float distance ;
  distance = abs (sommet1.x - sommet2.x) +  abs(sommet1.y - sommet2.y) ;
  return distance/2 ;
}

int Astar(int depart , int arrivee , graph* graf ) {

  //liste des sommets atteints : =1 si sommet atteint, 0 si pas atteint
  int* atteint ;

  //allocation de lla liste des sommets atteints
  atteint = calloc(graf -> nb_sommets , sizeof(int) ) ;

  //variable dont on aura besoin
  int minimum ;//valeur qui servira a stocker le minimum
  sommet* some ; //le pointeur qui servira a stocker l'adresse du commet avec le pcc minimum
  maillon_arc p_balayage ; //servira a faire un balayage des arc du sommet
  double duree_min ; //tout est dans le nom
  int i ; //entier pour les boucle for
  list_t p_ba ;//pointeur qui servira à avancer jusqu'au minimum

  //initialisation des pcc et des cout a l'infini
  for (i=0 ; i< graf -> nb_sommets ; i++) {
    (graf -> data)[i].pcc = DBL_MAX ;
    (graf -> data)[i].cout = DBL_MAX ;
    //(graf -> data)[i].precedent = -1 ;
  }

  //mise du precedent du depart a -1
  (graf -> data)[depart].precedent = -1 ;
  //mise du sommet de depart a 0
  (graf -> data)[depart].pcc = 0 ;
  (graf -> data)[depart].cout = 0;

  //on recupere le sommet d'arrivee
  sommet sommet_arrivee = graf -> data[arrivee] ;

  //liste des sommets a traiter : liste chainee
  list_t a_traiter = list_new() ;

  //on met le sommet de depart dans a_traiter
  a_traiter = list_add_first( (graf -> data)+depart , a_traiter) ;
  //printf("%p\n",(graf -> data)+depart );
  //printf("le numero du sommet de depart est %d\n", ((graf -> data)+depart) -> numero );

  //on entre dans la boucle
  while( list_is_empty(a_traiter) == 0 ) {

    //recherche minimum
    minimum = list_find_min(a_traiter) ;

    //on balaie la liste chainee pour aller jusqu'au minimum
    p_ba = a_traiter ;
    for(i=0 ; i < minimum ; i++) {
      //printf("%d\n",i );
      p_ba = p_ba -> next ;
    }
    //on a finit d'avancer dans la liste chainee : on récupere le sommet
    some = p_ba -> som ;



    //suppresion du minimum dans a_traiter
    a_traiter = list_remove_n(minimum, a_traiter) ;

    //on test si le sommet recupere est l'arrivee
    if (some -> numero == sommet_arrivee.numero ) {
    //on est a la fn de la fct
    //liberation
    list_delete(a_traiter) ;
    free(atteint) ;
    return 1 ;
    }

    else {
      //on a trouve le plus court chemin du depart a some : on met a jour les sommets atteints
      atteint[some -> numero] = 1;

      //on balaie les arcs du sommet recupere
      for(p_balayage = some -> arcs ; p_balayage != NULL ; p_balayage = p_balayage-> next ) {

        //recuperation duree
        duree_min = (some -> pcc) + (p_balayage -> val).cout ;

        //comparaison duree

        if (atteint[(p_balayage -> val).arrivee] == 0 && duree_min < graf -> data[(p_balayage -> val).arrivee].pcc ) {
          //cela veut dire que le chemin par u est plus court pour aller a v : on a un nouveau record
          //on remplace donc les 2 indicateurs de duree
          graf -> data[(p_balayage -> val).arrivee].cout = duree_min + heuristique(graf -> data[(p_balayage -> val).arrivee] , *some) ;
          graf -> data[(p_balayage -> val).arrivee].pcc = duree_min ;

          //on remplace aussi la valeur du sommet precedent : on a trouve un plus court chemin : on a donc un nouvau sommet precedent
          graf -> data[(p_balayage -> val).arrivee].precedent = some -> numero ;
          //on ajoute le sommet d'arrivee a add_last
          a_traiter = list_add_last(&graf -> data[(p_balayage -> val).arrivee] , a_traiter) ;
        }
      }
    }

  }
  //printf("liste_a_traiter\n" );list_print(a_traiter) ;

  if (graf -> data[arrivee].cout != DBL_MAX) {
    //liberation
    list_delete(a_traiter) ; free(atteint) ;
    printf("a traiter : %p\n",a_traiter ); printf("a traiter : %p\n",atteint ); printf("aaaaa\n" );
  return 1 ;}
  //liberation
  list_delete(a_traiter) ; free(atteint) ;
  return 0 ;

}

int main () {

  graph graphique ;
  char nom[512] = {"../data/metroetu.txt"} ;
  char station_depart[512] ;
  char station_arrivee[512] ;
  char stock[512] ;
  char stock2[512] ;
  int nb_depart ;
  int i ;
  int nb_arrivee ;
  int depart ;
  int arrivee ;
  int longueur ;
  int a ;

  int metro =1 ; //varibale pour savoir si on prend le metro ou non

  //remplissage du graphe
  ouverture(nom,&graphique) ;
  //graph_print(graphique) ;
  if (metro == 1) {
  printf("nom de la station de depart : \n");
  fgets (stock,500,stdin) ;
  printf("nom de la station d'arrivee : \n");
  fgets (stock2,500,stdin) ;

  simpli_ligne(stock,station_depart ) ;
  simpli_ligne(stock2,station_arrivee) ;

  //int depart = 399 ;
  //int arrivee = 676 ;

  //printf("nom de la station de depart ?\n");
  //scanf("%[^\t]\n", station);
  //printf("%s\n",station_depart);

  //recuperation des sommets de depart
  list_t liste_sommet = list_new() ;
  nb_depart = sommet_depart(&liste_sommet , station_depart , graphique) ;

  if (nb_depart > 1 ) creation_arc(liste_sommet , nb_depart ,&graphique) ;
  //printf("nb_depart = %d\n",nb_depart );


  list_t liste_som_arrivee = list_new() ;
  nb_arrivee = sommet_depart(&liste_som_arrivee , station_arrivee , graphique) ;
  if (nb_arrivee > 1 ) creation_arc(liste_som_arrivee , nb_arrivee ,&graphique) ;
  //printf("nb_arrivee = %d\n",nb_arrivee );
  //n'importe lequel des sommets d'arrivee ou de depart convient maintenant
  depart = (liste_sommet -> som) -> numero ;
  arrivee = (liste_som_arrivee -> som) -> numero ;

  //printf(" depart  = %d, arrivee = %d \n",depart, arrivee );
  list_delete(liste_som_arrivee) ; list_delete(liste_sommet) ;
  }

  else  {
    printf("numero sommet de depart : \n" ); scanf("%d",&depart );
    printf("numero sommet arrivee\n" ) ; scanf("%d",&arrivee   );
  }

  int cl ;
  cl = clock() ;
  //int a = 0 ;
  a = Astar(depart, arrivee,&graphique) ;
  if (a == 1) {
    //nb_depart = sommet_depart(&liste_sommet , station , graphique) ;
    //printf("nb_depart = %d\n",nb_depart );
    //list_print(liste_sommet) ;
    //creation_arc(liste_sommet , nb_depart ,&graphique) ;
    int * chemin = recuperation_chemin(depart , arrivee , graphique , 1 , &longueur) ;
    //list_print(liste_sommet) ;
    //print_arcs ((graphique.data)[399].arcs) ;
    free(chemin) ;
    cl = clock() - cl ;
    printf("temps mesure en seconde %lf\n",cl/(double)CLOCKS_PER_SEC );
  }
  else printf("il n'y a pas de chemin entre ces deux sommets\n" );


  //test de la duree
  /*
  int duree ; duree = clock () ;
  for (i=0 ; i < 10 ; i++) {
    printf("%d\n",i );
    depart = random() %graphique.nb_sommets ;
    arrivee = random() %graphique.nb_sommets ;
    a = Astar(depart, arrivee , &graphique) ;
  }

  duree = clock() - duree ;
  duree = duree/(double)CLOCKS_PER_SEC ;
  printf("la duree toatale est de %d\n",duree );
  duree = duree/(double)i ;
  printf("i = %d, la duree moyenne est de %d \n",i,duree );
  */
  //liberation memoire
  for (i=0 ; i<graphique.nb_sommets ; i ++) {
    //printf("hello\n" );
    liberation_arc(graphique.data[i].arcs) ;
  }
  free(graphique.data) ;


  return 15 ;

}

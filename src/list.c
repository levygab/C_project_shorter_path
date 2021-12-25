#include "../include/list.h"

list_t list_new() {
  return NULL;
}

int list_is_empty( list_t l ) {
  return NULL == l;
}

list_t list_add_first( sommet* e, list_t l ) {
  list_t p = calloc( 1, sizeof( *p ) );
  if ( NULL == p ) {
    fprintf( stderr, "Fatal: Unable to allocate new list link.\n" );
    return l;
  }
  p->som  = e;
  p->next = l;

  return p;
}

list_t list_add_last(sommet* e, list_t l) {
  //creation de l'ajout
  list_t ajout ;
  ajout = list_new() ;

  //on ajoute e au debut de l'ajout, comme ca on a juste a remplacer NIL par ajout dans l
  ajout = list_add_first ( e, ajout ) ;

  //on verifie que l ne soit pas vide, si elle l'est, on return ajout
  if ( list_is_empty(l) == 1 ) {
    return ajout ;
  }

  //parcours de la liste l, on s'arrete juste avant que p = NIL
  list_t p ;
  for( p=l ; p -> next != NULL ; p = p-> next ) {}

  p -> next = ajout ;

  return l ;
}

list_t list_remove_n(int n, list_t l) {
  //verif coherence
  int longueur ;
  longueur = list_length(l) ;
  if (longueur == 0) {
    printf("la longueur est de 0\n" );
    return NULL ;}
  if ( n > longueur ) {
    printf("il y a un probleme de longueur\n" ) ;
  return l ; }

  //cas n=0
  if (n==0){
      list_t p ;
      p = list_new() ;
      p = l -> next ;
      free (l) ;
      return p ;

  }

  //cas ou on enelve une autre valeur
  //p2 sera pour liberer la memoire
  list_t p = l ;
  list_t p2 = l;
  int i ;

  //on deplace p sur n-2, un cran avant la valeur a enlever
  for ( i = 0 ; i < n-1 ; i++ ) {
    p = p -> next ;
    p2 = p2 -> next ;
  }
  // sur n-2, on se deplace de deux valeur
  p2 = p2 -> next ; //on deplace p2 sur la valeur a enlver
  p -> next = p2 -> next ; //p -> next prend la valeur apres la valeur a enlever

  //on libere : non car on a besoin d'ertudier le sommet
  free ( p2) ;
  return l ;
}

int list_find_min(list_t l) {
  //un minimum
  float minimum =  (l -> som) -> pcc ;
  //printf("minimum dans list_find_min est %f\n",minimum );
  //printf("le minimum est %f\n",minimum );
  int num_sommet = 0 ;
  int i ;

  //pointeur de balayage
  list_t p ;

  for (p = l , i = 0; p != NULL ; p = p ->next , i++) {
    //printf("%p\n",p->next );
    //printf("entree dans la boucle\n" );
    //printf("pcc est %f \n", p -> som -> pcc);
    if ( (p -> som) -> pcc < minimum ) {
      num_sommet = i ;
      //printf("%d\n",num_sommet );
      minimum = (p -> som) -> pcc ;
    }
  }
  //printf("fin find_min\n" );
  return num_sommet ;
}

void print_arcs (maillon_arc arcs) {
  //pour print tous les arc d'un sommet
  maillon_arc p ;
  for(p = arcs ; p != NULL ; p = p -> next ) {
    printf("arrive = %d cout = %f \t", (p -> val).arrivee , (p -> val).cout );
  }
  printf("\n");
}

void list_print(list_t l) {
  list_t p = l ;
  sommet somme ;
  while (p != NULL ) {
    somme = *(p -> som) ;
    printf("sommet : %d , ",somme.numero );
    printf(" ligne : %s , coor : x=%f, y=%f ,son som est :%s ,pcc = %f , ",  somme.ligne , somme.x , somme.y , somme.nom , somme.cout);
    //print_arcs( somme.arcs ) ;
    printf("\n" );
    p = p -> next ;
  }

}

int list_length(list_t l) {
  int len = 0;
  list_t p;
  for( p=l; ! list_is_empty(p) ; p=p->next ) {
    len ++;
  }
  return len;
}

list_t list_del_first( list_t l ) {
  list_t p = l->next;
  free( l );
  return p;
}

list_t list_delete(list_t l) {
  //on balaye la liste et on libre avec list_del_first
  while (l != NULL) {
    l = list_del_first (l) ;
  }
  return l ;
}

/* Pour tester les fonctions sur les listes */
/*
int main () {
  list_t list = list_new() ;
  //printf("%d\n",list_is_empty(list) );

  //creation d'un sommet, puis ajout a la liste
  sommet* some ;
  some = calloc(1, sizeof(some)) ;
  some -> numero = 5 ;
  some -> pcc = 5 ;

  sommet* some2 ;
  some2 = calloc(1, sizeof(some2)) ;
  some2 -> numero = 2 ;
  some2 -> pcc = 2 ;

  //list = list_add_last(some2 , list) ;
  //printf ("numero 10 = %d \n", (list -> som) -> numero ) ;

  list = list_add_first(some , list) ;
  printf ("numero 5 = %d \n", (list ->  som) -> numero ) ;

  list = list_add_last(some2 , list) ;
  printf ("numero 2 = %d \n", ((list -> next) -> som) -> numero ) ;

  int numero =list_find_min(list) ;
  printf("le numero du plus petit sommet est %d\n", numero);
  printf("le numero 0 est %d\n" , (list  -> som) -> numero);
  list = list_remove_n(numero,list) ;
  printf("aa\n" );
  printf("%p\n",list -> next );
  printf("aa\n" );
  printf ("numero 5 = %d \n", (list ->  som) -> numero ) ;
  return 15 ;


}
*/

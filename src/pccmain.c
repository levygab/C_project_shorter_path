#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "f1.h"
#include "f2.h"


int main(int argc, char** argv) {
  int x=10,y,z;
  
  y=f1(x);
  z=f2(x);
  printf("Valeur de y:%d et z:%d\n",y,z);
}

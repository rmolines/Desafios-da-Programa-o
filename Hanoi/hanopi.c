#include <stdio.h>

void print (int n, char out){
  printf("Mova %d para %c", n, out);
}


void fill (int vec[], int n){
  int i;

  for (i=0; i<n; i++){
    vec[i]=i;
  }
}

void move (int src[], int out[], n){
  int swap, i;

  for (i=0; i<n; i++){
    out[i+1]=out[i];
  }

  out[0]=src[0];

}


void hanoi (int n, char src, char aux, char out){
  int size, src[n], aux[n], out[n, swap[n]];
  char current;

  fill(src,n);


  
}

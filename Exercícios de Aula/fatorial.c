#include <stdio.h>

int fatorial(int vec[], int n){
  if(n==0){
    return 0;
  }
  return vec[n-1]+fatorial(vec, n-1);
}

void main (void){
  int vec[]={10,20,30,10};
  int n = 4;
  printf("%d", fatorial(vec, n));
}

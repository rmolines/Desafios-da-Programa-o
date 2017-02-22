#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_ordered (int vec[], int n){
  int i;

  for (i=0; i<n-1; i++){
    if (vec[i]>vec[i+1]){
      return 0;
    }
  }

  return 1;
}

void fill_random_list (int vec[], int n){
  int i;

  srand(time(NULL));

  for (i=0; i<=n; i++){
    vec[i] = rand()%100;
  }
}

void bubble_sort(int vec[], int n){
  int i, j, swap, swapped;
  swapped = 0;

  for (i=0; i<n; i++){
    for(j=0; j<n-1-i; j++){
      if(vec[j]>vec[j+1]){
        swap = vec[j];
        vec[j]=vec[j+1];
        vec[j+1]=swap;

        swapped = 1;
      }
    }
    if (!swapped){
      break;
    }
  }
}

void display(int vec[], int n) {
   int i;
   printf("[");

   // navigate through all items
   for(i = 0; i < n; i++) {
      printf("%d ",vec[i]);
   }

   printf("]\n");
}

void selection_sort(int vec[], int n){
  int i, j, smallest, swap, j_pos;

  for(i=0; i<n; i++){
    smallest=vec[n-1-i];
    for(j=n; j>=i; j--){
      if(vec[j-1]<smallest){
        smallest=vec[j];
        j_pos=j;
      }
    }
    printf("{%d} ", smallest);
    swap = vec[i];
    vec[i]=smallest;
    vec[j_pos]=swap;
  }
}

void main (void){
  int vec[100];
  int i;
  fill_random_list(vec, 100);
  display(vec, 100);
  selection_sort(vec, 100);
  display(vec, 100);
  printf("%s \n", is_ordered(vec, 100)?"Está ordenado":"Não está ordenado");

}

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

  for (i=0; i<=n; i++){
    vec[i] = rand()%100;
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

void r_bubble_sort(int vec[], int n){
  int i, swap;

  if (n==0){
    return;
  }

  for (i=0; i<n-1; i++){
    if (vec[i]>vec[i+1]){
      swap = vec[i];
      vec[i] = vec[i+1];
      vec[i+1]=swap;
    }
  }
  return r_bubble_sort(vec, n-1);
}

void selection_sort(int vec[], int n){
  int i, j, swap, min_pos;

  for(i=0; i<n-1; i++){
    min_pos=i;
    for(j=i+1; j<n; j++){
      if(vec[j]<vec[min_pos]){
        min_pos=j;
      }
    }
    swap = vec[i];
    vec[i]=vec[min_pos];
    vec[min_pos]=swap;
  }
}

void r_selection_sort(int vec[], int n){
  int j, biggest, swap, j_pos;

  if(n==0){
    return;
  }
  biggest=vec[0];
  for(j=n-1; j>=0; j--){
    if(vec[j]>=biggest){
      biggest=vec[j];
      j_pos=j;
    }
  }
  swap=vec[n-1];
  vec[n-1]=biggest;
  vec[j_pos]=swap;

  return r_selection_sort(vec, n-1);
}

void insertion_sort (int vec[], int n){
  int i, j, temp;

  for (i=0; i<n-1; i++){
    temp = vec[i];
    for (j=i; j>=0; j--){
      if (vec[j+1]>temp){
        vec[j+1] = vec[j];
      }
    }
    vec[j+1] = temp;
  }
}

int test (int vec[], int n, int times){
  int i;
  int right_times = 0;

  for(i=0; i<times; i++){
    fill_random_list(vec, n);
    selection_sort (vec, n);
    right_times += is_ordered(vec, n)?1:0;
  }
  return right_times;
}


void main (void){
  int n = 20;
  int times = 1000;
  int vec[n], right_times;
  srand(time(NULL));


  printf("Você acertou %d vezes de %d", test(vec, n, times), times);
}

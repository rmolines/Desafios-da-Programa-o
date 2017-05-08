#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>

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

  for (i=1; i<n; i++){
    temp = vec[i];
    for (j=i-1; j>=0 && vec[j]>temp; j--){
      vec[j+1] = vec[j];
    }
    vec[j+1] = temp;
  }
}

void r_insertion_sort(int vec[], int n, int i){
  int j, temp;

  if (i==n){
    return;
  }

  temp = vec[i];
  for (j=i-1; j>=0 && vec[j]>temp; j--){
    vec[j+1] = vec[j];
  }
  vec[j+1] = temp;

  return r_insertion_sort (vec, n, i+1);

}

int test (int vec[], int n, int times, int type){
  int i;
  int right_times = 0;

  switch (type) {
    case 1:
      for(i=0; i<times; i++){
        fill_random_list(vec, n);
        bubble_sort(vec, n);
        right_times += is_ordered(vec,n);
      }
      break;
    case 2:
      for(i=0; i<times; i++){
        fill_random_list(vec, n);
        selection_sort(vec, n);
        right_times += is_ordered(vec,n);
      }
      break;
    case 3:
      for(i=0; i<times; i++){
        fill_random_list(vec, n);
        insertion_sort(vec, n);
        right_times += is_ordered(vec,n);
      }
      break;
    case 4:
      for(i=0; i<times; i++){
        fill_random_list(vec, n);
        r_bubble_sort(vec, n);
        right_times += is_ordered(vec,n);
      }
      break;
    case 5:
      for(i=0; i<times; i++){
        fill_random_list(vec, n);
        r_selection_sort(vec, n);
        right_times += is_ordered(vec,n);
      }
      break;
    case 6:
      for(i=0; i<times; i++){
        fill_random_list(vec, n);
        r_insertion_sort(vec, n, 1);
        right_times += is_ordered(vec,n);
      }
      break;
  }

  return right_times;
}



void main (void){
  int n = 1000;
  int times = 1000;
  int vec[n];
  srand(time(NULL));

  printf("Você acertou %d vezes de %d com o bubble_sort\n", test(vec, n, times, 1), times);
  printf("Você acertou %d vezes de %d com o selection_sort\n", test(vec, n, times, 2), times);
  printf("Você acertou %d vezes de %d com o insertion_sort\n", test(vec, n, times, 3), times);
  printf("Você acertou %d vezes de %d com o r_bubble_sort\n", test(vec, n, times, 4), times);
  printf("Você acertou %d vezes de %d com o r_selection_sort\n", test(vec, n, times, 5), times);
  printf("Você acertou %d vezes de %d com o r_insertion_sort\n", test(vec, n, times, 6), times);


}

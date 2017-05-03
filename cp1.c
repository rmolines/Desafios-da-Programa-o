#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

void sort (int v[], int n){
  int i, j, temp, max_pos, min_pos, found;
  max_pos = n-1;
  min_pos = 0;
  found = 0;

  for (i=0; i<n; i++){
    int max = INT_MIN;
    int min = INT_MAX;

    for (j=i; j<n-i; j++){
      if (v[j] >= max){
        max = v[j];
        max_pos = j;
        found = 1;
      }
      if (v[j] <= min){
        min = v[j];
        min_pos = j;
        found = 1;
      }
    }

    if (found == 0){
      break;
    }

    printf("%d\n", v[min_pos]);
    printf("%d\n", v[max_pos]);

    temp = v[i];
    v[i] = v[min_pos];
    v[min_pos] = temp;

    temp = v[n-i-1];
    v[n-i-1] = v[max_pos];
    v[max_pos] = temp;

    display(v, n);
  }
}

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

void display(int vec[], int n) {
   int i;
   printf("[");

   // navigate through all items
   for(i = 0; i < n; i++) {
      printf("%d ",vec[i]);
   }

   printf("]\n");
}

int test (int vec[], int n, int times){
  int i;
  int right_times = 0;

  for(i=0; i<times; i++){
    fill_random_list(vec, n);
    sort(vec, n);
    right_times += is_ordered(vec, n)?1:0;
  }
  return right_times;
}


int main (void){
  int n = 10;
  int times = 1000;
  int vec[n];
  srand(time(NULL));

  fill_random_list(vec, n);
  display(vec, n);
  sort(vec, n);
  display(vec, n);

  //printf("Você acertou %d vezes de %d", test(vec, n, times), times);

  return 0;
}

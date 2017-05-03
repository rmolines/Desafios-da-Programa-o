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

void display(int vec[], int n) {
   int i;
   printf("[");

   // navigate through all items
   for(i = 0; i < n; i++) {
      printf("%d ",vec[i]);
   }

   printf("]\n");
}

void merge(int v[], int l, int r, int m){
  int temp;
  while (l<m && m<r){
    if(v[l]<v[m+1]){
      temp = v[l];
      v[l] = v[m+1];
      v[m+1] = v[l];
      l++;
    } else {
      temp = v[l];
      v[l] = v[m+1];
      v[m+1] = v[l];
      m++;
    }
  }
}

void gangnam_sort_r(int v[], int l, int r){
  if(l<r){
    int n = r-l;
    int p1 = n/3;
    int p2 = p1*2;
    gangnam_sort_r(v, l, p1);
    gangnam_sort_r(v, p1+1, p2);
    gangnam_sort_r(v, p2+1, r);
    merge(v, l, r, p1);
    merge(v, l, r, p2);
  }
}

int sort(int v[], int n) {
  gangnam_sort_r(v, 0, n-1);
  return 1;
}

int test (int vec[], int n, int times){
  int i;
  int right_times = 0;

  for(i=0; i<times; i++){
    fill_random_list(vec, n);
    gangnam_sort_r(vec, 0, n-1);
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

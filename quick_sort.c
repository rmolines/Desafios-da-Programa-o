#include <stdio.h>

void quick_sort(int *v, int n){
  int marker = 0;
  int temp;

  for (int i=n-1; i>0; i--){
    if (marker==0){
      if (v[i]<v[marker]){
        temp = v[marker];
        v[marker] = v[i];
        v[i] = temp;
        marker = i;
      }
    } else {
      if (v[i]>v[marker]){
        temp = v[marker];
        v[marker] = v[i];
        v[i] = temp;
        marker = i;
      }
    }
  }

  quick_sort(v+marker, n-marker-1);
  quick_sort(v, n-marker-1);
}

#include <stdio.h>

void erdos_solver (int n, int m, int connections[100][100], int erdos_number[100], char names[100][100]);
void file_reader(int *n, char names[100][100], int *m, int connections [100][100]);
void print_array (int array[], int n);

int main() {
  char names [100][100];
  int n, m, i, j, erdos_number[100], connections [100][100];

  file_reader (&n, names, &m, connections);

  erdos_solver(n, m, connections, erdos_number, names);

  return 0;
}

void erdos_solver (int n, int m, int connections[100][100], int erdos_number[100], char names[100][100]) {
  int i, j;
  char a, b, temp, temp_list[n];

  printf("%d\n", n);

  for (i=0; i<n; i++) {
    erdos_number[i] = -1;
  }
  erdos_number[0] = 0;

  for (i=0; i<n; i++) {
    for (j=0; connections[i][j]!=-1; j++) {
      a = i;
      b = connections[i][j];
      if (erdos_number[b]==-1) {
        erdos_number[b] = erdos_number[a]+1;
      }
    }
  }

  for (i=0; i<n; i++) {
    printf("%s\n", names[i]);
    printf(": %d\n", erdos_number[i]);
  }
}

void file_reader(int *n, char names[100][100], int *m, int connections [100][100]) {
  int i, a, b, index[100];

  scanf("%d\n", n);

  for (i=0; i<*n; i++) {
    scanf("%200[^\n]\n", names[i]);
    index[i] = 0;
    connections[i][0] = -1;
  }


  scanf("%d\n", m);

  for (i=0; i<*m; i++) {
    scanf("%d\n", &a);
    scanf("%d\n", &b);

    connections[a][index[a]] = b;
    connections[a][++index[a]] = -1;
  }
}

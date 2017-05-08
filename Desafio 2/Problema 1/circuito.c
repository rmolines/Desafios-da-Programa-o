#include <stdio.h>
#include <stdlib.h>

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

void read_cout(char variables [10], char gate[30], char truth_table[1024][10], int *n);
char solve_variable(char truth_line[], char variable);
char line_solver(char gate[], char truth_line[]);
char solve_ops (char op, char a, char b);
void print_array (char array[], int n);
char op (char ops);
void gate_solver (char gate[], char truth_table[1024][10], int n);

int main() {
  char variables [10], gate[30], truth_table[1024][10];
  int n;

  read_cout(variables, gate, truth_table, &n);

  gate_solver(gate, truth_table, n);

  return 0;
}

void gate_solver (char gate[], char truth_table[1024][10], int n) {
  char cout;
  int i;
  printf("%c\n", n);

  for (i=0; i<n; i++) {
    cout = line_solver(gate, truth_table[i]);
    printf("%c\n", cout);
  }
}

char line_solver(char gate[], char truth_line[]){
  int i;
  char answer, temp, a, b;


  for (i=2; gate[i]!='\0'; i++){
    a = solve_variable(truth_line, gate[i-2]);
    b = solve_variable(truth_line, gate[i-1]);

    if (i == 2){
      answer = solve_ops(gate[i], a, b);
    }
    else if (op(gate[i])){
      if (op(gate[i-2])){
        answer = solve_ops(gate[i], answer, b);
      }
      else {
        temp = solve_ops(gate[i], a, b);
        answer = solve_ops(gate[i+1], temp, answer);
        i++;
      }
    }
  }

  return answer;
}

char op (char ops) {
  char is_op = 0;
  if (ops == '|' || ops == '^' || ops == '&') {
    is_op = 1;
  }
  return is_op;
}

char solve_variable(char truth_line[], char variable){
  int i, value;

  value = -1;

  if (!op(variable)){
    for(i=0; ALPHABET[i] != variable; i++);
    value = truth_line[i];
  }

  return value;
}

char solve_ops (char op, char a, char b){
  char answer;

  if (op == '|'){
    answer = a | b;
  } else if (op == '^'){
    answer = a ^ b;
  } else {
    answer = a & b;
  }

  return answer;
}

void solve(int number_of_lines, char gate[]){
  char truth_table[2][2][2];
  int i;

  for (i=0; i<number_of_lines; i++){

  }

}


void read_cout(char variables [10], char gate[30], char truth_table[1024][10], int *n){
  int k, i, j, number_of_variables;
  char temp[40];

  scanf("%d\n", &number_of_variables);
  /*eu sei, deveria ter usado fgets, agora já pode parar de me julgar*/

  for (i=0; i<number_of_variables; i++){
    scanf("%c\n", &variables[i]);
  }

  scanf("%s\n", gate);

  scanf("%d\n", n);

  for (i=0; i<*n; i++){
    for (k=0; k<number_of_variables; k++){
      scanf("%c\n", &truth_table[i][k]);
    }
  }
}

void print_array (char array[], int n) {
  int i;

  printf("{ ");
  for (i=0; i<n; i++) {
    printf("%c, ", array[i]);
  }
  printf("}\n");
}

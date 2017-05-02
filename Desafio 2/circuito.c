#include <stdio.h>
#include <stdlib.h>

#define OPS ('^' | '|' | '&')
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

void read_cout(char variables [10], char gate[30], char truth_table[1024][10]);
char solve_variable(char truth_line[], char variable);
char syntax_solver(char gate[], char truth_line[]);
char solve_ops (char op, char a, char b);

int main() {
  char variables [10], gate[30], truth_table[1024][10];
  char cout;

  read_cout(variables, gate, truth_table);

  cout = syntax_solver (gate, truth_table[0]);

  printf("%c\n", cout);

  return 0;
}

char syntax_solver(char gate[], char truth_line[]){
  int i;
  char answer, temp, a, b;


  for (i=2; gate[i]!='\0'; i++){
    a = solve_variable(truth_line, gate[i-2]);
    b = solve_variable(truth_line, gate[i-1]);

    if (i == 2){
      answer = solve_ops(gate[i], a, b);
    } else if (gate[i] == OPS){
      if (gate[i-2] == OPS){
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

char solve_variable(char truth_line[], char variable){
  int i, value;

  value = -1;

  if (variable != OPS){
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


void read_cout(char variables [10], char gate[30], char truth_table[1024][10]){
  int k, i, j, number_of_lines, number_of_variables;
  char temp[40];

  scanf("%d\n", &number_of_variables);
  /*eu sei, deveria ter usado fgets, agora já pode parar de me julgar*/

  for (i=0; i<number_of_variables; i++){
    scanf("%c\n", &variables[i]);
  }

  scanf("%s\n", gate);

  scanf("%s\n", (char *) &number_of_lines);

  for (i=0; i<number_of_lines; i++){
    for (k=0; k<number_of_variables; k++){
      scanf("%c\n", &truth_table[i][k]);
    }
  }
}

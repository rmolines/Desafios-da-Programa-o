#include <stdio.h>
#include <stdlib.h>
#include "desafio1.h"

int main(int argc, char const *argv[]) {
  int row, col, i, r, r_row, r_col;
  int board[8][8] = { {-1,-1,-1,-1,-1,-1,-1,-1,},{-1,-1,-1,-1,-1,-1,-1,-1,},{-1,-1,-1,-1,-1,-1,-1,-1,},{-1,-1,-1,0,1,-1,-1,-1,},{-1,-1,-1,1,0,-1,-1,-1,},{-1,-1,-1,-1,-1,-1,-1,-1,},{-1,-1,-1,-1,-1,-1,-1,-1,},{-1,-1,-1,-1,-1,-1,-1,-1,} };
  srand(time(NULL));

  for (i=0; i<100; i+=1){
    play(0, board, &row, &col);
    board[row][col] = 0;
    // print_board(board);
    // printf("\n");
    play(1, board, &row, &col);
    board[row][col] = 1;
    // print_board(board);
    // printf("\n");
  }

  printf("%s\n", "rodou");

  return 0;
}

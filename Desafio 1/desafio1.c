int play(int player, int board[8][8], int *p_row, int *p_col) {
  int i, j, k, board_size, plays_counter;
  int valid_plays[60][2] = {};
  plays_counter = 0;

  for (i=0; i<8; i+=1) {
    for (j=0; j<8; j+=1) {
      if (board[i][j] == player) {

        /* finds valid plays*/
        if (board[i-1][j] == !player && board[i+1][j] == -1) {
          for (k=i-2; k>=0; k-=1) {
            if (board[k][j] == player) {
              valid_plays[plays_counter][0] = i+1;
              valid_plays[plays_counter][1] = j;
              plays_counter+=1;
            }
          }
        }

        if (board[i+1][j] == !player && board[i-1][j] == -1) {
          for (k=i+2; k<8; k+=1) {
            if (board[k][j] == player) {
              valid_plays[plays_counter][0] = i-1;
              valid_plays[plays_counter][1] = j;
              plays_counter+=1;
            }
          }
        }

        if (board[i][j-1] == !player && board[i][j+1] == -1) {
          for (k=i-2; k>=0; k-=1) {
            if (board[i][k] == player) {
              valid_plays[plays_counter][0] = i1;
              valid_plays[plays_counter][1] = j+1;
              plays_counter+=1;
            }
          }
        }

        if (board[i][j-1] == !player && board[i][j-1] == -1) {
          for (k=i+2; k<8; k+=1) {
            if (board[i][k] == player) {
              valid_plays[plays_counter][0] = i;
              valid_plays[plays_counter][1] = j-1;
              plays_counter+=1;
            }
          }
        }


      }
    }
  }
}

#include <stdio.h>
#include <stdlib.h>

void print_board(int board[8][8]);
void assign_priority(int player, int valid_plays[60][3], int priorities[60], int board[8][8]);
int find_plays( int player, int board [8][8],int valid_plays[60][3]);
void create_mock_board(int board[8][8], int mock_board[8][8]);
void calculate_player_center(int board[8][8], int player, int player_avg_pos[2]);
int calculate_center_proximity(int player_avg_pos[2], int row, int col);
int return_opposing_priority(int player, int valid_plays[60][3], int board[8][8]);
int play(int player, int board[8][8], int *p_row, int *p_col);


int board_value[8][8] = { {99,-8,8,6,6,8,-8,99}, {-8,-24,-4,-3,-3,-4,-24,-8},{8,-4,7,4,4,7,-4,8},{6,-3,4,0,0,4,-3,6},{6,-3,4,0,0,4,-3,6},{8,-4,7,4,4,7,-4,8},{-8,-24,-4,-3,-3,-4,-24,-8},{99,-8,8,6,6,8,-8,99}};

int play(int player, int board[8][8], int *p_row, int *p_col) {
  int highest_priority, has_valid_play, i;
  int valid_plays[60][3] = { {0} };
  int priorities[60] = {0};
  has_valid_play = 0;
  highest_priority = 0;

  has_valid_play = find_plays(player, board, valid_plays);
  // printf("%d\n", has_valid_play);
  assign_priority(player, valid_plays, priorities, board);

  /*decides what play to choose based on priority*/
  if (has_valid_play){
    for (i = 0; i<60; i+=1){
      if (priorities[i] >=highest_priority){
        *p_row = valid_plays[i][0];
        *p_col = valid_plays[i][1];
        highest_priority = priorities[i];
      }
    }
    return 1;
  } else {
    return 0;
  }
}

int find_plays( int player, int board [8][8],int valid_plays[60][3]){
  int i, j, l, k, counter, not_player, plays_counter;
  plays_counter = 0;
  if (player == 0){
    not_player = 1;
  } else {
    not_player = 0;
  }

  /*finds valid plays*/
  for (i=0; i<8; i+=1) {
    for (j=0; j<8; j+=1) {
      if (board[i][j] == player) {

        for (k=-1; k<2; k+=1){
          for (l=-1; l<2; l+=1){
            if (board[i+l][j+k] == not_player){
              for (counter = 2; i+(l*(counter)) < 8 && i+(l*(counter)) >= 0 && j+(k*(counter)) < 8 && j+(k*(counter)) >= 0; counter+=1){
                if (board[i+(l*counter)][j+(k*counter)] == player){
                  break;
                }

                if (board[i+(l*counter)][j+(k*counter)] == -1){
                  valid_plays[plays_counter][0] = i+(l*(counter));
                  valid_plays[plays_counter][1] = j+(k*(counter));
                  valid_plays[plays_counter][2] = counter;

                  plays_counter += 1;
                  break;
                }
              }
            }
          }
        }
      }
    }
  }

  return plays_counter;
}

void create_mock_board(int board[8][8], int mock_board[8][8]){
  int i, j;

  for (i=0; i<8; i+=1){
    for (j=0; j<8; j+=1){
      mock_board[i][j] = board[i][j];
    }
  }
  return;
}

void calculate_player_center(int board[8][8], int player, int player_avg_pos[2]){
  int i, j;
  for (i=0; i<8; i+=1){
    for (j=0;j<8; j+=1){
      if (board[i][j]==player){
        player_avg_pos[0] += i;
        player_avg_pos[1] += j;
      }
    }
  }
  player_avg_pos[0]/=64;
  player_avg_pos[1]/=64;
}

int calculate_center_proximity(int player_avg_pos[2], int row, int col){
  float proximity = 0;

  proximity += (float) 20/abs((row-player_avg_pos[0]));
  proximity += (float) 20/abs((col-player_avg_pos[1]));

  if ((int) proximity<0){
    proximity = 0;
  }

  return (int) proximity;
}

int return_opposing_priority(int player, int valid_plays[60][3], int board[8][8]){
  int i, row, col, pieces, priority, proximity;
  int mock_board[8][8];
  int mock_valid_plays[60][3] = {0};
  float opposing_plays;
  int player_avg_pos[2] = {0};

  for (i=0; i<60; i+=1){
    row = valid_plays[i][0];
    col = valid_plays[i][1];
    pieces = valid_plays[i][2];


    calculate_player_center(board, player, player_avg_pos);
    proximity = calculate_center_proximity(player_avg_pos, row, col);


    if (pieces==0){
      priority = 0;
    } else {
      priority = 100;

      opposing_plays = (float)find_plays(!player, mock_board, mock_valid_plays);
      if(opposing_plays){
        opposing_plays=20/opposing_plays;
      }
      opposing_plays *= 12;

      if ((int) opposing_plays<0){
        opposing_plays = 0;
      }

      priority+=(int) opposing_plays;
      priority+=proximity;
      priority+=board_value[row][col];
      priority+=pieces*10;
    }
  }

  return priority;
}

void assign_priority(int player, int valid_plays[60][3], int priorities[60], int board[8][8]){
  int priority, i, row, col, pieces, proximity, opposing_priority, j;
  int mock_board[8][8];
  int mock_valid_plays[60][3] = {0};
  float opposing_plays;
  int player_avg_pos[2] = {0};


  for (i=0; i<60; i+=1){
    create_mock_board(board, mock_board);
    row = valid_plays[i][0];
    col = valid_plays[i][1];
    pieces = valid_plays[i][2];
    mock_board[row][col] = player;


    calculate_player_center(board, player, player_avg_pos);
    proximity = calculate_center_proximity(player_avg_pos, row, col);

    if (pieces == 0){
      priority = 0;
    } else {
      priority = 100;

      opposing_plays = (float)find_plays(!player, mock_board, mock_valid_plays);
      if(opposing_plays){
        opposing_plays=20/opposing_plays;
      }

      if ((int) opposing_plays<0){
        opposing_plays = 0;
      }

      priority += proximity;
      priority+=(int) opposing_plays;
      priority+=board_value[row][col];
      priority+=pieces*10;

      // opposing_priority += return_opposing_priority(!player, mock_valid_plays, mock_board);
      // priority += opposing_priority;

    }

    priorities[i] += priority;
  }

  return;
}

void print_board(int board[8][8]){\
  int i, j;
  for (i=0; i<8; i+=1){
    for (j=0; j<8; j+=1){
      switch (board[i][j]) {
        case -1:
          printf("%s", " .");
          break;
        case 0:
          printf("%s", " X");
          break;
        case 1:
          printf("%s", " O");
          break;
        case 2:
          printf("%s", " P");
        default:
          printf("%d ", board[i][j]);
      }
    }
    printf("\n");
  }
  printf("\n");
}

#include <stdio.h>
#include <stdlib.h>

void print_board(int board[8][8]);
void assign_priority(int player, int valid_plays[60][3], int priorities[60], int board[8][8], int empty_spaces);
int find_plays( int player, int board [8][8],int valid_plays[60][3], int *empty_spaces);
void create_mock_board(int board[8][8], int mock_board[8][8]);
void calculate_player_center(int board[8][8], int player, int player_avg_pos[2]);
int calculate_center_proximity(int player_avg_pos[2], int row, int col);
int return_opposing_priority(int player, int valid_plays[60][3], int board[8][8], int empty_spaces);
int play(int player, int board[8][8], int *p_row, int *p_col);
void assign_priority_r(int player, int valid_plays[60][3], int priorities[60], int board[8][8], int empty_spaces);


int board_value[8][8] = { {99,-8,8,6,6,8,-8,99}, {-8,-24,-4,-3,-3,-4,-24,-8},{8,-4,7,4,4,7,-4,8},{6,-3,4,0,0,4,-3,6},{6,-3,4,0,0,4,-3,6},{8,-4,7,4,4,7,-4,8},{-8,-24,-4,-3,-3,-4,-24,-8},{99,-8,8,6,6,8,-8,99}};

int board_value_dias[8][8]={{120,-20, 20,  5,  5, 20,-20,120},//0
                   {-20,-40, -5, -5, -5, -5,-40,-20},//1
                   { 20, -5, 15,  3,  3, 15, -5, 20},//2
                   {  5, -5,  3,  3,  3,  3, -5,  5},//3
                   {  5, -5,  3,  3,  3,  3, -5,  5},//4
                   { 20, -5, 15,  3,  3, 15, -5, 20},//5
                   {-20,-40, -5, -5, -5, -5,-40,-20},//6
                   {120,-20, 20,  5,  5, 20,-20,120}};//7


int play(int player, int board[8][8], int *p_row, int *p_col) {
  int highest_priority, has_valid_play, i, empty_spaces;
  int valid_plays[60][3] = { {0} };
  int priorities[60] = {0};
  has_valid_play = 0;
  highest_priority = -40;
  empty_spaces = 0;

  has_valid_play = find_plays(player, board, valid_plays, &empty_spaces);
  // printf("%d\n", has_valid_play);
  assign_priority(player, valid_plays, priorities, board, empty_spaces);

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

int find_plays( int player, int board [8][8],int valid_plays[60][3], int *empty_spaces){
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
      if (board[i][j] == -1){
        *empty_spaces+=1;
      }
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

int return_opposing_priority(int player, int valid_plays[60][3], int board[8][8], int empty_spaces){
  int priority, i, row, col, pieces, proximity, mock_empty_spaces;
  int mock_board[8][8];
  int mock_valid_plays[60][3] = {};
  int opposing_plays;
  int player_avg_pos[2] = {0};
  priority = 0;

  for (i=0; i<60; i+=1){
    create_mock_board(board, mock_board);
    row = valid_plays[i][0];
    col = valid_plays[i][1];
    pieces = valid_plays[i][2];
    mock_board[row][col] = player;


    calculate_player_center(board, player, player_avg_pos);
    proximity = calculate_center_proximity(player_avg_pos, row, col);

    if (pieces == 0){
      priority += 0;
    } else {
      priority += 100;

      opposing_plays = find_plays(!player, mock_board, mock_valid_plays, &mock_empty_spaces);

      if (opposing_plays<=0){
        opposing_plays = 0;
      } else {
        opposing_plays = 200/opposing_plays;
      }

      if(empty_spaces>20){
        priority+=10/pieces;
      } else {
        priority+=10*pieces;
      }

      priority+=proximity;
      priority+=opposing_plays;
      priority+=board_value[row][col];
    }
  }
  return priority/60;
}


// void assign_priority_r(int player, int valid_plays[60][3], int board[8][8]){
//   int priority, i, row, col, pieces, proximity, opposing_priority, mock_empty_spaces, highest_priority, highest_priority_index;
//   highest_priority = -41;
//   int mock_board[8][8];
//   int mock_valid_plays[60][3] = {};
//   int mock_priorities[60] = {0};
//   int opposing_plays;
//   int player_avg_pos[2] = {0};
//
//
//   for (i=0; i<60; i+=1){
//     row = valid_plays[i][0];
//     col = valid_plays[i][1];
//     pieces = valid_plays[i][2];
//
//     if (opposing_plays<=0){
//       opposing_plays = 0;
//     }
//
//     if (pieces == 0){
//       priority = 0;
//     } else {
//       priority = board_value_dias[row][col];
//
//       if (priority>highest_priority){
//         highest_priority = priority;
//         highest_priority_index = i;
//       }
//     }
//   }
//
//   create_mock_board(board, mock_board); //cria um tabuleiro simulando cada jogada possível
//   row = valid_plays[highest_priority_index][0];
//   col = valid_plays[highest_priority_index][1];
//   mock_board[row][col] = player;
//
//   opposing_plays = find_plays(!player, mock_board, mock_valid_plays);
//
//   assign_priority_r(!player, mock_valid_plays, mock_board, mock_empty_spaces);
//
//   return;
// }


void assign_priority(int player, int valid_plays[60][3], int priorities[60], int board[8][8], int empty_spaces){
  int priority, i, row, col, pieces, proximity, opposing_priority, mock_empty_spaces, mock_priority, mock_lowest_priority, mock_row, mock_col;
  mock_lowest_priority = 121;
  int mock_board[8][8];
  int mock_valid_plays[60][3] = {};
  int opposing_plays;
  int player_avg_pos[2] = {0};


  for (i=0; i<60; i+=1){
    row = valid_plays[i][0];
    col = valid_plays[i][1];
    pieces = valid_plays[i][2];

    create_mock_board(board, mock_board); //cria um tabuleiro simulando cada jogada possível
    mock_board[row][col] = player;


    // calcula a proximidade da peça com o centro medio das peças já no tabuleiro
    // calculate_player_center(board, player, player_avg_pos);
    // proximity = calculate_center_proximity(player_avg_pos, row, col);

    if (pieces == 0){
      priority = 0;
    } else {
      priority = 0;

      opposing_plays = find_plays(!player, mock_board, mock_valid_plays, &mock_empty_spaces);

      if (opposing_plays<=0){
        opposing_plays = 0;
      }

      for (int j = 0; j<60; j++){
        mock_row = mock_valid_plays[j][0];
        mock_col = mock_valid_plays[j][1];

        mock_priority = board_value_dias[mock_row][mock_col];

        if (mock_priority<mock_lowest_priority){
          mock_lowest_priority = mock_priority;
        }
      }

      // opposing_priority = return_opposing_priority(!player, mock_valid_plays, mock_board, mock_empty_spaces);

      // if (opposing_priority<=0){
      //   opposing_priority=0;
      // } else {
      //   opposing_priority = 50/opposing_priority;
      // }

      // priority+=opposing_priority;
      // priority+=proximity;
      // priority+=opposing_plays;
      // priority+=board_value[row][col];
      priority += board_value_dias[row][col];
      priority += mock_priority;
      priority /= 2;
      // if(empty_spaces>20){
      //   priority+=10/pieces;
      // } else {
      //   priority+=10*pieces;
      // }

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

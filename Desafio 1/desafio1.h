#include <stdio.h>
#include <stdlib.h>
#include "desafio1.c"

void print_board(int board[8][8]);
void assign_priority(int player, int valid_plays[60][3], int priorities[60], int board[8][8]);
int find_plays( int player, int board [8][8],int valid_plays[60][3]);
void create_mock_board(int board[8][8], int mock_board[8][8]);
void calculate_player_center(int board[8][8], int player, int player_avg_pos[2]);
int calculate_center_proximity(int player_avg_pos[2], int row, int col);
int return_opposing_priority(int player, int valid_plays[60][3], int board[8][8]);
int play(int player, int board[8][8], int *p_row, int *p_col);

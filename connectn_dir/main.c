/*
Program sets up connect N, plays game, and cleans up after
*/

#include <stdio.h>
#include <stdlib.h>
#include "set_up_game.h"
#include "play_game.h"

int main(int argc, char** argv) {
    int rows = get_row_from_cmd_line(argc, argv);
    int columns = get_col_from_cmd_line(argc, argv);
    int winNum = get_N_from_cmd_line(argc, argv);
    char** board;
    char* player_pieces;
    int cur_player_turn = 0;
    set_up_game(rows, columns, &board, &player_pieces);
    play_game(board, cur_player_turn, player_pieces, rows, columns, winNum);
    cleanup(&board, rows, &player_pieces);

    return 0;

}
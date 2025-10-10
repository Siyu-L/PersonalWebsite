#ifndef PLAY_GAME_H
#define PLAY_GAME_H
    #include <stdbool.h>
    void print_board(char** board, int row, int col);
    bool win_vertical(char** board, char cur_player_piece, int row, int playerCol, int win);
    bool win_horizontal(char** board, char cur_player_piece, int playerRow, int col, int win);
    bool win_left_diagonal(char** board, char cur_player_piece, int row, int col, int playerRow, int playerCol, int win);
    bool win_right_diagonal(char** board, char cur_player_piece, int row, int col, int playerRow, int playerCol, int win);
    bool has_won(char** board, char cur_player_piece, int row, int col, int playerRow, int playerCol, int win);
    bool column_full(char** board, int row, int player_col);
    int pick_valid_column(char** board, int row, int col);
    int get_landing_row(char** board, int row, int player_col);
    void take_turn(char** board, char cur_player_piece, int row, int col, int* player_row, int* player_col);
    void announce_game_results(int cur_player_turn, bool is_tie);
    void switch_player(int *cur_player_turn);
    void play_game(char** board, int cur_player_turn, char* player_pieces, int row, int col, int win);



#endif
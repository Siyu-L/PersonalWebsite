#ifndef SET_UP_GAME_H
#define SET_UP_GAME_H

    void check_cmd_line_args(int argc);
    int get_row_from_cmd_line(int argc, char** argv);
    int get_col_from_cmd_line(int argc, char** argv);
    int get_N_from_cmd_line(int argc, char** argv);
    char** create_board(int row, int col);
    char* set_player_pieces();
    void set_up_game(int row, int col, char** *out_board, char* *out_player_pieces);
    void cleanup(char** *board, int rows, char* *player_pieces);

#endif
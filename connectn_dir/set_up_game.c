/*
Program sets up game connect N
*/

#include <stdio.h>
#include <stdlib.h>
#include "set_up_game.h"

/*command line functions modified from class drive
checks if there are correct number of command line arguments
@param argc: number of command line arguments
*/
void check_cmd_line_args(int argc) {
    if (argc < 4){
        printf("Not enough arguments entered\n");
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
        exit(0);        
    }
    if (argc > 4) {
        printf("Too many arguments entered\n");
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
        exit(0);  

    }
}

/*
Gets the number of rows from command line
@param argc: number of command line arguments
@param argv: command line arguments
@return rows: number of rows
*/
int get_row_from_cmd_line(int argc, char** argv) {
    check_cmd_line_args(argc);
    int rows;
    char should_be_blank;
    int num_args_read = sscanf(argv[1], "%d %c", &rows, &should_be_blank);
    if(num_args_read != 1){
        printf("Rows needs to be an integer. Found %s\n", argv[1]);
        exit(0);
    }
    return rows;
    

}

/*
Gets the number of columns from command line
@param argc: number of command line arguments
@param argv: command line arguments
@return columns: number of columns
*/
int get_col_from_cmd_line(int argc, char** argv) {
    check_cmd_line_args(argc);
    int columns;
    char should_be_blank;
    int num_args_read = sscanf(argv[2], "%d %c", &columns, &should_be_blank);
    if(num_args_read != 1){
        printf("Columns needs to be an integer. Found %s\n", argv[2]);
        exit(0);
    }
    return columns;
    

}

/*
Gets the number of pieces in a row to win
@param argc: number of command line arguments
@param argv: command line arguments
@return winNum: number of pieces in a row to win
*/
int get_N_from_cmd_line(int argc, char** argv) {
    check_cmd_line_args(argc);
    int winNum;
    char should_be_blank;
    int num_args_read = sscanf(argv[3], "%d %c", &winNum, &should_be_blank);
    if(num_args_read != 1){
        printf("WinNum needs to be an integer. Found %s\n", argv[3]);
        exit(0);
    }
    return winNum;
    

}

/*create board code from class drive
@param row: number of rows
@param col: number of columns
@return board: board with specified number of rows and columns
*/
char** create_board(int row, int col) {
    char** board = (char**)malloc(row * sizeof(char*));

    for(int i = 0; i < row; i++) {
        board[i] = (char*)malloc(row * sizeof(char));
        for(int j = 0; j < col; j++) {
            board[i][j] = '*';
        }
    }
    return board;
}

/*
Sets player pieces
@return pieces: pieces representing the players
*/
char* set_player_pieces() {
    char* pieces = (char*)malloc(2 * sizeof(char));
    pieces[0] = 'X';
    pieces[1] = 'O';
    return pieces;
}

/*
creates board and sets up pieces
@param row: number of rows in the board
@param col: number of columns in the board
@param out_board: game board
@param out_player_pieces: the players' pieces
*/
void set_up_game(int row, int col, char** *out_board, char* *out_player_pieces) {
    *out_board = create_board(row, col);
    *out_player_pieces = set_player_pieces();

}

/*cleanup code from class drive
@param board: game board
@param row: number of rows in board
@param player_pieces: the players' pieces
*/
void cleanup(char** *board, int row, char* *player_pieces){
    for(int i = 0; i < row; i++){
        free((*board)[i]);
    }
    free(*board);
    *board = NULL;

    free(*player_pieces);
    *player_pieces = NULL;

}
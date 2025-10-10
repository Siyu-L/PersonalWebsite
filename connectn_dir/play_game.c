/*
Program plays the game connect N
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "play_game.h"
#include "input_validation.h"

/* print_board code modified from class drive
Function prints out entire board
@param board: game board to be printed
@param row: number of rows in the board
@param col: number of columns in the board
*/
void print_board(char** board, int row, int col) {

    for(int i = 0; i < row; i++) {
        printf("%d ", row - i-1);
        for(int j = 0; j < col; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");

    }
    printf("  ");
    for(int i = 0; i < col; i++) {
        printf("%d ", i);
    }
    printf("\n");

}

/*
Function checks if there is a vertical win
@param board: game board
@param cur_player_piece: character representing current player's pieces
@param row: number of rows in the board
@param playerCol: column that the player dropped piece in
@param win: number of pieces in a row needed to win
@return: true if there is a vertical win
*/
bool win_vertical(char** board, char cur_player_piece, int row, int playerCol, int win) {
    int count = 0;
    for(int i = 0; i < row; i++) {
        if (board[i][playerCol] == cur_player_piece) {
            count++;
        }
        else {
            count = 0;
        }
        if (count >= win) {
            return true;
        }
        
    }
    return false;
}

/*
Function checks if there is a horizontal win
@param board: game board
@param cur_player_piece: character representing current player's pieces
@param playerRow: row which player's piece landed in
@param col: number of columns in the board
@param win: number of pieces in a row needed to win
@return: true if there is a horizontal win
*/
bool win_horizontal(char** board, char cur_player_piece, int playerRow, int col, int win) {
    int count = 0;
    for(int j = 0; j < col; j++) {
        if(board[playerRow][j] == cur_player_piece) {
            count++;
        }
        else {
            count = 0;
        }
        if(count >= win) {
            return true;
        }

        }

    return false;
}

/*
Function checks if there is a win on the left diagonal
@param board: game board
@param cur_player_piece: character representing current player's pieces
@param row: number of rows in the board
@param col: number of columns in the board
@param playerRow: row which player's piece landed in
@param playerCol: column that the player dropped piece
@param win: number of pieces in a row needed to win
@return: true if there is a left diagonal win
*/
bool win_left_diagonal(char** board, char cur_player_piece, int row, int col, int playerRow, int playerCol, int win) {
    /* Checking for a win on the main diagonal that looks like this

        X
            X
                X
    */

    int count = 1;
    int x = playerRow - 1;
    int y = playerCol - 1;
    while((x >= 0 && y >= 0) && board[x][y] == cur_player_piece) {
        count++;
        x--;
        y--;
    }
    x = playerRow + 1;
    y = playerCol + 1;
    while((x < row && y < col) && board[x][y] == cur_player_piece) {
        count++;
        x++;
        y++;
    }
    return (count >= win);
}

/*
Function checks if there is a win on the right diagonal
@param board: game board
@param cur_player_piece: character representing current player's pieces
@param row: number of rows in the board
@param col: number of columns in the board
@param playerRow: row which player's piece landed in
@param playerCol: column that the player dropped piece
@param win: number of pieces in a row needed to win
@return: true if there is a right diagonal win
*/
bool win_right_diagonal(char** board, char cur_player_piece, int row, int col, int playerRow, int playerCol, int win) {
    /* Checking for a win on the main diagonal that looks like this

                X
            X
        X
    */
    
    int count = 1;
    int x = playerRow - 1;
    int y = playerCol + 1;
    while((x >= 0 && y < col) && board[x][y] == cur_player_piece) {
        count++;
        x--;
        y++;
    }
    x = playerRow + 1;
    y = playerCol - 1;
    while((x < row && y >=0 ) && board[x][y] == cur_player_piece) {
        count++;
        x++;
        y--;
    }
    return (count >= win);
}

/*
Checks if there is a win in any way
@param board: game board
@param cur_player_piece: character representing current player's pieces
@param row: number of rows in the board
@param col: number of columns in the board
@param playerRow: row which player's piece landed in
@param playerCol: column that the player dropped piece
@param win: number of pieces in a row needed to win
@return: true if there is a win
*/

bool has_won(char** board, char cur_player_piece, int row, int col, int playerRow, int playerCol, int win) {
    if(win_horizontal(board, cur_player_piece, playerRow, col, win) || win_vertical(board, cur_player_piece, row, playerCol, win) || win_left_diagonal(board, cur_player_piece, row, col, playerRow, playerCol, win) || win_right_diagonal(board, cur_player_piece, row, col, playerRow, playerCol, win)) {
        return true;
    }
    else {
        return false;
    }

}

/*
Checks if column player chose is full
@param board: game board
@param row: number of rows in the board
@param player_col: column the player chose
@return: true if column is full
*/
bool column_full(char** board, int row, int player_col) {
    for(int i = 0; i < row; i++) {
        if(board[i][player_col] == '*') {
            return false;
        }

    }
    return true;

}

/*
Gets a valid column from user
@param board: game board
@param row: number of rows in the board
@param col: number of columns in the board
@return playerCol: column that player chose
*/
int pick_valid_column(char** board, int row, int col) {
    int playerCol;
    do {
    playerCol = getValidIntInRange(0, col - 1);
    }while(column_full(board, row, playerCol));

    return playerCol;

}

/*
Gets the row the piece lands on
@param board: game board
@param row: number of rows in the board
@param playerCol: column that player chose
@return landingRow: row which the piece lands on
*/
int get_landing_row(char** board, int row, int playerCol) {
    int landingRow = row-1;
    while(board[landingRow][playerCol] != '*') {
        landingRow--;
    }

    return landingRow;

}

/*
Prints the board, gets the input for column, gets the row which the piece lands on, places piece
@param board: game board
@param cur_player_piece: character representing current player's piece
@param row: number of rows in the board
@param col: number of columns in the board
@param player_row: row which the piece landed in
@param player_col: column that the player chose
*/
void take_turn(char** board, char cur_player_piece, int row, int col, int* player_row, int* player_col) {
    print_board(board, row, col);
    *player_col = pick_valid_column(board, row, col);
    *player_row = get_landing_row(board, row, *player_col);
    board[*player_row][*player_col] = cur_player_piece;
}

/*
Announces results after game is over
@param cur_player_turn: which player has won
@param is_tie: whether or not the game ended in a tie
*/
void announce_game_results(int cur_player_turn, bool is_tie) {
    if (is_tie) {
        printf("Tie game!\n");

    } else {
        printf("Player %d Won!\n", cur_player_turn + 1);
    }

}

/*
switch_player code taken from class drive
switches between player 1 and player 2
@param cur_player_turn: the current player
*/
void switch_player(int *cur_player_turn) {
    if(*cur_player_turn == 0) {
        *cur_player_turn = 1;
    }else {
        *cur_player_turn = 0;
    }
}

/*
Plays the game
@param board: game board
@param cur_player_turn: the current player
@param player_pieces: the characters representing each player's pieces
@param row: number of rows in the board
@param col: number of columns in the board
@param win: number of same pieces in a row to win
*/
void play_game(char** board, int cur_player_turn, char* player_pieces, int row, int col, int win) {
    int turn_count = 0;
    bool is_tie;
    int player_row;
    int player_col;
    while(true) {
        take_turn(board, player_pieces[cur_player_turn], row, col, &player_row, &player_col);
        turn_count++;
        if(has_won(board, player_pieces[cur_player_turn], row, col, player_row, player_col, win)) {
            is_tie = false;
            break;
        }
        if(turn_count >= (row*col)) {
            is_tie = true;
            break;
        }
        switch_player(&cur_player_turn);
    }
    print_board(board, row, col);
    announce_game_results(cur_player_turn, is_tie);

}
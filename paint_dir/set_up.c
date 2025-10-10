#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "set_up.h"
#include "input_validation.h"


/*command line functions modified from class drive
checks if there are correct number of command line arguments
@param argc: number of command line arguments
*/
bool check_cmd_line_args(int argc) {
    if(argc == 3) {
        return true;
    }
    else if (argc == 1) {
        return false;
    }
    else {
        printf("Wrong number of command line arguments entered.\n");
        printf("Usage: ./paint.out [num_rows num_cols]\n");
        return false;
    }
}


/*
Gets the number of rows from command line
@param argc: number of command line arguments
@param argv: command line arguments
@return rows: number of rows
*/
int get_row_from_cmd_line(int argc, char** argv) {

        int rows;
        char should_be_blank;
        int num_args_read = sscanf(argv[1], "%d %c", &rows, &should_be_blank);
        if(num_args_read != 1){
            printf("The number of rows is not an integer.\n");
            return 10;
        }

        else {
        return rows;
        }

}


/*
Gets the number of columns from command line
@param argc: number of command line arguments
@param argv: command line arguments
@return columns: number of columns
*/
int get_col_from_cmd_line(int argc, char** argv) {

        int col;
        char should_be_blank;
        int num_args_read = sscanf(argv[2], "%d %c", &col, &should_be_blank);
        if(num_args_read != 1){
            printf("The number of columns is not an integer.\n");
            return 10;
        }

         else {
        return col;
        }

}


/*create board code from class drive
@param row: number of rows
@param col: number of columns
@return canvas: canvas with specified number of rows and columns
*/
char** create_canvas(int row, int col) {
    char** board = (char**)malloc(row * sizeof(char*));

    for(int i = 0; i < row; i++) {
        board[i] = (char*)malloc(row * sizeof(char));
        for(int j = 0; j < col; j++) {
            board[i][j] = '*';
        }
    }
    return board;
}
/* creates canvas struct from command line
@param argc: number of command line arguments
@param argv: command line arguments
@return tempCan: canvas struct
*/

Canvas* set_up_canvas(int argc, char** argv) {
    Canvas* tempCan = (Canvas*)malloc(1 * sizeof(Canvas));
    int row;
    int column;
    bool isSpec = check_cmd_line_args(argc);
    if(isSpec) {
        row = get_row_from_cmd_line(argc, argv);
        column = get_col_from_cmd_line(argc, argv);
    }

    if(!isSpec || row < 0 || column < 0) {
        if(row < 0) {
            printf("The number of rows is less than 1.\n");        
        }
        if(column < 0) {
            printf("The number of columns is less than 1.\n");
        }
        printf("Making default board of 10 X 10.\n");
        row = 10;
        column = 10;
    }

    tempCan->canvas = create_canvas(row, column);
    tempCan->rows = row;
    tempCan->columns = column;
    return tempCan;

}
/* prints out canvas
@param canPoint: pointer to canvas struct
@return: nothing
*/
void print_canvas(Canvas* canPoint) {

    int row = canPoint->rows;
    int col = canPoint->columns;
    char** canvas = canPoint->canvas;

    for(int i = 0; i < row; i++) {
        printf("%d ", row - i-1);
        for(int j = 0; j < col; j++) {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");

    }
    printf("  ");
    for(int i = 0; i < col; i++) {
        printf("%d ", i);
    }
    printf("\n");

}
/* erases a point on the canvas
@param canPoint: pointer to canvas
@param row: row of point
@param col: column of point
@modifies: canPoint
*/
void erase(Canvas* canPoint, int row, int col) {
    canPoint->canvas[canPoint->rows - 1 - row][col] = '*';

}

/*returns the canvas without the columnn remCol
@param canPoint: canvas pointer
@param remCol: column to remove
@return tempMat: new canvas without deleted column
*/
char** delete_column(Canvas* canPoint, int remCol) {


    char** src = canPoint->canvas;
    canPoint->columns = canPoint->columns - 1;

    int rows = canPoint->rows;
    int columns = canPoint->columns;


    char** tempMat = (char**)malloc(rows * sizeof(char*));
    for(int i = 0; i < rows; i++) {
        tempMat[i] = (char*)malloc(columns * sizeof(char));
    }

    for(int j = 0; j < remCol; j++) {
        for(int i = 0; i < rows; i++) {
            tempMat[i][j] = src[i][j];
        }
    }
    for(int j = remCol+1; j < columns+1; j++) {
        for(int i = 0; i < rows; i++) {
            tempMat[i][j-1] = src[i][j];
        }
    }

    return tempMat;

}

/*returns the canvas without the row remRow
@param canPoint: canvas pointer
@param remRow: row to remove
@return tempMat: new canvas without deleted row
*/

char** delete_row(Canvas* canPoint, int remRow) {

    char** src = canPoint->canvas;
    canPoint->rows = canPoint->rows - 1;

    int rows = canPoint->rows;
    int columns = canPoint->columns;
    remRow = canPoint->rows - remRow;

    char** tempMat = (char**)malloc(rows * sizeof(char*));

    for(int i = 0; i < rows; i++) {
        tempMat[i] = (char*)malloc(columns * sizeof(char));
    }

    for(int i = 0 ; i < remRow; i++) {
        tempMat[i] = src[i];
    }
    for(int i = remRow+1; i < rows + 1; i++) {
        tempMat[i-1] = src[i];
    }
    return tempMat;

}

/* adds a column to the canvas
@param canPoint: canvas pointer
@param addCol: column to add

*/
void add_column(Canvas* canPoint, int addCol) {
    
    canPoint->columns = canPoint->columns + 1;
    int rows = canPoint->rows;
    int cols = canPoint->columns;
    for(int i = 0; i < rows; i++) {
        canPoint->canvas[i] = (char*)realloc(canPoint->canvas[i], cols * sizeof(char));
    }
    for(int i = 0; i < rows; i++) {
        for(int j = cols - 1; j > addCol; j--) {
            canPoint->canvas[i][j] = canPoint->canvas[i][j-1];
        }
    }

    for(int i = 0; i < rows; i++) {
        canPoint->canvas[i][addCol] = '*';
    }

}
/* adds a row to the canvas
@param canPoint: canvas pointer
@param addRow: row to add

*/
void add_row(Canvas* canPoint, int addRow) {
    
    canPoint->rows = canPoint->rows + 1;
    int rows = canPoint->rows;
    int cols = canPoint->columns;
    canPoint->canvas = (char**)realloc(canPoint->canvas, rows * sizeof(char*));
    canPoint->canvas[rows-1] = (char*)malloc(1 * sizeof(char));

    addRow = rows - 1 - addRow;
    for(int j = 0; j < cols; j++) {
        for(int i = rows - 1; i > addRow; i--) {
            canPoint->canvas[i][j] = canPoint->canvas[i-1][j];
        }
    }

    for(int j = 0; j < cols; j++) {
        canPoint->canvas[addRow][j] = '*';
    }

}
/* resizes canvas to given dimensions
@param canPoint: canvas pointer
@param num_rows: number of rows
@param num_cols: number of columns

*/
void resize(Canvas* canPoint, int num_rows, int num_cols) {
    while(num_rows > canPoint->rows) {
        add_row(canPoint, canPoint->rows-1);
    }
    while(num_cols > canPoint->columns) {
        add_column(canPoint, canPoint->columns-1);
    }


    while(num_rows < canPoint->rows) {
        canPoint->canvas = delete_row(canPoint, canPoint->rows);

    }
    while(num_cols < canPoint->columns) {
        canPoint->canvas = delete_column(canPoint, canPoint->columns);
    }
}


/* checks if horizontal
@param y1: y coordinate 1
@param y2: y coordinate 2
*/
bool isHoriz(int y1, int y2) {
    return (y1 - y2 == 0);
}


/* checks if vertical
@param x1: x coordinate 1
@param x2: x coordinate 2
*/
bool isVertic(int x1, int x2) {
    return (x1 - x2 == 0);
}

/* checks if diagonal
@param x1: x coordinate 1
@param y1: y coordinate 1
@param x2: x coordinate 2
@param y2: y coordinate 2
*/
bool isDiagonal(int x1, int y1, int x2, int y2) {
    int xComp;
    int yComp;
    if((x2 - x1) < 0) {
        xComp = -1 * (x2 - x1);
    }
    else {
        xComp = (x2 - x1);
    }

    if((y2 - y1) < 0) {
        yComp = -1 * (y2 - y1);
    }
    else {
        yComp = (y2 - y1);
    }

    return(xComp == yComp);

}

/* checks if left diagonal
@param x1: x coordinate 1
@param y1: y coordinate 1
@param x2: x coordinate 2
@param y2: y coordinate 2
*/
bool isLeftDiag(int x1, int y1, int x2, int y2) {
    if(isDiagonal(x1, y1, x2, y2)) {
        return (x2 < x1 && y2 > y1) || (x2 < x1 && y2 < y1);
    }
    else {
        return false;
    }

}

/* checks if right diagonal
@param x1: x coordinate 1
@param y1: y coordinate 1
@param x2: x coordinate 2
@param y2: y coordinate 2
*/
bool isRightDiag(int x1, int y1, int x2, int y2) {
    if(isDiagonal(x1, y1, x2, y2)) {
        return (x2 < x1 && y2 < y1) || (x2 >x1 && y2 > y1);
    }
    else {
        return false;
    }

}

/* checks if line is straight
@param x1: x coordinate 1
@param y1: y coordinate 1
@param x2: x coordinate 2
@param y2: y coordinate 2
*/
bool isStraight(int x1, int y1, int x2, int y2) {
    return (isHoriz(y1, y2) || isVertic(x1, x2) || isDiagonal(x1, y1, x2, y2));

}

/* draws a line on the canvas
@param canPoint: canvas pointer
@param x1: x coordinate 1
@param y1: y coordinate 1
@param x2: x coordinate 2
@param y2: y coordinate 2
*/
void write(Canvas* canPoint, int y1, int x1, int y2, int x2) {
    char letter;
    int startX;
    int endX;
    int startY;
    int endY;
    bool isVertical = isVertic(x1, x2);
    bool isHorizontal = isHoriz(y1, y2);
    bool isRDiagonal = isRightDiag(x1, y1, x2, y2);


    if(!isStraight(x1, y1, x2, y2)) {
        printf("Improper draw command.\n");
        return;
    }

    if(isHorizontal) {
        letter = '-';
    }
    else if(isVertical) {
        letter = '|';
    }
    else if(isRDiagonal) {
        letter = '/';
    }
    else {
        letter = '\\';
    }


    if(x1 >= x2) {
        startX = x2;
        startY = canPoint->rows - 1 - y2;
        endX = x1;
        endY = canPoint->rows - 1 - y1;
    }
    else {
        startX = x1;
        startY = canPoint->rows - 1 - y1;        
        endX = x2;
        endY = canPoint->rows - 1 - y2;
    }


    int i;
    int j;
    if (isRDiagonal) {    
        for(j = startX, i = startY; j <= endX && i >= endY; j++, i--) {
            if(canPoint->canvas[i][j] != '*' && canPoint->canvas[i][j] != letter) {
                canPoint->canvas[i][j] = '+';
            }else {
                canPoint->canvas[i][j] = letter;
            }
        }
    } else if (isHorizontal) {
        for(j = startX, i = startY; j <= endX; j++) {
            if(canPoint->canvas[i][j] != '*' && canPoint->canvas[i][j] != letter) {
                canPoint->canvas[i][j] = '+';
            }else {
                canPoint->canvas[i][j] = letter;
            }
        }
    } else if (isVertical && startY >= endY) {
        for(j = startX, i = startY; i >=endY; i--) {
            if(canPoint->canvas[i][j] != '*' && canPoint->canvas[i][j] != letter) {
                canPoint->canvas[i][j] = '+';
            }else {
                canPoint->canvas[i][j] = letter;
            }            
        }
    } else if(isVertical && startY <= endY) {
        for(j = startX, i = startY; i <= endY; i++) {
            if(canPoint->canvas[i][j] != '*' && canPoint->canvas[i][j] != letter) {
                canPoint->canvas[i][j] = '+';
            }else {
                canPoint->canvas[i][j] = letter;
            }                 
        }
    }

    else{        
        for(i = startY, j = startX; j <= endX && i <= endY; j++, i++) {
            if(canPoint->canvas[i][j] != '*' && canPoint->canvas[i][j] != letter) {
                canPoint->canvas[i][j] = '+';
            }else {
                canPoint->canvas[i][j] = letter;
            }
        }
    }

}

/* saves canvas into a file
@param canPoint: canvas pointer
@param file_name: file name
*/
void save(Canvas* canPoint, char* file_name) {
    int rows = canPoint->rows;
    int columns = canPoint->columns;
    FILE* saveFile = fopen(file_name, "w");
    if(saveFile == NULL) {
        printf("Improper save command or file could not be created.\n");
        return;
    }
    fprintf(saveFile, "%d", rows);
    fprintf(saveFile, " ");
    fprintf(saveFile, "%d", columns);
    fprintf(saveFile, "\n");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            fprintf(saveFile, "%c", canPoint->canvas[i][j]);
        }
        fprintf(saveFile, "\n");
    }
    fclose(saveFile);
}
/* loads canvas from a file
@param canPoint: canvas pointer
@param file_name: file name
*/
void load(Canvas* canPoint, char* file_name) {

    int rows;
    int columns;

    FILE* loadFile = fopen(file_name, "r");
    if(loadFile == NULL) {
        printf("Improper load command or file could not be opened.\n");
        return;
    }
    fscanf(loadFile, "%d %d", &rows, &columns);

    canPoint->rows = rows;
    canPoint->columns = columns;
    canPoint->canvas = create_canvas(canPoint->rows, canPoint->columns);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            fscanf(loadFile, " %c", &canPoint->canvas[i][j]);
        }
    }

    fclose(loadFile);

}
/* prints out command information*/
void print_help(){

  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}


/*cleanup code from class drive
@param board: game board
@param row: number of rows in board
@param player_pieces: the players' pieces
*/
void cleanup(char** *board, int row){
    for(int i = 0; i < row; i++){
        free((*board)[i]);
    }
    free(*board);
    *board = NULL;

}

/*cleans up and terminates program
@param canPoint: canvas pointer
*/
void quit(Canvas* canPoint) {
    cleanup(&canPoint->canvas, canPoint->rows);
    exit(0);
}

/*executes command with given arguments
@param canPoint: canvas pointer
@param file_name: file name
@param letter: command letter
@param dimension: row or column
@param arg1: possible row or column argument
@param arg2: possible row or column argument
@param arg3: possible row or column argument
@param arg4: possible row or column argument
*/
void findCommand(Canvas* canPoint, char* file_name, char letter, char dimension, int arg1, int arg2, int arg3, int arg4) {
    if(letter == 'q') {
        quit(canPoint);
    }
    else if(letter == 'h') {
        print_help();
    }
    else if (letter == 'w') {
        write(canPoint, arg1, arg2, arg3, arg4);
    }
    else if (letter == 'e') {
        erase(canPoint, arg1, arg2);
    }
    else if (letter == 'r') {
        resize(canPoint, arg1, arg2);
    }
    else if (letter == 'a' && dimension == 'r') {
        add_row(canPoint, arg1);
    }
    else if (letter == 'a' && dimension == 'c') {
        add_column(canPoint, arg1);
    }
    else if (letter == 'd' && dimension == 'r') {
        canPoint->canvas = delete_row(canPoint, arg1);
    }
    else if (letter == 'd' && dimension == 'c') {
        canPoint->canvas = delete_column(canPoint, arg1);        
    }
    else if (letter == 's') {
        save(canPoint, file_name);
    }
    else {
        load(canPoint, file_name);
    }

};
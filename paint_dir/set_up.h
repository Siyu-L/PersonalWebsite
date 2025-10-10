#ifndef SET_UP_H
#define SET_UP_H 
    
    typedef struct Canvas_struct{
    int rows;
    int columns;
    char** canvas;
    }Canvas;

    bool check_cmd_line_args(int argc);
    int get_row_from_cmd_line(int argc, char** argv);
    int get_col_from_cmd_line(int argc, char** argv);
    char** create_canvas(int row, int col);
    Canvas* set_up_canvas(int argc, char** argv);
    void print_canvas(Canvas* canPoint);
    void erase(Canvas* canPoint, int row, int col);
    char** delete_column(Canvas* canPoint, int remCol);
    char** delete_row(Canvas* canPoint, int remRow);
    void add_column(Canvas* canPoint, int addCol);
    void add_row(Canvas* canPoint, int addRow);
    void resize(Canvas* canPoint, int num_rows, int num_cols);
    bool isHoriz(int y1, int y2);
    bool isVertic(int x1, int x2);
    bool isDiagonal(int x1, int y1, int x2, int y2);
    bool isLeftDiag(int x1, int y1, int x2, int y2);
    bool isRightDiag(int x1, int y1, int x2, int y2);
    bool isStraight(int x1, int y1, int x2, int y2);
    void write(Canvas* canPoint, int y1, int x1, int y2, int x2);
    void save(Canvas* canPoint, char* file_name);
    void load(Canvas* canPoint, char* file_name);
    void print_help();
    void cleanup(char** *board, int row);
    void quit(Canvas* canPoint);
    void findCommand(Canvas* canPoint, char* file_name, char letter, char dimension, int arg1, int arg2, int arg3, int arg4);

#endif
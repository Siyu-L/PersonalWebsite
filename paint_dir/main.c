/*Program sets up and runs paint*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "set_up.h"
#include "input_validation.h"

int main(int argc, char** argv) {
    Canvas* canPoint = (Canvas*)malloc(1 * sizeof(Canvas));
    canPoint = set_up_canvas(argc, argv);
    print_canvas(canPoint);

    char dimensions;
    char letter;
    char* file_name;
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    while(true) {

        getValidCommand(canPoint->rows, canPoint->columns, &file_name, &letter, &dimensions, &arg1, &arg2, &arg3, &arg4);
        findCommand(canPoint, file_name, letter, dimensions, arg1, arg2, arg3, arg4);
        print_canvas(canPoint);
    
    }
    return 0;

}
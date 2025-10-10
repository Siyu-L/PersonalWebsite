/*
Programs checks if user input is valid
Code taken from class drive
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <ctype.h>
#include "input_validation.h"

/*
checks if input has valid format
@param numArgsRead: number of arguments read
@param numArgsNeed: number of arguments needed
@return formatIsGood: true if format is good
*/
bool isValidFormat(const int numArgsRead, const int numArgsNeed);
bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;
  do{
    scanf("%c", &character);
		if(!isspace(character)){
			formatIsGood = false;
		}
	}while(character != '\n');
  return formatIsGood;
}

/*
checks if value is in between two values
@param lowerBound: lower value
@param upperBound: upper value
@return: true if value is between lower and upper value
*/
bool inbetween(int val, int lowerBound, int upperBound){
  return val >= lowerBound && val <= upperBound;
}

/*
gets a valid integer from user
@param lowerBound: lower value to print out
@param upperBound: upper value to print out
@return num: valid integer
*/
int getValidInt(int lowerBound, int upperBound){
  int num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("Enter a column between %d and %d to play in: ", lowerBound, upperBound);
    numArgsRead = scanf(" %d", &num); // waffles 45\n
  }while(!isValidFormat(numArgsRead, numArgsNeeded));

  return num;
}

/*
gets a valid integer between two values from user
@param lowerBound: lower value
@param upperBound: upper value
@return num: valid integer between lower and upper value
*/
int getValidIntInRange(int lowerBound, int upperBound){
  int num;
  do{    
    num = getValidInt(lowerBound, upperBound);
  }while(!(inbetween(num, lowerBound, upperBound)));

  return num;
}

/*
checks if is valid quit/help command
@param numArgsRead: number of arguments
@return: true if valid
*/
bool isValidQuitOrHelp(int numArgsRead) {
  if(isValidFormat(numArgsRead, 1)){
    return true;
  }
  else {
    printf("Wrong command.\n");
    return false;
  }

}
/*
checks if is valid write command
@param numArgsRead: number of arguments
@param start_r: start row
@param start_c: start column
@param end_r: end row
@param end_c: end column
@param rows: number of rows
@param cols: number of columns
@return: true if valid
*/
bool isValidWrite(int numArgsRead, int start_r, int start_c, int end_r, int end_c, int rows, int cols) {
      if(isValidFormat(numArgsRead, 4)) {
        if(inbetween(start_r, 0, rows-1) && inbetween(start_c, 0, cols-1) && inbetween(end_r, 0, rows-1) && inbetween(end_c, 0, cols-1)) {
          return true;
        }
        else {
          printf("Improper draw command.\n");
          return false;
        }
      } 
      else{
        printf("Improper draw command.\n");
        return false;
      }

}
/*
checks if is valid erase command
@param numArgsRead: number of arguments
@param er_row: erase row
@param er_col: erase col
@param rows: number of rows
@param cols: number of columns
@return: true if valid
*/
bool isValidErase(int numArgsRead, int er_row, int er_col, int rows, int cols) {
  if(isValidFormat(numArgsRead, 2)) {
    if(inbetween(er_row, 0, rows-1) && inbetween(er_col, 0, cols-1)) {
      return true;
    }
    else {
      printf("Improper erase command.\n");
      return false;
    }
  }
  else {
    printf("Improper erase command.\n");
    return false;
  }

}

bool isValidAdd(int numArgsRead, char dim, int position, int rows, int cols) {
  if(isValidFormat(numArgsRead, 2)) {
    if(dim == 'r' && inbetween(position, 0, rows)) {
      return true;
    }
    else if (dim == 'c' && inbetween(position, 0, cols)) {
      return true;
    }
    else {
      printf("Improper add command.\n");
      return false;
    }
  } else {
    printf("Improper add command.\n");
    return false;
  }
}

bool isValidDelete(int numArgsRead, char dim, int position, int rows, int cols) {
    if(isValidFormat(numArgsRead, 2)) {
    if(dim == 'r' && inbetween(position, 0, rows-1)) {
      return true;
    }
    else if (dim == 'c' && inbetween(position, 0, cols-1)) {
      return true;
    }
    else {
      printf("Improper delete command.\n");
      return false;
    }
  } else {
    printf("Improper delete command.\n");
    return false;
  }
}

bool isValidResize(int numArgsRead, int rows, int cols) {
  if (isValidFormat(numArgsRead, 2)) {
    if(rows > 0 && cols > 0) {
      return true;
    }
    else {
      printf("Improper resize command.\n");
      return false;
    }
  }
  else {
    printf("Improper resize command.\n");
    return false;
  }
  
}

bool isValidLoadOrSave(char* file_name) {
  if(file_name[0] != '\0') {
    return true;
  }
  else {
    return false;
  }
}
// append and read_any_len_str from class drive
char* append(char val, char* str, int* size){
	(*size)++;
	str = (char*)realloc(str, *size * sizeof(char));
	str[*size - 1] = val;
	return str;
}

char* read_any_len_str() {
	char cur_char;
	char* str = NULL;
	int cur_size = 0;

	do{
		scanf("%c", &cur_char);
	}while(isspace(cur_char));

	do{
		str = append(cur_char, str, &cur_size);
		scanf("%c", &cur_char);
	}while(!isspace(cur_char));

	//add the null character
	str = append('\0', str, &cur_size);

	return str;
}

/*

bool isValidCommand(char* command, int rows, int columns) {
    char letter;
    char dimension;
    //char* file_name;
    int num_args_read;
    int arg1;
    int arg2;
    int arg3;
    int arg4;

    sscanf(command, " %c", &letter);
    if(letter == 'w') {
       num_args_read = sscanf(command, " %d %d %d %d", &arg1, &arg2, &arg3, &arg4);
       return isValidWrite(num_args_read, arg1, arg2, arg3, arg4, rows, columns);
    }
    else if (letter == 'q' || letter == 'h') {
      num_args_read = sscanf(command, " %d", &arg1);
      return isValidQuitOrHelp(num_args_read);
    }
    else if (letter == 'e') {
      num_args_read = sscanf(command, " %d %d", &arg1, &arg2);
      return isValidErase(num_args_read, arg1, arg2, rows, columns);
    }
    else if (letter == 'a') {
      num_args_read = sscanf(command, " %c %d", &dimension, &arg1);
      return isValidAdd(num_args_read, dimension, arg1, rows, columns);
    }
    else if (letter == 'd') {
      num_args_read = sscanf(command, " %c %d", &dimension, &arg1);
      return isValidDelete(num_args_read, dimension, arg1, rows, columns);
    } else {
    return false;
    }
}

char* getValidCommand(int rows, int columns) {
  char* command;
  do {
    command = getCommand();
  } while(!isValidCommand(command, rows, columns));

  return command;

}
*/
void getValidCommand(int rows, int columns, char** file_name, char* letter, char* dimension, int* arg1, int*arg2, int* arg3, int* arg4) {

  bool isValid;
  int num_args_read;

  do {
    printf("Enter your command:");

    num_args_read = scanf(" %c", letter);

    if(*letter == 'w') {
       num_args_read = scanf(" %d %d %d %d", arg1, arg2, arg3, arg4);
       isValid = isValidWrite(num_args_read, *arg1, *arg2, *arg3, *arg4, rows, columns);
       return;
    }
    else if (*letter == 'q' || *letter == 'h') {
      isValid = isValidQuitOrHelp(num_args_read);
    }
    else if (*letter == 'e') {
      num_args_read = scanf(" %d %d", arg1, arg2);
      isValid = isValidErase(num_args_read, *arg1, *arg2, rows, columns);
    }
    else if (*letter == 'a') {
      num_args_read = scanf(" %c %d", dimension, arg1);
      isValid = isValidAdd(num_args_read, *dimension, *arg1, rows, columns);
    }
    else if (*letter == 'd') {
      num_args_read = scanf(" %c %d", dimension, arg1);
      isValid = isValidDelete(num_args_read, *dimension, *arg1, rows, columns);
    } else if (*letter == 'r') {
      num_args_read = scanf(" %d %d", arg1, arg2);
      isValid = isValidResize(num_args_read, *arg1, *arg2);
    }
    else if (*letter == 'l') {
      (*file_name) = read_any_len_str();

      isValid = isValidLoadOrSave(*file_name);

    } else if (*letter == 's') {
      (*file_name) = read_any_len_str();        

      isValid = isValidLoadOrSave(*file_name);

    }
     else {
      
      isValid = false;
      printf("Invalid command.\n");
    }    
  } while(!isValid);


}

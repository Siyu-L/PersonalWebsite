#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

bool isValidFormat(const int numArgsRead, const int numArgsNeed);
bool inbetween(int val, int lowerBound, int upperBound);
int getValidInt(int lowerBound, int upperBound);
int getValidIntInRange(int lowerBound, int upperBound);
bool isValidQuitOrHelp(int numArgsRead);
bool isValidWrite(int numArgsRead, int start_r, int start_c, int end_r, int end_c, int rows, int cols);
bool isValidErase(int numArgsRead, int er_row, int er_col, int rows, int cols);
bool isValidAdd(int numArgsRead, char dim, int position, int rows, int cols);
bool isValidDelete(int numArgsRead, char dim, int position, int rows, int cols);
bool isValidLoadOrSave(char* file_name);
char* append(char val, char* str, int* size);
char* read_any_len_str();
void getValidCommand(int rows, int columns, char** file_name, char* letter, char* dimension, int* arg1, int*arg2, int* arg3, int* arg4);

#endif
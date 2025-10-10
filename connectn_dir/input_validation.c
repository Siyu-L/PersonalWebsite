
#include <stdio.h>
#include <stdbool.h>
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
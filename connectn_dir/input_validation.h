#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

bool isValidFormat(const int numArgsRead, const int numArgsNeed);
bool inbetween(int val, int lowerBound, int upperBound);
int getValidInt(int lowerBound, int upperBound);
int getValidIntInRange(int lowerBound, int upperBound);

#endif
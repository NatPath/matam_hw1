#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_
#include <stdbool.h>

//gets a string , returns an int
int stringToInt(char* string);

//gets an int, returns a string
char* intToString(int num);

bool lowerCaseAndSpacesOnly(char* string);


#endif
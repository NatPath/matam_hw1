#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_
#include <stdbool.h>

/**
 * Utilities function for handeling string 
 * */

/**
 * stringToInt: get a string of a number, returns it as an int
 * @param string - The string to convert
 * @return 
 *      An integer representing the number in the string
 * */
int stringToInt(char* string);

//gets an int, returns a string
/** intToString: get an integer, returns in as a string
 * @param num - the number to convert
 * @return
 *      A string representing the number
 * */
char* intToString(int num);

/**
 * lowerCaseAndSpacesOnly: checks if a string has only lower case letters and spaces
 * @param string - the string to check
 * @return 
 *      Wether the condition are met
 * */
bool lowerCaseAndSpacesOnly(const char* string);

/**
 * initializeAndCopy: Make a copy of a string, without the const, taking care of memory allocation.
 * @param destination- The pointer to allocat memory and copy the string into
 * @param source- The string to copy
 * @return
 *      returns the string of allocation went well,
 *      if failed, return NULL
 * */
char* initializeAndCopy(char* destination, const char* source);
#endif
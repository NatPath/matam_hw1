#include "string_utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SMALL_Z 122
#define SMALL_A 97
#define SPACE_ASCI 32
#define SMALL_LETTERS_ASCI(letter) ((int)letter>=SMALL_A&&(int)letter<=SMALL_Z)

static int numOfDigits(int num){
    if(num == 0){
        // 0 still has one digit, although we would not count it normally
        return 1;
    }
    int i=0;
    while(num){
        i++;
        num=num/10;
    }
    return i;
}
int stringToInt(char* string){
    if(!string){
        return 0;
    }
    return atoi(string);
}

char* intToString(int num){
    int num_size=numOfDigits(num);
    char *res=malloc(sizeof(char)*num_size+1);
    sprintf(res,"%d",num);
    return res;
}

bool lowerCaseAndSpacesOnly(const char* string){
    while(*string){
        if(!SMALL_LETTERS_ASCI(*string)&&!((int)*string==SPACE_ASCI)){
            return false;
        }
        string++;
    }
    return true;
}

char* initializeAndCopy(char* destination, const char* source){
    destination = malloc(strlen(source)+1);
    if(!destination){
        return NULL;
    }
    strcpy(destination,source);
    return destination;
}

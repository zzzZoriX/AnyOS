#include "stdstr.h"

int compare(char* str1, char* str2){
    while(*str1 && *str2 && *str1 == *str2){
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

int ncompare(char* str1, char* str2, int count){
    if(count == 0) return 0;
    
    while(count-- > 0 && *str1 && *str2 && *str1 == *str2){
        str1++;
        str2++;
    }
    
    if (count == (unsigned int)-1)
        return 0;
    else
        return (unsigned char)*str1 - (unsigned char)*str2;
}
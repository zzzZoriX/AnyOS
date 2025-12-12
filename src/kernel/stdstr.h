#ifndef ANYSTDSTR
#define ANYSTDSTR

#define GET_STR_LENGTH(sptr, msg)\
    for(char* ptr = (msg); *ptr != '\0'; ++ptr, ++(sptr));

int compare(char* str1, char* str2);
int ncompare(char* str1, char* str2, int count);

#endif // ANYSTDSTR
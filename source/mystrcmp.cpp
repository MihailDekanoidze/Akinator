#include <stdio.h>

int mystrcmp(const void * str1, const void * str2)
{
    char* ptr1 = (char*) str1;
    char* ptr2 = (char*) str2;
    int i = 0;
    while ((ptr1[i] != '\0') && (ptr2[i] != '\0') && (ptr1[i] == ptr2[i]))
    {
        i++;
    }
    return i;
}

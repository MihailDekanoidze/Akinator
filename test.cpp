#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "Akinator.h"
//#include "./include/InputText.h"


#define START_NODE  "неизвестно кто"  



void fprint_nchar(FILE* dest, char symbol, size_t count)
{
    for (size_t i = 0; i < count; i++) {fprintf(dest, "%c", symbol);}
}

int main()
{
    
    printf("%*s\n",12,  "a");
    return 0;
}


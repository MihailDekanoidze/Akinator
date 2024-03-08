#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Akinator.h"


#define START_NODE  "неизвестно кто"  



void print_nodes(Node* curr_node)
{
    if (curr_node != NULL)
    {
        printf("\nnode_val = %s\n", curr_node->val);
        if(curr_node->left != NULL) printf("node_left  = %s\n", curr_node->left->val);
        if(curr_node->right != NULL)printf("node_right  = %s\n\n", curr_node->right->val);
        print_nodes(curr_node->left);
        print_nodes(curr_node->right);
    }
}

int main()
{
    printf("Русский язык поддерживается!\n");


    Node* start_node = (Node*)calloc(1, sizeof(Node));
    start_node->left = NULL;
    start_node->right = NULL;
    memcpy(start_node->val, START_NODE, BASE_NODE_COUNT);

    print_nodes(start_node);

    print_nodes(start_node);

    unsigned char* string = (unsigned char*)calloc(STR_LEN, sizeof(unsigned char));

    str_print(string);
    printf("\n");

    string = str_scanf();

    str_print(string);
    printf("\n");

    return 0;
}

void str_print(unsigned char* source)
{
    size_t i = 0;
    while (source[i])
    {
        printf("%c", source[i++]);
    }

    for (i = 0; i < STR_LEN; i++)
    {
        printf("source[%zu] = %c(%d)\n", i, source[i], source[i]);
    }
}


unsigned char* str_scanf(void)
{
    unsigned char* new_object = (unsigned char*)calloc(STR_LEN, sizeof(unsigned char));

    size_t i = 0;
    size_t max_len = STR_LEN;
    
    //unsigned char first = (unsigned char)getchar();
    do
    {
        if (i == max_len - 1)
        {    
            printf("max len\n");
            new_object = (unsigned char*)realloc(new_object, max_len * 2);
            max_len *= 2;
        }
        new_object[i++] = (unsigned char)getchar();
    }
    while (new_object[i - 1] != '\n');

    //printf("first = %c(%d)\n", first, first);
    //new_object[0] = first;
    printf("new_object[i - 1] = %c(%d)\n", new_object[i - 1], new_object[i - 1]);
    new_object[i - 1] = '\0';

    i = 0;
    unsigned char* source = new_object;
    while (source[i])
    {
        printf("%c", source[i++]);
    }

    printf("\n");
    for (i = 0; i < STR_LEN; i++)
    {
        printf("source[%zu] = %c(%d)\n", i, source[i], source[i]);
    }

    str_print(new_object);

    return new_object;
}
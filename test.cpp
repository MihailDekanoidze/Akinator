#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Akinator.h"
#include "./include/InputText.h"


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

    FILE* data =  fopen("tree.txt", "rb");

    TextInfo* buffer = (TextInfo*) calloc(1, sizeof(TextInfo));
    InputText(buffer, data); 

    fclose(data);

    Tree* akinator_tree = tree_create(BASE_NODE_COUNT);

    akinator_tree_read((char*)(buffer->buffer), akinator_tree);

    tree_print(akinator_tree->root, fopen("tree_log.cpp", "w"));

    for (size_t i = 0; i < akinator_tree->node_count; i++)
    {
        printf("Node[%zu] = %s\n", i, (akinator_tree->root + i)->val);
    }

    tree_detor(akinator_tree);

    return 0;
}

Node* akinator_tree_read(char* source, Tree* akinator_tree)
{
    if (*source == '{')
    {
        printf("current symbol is {\n");

        if (source[1] == '}') 
        {
            printf("processed symbol is }\n");
            return NULL;
        }

        printf("creating a new_node\n");

        unsigned char* arg = arg_scanf(source);
        printf("arg is %s\n", arg);  

        Node* new_node = akinator_tree->root + (akinator_tree->node_count++);

        memcpy(new_node->val, (char*)arg, sizeof(char) * STR_LEN);
        new_node->left  = akinator_tree_read(source, akinator_tree);
        new_node->right = akinator_tree_read(source, akinator_tree);

        return new_node;
    }
}

// regular expression 

unsigned char* arg_scanf(char* source)
{
    unsigned char* arg = (unsigned char*)calloc(STR_LEN, rus_char_size);

    size_t i = 0;

    source = skip_spaces(source);

    if (*source == '"')
    {
        i++;
        while (*(source++) != '"')
        {
            arg[i] = *source;
        }
        return arg;
    }

    return nullptr;
}

char* skip_spaces(char* source)
{
    size_t i = 0;
    while (*(source++) == ' ');
    return source;
}
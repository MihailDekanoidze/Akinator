#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>

#define BASE_NODE_COUNT 100
#define INCREASE_COEF   2     
#define STR_LEN 100


static const char START_NODE[BASE_NODE_COUNT] =  "неизвестно кто";  

typedef unsigned char Data;

struct Node {
        Data val[STR_LEN];
        Node* left;
        Node* right;
        Node* previous;
};

typedef struct Node Node;

struct Tree {
        Node* root;
        size_t node_count;
        size_t capacity;
        FILE* tree_log;
};


#define TREE_CALLOC_ERROR  NULL;
const unsigned long int TREE_OPEN_FILE = NULL;
 






typedef struct Node Node;

Tree* tree_create(size_t node_count);
void node_insert(Tree* tree, Data val);
Node* node_search(Tree* tree, Data val);
void tree_print(Node* tree, FILE* tree_log);
void tree_increase_capasity(Tree* tree);
void tree_detor(Tree* tree);

Node* object_search(Tree* main_tree);
void akinator_playing(Tree* main_tree);
int is_continue(Tree* main_tree);
void object_add(Node* old_object, const char* new_object, const char* feature, Tree* main);
unsigned char* str_scanf(void);
void str_print(unsigned char* source);
void object_processing(Node* curr_node, Tree* main_tree);
size_t question(Node* curr_node);
void node_list_print(Tree* main_tree);

#endif // AKINATOR_H

#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>

#define BASE_NODE_COUNT 100
#define INCREASE_COEF   2     
#define STR_LEN         100

static const unsigned char ru_yes[] = "да";
static const unsigned char ru_Yes[] = "Да";
static const size_t rus_char_size = sizeof('ф'); 

static const char START_NODE[STR_LEN] = "неизвестно кто";  

typedef unsigned char Data;

typedef struct Node {
    Data val[STR_LEN * rus_char_size];              //calloc / extern storage
    Node* left;
    Node* right;
    Node* previous;
} Node;

struct Tree {
    Node* node_list;             //rename
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
void tree_print(Node* tree, FILE* tree_log, size_t* level);
void tree_increase_capasity(Tree* tree);
void tree_detor(Tree* tree);

Node* object_search(Tree* main_tree);
void akinator_playing(Tree* main_tree);
int is_continue(Tree* main_tree);
void object_add(Node* old_object, const char* new_object, const char* feature, Tree* main);
unsigned char* str_scanf(void);
void object_processing(Node* curr_node, Tree* main_tree);
size_t question(Node* curr_node);
void node_list_print(Tree* main_tree);
int negative_feature(unsigned char* feature);
Node* akinator_tree_read(char* source, Tree* akinator_tree, size_t* pos);
unsigned char* arg_scanf(char* source, size_t* pos);
void skip_spaces(char* source, size_t* pos);
void ClearBuffer(void);
Tree* akinator_upload_tree(FILE* data);
void akinator_end(Tree* akinator_tree, FILE* data);
void fprint_nchar(FILE* dest, char symbol, size_t count);

#endif // AKINATOR_H

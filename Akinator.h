#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include <assert.h>

#define BASE_NODE_COUNT 100
#define TREE_NODE_INCREASE_COEF   20     
#define STR_LEN         100
#define OBJECT_FOUND    1 << 7
#define OBJECT_N_FOUND  1 << 8
#define RUS_CHAR_SIZE   sizeof('ф')

static const unsigned char ru_yes[] = "да";
static const unsigned char ru_Yes[] = "Да";


static const char START_NODE[STR_LEN] = "неизвестно кто";  

typedef unsigned char Data;

#define FOPEN(file_name, mode) fopen(file_name, mode); /*fprintf(stderr, "open: %s on line: %d %s\n", #file_name, __LINE__, __PRETTY_FUNCTION__);*/ 
#define FCLOSE(file_name) int FUCK_MY_ASS_CHECK = fclose(file_name); /*fprintf(stderr, "close: %s  on line: %d %s\n", #file_name, __LINE__, __PRETTY_FUNCTION__);*/ \
    if (FUCK_MY_ASS_CHECK != 0) {fprintf(stderr, "meow!!\n");}

enum child
{
    left  = 1,
    right = 2
};


typedef struct Node {
    Data val[STR_LEN * RUS_CHAR_SIZE];              //calloc / extern storage
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
//const unsigned long int TREE_OPEN_FILE = NULL;
 

typedef struct Node Node;

Tree*               tree_create(size_t node_count);
void                node_insert(Tree* tree, Data val);
Node*               node_search(Tree* tree, Data val);
void                tree_print(Node* tree, FILE* tree_log, size_t* level);
void                tree_increase_capasity(Tree* tree);
void                tree_detor(Tree* tree);

Node*               object_guess(Tree* main_tree);
void                akinator_playing(Tree* main_tree);
int                 is_continue(Tree* main_tree);
void                object_add(Node* old_object, const char* new_object, const char* feature, Tree* main);
unsigned char*      str_scanf(void);
void                object_processing(Node* curr_node, Tree* main_tree);
size_t              question(Node* curr_node);
void                node_list_print(Tree* main_tree);
int                 negative_feature(unsigned char* feature);
Node*               akinator_tree_read(char* source, Tree* akinator_tree, size_t* pos);
unsigned char*      arg_scanf(char* source, size_t* pos);
void                skip_spaces(char* source, size_t* pos);
void                ClearBuffer(void);
Tree*               akinator_upload_tree(FILE* data);
void                akinator_end(Tree* akinator_tree);
void                fprint_nchar(FILE* dest, char symbol, size_t count);
Node*               tree_add_node(Node* parent, child subtree, const char* val, Tree* curr_tree);


int                 menu(void);
int                 way_search(Node* curr_node, const char* val, struct Stack* way_to_obj);
void                difinition_print(Tree* tree, struct Stack* way_to_obj, size_t start_pos, size_t end_pos);
void                object_search(Tree* tree);
void                object_compare(Tree* akinator_tree);
void                game_mod_playing(Tree* akinator_tree);
struct Stack*       way_stack(Tree* tree, char* val);

#endif // AKINATOR_H

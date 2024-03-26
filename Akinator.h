#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include <assert.h>
#include "./include/Tree.h"

static const unsigned char ru_yes[] = "да";
static const unsigned char ru_Yes[] = "Да";

enum Options
{
    Object_guess    = 1,
    Object_search   = 2,
    Objects_compare = 3,
    Exit            = 4
};

Node*               object_guess(Tree* main_tree);
void                akinator_playing(Tree* main_tree);
int                 is_continue(Tree* main_tree);
void                object_add(Node* old_object, const char* new_object, const char* feature, Tree* main);
unsigned char*      str_scanf(void);
void                object_processing(Node* curr_node, Tree* main_tree);
size_t              question(Node* curr_node);
int                 negative_feature(unsigned char* feature);
Node*               akinator_tree_read(char* source, Tree* akinator_tree, size_t* pos);
unsigned char*      arg_scanf(char* source, size_t* pos);
Tree*               akinator_upload_tree(const char*);
void                akinator_end(Tree* akinator_tree);


int                 menu(void);
void                difinition_print(Tree* tree, struct Stack* way_to_obj, size_t start_pos, size_t end_pos);
void                object_search(Tree* tree);
void                object_compare(Tree* akinator_tree);
void                game_mod_playing(Tree* akinator_tree);

#endif // AKINATOR_H

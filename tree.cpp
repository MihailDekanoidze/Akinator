#include <stdio.h>
#include <stdlib.h>

#include "Akinator.h"

Tree* tree_create(size_t node_count)
{
    Tree* tree = (Tree*)calloc(1, sizeof(Tree));

    if (!tree)
        return TREE_CALLOC_ERROR;
    
    Node* root = (Node*) calloc(node_count, sizeof(Node));

    if (!root)
        return TREE_CALLOC_ERROR;

    tree->root = root;

    tree->capacity = node_count;
    tree->root->val  = START_ROOT;
    tree->root->left = NULL;
    tree->root->right = NULL;
    tree->root->previous = NULL;

    tree->node_count++;

    FILE* tree_log = fopen("tree_log.cpp", "a+");
    
    /*if (!tree_log)
        return TREE_OPEN_FILE;*/

    tree->tree_log = tree_log;
    
    return tree;
}


void node_insert(Tree* tree, Data val)
{
    if (tree->node_count == tree->capacity)
        tree_increase_capasity(tree);

    Node* new_node = tree->root + tree->node_count;
    new_node->val = val;

    Node* curr_node = tree->root;

    while (true)
    {
        printf("Is it %s?\n", curr_node->val);

        char answer[50] = {};
        scanf("%s", answer);

        if (curr_node->val > val)
        {
            printf("%d > %d\n", curr_node->val, val);

            if (curr_node->left == NULL)
            {
                curr_node->left = new_node;
                break;
            }
            else
            {
                curr_node = curr_node->left;
            }
        }
        else
        {
            printf("%d < %d\n", curr_node->val, val);

            if (curr_node->right == NULL)
            {
                curr_node->right = new_node;
                break;
            }
            else
            {
                curr_node = curr_node->right;
            }
        }
    }

    tree->node_count++;

    printf("added elem = %d\n", val);
    printf("curr_node = %d\n\n", curr_node->val);

    return;
}

Node* node_search(Tree* tree, Data val)
{
    Node* node_found = NULL;

    Node* curr_node = tree->root;

    while (curr_node != NULL)
    {
        if (curr_node->val > val)
            curr_node = curr_node->left;
        else if (curr_node->val < val)
            curr_node = curr_node->right;
        else 
        {
            node_found = curr_node;
            break;
        }
    }

    return node_found; 
}


void tree_print(Node* tree, FILE* tree_log)
{
    if (tree != NULL)
    {
        fprintf(tree_log, "{%d\n", tree->val);
        tree_print(tree->left, tree_log);
        tree_print(tree->right, tree_log);
        fprintf(tree_log, "}\n");
    }
}

void tree_detor(Tree* tree)
{
    free(tree->root);
    
    fclose(tree->tree_log);

    tree->capacity = 0;
    tree->node_count = 0;

    free(tree);
}


void node_delete(Tree* tree, Data val)
{
    if (!node_search(tree, val))
    {
        return;
    }
    else
    {
        
    }
}



void tree_increase_capasity(Tree* tree)
{
    tree->root = (Node*)realloc(tree->root, sizeof(Node) * tree->capacity * INCREASE_COEF);
    tree->capacity *= 2;

    return;
}

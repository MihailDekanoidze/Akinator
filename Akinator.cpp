#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include "Akinator.h"
#include "./includes/others.h"

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
    memcpy(tree->root, START_NODE, BASE_NODE_COUNT);
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



Node* object_search(Tree* main_tree)
{
    Node* curr_node = main_tree->root;
    tree_print(main_tree->root, main_tree->tree_log);

    while (curr_node->left != NULL)
    {
        size_t answer = question(curr_node);

        if (answer)
        {
            curr_node = curr_node->left;
        }
        else
        {
            curr_node = curr_node->right;
        }

        printf("object_seached = %s\n", curr_node->val);
    }

    return curr_node;
}

size_t question(Node* curr_node)
{
    printf("Это существо ");

    size_t i = 0;
    while (curr_node->val[i])
    {
        printf("%c", curr_node->val[i++]);
    }

    printf(" ?\nДа / Нет\n");

    char answer[50] = {};
    scanf("%s", answer);

    return mystrcmp(answer, "Нет");
}

void object_processing(Node* curr_node, Tree* main_tree)
{
    size_t answer = question(curr_node);

    if (answer)
    {
        printf("Я это знал!\n");
    }
    else
    {
        printf("Вы перехитрили меня!\n");
        printf("Тогда кто же это ?\n");
        printf("\r");

        unsigned char* new_object = 0;
        new_object = str_scanf();

        printf("new_obj = ");
        str_print(new_object);
        printf("\n");

        printf("Чем ");
        str_print(new_object);
        printf(" отличается от ");
        str_print(curr_node->val);
        printf("?\n");
    
        unsigned char* feature = str_scanf();

        printf("feature is ");
        str_print(feature);
        printf("\n");

        object_add(curr_node, (const char*)new_object, (const char*)feature, main_tree);

        free(new_object);
        free(feature);
        printf("Я запомнил это...\n");
    }
}


void str_print(unsigned char* source)
{
    size_t i = 0;
    while (source[i])
    {
        printf("%c", source[i++]);
    }
}



unsigned char* str_scanf(void)
{
    unsigned char* new_object = (unsigned char*)calloc(STR_LEN, sizeof(unsigned char));

    size_t i = 0;
    size_t max_len = STR_LEN;
    
    unsigned char first = (unsigned char)getchar();
    do
    {
        if (i == max_len - 1)
        {    
            printf("max len\n");
            new_object = (unsigned char*)realloc(new_object, max_len * 2);
            max_len *= 2;
        }
        if (first != '\n')  
        {
            new_object[i++] = first;
            first = '\n';
        }
        new_object[i++] = (unsigned char)getchar();
        //printf("%c(%d)\n", new_object[i - 1], new_object[i - 1]);
    }
    while (new_object[i - 1] != '\n');

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

void object_add(Node* old_node, const char* new_object, const char* feature, Tree* main_tree)
{
    printf("old_node = ");
    str_print(old_node->val);
    printf("\n");

    /*if (main_tree->node_count == main_tree->capacity)
        tree_increase_capasity(main_tree);*/

    Node* new_node = &(main_tree->root)[main_tree->node_count++];

    new_node->left  = NULL;
    new_node->right = NULL;
    new_node->previous = old_node;
    memcpy(new_node->val, new_object, STR_LEN);

    /*if (main_tree->node_count == main_tree->capacity)
        tree_increase_capasity(main_tree);*/

    Node* old_object = &(main_tree->root)[main_tree->node_count++];

    old_object->left  = NULL;
    old_object->right = NULL;
    old_object->previous = old_node;
    memcpy(old_object->val, old_node->val, STR_LEN);

    //printf("tree capacity = %zu\n", main_tree->capacity);
    //printf("tree_node_count = %zu\n", main_tree->node_count);

    Node* feature_node = old_node;

    old_node->left  = new_node;
    old_node->right = old_object;
    memcpy(old_node->val, feature, STR_LEN);

    printf("old_node = %s\n", old_node->val);
    str_print(old_node->val);

    str_print(feature_node->left->val);
    printf(" отличается от ");
    str_print(feature_node->right->val); 
    printf(" тем, что ");
    str_print(feature_node->val);
    printf("\n");

    node_list_print(main_tree);

    return;
}

int is_continue(Tree* main_tree)
{
    tree_print(main_tree->root, main_tree->tree_log);
    node_list_print(main_tree);

    printf("Желаете продолжить ? (Да / Нет)\n");

    char* answer = (char*) calloc(STR_LEN, sizeof(char));
    scanf("%s", answer);

    tree_print(main_tree->root, main_tree->tree_log);
    node_list_print(main_tree);

    if (mystrcmp(answer, "Да"))
    {   
        free(answer);
        tree_detor(main_tree);
        printf("Буду ждать вас снова здесь\n");
        return 0;
    }
    free(answer);
    
    return 1;
}


void akinator_playing(Tree* main_tree)
{
    int continue_flag = 1;
    while (continue_flag)
    {
        Node* found_object = object_search(main_tree);
        object_processing(found_object, main_tree);
        continue_flag = is_continue(main_tree);
    }
}


void tree_increase_capasity(Tree* tree)
{
    printf("increase capacity!\n");
    printf("old capacity = %zu\n", tree->capacity);

    tree->root = (Node*)realloc(tree->root, sizeof(Node) * tree->capacity * INCREASE_COEF);
    tree->capacity *= 2;

    printf("new capacity = %zu\n", tree->capacity);

    return;
}

void tree_detor(Tree* tree)
{
    free(tree->root);
    
    fclose(tree->tree_log);

    tree->capacity = 0;
    tree->node_count = 0;

    free(tree);
}

void tree_print(Node* tree, FILE* tree_log)
{
    //printf("tree_print\n");
    //printf("tree is NULL = %d\n", tree == NULL);

    if (tree != NULL)
    {
        printf("{%s\n", tree->val);
        tree_print(tree->left, tree_log);
        tree_print(tree->right, tree_log);
        printf("}\n");
    }
}

void node_list_print(Tree* main_tree)
{
    for (size_t i = 0; i < main_tree->node_count; i++)
    {
        printf("\nnode[%zu] = %s\n", i, (main_tree->root + i)->val);
    }
}

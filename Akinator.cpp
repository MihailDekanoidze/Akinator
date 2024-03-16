#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Akinator.h"
#include "./include/others.h"

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
    tree->root->left = NULL;
    tree->root->right = NULL;
    tree->root->previous = NULL;

    FILE* tree_log = fopen("tree_log.cpp", "a+");
    
    /*if (!tree_log)
        return TREE_OPEN_FILE;*/

    tree->tree_log = tree_log;
    
    return tree;
}



Node* object_search(Tree* akinator_tree)                    
{
    Node* curr_node = akinator_tree->root;
    tree_print(akinator_tree->root, akinator_tree->tree_log);

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
    printf("��� �������� ");

    size_t i = 0;
    while (curr_node->val[i])
    {
        printf("%c", curr_node->val[i++]);
    }

    printf(" ?\n�� / ���\n");

    char answer[50] = {};
    scanf("%s", answer);

    return strncmp(answer, "���", sizeof(STR_LEN));
}

void object_processing(Node* curr_node, Tree* akinator_tree)
{
    size_t answer = question(curr_node);

    if (answer)
    {
        printf("� ��� ����!\n");
        return; 
    }

    printf("�� ����������� ����!\n");
    printf("����� ��� �� ��� ?\n");

    unsigned char* new_object = str_scanf();

    printf("��� %s ���������� �� %s?\n", new_object, curr_node->val);

    unsigned char* feature = str_scanf();
    printf("negative_feature(feature) = %d\n", negative_feature(feature));

    while (negative_feature(feature))
    {
        printf("��������� ���� ������� � ������������� �����\n");
        feature = str_scanf();
    }

    object_add(curr_node, (const char*)new_object, (const char*)feature, akinator_tree);

    free(new_object);
    free(feature);
    printf("� �������� ���...\n");
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
            new_object = (unsigned char*)realloc(new_object, max_len * 2);
            max_len *= 2;
        }
        if (first != '\n')  
        {
            new_object[i++] = first;
            first = '\n';
        }
        new_object[i++] = (unsigned char)getchar();
    }
    while (new_object[i - 1] != '\n');

    new_object[i - 1] = '\0';

    return new_object;
}


void object_add(Node* old_node, const char* new_object, const char* feature, Tree* akinator_tree)
{           // akinator without tree
    printf("old_node = %s\n", old_node->val);

    /*if (akinator_tree->node_count == akinator_tree->capacity)
        tree_increase_capasity(akinator_tree);*/

    Node* new_node = &(akinator_tree->root)[akinator_tree->node_count++];

    new_node->left  = NULL;
    new_node->right = NULL;
    new_node->previous = old_node;
    memcpy(new_node->val, new_object, STR_LEN);

    /*if (akinator_tree->node_count == akinator_tree->capacity)
        tree_increase_capasity(akinator_tree);*/

    Node* old_object = &(akinator_tree->root)[akinator_tree->node_count++];

    old_object->left  = NULL;
    old_object->right = NULL;
    old_object->previous = old_node;
    memcpy(old_object->val, old_node->val, STR_LEN);

    //printf("tree capacity = %zu\n", akinator_tree->capacity);
    //printf("tree_node_count = %zu\n", akinator_tree->node_count);

    Node* feature_node = old_node;

    old_node->left  = new_node;
    old_node->right = old_object;
    memcpy(old_node->val, feature, STR_LEN);

    printf("old_node = %s\n", old_node->val);

    printf("feature_node->left->val = %s\n", feature_node->left->val);
    printf(" ���������� �� ");
    printf("feature_node->right->val =%s\n", feature_node->right->val); 
    printf(" ���, ��� ");
    printf("feature_node->val = %s\n", feature_node->val);
    printf("\n");

    node_list_print(akinator_tree);

    return;
}

int is_continue(Tree* akinator_tree)
{
    tree_print(akinator_tree->root, akinator_tree->tree_log);
    node_list_print(akinator_tree);

    printf("������� ���������� ? (�� / ���)\n");

    char* answer = (char*) calloc(STR_LEN, sizeof(char));
    scanf("%s", answer);

    tree_print(akinator_tree->root, akinator_tree->tree_log);
    node_list_print(akinator_tree);

    if (strncmp(answer, "��", STR_LEN))
    {   
        free(answer);
        tree_detor(akinator_tree);
        printf("���� ����� ��� ����� �����\n");
        return 0;
    }
    free(answer);
    
    return 1;
}


void akinator_playing(Tree* akinator_tree)
{
    int continue_flag = 1;
    while (continue_flag)
    {
        Node* found_object = object_search(akinator_tree);
        object_processing(found_object, akinator_tree);
        continue_flag = is_continue(akinator_tree);
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

void node_list_print(Tree* tree)
{
    for (size_t i = 0; i < tree->node_count; i++)
    {
        printf("\nnode[%zu] = %s\n", i, (tree->root + i)->val);
    }
}

int negative_feature(unsigned char* feature)
{
    unsigned char ru_not[] = "��";
    unsigned char ru_Not[] = "��";
    unsigned char cmp_symbols[] = {feature[0], feature[1], feature[2], feature[3], '\0'};

    //printf("cmp_symbols = %s\n", cmp_symbols);

    return !((strncmp((char*)ru_not, (char*)feature, sizeof(ru_not))) 
           || strncmp((char*)ru_Not, (char*)feature, sizeof(ru_not)));
}


Node* akinator_tree_read(char* source, Tree* akinator_tree, size_t* pos)
{
    if (*(source + *(pos)) == '{')
    {
        /*printf("current symbol is %c\n", *source);
        printf("Increase pos\n");
        char pause = getchar();
        ClearBuffer();*/

        (*pos)++;

        //printf("current symbol is %c\n", *(source + *pos));

        if (source[*pos] == '}') 
        {
            //printf("processed symbol is }\n");
            (*pos)++;
            return NULL;
        }

        //printf("\ncreating a new_node\n");

        unsigned char* arg = arg_scanf(source, pos);
        //printf("arg is %s\n", arg);  

        Node* new_node = akinator_tree->root + (akinator_tree->node_count++);

        memcpy(new_node->val, (char*)arg, sizeof(char) * STR_LEN);
        free(arg);

        //printf("source = %s\n", source + *(pos));

        new_node->left  = akinator_tree_read(source, akinator_tree, pos);
        (*pos)++;

        /*printf("the left node for %s is %s\n\n", new_node->val, new_node->left->val);

        printf("source after left = %s\n", source + *(pos));
        printf("the next symbol after left is %c\n", *(source +*pos));*/

        new_node->right = akinator_tree_read(source, akinator_tree, pos);
        
        /*printf("the right node for %s is %s\n\n", new_node->val, new_node->right->val);
        
        printf("source after right = %s\n", source + *(pos));
        printf("the next symbol after right is %c\n\n", *(source +*pos));*/

        return new_node;
    }
    else
    {
        /*printf("\nthe symbol different from '{' is '%c'\n", *(source + *pos));
        printf("Increase pos from %zu to %zu\n", *pos, *(pos) + 1);

        char pause = getchar();
        ClearBuffer();*/

        (*pos)++;

        /*printf("pos = %zu\nbuffer[%zu] = %c(%d)\n", *pos, *pos, *(source + (*pos)));

        printf("current symbol is %c(%d)\n", *(source + (*pos)), *(source + (*pos)));*/
    }

    return nullptr;
}

// regular expression 

unsigned char* arg_scanf(char* source, size_t* pos)
{
    unsigned char* arg = (unsigned char*)calloc(STR_LEN, rus_char_size);

    size_t i = 0;

    skip_spaces(source, pos);
    /*printf("source = %s\n", source + *pos);

    printf("symbol = %c\n", (unsigned char) (*(source + *pos)));*/

    if (*(source + (*pos)) == 34)
    {
        (*pos)++;
        while (*(source + *(pos)) != '"')
        {
            arg[i] = *(source + *pos);
            i++; (*pos)++;
        }
        (*pos)++;

        //printf("in arg source = %s\n", source + *(pos));
        return arg;
    }

    free(arg);
    return nullptr;
}

void skip_spaces(char* source, size_t* pos)
{
    size_t i = 0;
    while (*(source + *pos) == ' ');
    return;
}

void ClearBuffer(void)
{
    char ch = 0;

    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

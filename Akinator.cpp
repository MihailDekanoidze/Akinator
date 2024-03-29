#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "Akinator.h"
#include "./include/Tree.h"
#include "./include/others.h"
#include "./include/InputText.h"
#include "./include/Stack.h"



Tree* akinator_upload_tree(const char* file_name)
{
    FILE* data = FOPEN(file_name, "rb");

    TextInfo* input_buffer = (TextInfo*)calloc(1, sizeof(TextInfo));
    InputText(input_buffer, data);

    FCLOSE(data);

    Tree* akinator_tree = tree_create(BASE_NODE_COUNT);
    size_t pos = 0; 

    akinator_tree_read((char*)(input_buffer->buffer), akinator_tree, &pos);
    
    TextInfoDtor(input_buffer);

    size_t level = 0;

    tree_print(akinator_tree->node_list, akinator_tree->tree_log, &level);

    return akinator_tree;
}

Node* object_guess(Tree* akinator_tree)                    
{
    Node* curr_node = akinator_tree->node_list;

    TREE_PRINT(akinator_tree->node_list, akinator_tree->tree_log);

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
    }

    return curr_node;
}

size_t question(Node* curr_node)
{
    printf("Это существо %s ?\nДа / Нет\n", curr_node->val);

    char answer[50] = {};                       // overflow and const 
    int correct_answer = scanf("%s", answer);

    if (!correct_answer)
    {
        printf("Не понял, давай ещё раз\n");
        correct_answer = scanf("%s", answer);
    }

    return (size_t)strncmp(answer, "Нет", sizeof(STR_LEN));
}

void object_processing(Node* curr_node, Tree* akinator_tree)
{
    size_t answer = question(curr_node);

    if (answer)
    {
        printf("Я это знал!\n");
        return; 
    }

    printf("Вы перехитрили меня!\n");
    printf("Тогда кто же это?\n");

    unsigned char* new_object = str_scanf();

    printf("Чем %s отличается от %s?\n", new_object, curr_node->val);

    unsigned char* feature = str_scanf();
    //printf("negative_feature(feature) = %d\n", negative_feature(feature));

    while (negative_feature(feature))
    {
        printf("Не 'некай' мне тут!\n");
        feature = str_scanf();
    }

    object_add(curr_node, (const char*)new_object, (const char*)feature, akinator_tree);

    free(new_object);
    free(feature);
    printf("Я это запомнил...\n");
}

unsigned char* str_scanf(void)              //gets
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
{           
    tree_add_node(old_node, left, new_object, akinator_tree);
    tree_add_node(old_node, right, (const char*) old_node->val, akinator_tree);
    memcpy(old_node->val, feature, STR_LEN);
}

int is_continue(Tree* akinator_tree)
{
    size_t level = 0;   
    tree_print(akinator_tree->node_list, akinator_tree->tree_log, &level);

    //node_list_print(akinator_tree);

    printf("Желаешь ешё попытать удачу ? (Да / Нет)\n");

    char* answer = (char*) calloc(STR_LEN, sizeof(char));
    
    int answer_scaned = scanf("%s", answer);
    if (!answer_scaned)
    {
        printf("Пожалуйства повторите ввод ответа\n");
        answer_scaned = scanf("%s", answer);
    }

    level = 0;
    tree_print(akinator_tree->node_list, akinator_tree->tree_log, &level);
    //node_list_print(akinator_tree);

    if (strncmp(answer, "Да", STR_LEN))
    {   
        free(answer);
        //tree_detor(akinator_tree);
        printf("Возвращайся когда будешь готов ещё раз сразиться со мной\n");
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
        Node* found_object = object_guess(akinator_tree);
        object_processing(found_object, akinator_tree);
        continue_flag = is_continue(akinator_tree);
    }
}

int negative_feature(unsigned char* feature)
{
    return !(strncmp((const char*)ru_yes, (const char*)feature, sizeof(ru_yes))
           || strncmp((const char*)ru_Yes, (const char*)feature, sizeof(ru_Yes)));
}


Node* akinator_tree_read(char* source, Tree* akinator_tree, size_t* pos)
{
    //printf("\nbegin read\n");
    //printf("the remained tree = \n%s\n", source + *(pos));

    skip_spaces(source, pos);

    //printf("the remained tree = \n%s\n", source + *(pos));
    //printf("the next symbol is %c(%d)\n", *(source + *(pos)), *(source + *(pos)));
    
    if (*(source + *(pos)) == '{')                  // reverse if 
    {
        //printf("processing symbol {\n");
        
        (*pos)++;
        
        //printf("the next processing symbol is %c(%d)\n", *(source + *(pos)), *(source + *(pos)));
        //printf("the remained tree = \n%s\n", source + *(pos));
        
        skip_spaces(source, pos);
        
        //printf("the reamined tree = \n%s\n", source + *(pos));
        //printf("the next processing symbol is %c(%d)\n", *(source + *(pos)), *(source + *(pos)));
        
        if (*(source + *(pos)) == '}') 
        {   
            //printf("processing symbol }\n");
            
            (*pos)++;
            
            //printf("the next processing symbol is %c(%d)\n", *(source + *(pos)), *(source + *(pos)));
            //printf("the remained tree = \n%s\n", source + *(pos));
            
            return NULL;
        }

        //printf("the remained tree = \n%s\n", source + *(pos));
        
        unsigned char* arg = arg_scanf(source, pos);

        //printf("the remained tree after arg scanned = \n%s\n", source + *(pos));

        Node* new_node = akinator_tree->node_list + (akinator_tree->node_count++);
        if (arg != NULL) memcpy(new_node->val, (char*)arg, sizeof(char) * STR_LEN);

        skip_spaces(source, pos);
        
        if (*(source + *(pos)) == '}') 
        {
            //printf("the next symbol is '}'\n");
            
            new_node->left  = NULL;
            new_node->right = NULL;
            skip_spaces(source, pos);          
        }
        else
        {
            //printf("the remained tree = \n%s\n", source + *(pos));
            //printf("the next processing symbol is %c(%d)\n", *(source + *(pos)), *(source + *(pos)));
            //printf("\nbegin left for %s\n", arg);
            
            new_node->left  = akinator_tree_read(source, akinator_tree, pos);
            skip_spaces(source, pos);

            //printf("the next processing symbol is %c(%d)\n", *(source + *(pos)), *(source + *(pos)));
            (*pos)++; 
            //printf("left end for %s\n", arg);

            skip_spaces(source, pos);
            
            //printf("the next processing symbol is %c(%d)\n", *(source + *(pos)), *(source + *(pos)));
            //printf("the remained tree = \n%s\n", source + *(pos));
            //printf("the next processing symbol is %c(%d)\n", *(source + *(pos)), *(source + *(pos)));
            //printf("\nbegin right for %s\n", arg);

            new_node->right = akinator_tree_read(source, akinator_tree, pos);
            skip_spaces(source, pos);
            (*pos)++;
            //printf("end right for %s\n", arg);

            //printf("the remained tree after arg scanned = \n%s\n", source + *(pos));
        }
        free(arg);
        return new_node;
    }
    else
    {
        //printf("symbol is not {, but %c(%d)\n", *(source + *(pos)), *(source + *(pos)));
        //printf("the remained tree = \n%s\n", source + *(pos));
        
        skip_spaces(source, pos);
        (*pos)++;
        return NULL;
        
        //printf("the remained tree = \n%s\n", source + *(pos));
    }

    //printf("Unexpected exit in pos = %zu\n", *pos);
}

// regular expression 

unsigned char* arg_scanf(char* source, size_t* pos)
{
    unsigned char* arg = (unsigned char*)calloc(STR_LEN, RUS_CHAR_SIZE);
    
    //printf("before arg source = %s\n", source + *(pos));
    
    size_t i = 0;

    skip_spaces(source, pos);

    //printf("source = %s\n", source + *pos);
    //printf("symbol = %c\n", (unsigned char) (*(source + *pos)));

    if(*(source + (*pos)) != '"') 
    {
        free(arg);
        return NULL;
    }

    (*pos)++;
    while (*(source + *(pos)) != '"')
    {
        arg[i] = (unsigned char)*(source + (*pos));
        i++; 
        (*pos)++;
    }
    (*pos)++;
    skip_spaces(source, pos);

    //printf("arg is %s\n", arg);

    return arg;
}

void akinator_end(Tree* akinator_tree)
{
    FILE* output = FOPEN("tree.txt", "wb");

    //printf("in akinator ending\n");

    size_t level = 0;
    tree_print(akinator_tree->node_list, output, &level);
    tree_detor(akinator_tree);

    FCLOSE(output);
}

void object_search(Tree* tree)
{
    char* val = (char*)calloc(STR_LEN, sizeof(char));
    printf("Введите объект, который хотите найти\n");
    val = (char*)str_scanf();

    Stack* way_to_obj = way_stack(tree, val);

    if (way_to_obj != NULL)
    {
        printf("%s найден!\n", val);
        printf("%s", val);
        difinition_print(tree, way_to_obj, 0, way_to_obj->size);
        StackDtor(way_to_obj);
        free(way_to_obj);
    }
    else
    {
        printf("%s не найден\n", val);
        printf("Если вы хотите добавить %s перейдите в режим угадать объект\n", val);
    }

    free(val);

    return;
}

void difinition_print(Tree* tree, Stack* way_to_obj, size_t start_pos, size_t end_pos)
{

    size_t level = 0;

    Node* curr_node = tree->node_list;

    while (level != start_pos)
    {
        if (way_to_obj->data[level] == left) curr_node = curr_node->left;
        if (way_to_obj->data[level] == right) curr_node = curr_node->right;

        level++;
    }

    while (level != end_pos)
    {
        if ((way_to_obj->data)[level] == right) printf(" не");

        printf(" %s ", curr_node->val);

        if (level == end_pos - 2)  printf("и");
        else if (level != end_pos - 1) printf(",");

        if ((way_to_obj->data)[level] == left) curr_node = curr_node->left;
        else curr_node = curr_node->right;

        level++;
    }

    printf("\n");
}

int menu(void)
{
    fprint_nchar(stdout, '*', 25);
    printf("AKINATOR");
    fprint_nchar(stdout, '*', 25);

    printf("%-40s 2)Дать определение\n", "1)Угадать объект");
    printf("%-42s 4)Выйти\n", "3)Сравнить объекты");

    fprint_nchar(stdout, '*', 25);
    printf("AKINATOR");
    fprint_nchar(stdout, '*', 25);
    printf("\n");

    int option = 0;
    int option_scaned = scanf("%d", &option);

    while ((option > 4) || (option < 1) || (option_scaned == 0))
    {
        printf("Выберите режим снова\n");
        ClearBuffer();
        option_scaned = scanf("%d", &option);
    }



    return option;
}

void game_mod_playing(Tree* akinator_tree)
{
    int continue_flag = 1;

    while(continue_flag)
    {
        int option = menu();

        switch (option)            
        {
        case Object_guess:
            akinator_playing(akinator_tree);
            break;
        case Object_search:
            object_search(akinator_tree);
            break;
        case Objects_compare:
            object_compare(akinator_tree);
            break;
        case Exit:
        default:
            continue_flag = 0;
            break;
        }
    }

    return;
}

void object_compare(Tree* akinator_tree)
{
    assert(akinator_tree != NULL);

    char* val1 = (char*)calloc(STR_LEN, sizeof(char));
    char* val2 = (char*)calloc(STR_LEN, sizeof(char));

    printf("Введите объекты, которые хотите найти\n");

    printf("Первый обЪект:\n");
    val1 = (char*)str_scanf();

    printf("Второй объект:\n");
    val2 = (char*)str_scanf();

    printf("\n");

    Stack* way_to_obj1 = way_stack(akinator_tree, val1);

    if (way_to_obj1 == NULL)
    {
        printf("%s не найден\n", val1);
        free(val1);
        free(val2);
    }
    else if (strcmp(val1, val2) == 0)
    {
        printf("Вы ввели одинаковые объекты\n");
        printf("%s ", val1);
        difinition_print(akinator_tree, way_to_obj1, 0, way_to_obj1->size);

        free(val1);
        free(val2);
        StackDtor(way_to_obj1);
        free(way_to_obj1);
    }
    else
    {
        Stack* way_to_obj2 = way_stack(akinator_tree, val2);

        if (way_to_obj2 == NULL) 
        {
            printf("%s не найден\n", val2);

            free(val1);
            free(val2);
            StackDtor(way_to_obj1);
            free(way_to_obj1);
        }
        else
        {
            size_t curr_pos = 0;

            while (way_to_obj1->data[curr_pos] == way_to_obj2->data[curr_pos]){curr_pos++;}        

            printf("%s похож на %s тем, что ", val1, val2);
            difinition_print(akinator_tree, way_to_obj1, 0, curr_pos);

            printf("Но %s ", val1);
            difinition_print(akinator_tree, way_to_obj1, curr_pos, way_to_obj1->size);

            printf("А %s ", val2);
            difinition_print(akinator_tree, way_to_obj2, curr_pos, way_to_obj2->size);
            printf("\n");

            free(val1);
            free(val2);
            StackDtor(way_to_obj1);
            free(way_to_obj1);
            StackDtor(way_to_obj2);
            free(way_to_obj2);
        }
    }    

    return;
}



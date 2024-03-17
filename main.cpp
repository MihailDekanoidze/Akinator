#include <stdio.h>
#include <stdlib.h>

#include "Akinator.h"
#include "./include/InputText.h"


int main()
{
    FILE* data =  fopen("tree.txt", "rb");

    TextInfo* buffer = (TextInfo*) calloc(1, sizeof(TextInfo));
    InputText(buffer, data);

    /*printf("buffer = %s\n", (unsigned char*)(buffer->buffer));
    for (size_t i = 0; i < buffer->elemcount + 1; i++)
    {
        printf("buffer[%zu] = %c(%d)\n", i, *((unsigned char*)(buffer->buffer) + i), *((unsigned char*)(buffer->buffer) + i));
    }*/

    fclose(data);

    Tree* akinator_tree = tree_create(BASE_NODE_COUNT);
    size_t pos = 0; 

    akinator_tree_read((char*)(buffer->buffer), akinator_tree, &pos);

    tree_print(akinator_tree->root, fopen("tree_log.cpp", "w"));

    node_list_print(akinator_tree);

    akinator_playing(akinator_tree);

    tree_detor(akinator_tree);

    return 0;
}


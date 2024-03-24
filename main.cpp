#include <stdio.h>
#include <stdlib.h>

#include "Akinator.h"


int main()
{
    FILE* data_base = FOPEN("tree.txt", "rb");

    Tree* akinator_tree = akinator_upload_tree(data_base);

    game_mod_playing(akinator_tree);

    //object_search(akinator_tree);


    akinator_end(akinator_tree);

    return 0;
}

    /*tree_print(akinator_tree->root, output);
    fclose(output);*/
#include <stdio.h>
#include <stdlib.h>

#include "Akinator.h"


int main()
{
    Tree* akinator_tree = akinator_upload_tree("tree.txt");

    graph_image(akinator_tree->node_list);

    //game_mod_playing(akinator_tree);

    akinator_end(akinator_tree);

    return 0;
}

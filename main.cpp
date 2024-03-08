#include <stdio.h>

#include "Akinator.h"


int main()
{
    Tree* main_tree = tree_create(BASE_NODE_COUNT);

    akinator_playing(main_tree);
}


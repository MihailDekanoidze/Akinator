#include <stdio.h>
#include <stdlib.h>

#include "Akinator.h"


int main()
{
    Tree* akinator_tree = akinator_upload_tree(fopen("tree.txt", "rb"));

    akinator_playing(akinator_tree);

    akinator_end(akinator_tree, fopen("tree.txt", "wb"));

    return 0;
}


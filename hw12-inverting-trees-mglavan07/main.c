#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) { 
    // Check for correct number of arguments
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    // Read the tree from input file
    Tree *root = read_from_file(argv[1]);
    if (root == NULL) {
        FILE *out = fopen(argv[2], "wb");
        if (out != NULL) {
            fclose(out);
        } // Just create empty file
        return EXIT_SUCCESS;
    }

    // Invert the tree
    Tree *inverted = invert_tree(root);

    // Write the inverted tree to the output file
    preorder_print(inverted, argv[2]);

    // preorder_print frees the tree
    free_tree(inverted);

    return EXIT_SUCCESS;
}

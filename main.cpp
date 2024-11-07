#include "tree.hpp"

int main(void) {

    int code_error = 0;
    Tree tree = {};

    DataInsert(&tree.root, 10, &code_error);
    DataInsert(&tree.root, 5, &code_error);
    DataInsert(&tree.root, 15, &code_error);
    DataInsert(&tree.root, 100, &code_error);
    for(int i = -3, j = 5; i <= 15; i++, j--) {
        DataInsert(&tree.root, i * j - j * j, &code_error);
    }
    for(int i = 0, j = 9; i <= 16; i++, j--) {
        DataInsert(&tree.root, i * j * (j - i), &code_error);
    }
    DotTreeDump(&tree, &code_error);

    fprintf(stderr, "%d\n", tree.root->data);

    return 0;
}
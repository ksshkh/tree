#include "tree.hpp"

#define NODE_COLOR         "\"#EC9594\""
#define NODE_BORDER_COLOR  "\"#FEE8D6\""
#define BACKGROUND_COLOR   "\"#0F0000\""

static const char* DOT_FILE_NAME   = "./debug/tree.dot";
static const char* DEBUG_FILE_NAME = "./debug/tree_dump.txt";
static const char* IMAGE_NAME      = "./debug/tree_image.png";
static const char* HTML_FILE_NAME  = "./debug/tree.html";

static int GRAPH_NUM = 1;

void TreeCtor(Tree* tree, int* code_error) {

    MY_ASSERT(tree != NULL, PTR_ERROR);

}

Node* NodeCtor(TreeElem data, Node* left, Node* right, int* code_error) {

    Node* NewNode = (Node*)calloc(1, sizeof(Node));
    MY_ASSERT(NewNode != NULL, PTR_ERROR);

    NewNode->data = data;
    NewNode->left = left;
    NewNode->right = right;

    return NewNode;
}

void DataInsert(Node** node, TreeElem value, int* code_error) {

    if(*node == NULL) {
        *node = NodeCtor(value, NULL, NULL, code_error);
        MY_ASSERT(node != NULL, PTR_ERROR);

        return;
    }

    if(value < (*node)->data) {
        DataInsert(&(*node)->left, value, code_error);
    }
    else {
        DataInsert(&(*node)->right , value, code_error);
    }

}

void TreeDtor(Tree* tree, int* code_error) {

    MY_ASSERT(tree != NULL, PTR_ERROR);

    free(tree->root);

    tree->tree_size = 0;
}

void DotTreeDump(Tree* tree, int* code_error) {

    MY_ASSERT(tree != NULL, PTR_ERROR);

    FILE* dot_file = fopen(DOT_FILE_NAME, "w");
    MY_ASSERT(dot_file != NULL, FILE_ERROR);

    fprintf(dot_file, "digraph Tree {\n");
    fprintf(dot_file, "\trankdir = TB;\n");
    fprintf(dot_file, "\tnode [shape = record];\n");
    fprintf(dot_file, "\tedge[color = " NODE_BORDER_COLOR "];\n");
    fprintf(dot_file, "\tbgcolor = " BACKGROUND_COLOR ";\n");

    PrintNode(tree->root, dot_file);

    fprintf(dot_file, "}\n");

    MY_ASSERT(fclose(dot_file) == 0, FILE_ERROR);

    GraphCreate();
}

void PrintNode(Node* node, FILE* stream) {

    if(!node) return;

    fprintf(stream, "\tnode%p [color = " NODE_BORDER_COLOR ", shape = Mrecord, style = filled, fillcolor = " NODE_COLOR ", label = \"{indx: %p | value: %d | { left: %p | right: %p}}\"];\n",
            node, node, node->data, node->left, node->right);

    if(node->left) {
        fprintf(stream, "\t\tnode%p -> node%p\n", node, node->left);
        PrintNode(node->left,  stream);
    }

    if(node->right) {
        fprintf(stream, "\t\tnode%p -> node%p\n", node, node->right);
        PrintNode(node->right, stream);
    }

}

void GraphCreate(void) {

    char command[] = "dot -Tpng /home/ksenia/huawei/tree/debug/tree.dot -o /home/ksenia/huawei/tree/debug/tree_image";
    char exp[] = ".png";
    char graph_num_str[2] = {};

    snprintf(graph_num_str, 2,  "%d", GRAPH_NUM);
    strcat(command, graph_num_str);
    strcat(command, exp);
    system(command);

    GRAPH_NUM++;
}
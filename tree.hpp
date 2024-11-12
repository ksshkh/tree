#ifndef TREE_HPP
#define TREE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#include "errors.hpp"

typedef int TreeElem;

struct Node {
    TreeElem data = 0;

    Node* left = NULL;
    Node* right = NULL;
};

struct Tree {
    Node* root = NULL;
    size_t tree_size = 0;
};

Node* NodeCtor(TreeElem data, Node* left, Node* right, int* code_error);

void DataInsert(Node** node, TreeElem data, int* code_error);

void DotTreeDump(Tree* tree, int* code_error);

void TreeDtor(Tree* tree, int* code_error);

void PrintNode(Node* node, FILE* stream);

void GraphCreate(void);

#endif // TREE_HPP
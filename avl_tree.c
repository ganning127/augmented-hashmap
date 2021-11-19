#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void avl_insert(NodePtr *root, int data);
void avl_delete(NodePtr *root, int data);
void avl_print(NodePtr root);
void avl_print_inorder(NodePtr root);
int avl_height(NodePtr root);

int avl_height(NodePtr root)
{
    if (root == NULL)
        return -1;
    return root->height;
}
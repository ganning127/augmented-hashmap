#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
    size_t height;
} Node;
typedef Node *NodePtr;

void avl_insert(NodePtr *root, int data);
void avl_delete(NodePtr *root, int data);
void avl_print(NodePtr root);
void avl_print_inorder(NodePtr root);
int avl_height(NodePtr root);

int main(void)
{
    NodePtr root = NULL;

    return 0;
}

int avl_height(NodePtr root)
{
    if (root == NULL)
        return -1;
    return root->height;
}
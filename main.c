#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void avl_insert(NodePtr *root, int data);
void avl_delete(NodePtr *root, int data);
void avl_print(NodePtr root);
void avl_print_inorder(NodePtr root);
int avl_height(NodePtr root);
void print_avl(NodePtr bst);
void destroy_avl(NodePtr *bstPtr);
int max(int a, int b);
size_t height(NodePtr node);
void leftRotate(NodePtr *bst);
void rightRotate(NodePtr *bst);
int getBalance(NodePtr node);
NodePtr *successor_avl(NodePtr *treePtr);
NodePtr avl_balance_insert(NodePtr bst, int data);
NodePtr avl_balance_delete(NodePtr bst, int data);

int main(void)
{
    NodePtr root = NULL;
    avl_insert(&root, 1);
    avl_insert(&root, 2);
    avl_insert(&root, 3);
    avl_insert(&root, 4);
    avl_insert(&root, 5);
    avl_insert(&root, 6);
    avl_insert(&root, 7);
    avl_insert(&root, 8);

    print_avl(root);
    puts(" -- -- -- -- -- -- -- -- -");
    avl_delete(&root, 1);
    avl_delete(&root, 2);
    avl_delete(&root, 3);
    // avl_delete(&root, 4);
    // avl_delete(&root, 5);
    // avl_delete(&root, 6);
    // avl_delete(&root, 7);
    // avl_delete(&root, 8);

    destroy_avl(&root);
    free(root);

    return 0;
}
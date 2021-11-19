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
void print_bst(NodePtr bst);
int max(int a, int b);
size_t height(NodePtr node);
void leftRotate(NodePtr *bst);
void rightRotate(NodePtr *bst);
int getBalance(NodePtr node);

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

    print_bst(root);
    return 0;
}

void avl_insert(NodePtr *root, int data)
{
    NodePtr bst = *root;
    if (!bst)
    {
        // we have gotten to an empty space, insert here
        NodePtr node = malloc(sizeof(Node));
        node->data = data;
        node->left = node->right = NULL;
        node->height = 0;
        *root = node; // bstPtr is a pointer to the node. we can't change the node itself because it is a local variable
    }
    else
    {
        if (bst->data >= data)
            avl_insert(&(bst->left), data);
        else
            avl_insert(&(bst->right), data);
    }

    bst = *root;
    // code below runs after we have inserted a node
    bst->height = 1 + max(height(bst->left), height(bst->right));
    int balance = getBalance(bst);

    if (balance > 1 && data > bst->left->data) // left heavy
        rightRotate(&bst);
    if (balance < -1 && data > bst->right->data) // right heavy
    {
        leftRotate(&bst);
    }

    if (balance > 1 && data < bst->left->data) // left heavy
    {
        leftRotate(&(bst->left));
        rightRotate(&bst);
    }
    if (balance < -1 && data < bst->right->data) // right heavy
    {
        rightRotate(&(bst->right));
        leftRotate(&bst);
    }

    *root = bst;
}

void leftRotate(NodePtr *bst)
{
    NodePtr bst_right = (*bst)->right;
    NodePtr bst_right_left = bst_right->left;

    bst_right->left = *bst;
    (*bst)->right = bst_right_left;

    (*bst)->height = max(height((*bst)->left), height((*bst)->right)) + 1;
    bst_right->height = max(height(bst_right->left), height(bst_right->right)) + 1;

    *bst = bst_right;
}
void rightRotate(NodePtr *bst)
{
    NodePtr bst_left = (*bst)->left;
    NodePtr bst_left_right = bst_left->right;

    bst_left->right = *bst;
    (*bst)->left = bst_left_right;

    (*bst)->height = max(height((*bst)->left), height((*bst)->right)) + 1;
    bst_left->height = max(height(bst_left->left), height(bst_left->right)) + 1;
    *bst = bst_left;
}

int getBalance(NodePtr node)
{
    if (!node)
        return 0;
    return height(node->left) - height(node->right);
}

size_t height(NodePtr node)
{
    if (!node)
        return 0;
    return node->height;
}

void print_bst(NodePtr bst)
{
    /*
        Avg, Best, Worst: O(n)
            You need to go through each node in order to print it, resulting in a time complexity of O(n).
    */

    static unsigned int depth = 0; // this line only runs once
    if (bst == NULL)
        return;
    ++depth;
    print_bst(bst->right);
    --depth;

    for (unsigned int i = 0; i < depth; ++i)
        printf("  ");

    printf("%d\n", bst->data);
    ++depth;
    print_bst(bst->left);
    --depth;
}

int avl_height(NodePtr root)
{
    if (root == NULL)
        return -1;
    return root->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}
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
void avl_print(NodePtr bst);
int max(int a, int b);
size_t height(NodePtr node);
void avl_left_rotate(NodePtr *bst);
void avl_right_rotate(NodePtr *bst);
int avl_get_balance(NodePtr node);
NodePtr *avl_successor(NodePtr *treePtr);
NodePtr avl_balance_insert(NodePtr bst, int data);
NodePtr avl_balance_delete(NodePtr bst, int data);
NodePtr avl_tree_find(NodePtr bst, int data);

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
    avl_insert(&root, 2);

    avl_print(root);
    return 0;
}

// important functions
void avl_insert(NodePtr *root, int data)
{
    NodePtr bst = *root;
    if (!bst)
    {
        // we have gotten to an empty space, insert here
        NodePtr node = malloc(sizeof(Node));
        node->data = data;
        node->left = node->right = NULL;
        node->height = 1;
        *root = node; // bstPtr is a pointer to the node. we can't change the node itself because it is a local variable
    }
    else
    {
        if (bst->data > data)
            avl_insert(&(bst->left), data);
        else
            avl_insert(&(bst->right), data);
    }

    NodePtr balanced = avl_balance_insert(*root, data);
    *root = balanced;
}

NodePtr *avl_successor(NodePtr *treePtr)
{
    //
    NodePtr tree = *treePtr;
    if (tree->left == NULL)
    {
        return treePtr;
    }
    return avl_successor(&(tree->left));
}

void avl_left_rotate(NodePtr *bst)
{
    NodePtr bst_deref = *bst;
    NodePtr bst_right = bst_deref->right;
    NodePtr bst_right_left = bst_right->left;

    bst_right->left = *bst;
    bst_deref->right = bst_right_left;

    bst_deref->height = max(height(bst_deref->left), height(bst_deref->right)) + 1;
    bst_right->height = max(height(bst_right->left), height(bst_right->right)) + 1;

    *bst = bst_right;
}
void avl_right_rotate(NodePtr *bst)
{
    NodePtr bst_deref = *bst;
    NodePtr bst_left = bst_deref->left;
    NodePtr bst_left_right = bst_left->right;

    bst_left->right = *bst;
    bst_deref->left = bst_left_right;

    bst_deref->height = max(height(bst_deref->left), height(bst_deref->right)) + 1;
    bst_left->height = max(height(bst_left->left), height(bst_left->right)) + 1;
    *bst = bst_left;
}
void avl_print(NodePtr bst)
{
    /*
        Avg, Best, Worst: O(n)
            You need to go through each node in order to print it, resulting in a time complexity of O(n).
    */

    static unsigned int depth = 0; // this line only runs once
    if (bst == NULL)
        return;
    ++depth;
    avl_print(bst->right);
    --depth;

    for (unsigned int i = 0; i < depth; ++i)
        printf("  ");

    printf("%d\n", bst->data);
    ++depth;
    avl_print(bst->left);
    --depth;
}

void avl_delete(NodePtr *root, int data)
{
    NodePtr bst = *root;
    if (!bst) // if the bst is empty, we can't delete anything
        return;

    if (bst->data > data)
        avl_delete(&(bst->left), data);
    else if (bst->data < data)
        avl_delete(&(bst->right), data);
    else
    {
        NodePtr newPtr;
        if (bst->left && bst->right)
        {
            NodePtr *successorPtr = avl_successor(&(bst->right));
            newPtr = *successorPtr;        // deref to get successor
            *successorPtr = newPtr->right; // promote the right child to where the deleted node is

            // copy original nodes childrent to successor
            newPtr->right = bst->right;
            newPtr->left = bst->left;
        }
        else
        {
            // no children or one child
            newPtr = bst->left != NULL ? bst->left : bst->right;
        }

        *root = newPtr;
        free(bst);
    }

    NodePtr balanced = avl_balance_delete(*root, data);
    *root = balanced;
}

NodePtr avl_tree_find(NodePtr bst, int data)
{
    if (!bst)
        return NULL;
    else if (bst->data > data)
        return avl_tree_find(bst->left, data);
    else if (bst->data < data)
        return avl_tree_find(bst->right, data);
    else
        return bst;
}

// helper functions
int max(int a, int b)
{
    // returns the max value of two numbers
    return (a > b) ? a : b;
}

int avl_get_balance(NodePtr node)
{
    // get the balance factor of the left and right subtrees
    if (!node)
        return 0;
    return height(node->left) - height(node->right);
}

size_t height(NodePtr node)
{
    // returns the height of a node
    if (!node)
        return 0;
    return node->height;
}

NodePtr avl_balance_insert(NodePtr bst, int data)
{
    // code below runs after we have inserted a node
    bst->height = 1 + max(height(bst->left), height(bst->right));
    int balance = avl_get_balance(bst);

    if (balance > 1 && data > bst->left->data) // left heavy
        avl_right_rotate(&bst);
    if (balance < -1 && data > bst->right->data) // right heavy
        avl_left_rotate(&bst);

    if (balance > 1 && data < bst->left->data) // left heavy
    {
        avl_left_rotate(&(bst->left));
        avl_right_rotate(&bst);
    }
    if (balance < -1 && data < bst->right->data) // right heavy
    {
        avl_right_rotate(&(bst->right));
        avl_left_rotate(&bst);
    }

    return bst;
}

NodePtr avl_balance_delete(NodePtr bst, int data)
{
    if (!bst) // in case we deleted the root node
        return NULL;

    bst->height = 1 + max(height(bst->left), height(bst->right));

    int balance_root = avl_get_balance(bst);
    int balance_left = avl_get_balance(bst->left);
    int balance_right = avl_get_balance(bst->right);

    if (balance_root > 1 && balance_left >= 0)
        avl_right_rotate(&bst);
    if (balance_root > 1 && balance_right < 0)
    {
        avl_left_rotate(&(bst->left));
        avl_right_rotate(&bst);
    }
    if (balance_root < -1 && balance_right <= 0)
        avl_left_rotate(&bst);
    if (balance_root < -1 && balance_right > 0)
    {
        avl_right_rotate(&(bst->right));
        avl_left_rotate(&bst);
    }

    return bst;
}
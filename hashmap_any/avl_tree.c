#include "structs.h"

void avl_insert(TreeNodePtr *root, HNodePtr data);
void avl_delete(TreeNodePtr *root, char *key);
void avl_print(TreeNodePtr bst);
int max(int a, int b);
size_t height(TreeNodePtr node);
void avl_left_rotate(TreeNodePtr *bst);
void avl_right_rotate(TreeNodePtr *bst);
int avl_get_balance(TreeNodePtr node);
TreeNodePtr *avl_successor(TreeNodePtr *treePtr);
TreeNodePtr avl_balance_insert(TreeNodePtr bst, HNodePtr data);
TreeNodePtr avl_balance_delete(TreeNodePtr bst);
TreeNodePtr avl_find(TreeNodePtr bst, char *key);
void avl_destroy(TreeNodePtr *bst);

// Main Functions

TreeNodePtr avl_find(TreeNodePtr bst, char *key)
{
    // find the node in a bucket
    if (!bst)
        return NULL;
    else if (strcmp(bst->data->key, key) < 0)
        return avl_find(bst->right, key);
    else if (strcmp(bst->data->key, key) > 0)
        return avl_find(bst->left, key);
    else if (strcmp(bst->data->key, key) == 0)
        return bst;
    else
        return NULL;
}

void avl_delete(TreeNodePtr *root, char *key)
{
    // delete node in AVL tree bucket
    TreeNodePtr bst = *root;
    if (!bst) // if the bst is empty, we can't delete anything
        return;

    if (strcmp(bst->data->key, key) > 0)
        avl_delete(&(bst->left), key);
    else if (strcmp(bst->data->key, key) < 0)
        avl_delete(&(bst->right), key);
    else
    {
        TreeNodePtr newPtr;
        if (bst->left && bst->right)
        {
            TreeNodePtr *successorPtr = avl_successor(&(bst->right));
            newPtr = *successorPtr;        // deref to get successor
            *successorPtr = newPtr->right; // promote the right child to where the deleted node is

            // copy original nodes childrent to successor
            newPtr->right = bst->right;
            newPtr->left = bst->left;
        }
        else
            // no children or one child
            newPtr = bst->left != NULL ? bst->left : bst->right;

        *root = newPtr;
        free(bst->data);
        free(bst);
    }

    TreeNodePtr balanced = avl_balance_delete(*root);
    *root = balanced;
}

void avl_insert(TreeNodePtr *root, HNodePtr data)
{
    // insert into avl_tree bucket
    TreeNodePtr bst = *root;
    if (bst == NULL)
    {
        // we have gotten to an empty space, insert here
        TreeNodePtr node = malloc(sizeof(TreeNode));
        node->data = data;
        node->left = node->right = NULL;
        node->height = 1;
        *root = node; // bstPtr is a pointer to the node. we can't change the node itself because it is a local variable
    }
    else
    {
        if (strcmp(bst->data->key, data->key) > 0)
            avl_insert(&(bst->left), data);
        else if (strcmp(bst->data->key, data->key) == 0)
            return; // we don't want to insert a duplicate
        else
            avl_insert(&(bst->right), data);
    }

    TreeNodePtr balanced = avl_balance_insert(*root, data);
    *root = balanced;
}

void avl_destroy(TreeNodePtr *bst)
{
    // free an avl_tree
    if (*bst == NULL)
        return;
    avl_destroy(&((*bst)->left));
    avl_destroy(&((*bst)->right));
    free((*bst)->data);
    free(*bst);

    *bst = NULL;
}

// Helper Functions
TreeNodePtr avl_balance_insert(TreeNodePtr bst, HNodePtr data)
{
    // code below runs after we have inserted a node
    bst->height = 1 + max(height(bst->left), height(bst->right));
    int balance = avl_get_balance(bst);

    if (balance > 1 && strcmp(data->key, bst->left->data->key) < 0) // left heavy
    {
        avl_right_rotate(&bst);
        return bst;
    }
    if (balance < -1 && strcmp(data->key, bst->right->data->key) > 0) // right heavy
    {
        avl_left_rotate(&bst);
        return bst;
    }

    if (balance > 1 && strcmp(data->key, bst->left->data->key) > 0) // left heavy
    {
        avl_left_rotate(&(bst->left));
        avl_right_rotate(&bst);
        return bst;
    }

    if (balance < -1 && strcmp(data->key, bst->right->data->key) < 0) // right heavy
    {
        avl_right_rotate(&(bst->right));
        avl_left_rotate(&bst);
        return bst;
    }

    return bst;
}

TreeNodePtr avl_balance_delete(TreeNodePtr bst)
{
    if (!bst) // in case we deleted the root node
        return NULL;

    bst->height = 1 + max(height(bst->left), height(bst->right));

    int balance_root = avl_get_balance(bst);
    int balance_left = avl_get_balance(bst->left);
    int balance_right = avl_get_balance(bst->right);

    if (balance_root > 1 && balance_left >= 0)
    {
        avl_right_rotate(&bst);
        return bst;
    }
    if (balance_root > 1 && balance_left < 0)
    {
        avl_left_rotate(&(bst->left));
        avl_right_rotate(&bst);
        return bst;
    }
    if (balance_root < -1 && balance_right <= 0)
    {
        avl_left_rotate(&bst);
        return bst;
    }
    if (balance_root < -1 && balance_right > 0)
    {
        avl_right_rotate(&(bst->right));
        avl_left_rotate(&bst);
        return bst;
    }

    return bst;
}

void avl_left_rotate(TreeNodePtr *bst)
{
    // left rotate in avl tree balance
    TreeNodePtr bst_deref = *bst;
    TreeNodePtr bst_right = bst_deref->right;
    TreeNodePtr bst_right_left = bst_right->left;

    bst_right->left = *bst;
    bst_deref->right = bst_right_left;

    bst_deref->height = max(height(bst_deref->left), height(bst_deref->right)) + 1;
    bst_right->height = max(height(bst_right->left), height(bst_right->right)) + 1;

    *bst = bst_right;
}
void avl_right_rotate(TreeNodePtr *bst)
{
    // right rotate in avl tree balance
    TreeNodePtr bst_deref = *bst;
    TreeNodePtr bst_left = bst_deref->left;
    TreeNodePtr bst_left_right = bst_left->right;

    bst_left->right = *bst;
    bst_deref->left = bst_left_right;

    bst_deref->height = max(height(bst_deref->left), height(bst_deref->right)) + 1;
    bst_left->height = max(height(bst_left->left), height(bst_left->right)) + 1;
    *bst = bst_left;
}
void avl_print(TreeNodePtr bst)
{
    // print avl tree horizontally
    static unsigned int depth = 0; // this line only runs once
    if (bst == NULL)
        return;
    ++depth;
    avl_print(bst->right);
    --depth;

    for (unsigned int i = 0; i < depth; ++i)
        printf("  ");

    printf("%d\n", *((int *)(bst->data->value)));
    ++depth;
    avl_print(bst->left);
    --depth;
}

TreeNodePtr *avl_successor(TreeNodePtr *treePtr)
{
    // find node to succeed a node in avl_delete()
    TreeNodePtr tree = *treePtr;
    if (tree->left == NULL)
        return treePtr;
    return avl_successor(&(tree->left));
}

// Math Functions

int max(int a, int b)
{
    // returns the max value of two numbers
    return (a > b) ? a : b;
}

int avl_get_balance(TreeNodePtr node)
{
    // get the balance factor of the left and right subtrees
    if (!node)
        return 0;
    return height(node->left) - height(node->right);
}

size_t height(TreeNodePtr node)
{
    // returns the height of a node
    if (!node)
        return 0;
    return node->height;
}

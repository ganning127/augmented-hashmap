#include <stdio.h>
#include <stdlib.h>

typedef struct hash_node
{
    char *key;
    int value;
} HNode;
typedef HNode *HNodePtr;

typedef struct tree_node
{
    HNodePtr data;
    struct tree_node *left;
    struct tree_node *right;
    size_t height;
} TreeNode;
typedef TreeNode *TreeNodePtr;

void avl_insert(TreeNodePtr *root, HNodePtr data);
void avl_delete(TreeNodePtr *root, HNodePtr data);
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
HNodePtr createHNode(char *key, int value);

int main(void)
{
    TreeNodePtr root = NULL;

    HNodePtr first = createHNode("first", 1);
    HNodePtr second = createHNode("second", 2);
    HNodePtr third = createHNode("third", 3);

    avl_insert(&root, first);
    avl_insert(&root, second);
    avl_insert(&root, third);

    avl_delete(&root, second);
    TreeNodePtr found = avl_find(root, "first");
    printf("Found: %d\n", found->data->value);

    avl_print(root);
    return 0;
}

HNodePtr createHNode(char *key, int value)
{
    HNodePtr node = malloc(sizeof(HNode));
    node->key = key;
    node->value = value;
    return node;
}

// important functions
void avl_insert(TreeNodePtr *root, HNodePtr data)
{
    TreeNodePtr bst = *root;
    if (!bst)
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
        if (bst->data->key > data->key)
            avl_insert(&(bst->left), data);
        else
            avl_insert(&(bst->right), data);
    }

    TreeNodePtr balanced = avl_balance_insert(*root, data);
    *root = balanced;
}

TreeNodePtr *avl_successor(TreeNodePtr *treePtr)
{
    //
    TreeNodePtr tree = *treePtr;
    if (tree->left == NULL)
    {
        return treePtr;
    }
    return avl_successor(&(tree->left));
}

void avl_left_rotate(TreeNodePtr *bst)
{
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

    printf("%d\n", bst->data->value);
    ++depth;
    avl_print(bst->left);
    --depth;
}

void avl_delete(TreeNodePtr *root, HNodePtr data)
{
    TreeNodePtr bst = *root;
    if (!bst) // if the bst is empty, we can't delete anything
        return;

    if (bst->data->key > data->key)
        avl_delete(&(bst->left), data);
    else if (bst->data->key < data->key)
        avl_delete(&(bst->right), data);
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
        {
            // no children or one child
            newPtr = bst->left != NULL ? bst->left : bst->right;
        }

        *root = newPtr;
        free(bst);
    }

    TreeNodePtr balanced = avl_balance_delete(*root);
    *root = balanced;
}

TreeNodePtr avl_find(TreeNodePtr bst, char *key)
{
    if (!bst)
        return NULL;
    else if (bst->data->key > key)
        return avl_find(bst->left, key);
    else if (bst->data->key < key)
        return avl_find(bst->right, key);
    else
        return bst;
}

// helper functions
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

TreeNodePtr avl_balance_insert(TreeNodePtr bst, HNodePtr data)
{
    // code below runs after we have inserted a node
    bst->height = 1 + max(height(bst->left), height(bst->right));
    int balance = avl_get_balance(bst);

    if (balance > 1 && data->key > bst->left->data->key) // left heavy
        avl_right_rotate(&bst);
    if (balance < -1 && data->key > bst->right->data->key) // right heavy
        avl_left_rotate(&bst);

    if (balance > 1 && data->key < bst->left->data->key) // left heavy
    {
        avl_left_rotate(&(bst->left));
        avl_right_rotate(&bst);
    }
    if (balance < -1 && data->key < bst->right->data->key) // right heavy
    {
        avl_right_rotate(&(bst->right));
        avl_left_rotate(&bst);
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
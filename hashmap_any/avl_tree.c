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

/*

Time Complexity

avl_insert():
    Worst Case: O(log(n))
        If the item we are trying to insert is at the very bottom of the tree then it would be O(log(n)) because the tree is balanced

    Best Case: O(1)
        If the item we are trying to insert is inserted at the root then it would have constant time

    Average Case: O(log(n))
        The average time complexity would be O(log(n)) because the tree is always balanced

avl_delete():
    Worst Case: O(log(n))
        If the item we are trying to delete is at the very bottom of the tree then it would be O(log(n)) because the tree is balanced

    Best Case: O(1)
        If the item we are trying to deleted is at the root then it would have constant time

    Average Case: O(log(n))
        The average time complexity would be O(log(n)) because the tree is always balanced

avl_destroy():
    Worst Case: O(n)
        We have to go through all of the elements of the tree to free them

    Best Case: O(n)
        We have to go through all of the elements of the tree to free them

    Average Case: O(n)
        We have to go through all of the elements of the tree to free them

avl_find():
    Worst Case: O(log(n))
        If the node we are trying to find is at the bottom then we would have log(n) time because it is balanced

    Best Case: O(1)
        If the node we are trying to find is at the root then we have constant time

    Average Case: O(log(n))
        The tree is always balanced so our average time complexity would be log(n)


Space Complexity

AVL Tree Space Complexity:
    The average and worst case space complexity are both O(n) because you are going
    to have n number of nodes for an n amount of data.

avl_insert():
    Worst Case: O(1)
        We use a constant amount of data for insert so the amount of space we use doesn't increase

    Best Case: O(1)
        We use a constant amount data for insert so the amount of space we use doesn't increase

    Average Case: O(1)
        We use a constant amount data for insert so the amount of space we use doesn't increase

avl_delete():
    Worst Case: O(1)
        We use a constant amount data for delete so the amount of space we use doesn't increase

    Best Case: O(1)
        We use a constant amount data for delete so the amount of space we use doesn't increase

    Average Case: O(1)
        We use a constant amount data for delete so the amount of space we use doesn't increase 

avl_destroy():
    Worst Case: O(1)
        We use a constant amount data for destroy so the amount of space we use doesn't increase

    Best Case: O(1)
        We use a constant amount data for destroy so the amount of space we use doesn't increase

    Average Case: O(1)
        We use a constant amount data for destroy so the amount of space we use doesn't increase

avl_find():
    Worst Case: O(1)
        We use a constant amount data for find so the amount of space we use doesn't increase

    Best Case: O(1)
        We use a constant amount data for find so the amount of space we use doesn't increase

    Average Case: O(1)
        We use a constant amount data for find so the amount of space we use doesn't increase

*/

// Main Functions

TreeNodePtr avl_find(TreeNodePtr bst, char *key)
{
    /*
        Finds a node in a tree using a key
    */
    if (!bst) // Go up a node if the current is NULL
        return NULL;
    else if (strcmp(bst->data->key, key) < 0) // Go right if the the key is greater than the current node
        return avl_find(bst->right, key);
    else if (strcmp(bst->data->key, key) > 0) // Go let if the key is less than the current node
        return avl_find(bst->left, key);
    else if (strcmp(bst->data->key, key) == 0) // Return the node if we found the right node
        return bst;
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
    if (*bst == NULL) // Go up a node if the current node is NULL
        return;
    avl_destroy(&((*bst)->left));  // Destroy the left tree
    avl_destroy(&((*bst)->right)); // Destroy the right tree
    free((*bst)->data);            // Free the current node's data
    free(*bst);                    // Free the current node

    *bst = NULL; // Set the root node to NULL
}

// Helper Functions
TreeNodePtr avl_balance_insert(TreeNodePtr bst, HNodePtr data)
{
    // code below runs after we have inserted a node
    bst->height = 1 + max(height(bst->left), height(bst->right)); // Calculate the current height of the node
    int balance = avl_get_balance(bst);                           // Get the balance value of the current node

    if (balance > 1 && strcmp(data->key, bst->left->data->key) < 0) // left heavy
    {
        avl_right_rotate(&bst); // Right rotate if we are left heavy and the left child is greater than what we are trying to insert
        return bst;
    }
    if (balance < -1 && strcmp(data->key, bst->right->data->key) > 0) // right heavy
    {
        avl_left_rotate(&bst); // Left rotate if we are right heavy and the right child is less than what we are trying to insert
        return bst;
    }

    if (balance > 1 && strcmp(data->key, bst->left->data->key) > 0) // left heavy
    {
        // Left-right rotate if we are left heavy and the left child is smaller than the key we are trying to insert
        avl_left_rotate(&(bst->left));
        avl_right_rotate(&bst);
        return bst;
    }

    if (balance < -1 && strcmp(data->key, bst->right->data->key) < 0) // right heavy
    {
        // Right-left rotate if we are right heavy and the right child is greater than what we are trying to insert
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

    bst->height = 1 + max(height(bst->left), height(bst->right)); // Get the height of the current node

    int balance_root = avl_get_balance(bst);         // Find the balance of the current node
    int balance_left = avl_get_balance(bst->left);   // Find the balance of the left node
    int balance_right = avl_get_balance(bst->right); // Find the balance of the right node

    if (balance_root > 1 && balance_left >= 0) // Both the root and the left are left heavy
    {
        avl_right_rotate(&bst); // Right rotate
        return bst;
    }
    if (balance_root > 1 && balance_left < 0) // Root is left heavy but left is right heavy
    {
        avl_left_rotate(&(bst->left)); // Left-right rotate
        avl_right_rotate(&bst);
        return bst;
    }
    if (balance_root < -1 && balance_right <= 0) // Both root and right are right heavy
    {
        avl_left_rotate(&bst); // Left rotate
        return bst;
    }
    if (balance_root < -1 && balance_right > 0) // Root is right heavy but right is left heavy
    {
        avl_right_rotate(&(bst->right)); // Right-left rotate
        avl_left_rotate(&bst);
        return bst;
    }

    return bst;
}

void avl_left_rotate(TreeNodePtr *bst)
{
    // left rotate in avl tree balance

    // Get all of the nodes so we can move them around
    TreeNodePtr bst_deref = *bst;
    TreeNodePtr bst_right = bst_deref->right;
    TreeNodePtr bst_right_left = bst_right->left;

    // Move the root node to the left of the right node and make the right child of the
    bst_right->left = *bst;
    bst_deref->right = bst_right_left;

    // Get the new heights
    bst_deref->height = max(height(bst_deref->left), height(bst_deref->right)) + 1;
    bst_right->height = max(height(bst_right->left), height(bst_right->right)) + 1;

    //
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

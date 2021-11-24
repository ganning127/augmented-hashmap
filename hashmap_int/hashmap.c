#include "structs.h"

size_t hashmap_hash(char *str, size_t size);
void hashmap_insert(ArrayListNodesPtr list, char *key, int value);
int hashmap_get(ArrayListNodesPtr list, char *key);
void hashmap_delete(ArrayListNodesPtr list, char *key);

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
ArrayListNodes *arln_create();

void resize(ArrayListNodes *list);

int main(void)
{
    ArrayListNodesPtr list = arln_create();
    hashmap_insert(list, "abc", 1);
    hashmap_insert(list, "abc", 2);
    hashmap_insert(list, "adc", 3);
    hashmap_insert(list, "aec", 4);

    // hashmap_delete(list, "abc");
    avl_print(list->array[0]);

    printf("%d\n", hashmap_get(list, "abc"));

    return 0;
}

ArrayListNodes *arln_create()
{
    ArrayListNodes *list = malloc(sizeof(ArrayListNodes));
    list->size = 0;
    list->capacity = INITIAL_SIZE;
    list->array = calloc(sizeof(HNode *), INITIAL_SIZE);
    // set all the pointers to NULL
    for (size_t i = 0; i < list->capacity; i++)
        list->array[i] = NULL;
    return list;
}

void hashmap_delete(ArrayListNodesPtr list, char *key)
{
    size_t index = hashmap_hash(key, list->capacity);
    TreeNodePtr *treePtr = &(list->array[index]);
    HNodePtr data = createHNode(key, 0);
    avl_delete(treePtr, data);
    free(data);
}

void hashmap_insert(ArrayListNodesPtr list, char *key, int value)
{
    size_t index = hashmap_hash(key, list->capacity);
    list->size++;
    HNodePtr nu = createHNode(key, value);
    // nu is now the data that we want to insert into the tree

    avl_insert(&(list->array[index]), nu);

    // if (list->size > list->capacity * LOAD_FACTOR) // change this
    //     resize(list);
}

int hashmap_get(ArrayListNodesPtr list, char *key)
{
    size_t index = hashmap_hash(key, list->capacity);
    TreeNodePtr bst = list->array[index];
    TreeNodePtr node = avl_find(bst, key);
    if (node == NULL)
    {
        printf("key \"%s\" was not found, returning -1\n", key);
        return -1; // node was not found
    }
    else
    {
        return node->data->value;
    }
}

size_t hashmap_hash(char *str, size_t size)
{
    // generate a hash value for a string (to index into array)
    size_t hash = 0;
    while (*str != '\0')
    {
        // printf("%c", *str);
        hash = (hash * 31 + *str) % size;
        ++str;
    }

    return hash;
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
        if (strcmp(bst->data->key, data->key) > 0)
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

    if (strcmp(bst->data->key, data->key) > 0)
        avl_delete(&(bst->left), data);
    else if (strcmp(bst->data->key, data->key) < 0)
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
    else if (strcmp(bst->data->key, key) < 0)
        return avl_find(bst->right, key);
    else if (strcmp(bst->data->key, key) > 0)
        return avl_find(bst->left, key);
    else if (strcmp(bst->data->key, key) == 0)
        return bst;
    else
        return NULL;
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

    /// asdfasf

    if (balance > 1 && strcmp(data->key, bst->left->data->key) > 0) // left heavy
        avl_right_rotate(&bst);
    if (balance < -1 && strcmp(data->key, bst->right->data->key) > 0) // right heavy
        avl_left_rotate(&bst);

    if (balance > 1 && strcmp(data->key, bst->left->data->key) < 0) // left heavy
    {
        avl_left_rotate(&(bst->left));
        avl_right_rotate(&bst);
    }
    if (balance < -1 && strcmp(data->key, bst->left->data->key) < 0) // right heavy
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
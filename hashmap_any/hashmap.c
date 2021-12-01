#include "structs.h"
enum
{
    INT = 1,
    STRING = 2,
    DOUBLE = 3,
    CHAR = 4,
    UINT = 5,
    ULONG = 6,
    LONG = 7,
    SHORT = 8,
    USHORT = 9,
};

size_t hashmap_hash(char *str, size_t size);
void hashmap_insert_any(ArrayListNodesPtr list, char *key, int type, void *value);
HNodePtr hashmap_get(ArrayListNodesPtr list, char *key);
void hashmap_delete(ArrayListNodesPtr list, char *key);
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
HNodePtr createHNodeAny(char *key, int type, void *value);
ArrayListNodes *arln_create(size_t capacity);
void displayNodeValue(HNodePtr node);
void hashmap_resize(ArrayListNodesPtr list, size_t new_capacity);
void avl_destroy(TreeNodePtr *bst);
void hashmap_destroy(ArrayListNodesPtr *listPtr);
double getLoadFactor(ArrayListNodesPtr list);

/*
Time Complexity Analysis


*/

int main(void)
{
    ArrayListNodesPtr list = arln_create(INITIAL_CAPACITY);
    char *ins1 = "Ganning";
    unsigned int ins2 = 16;
    double ins3 = 94.53;
    char ins4 = 'A';
    unsigned long ins5 = 123456789;

    hashmap_insert_any(list, "name", STRING, ins1);

    hashmap_insert_any(list, "age", UINT, &ins2);
    hashmap_insert_any(list, "grade", DOUBLE, &ins3);
    hashmap_insert_any(list, "letter_grade", CHAR, &ins4);
    hashmap_insert_any(list, "id", ULONG, &ins5);

    hashmap_delete(list, "name");
    hashmap_delete(list, "age");
    hashmap_delete(list, "grade");
    hashmap_delete(list, "letter_grade");
    hashmap_delete(list, "id");

    hashmap_insert_any(list, "name", STRING, ins1);
    hashmap_insert_any(list, "age", UINT, &ins2);
    hashmap_insert_any(list, "grade", DOUBLE, &ins3);
    hashmap_insert_any(list, "letter_grade", CHAR, &ins4);
    hashmap_insert_any(list, "id", ULONG, &ins5);

    HNodePtr res1 = hashmap_get(list, "name");
    HNodePtr res2 = hashmap_get(list, "age");
    HNodePtr res3 = hashmap_get(list, "grade");
    HNodePtr res4 = hashmap_get(list, "letter_grade");
    HNodePtr res5 = hashmap_get(list, "id");

    displayNodeValue(res1);
    displayNodeValue(res2);
    displayNodeValue(res3);
    displayNodeValue(res4);
    displayNodeValue(res5);

    hashmap_destroy(&list);

    return 0;
}

void hashmap_destroy(ArrayListNodesPtr *listPtr)
{
    /*
    hashmap_destroy()
            Worst Case: O(n)
                - n is total number of nodes in the hashmap
                we need to go to each node in the hashmap and free it

            Best Case: O(n)
                - n is total number of nodes in the hashmap
                we need to go to each node in the hashmap and free it

            Average Case: O(n)
                - n is total number of nodes in the hashmap
                we need to go to each node in the hashmap and free it
    */
    ArrayListNodesPtr list = *listPtr;
    for (size_t i = 0; i < list->capacity; i++)
    {
        TreeNodePtr node = list->array[i];

        if (node != NULL)
        {
            // free(node->data);
            avl_destroy(&node);
        }
    }
    free(list->array);
    free(list);
}

void hashmap_resize_helper(TreeNodePtr *newArray, TreeNodePtr bst, size_t new_capacity)
{

    if (bst == NULL)
        return;

    hashmap_resize_helper(newArray, bst->left, new_capacity);
    hashmap_resize_helper(newArray, bst->right, new_capacity);

    // printf("%s: %d\n", bst->data->key, *(int *)bst->data->value);

    HNodePtr node = createHNodeAny(bst->data->key, bst->data->type, bst->data->value);
    printf("node key: %s, capacity: %zu\n", node->key, new_capacity);
    size_t hash = hashmap_hash(node->key, new_capacity);

    // printf("new hash of %s is %zu\n", node->key, hash);
    avl_insert(&(newArray[hash]), node);
}

void free_list(ArrayListNodesPtr list)
{
    for (size_t i = 0; i < list->capacity; i++)
    {
        TreeNodePtr node = list->array[i];
        if (node != NULL)
        {
            avl_destroy(&node);
        }
    }
    free(list->array);
}

void hashmap_resize(ArrayListNodesPtr list, size_t new_capacity)
{
    TreeNodePtr *newArray = (TreeNodePtr *)calloc(sizeof(TreeNodePtr), new_capacity);

    for (size_t i = 0; i < list->capacity; i++)
    {
        if (list->array[i] != NULL)
        {
            // list->array[i] is a TreeNodePtr
            TreeNodePtr node = list->array[i];
            hashmap_resize_helper(newArray, node, new_capacity);
        }
    }

    free_list(list);
    list->array = newArray;
    list->capacity = new_capacity;
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

void displayNodeValue(HNodePtr node)
{
    // display a node value
    if (node == NULL)
        return;
    switch (node->type)
    {
    case INT:
        printf("%d\n", *(int *)node->value);
        break;
    case STRING:
        printf("%s\n", (char *)node->value);
        break;
    case DOUBLE:
        printf("%f\n", *(double *)node->value);
        break;
    case CHAR:
        printf("%c\n", *(char *)node->value);
        break;
    case UINT:
        printf("%u\n", *(unsigned int *)node->value);
        break;
    case ULONG:
        printf("%lu\n", *(unsigned long *)node->value);
        break;
    };
}

ArrayListNodes *arln_create(size_t capacity)
{
    // create array of TreeNodePtrs that contains each an avl tree
    ArrayListNodes *list = malloc(sizeof(ArrayListNodes));
    list->size = 0;
    list->capacity = capacity;
    list->array = calloc(sizeof(TreeNodePtr), list->capacity);
    return list;
}

void hashmap_delete(ArrayListNodesPtr list, char *key)
{
    /*
        hashmap_delete()
            Worst Case: O((nlog (n/capacity) + log (n/capacity)))
                - n is total number of nodes in the hashmap
                - capacity is number of buckets in the hashmap array
                nlog(n/capacity) is beacause we need to resize the array (deleting, creating, and rehashing each node)
                log n is because we need to insert each node into the array

            Best Case: O(1)
                occurs when there is nothing else in the avl tree at that bucket and we are deleting the root node

            Average Case: O(log(n/capacity))
                - n is total number of nodes in the hashmap
                - capacity is number of buckets in the hashmap array
                on average, we won't need to resize the array, and n/capacity is the number of nodes we have in a bucket
    */

    // delete node with key
    size_t index = hashmap_hash(key, list->capacity);
    TreeNodePtr *treePtr = &(list->array[index]);
    avl_delete(treePtr, key);
    list->size--;
    if (list->size < list->capacity * LOAD_FACTOR_LOWER) // change this
    {
        if (list->capacity <= INITIAL_CAPACITY) // cannot resize to 0
            return;
        hashmap_resize(list, list->capacity / 2);
    }
}

double getLoadFactor(ArrayListNodesPtr list)
{
    return (double)list->size / list->capacity;
}

void hashmap_insert_any(ArrayListNodesPtr list, char *key, int type, void *value)
{
    /*
        hashmap_insert_any()
            Worst Case: O((nlog (n/capacity) + log (n/capacity)))
                - n is total number of nodes in the hashmap
                - capacity is number of buckets in the hashmap array
                nlog(n/capacity) is beacause we need to resize the array (deleting, creating, and rehashing each node)
                log n is because we need to insert each node into the array

            Best Case: O(1)
                occurs when there is nothing else in the avl tree and hashmap array initially, so we have a constant insert time

            Average Case: O(log(n/capacity))
                - n is total number of nodes in the hashmap
                - capacity is number of buckets in the hashmap array
                on average, we won't need to resize the array, and n/capacity is the number of nodes we have in a bucket
    */
    // TODO: check if key already exists, and if it does, just update the key with the new value
    if (list->size > list->capacity * LOAD_FACTOR_UPPER) // change this
        hashmap_resize(list, list->capacity * 2);

    size_t index = hashmap_hash(key, list->capacity);
    // printf("hashindex of %s is %zu\n", key, index);
    list->size++;
    // printf("size: %zu\n", list->size);
    HNodePtr nu = createHNodeAny(key, type, value);

    avl_insert(&(list->array[index]), nu); // nu is now the data that we want to insert into the tree
}

HNodePtr hashmap_get(ArrayListNodesPtr list, char *key)
{
    /*
        hashmap_get()
            Worst: O(1)
                - the maximum number of nodes in the avl tree is 8, which is a bascially-constant search time

            Best: O(1)
                - the minimum number of nodes in each avl tree (on average) is 2, which is a bascially-constant search time

            Average: O(1)
                - the average number of nodes in each avl tree is 4, which is a bascially-constant search time
    */
    // get node with a key
    size_t index = hashmap_hash(key, list->capacity);
    TreeNodePtr bst = list->array[index];
    TreeNodePtr node = avl_find(bst, key);
    if (node == NULL)
    {
        printf("key \"%s\" was not found, returning NULL\n", key);
        return NULL; // node was not found
    }
    else
        return node->data;
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

HNodePtr createHNodeAny(char *key, int type, void *value)
{
    // create HNode
    HNodePtr node = malloc(sizeof(HNode));
    node->key = key;
    node->type = type;
    node->value = value;
    return node;
}

// important functions
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

TreeNodePtr *avl_successor(TreeNodePtr *treePtr)
{
    // find node to succeed a node in avl_delete()
    TreeNodePtr tree = *treePtr;
    if (tree->left == NULL)
        return treePtr;
    return avl_successor(&(tree->left));
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
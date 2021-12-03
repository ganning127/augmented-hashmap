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

/*
    Final Project Report: https://docs.google.com/document/d/1zridcGqDUKdQFI2e_7YKVFYb9zUMmOIzB2rqOThJQ1A/edit?usp=sharing
*/

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
void show_all_buckets(ArrayListNodesPtr list);

int main(void)
{
    ArrayListNodesPtr list = arln_create(INITIAL_CAPACITY);
    char *ins1 = "Ganning";
    unsigned int ins2 = 16;
    double ins3 = 94.53;
    char ins4 = 'A';
    unsigned long ins5 = 123456789;

    char *key1 = "xzRyyIgY5rHzKgdWXFdw";
    char *key2 = "EbI3v03srIID7U510Zl6";
    char *key3 = "dkdFsUiENYylpTnZwGFj";
    char *key4 = "dqa9raqZsj70jgkiJbQ3";
    char *key5 = "E78i3OEDNNkvnxH1NYbM";
    char *key6 = "VfXZNsuqpimj12tzB928";
    char *key7 = "xD2KwCYjJtzk0O1jLfb9";
    char *key8 = "YOzU86hEpC6ntekJWnRy";
    char *key9 = "RwiEgg6b5oYzqcRH6VeU";
    char *key10 = "KcC6thzPQggFYVjE2Ixx";
    char *key11 = "qPYSFTGascyHjO8HtgzS";
    char *key12 = "ao3dftOOPKAl4zIVG4wZ";
    char *key13 = "QISI21CTjUyF0MC04LOm";

    // char *key1 = "key1";
    // char *key2 = "key2";
    // char *key3 = "key3";
    // char *key4 = "key4";
    // char *key5 = "key5";
    // char *key6 = "key6";
    // char *key7 = "key7";
    // char *key8 = "key8";
    // char *key9 = "key9";
    // char *key10 = "key10";
    // char *key11 = "key11";
    // char *key12 = "key12";
    // char *key13 = "key13";

    hashmap_insert_any(list, key1, STRING, ins1);
    hashmap_insert_any(list, key2, UINT, &ins2);
    hashmap_insert_any(list, key3, DOUBLE, &ins3);
    hashmap_insert_any(list, key4, CHAR, &ins4);
    hashmap_insert_any(list, key5, ULONG, &ins5);
    hashmap_insert_any(list, key6, STRING, ins1);
    hashmap_insert_any(list, key7, UINT, &ins2);
    hashmap_insert_any(list, key8, DOUBLE, &ins3);
    hashmap_insert_any(list, key9, CHAR, &ins4);
    hashmap_insert_any(list, key10, ULONG, &ins5);
    hashmap_insert_any(list, key11, STRING, ins1);
    hashmap_insert_any(list, key12, UINT, &ins2);
    hashmap_insert_any(list, key13, DOUBLE, &ins3);

    // hashmap_delete(list, key1);
    // hashmap_delete(list, key2);
    // hashmap_delete(list, key3);
    // hashmap_delete(list, key4);
    // hashmap_delete(list, key5);
    // hashmap_delete(list, key6);
    // hashmap_delete(list, key7);
    // hashmap_delete(list, key8);
    // hashmap_delete(list, key9);
    // hashmap_delete(list, key10);
    // hashmap_delete(list, key11);
    // hashmap_delete(list, key12);
    // hashmap_delete(list, key13);

    // show_all_buckets(list);

    HNodePtr res1 = hashmap_get(list, key1);
    HNodePtr res2 = hashmap_get(list, key2);
    HNodePtr res3 = hashmap_get(list, key3);
    HNodePtr res4 = hashmap_get(list, key4);
    HNodePtr res5 = hashmap_get(list, key5);
    HNodePtr res6 = hashmap_get(list, key6);
    HNodePtr res7 = hashmap_get(list, key7);
    HNodePtr res8 = hashmap_get(list, key8);
    HNodePtr res9 = hashmap_get(list, key9);
    HNodePtr res10 = hashmap_get(list, key10);
    HNodePtr res11 = hashmap_get(list, key11);
    HNodePtr res12 = hashmap_get(list, key12);
    HNodePtr res13 = hashmap_get(list, key13);

    displayNodeValue(res1);
    displayNodeValue(res2);
    displayNodeValue(res3);
    displayNodeValue(res4);
    displayNodeValue(res5);
    displayNodeValue(res6);
    displayNodeValue(res7);
    displayNodeValue(res8);
    displayNodeValue(res9);
    displayNodeValue(res10);
    displayNodeValue(res11);
    displayNodeValue(res12);
    displayNodeValue(res13);

    hashmap_destroy(&list);

    return 0;
}

void show_all_buckets(ArrayListNodesPtr list)
{
    for (size_t i = 0; i < list->capacity; i++)
    {
        printf("Bucket %zu:\n", i);
        if (list->array[i] != NULL)
        {
            avl_print(list->array[i]);
        }
        printf("------------------------\n");
    }
}

void hashmap_destroy(ArrayListNodesPtr *listPtr)
{
    /*
        Destroys the hashmap, freeing all memory allocated to it
    */
    ArrayListNodesPtr list = *listPtr;
    for (size_t i = 0; i < list->capacity; i++) // go through each node in the array
    {
        TreeNodePtr node = list->array[i];

        if (node != NULL)
        {
            // free(node->data);
            avl_destroy(&node); // destroy the AVL tree at that bucket
        }
    }
    free(list->array); // free the array
    free(list);        // free the list
}

void hashmap_resize_helper(TreeNodePtr *newArray, TreeNodePtr bst, size_t new_capacity)
{
    /*
        Goes through each node in the bst and rehashes it into the new, resized hashmap
    */

    if (bst == NULL)
        return;

    hashmap_resize_helper(newArray, bst->left, new_capacity); // recursion to traverse through each node
    hashmap_resize_helper(newArray, bst->right, new_capacity);

    HNodePtr node = createHNodeAny(bst->data->key, bst->data->type, bst->data->value); // create a new node with the same data
    // printf("node key: %s, capacity: %zu\n", node->key, new_capacity);
    size_t hash = hashmap_hash(node->key, new_capacity); // get the hash of the new node

    // printf("new hash of %s is %zu\n", node->key, hash);
    avl_insert(&(newArray[hash]), node); // insert the new node into the new bucket
}

void free_list(ArrayListNodesPtr list)
{
    /*
        Frees the list->array in a hashmap
    */
    for (size_t i = 0; i < list->capacity; i++) // go through each AVL tree at the bucket
    {
        TreeNodePtr node = list->array[i];
        if (node != NULL)
            avl_destroy(&node); // destroy the AVL tree at that bucket
    }
    free(list->array); // free the array
}

void hashmap_resize(ArrayListNodesPtr list, size_t new_capacity)
{
    /*
        Resize the hashmap->array to the new capacity
    */
    TreeNodePtr *newArray = (TreeNodePtr *)calloc(sizeof(TreeNodePtr), new_capacity);

    for (size_t i = 0; i < list->capacity; i++) // go through each bucket in the hashmap
    {
        if (list->array[i] != NULL) //
        {
            // list->array[i] is a TreeNodePtr
            TreeNodePtr node = list->array[i];                   // the root of the BST
            hashmap_resize_helper(newArray, node, new_capacity); // rehash the node into a new BST bucket in the new array
        }
    }

    free_list(list);               // free the old array
    list->array = newArray;        // set the new array with nodes
    list->capacity = new_capacity; // set the new capacity
}

void displayNodeValue(HNodePtr node)
{
    // display the value stored in a node
    if (node == NULL)
        return;

    // go through each node and display the value according to node->type
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
    // create array of TreeNodePtrs (at the size of capacity) that contains each an avl tree
    ArrayListNodes *list = malloc(sizeof(ArrayListNodes));
    list->size = 0;
    list->capacity = capacity;
    list->array = calloc(sizeof(TreeNodePtr), list->capacity);
    return list;
}

void hashmap_delete(ArrayListNodesPtr list, char *key)
{
    /*
        Deletes an element in a hashmap
    */

    size_t index = hashmap_hash(key, list->capacity); // hash of the key
    TreeNodePtr *treePtr = &(list->array[index]);     // pointer to the tree at the bucket
    avl_delete(treePtr, key);                         // delete the node with the key at the bucket
    list->size--;                                     // decrement the size of the hashmap
    if (list->size < list->capacity * LOAD_FACTOR_LOWER)
    {
        if (list->capacity <= INITIAL_CAPACITY) // cannot resize to 0
            return;
        hashmap_resize(list, list->capacity / 2); // half the size of list->array
    }
}

double getLoadFactor(ArrayListNodesPtr list)
{
    return (double)list->size / list->capacity; // get the load factor of the hashmap
}

void hashmap_insert_any(ArrayListNodesPtr list, char *key, int type, void *value)
{
    /*
        insert a node into the hashmap
        TODO: figure out where to put list->size++
    */

    // check if the node is already in there

    size_t index = hashmap_hash(key, list->capacity); // get the hash
    // printf("hashindex of %s is %zu\n", key, index);
    if (avl_find(list->array[index], key) != NULL) // if the node is already in the hashmap
    {
        printf("node already in hashmap\n");
        return;
    }

    // printf("size: %zu\n", list->size);
    HNodePtr nu = createHNodeAny(key, type, value);
    avl_insert(&(list->array[index]), nu);               // nu is now the data that we want to insert into the tree
    list->size++;                                        // increment the size of the hashmap
    if (list->size > list->capacity * LOAD_FACTOR_UPPER) // change this
        hashmap_resize(list, list->capacity * 2);        // double the size of the array
}

HNodePtr hashmap_get(ArrayListNodesPtr list, char *key)
{
    /*
        get the node with the key
    */
    // get node with a key
    size_t index = hashmap_hash(key, list->capacity);
    TreeNodePtr bst = list->array[index];  // get root of tree at the bucket
    TreeNodePtr node = avl_find(bst, key); // find the node with the key in a bucket
    if (node == NULL)
    {
        printf("key \"%s\" was not found, returning NULL\n", key);
        return NULL; // node was not found
    }
    else
        return node->data; // return a HNodePtr
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
    // create HNode (each of the things to be stored in a TreeNode)
    HNodePtr node = malloc(sizeof(HNode));
    node->key = key;
    node->type = type;
    node->value = value;
    return node;
}

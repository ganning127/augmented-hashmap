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
TIME Complexity Analysis
    hashmap_get()
        Worst: O(1)
            - the maximum number of nodes in the avl tree is 8, which is a bascially-constant search time

        Best: O(1)
            - the minimum number of nodes in each avl tree (on average) is 2, which is a bascially-constant search time

        Average: O(1)
            - the average number of nodes in each avl tree is 4, which is a bascially-constant search time

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

SPACE Complexity Analysis
    hashmap_insert_any()
        Worst O(n)
            - n = number of nodes in the tree
            When we resize the hashmap, we need to create a new array of double the current capacity, so we would have allocated 2n space. Therefore, the time complexity is O(n)

        Best O(1)
            If we don't need to resize, then we only malloc the size of the node, which means space allocated is not dependent on the number of nodes in the tree. Therefore, the time complexity is O(1)

        Average O(1)
            On average, we don't need to resize. If we don't need to resize, then we only malloc the size of the node, which means space allocated is not dependent on the number of nodes in the tree. Therefore, the time complexity is O(1)

    hashmap_delete()
        Worst O(n)
            - n = number of nodes in the tree
            When we resize the hashmap, we need to create a new array of half the current capacity, so we would have allocated n/2 space. Therefore, the time complexity is O(n)

        Best O(1)
            If we don't need to resize, then we are not allocating any more memory, so the time complexity is O(1), because it is constant.

        Average O(1)
            On average, we don't need to resize. If we don't need to resize, then we are not allocating any more memory, so the time complexity is O(1), because it is constant.

    hashmap_destroy()
        Best Case: O(1)
            we are not allocating any more memory in this function, so O(1) is the space complexity

        Worst Case: O(1)
            we are not allocating any more memory in this function, so O(1) is the space complexity

        Average Case: O(1)
            we are not allocating any more memory in this function, so O(1) is the space complexity

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

// Main Functions

void hashmap_delete(ArrayListNodesPtr list, char *key)
{
    /*

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

void hashmap_destroy(ArrayListNodesPtr *listPtr)
{
    /*

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

void hashmap_insert_any(ArrayListNodesPtr list, char *key, int type, void *value)
{
    /*

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

// Helper Functions

void hashmap_resize_helper(TreeNodePtr *newArray, TreeNodePtr bst, size_t new_capacity)
{

    if (bst == NULL)
        return;

    hashmap_resize_helper(newArray, bst->left, new_capacity);
    hashmap_resize_helper(newArray, bst->right, new_capacity);

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

double getLoadFactor(ArrayListNodesPtr list)
{
    return (double)list->size / list->capacity;
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

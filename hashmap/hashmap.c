#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#define INITIAL_SIZE 8

typedef struct hash_node
{
    char *key;
    int value;
} HNode;
typedef HNode *HNodePtr;

typedef struct tree_node
{
    HNodePtr data; // each node in the bst should hold a HNode
    struct node *left;
    struct node *right;
    size_t height;
} TreeNode;
typedef TreeNode *TreeNodePtr;

typedef struct arraylist_nodes
{
    TreeNodePtr *array; // array of avl trees
    size_t size;
    size_t capacity;
} ArrayListNodes;
typedef ArrayListNodes *ArrayListNodesPtr;

size_t hashmap_hash(char *str, size_t size);
void hashmap_insert(ArrayListNodesPtr list, char *key, int value);

int main(void)
{
}

void hashmap_insert(ArrayListNodesPtr list, char *key, int value)
{
    size_t index = hashmap_hash(key, list->size);
    HNodePtr nu = malloc(sizeof(HNode));
    nu->key = key;
    nu->value = value;
    // nu is now the data that we want to insert into the tree

    avl_insert(list->array[index], nu);
}

ArrayListNodes *arln_create()
{
    ArrayListNodes *list = malloc(sizeof(ArrayListNodes));
    list->size = 0;
    list->capacity = INITIAL_SIZE;
    list->array = calloc(sizeof(HNode *), INITIAL_SIZE);
    // set all the pointers to NULL
    for (size_t i = 0; i < list->capacity; i++)
    {
        list->array[i] = NULL;
    }
    return list;
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 1
#define LOAD_FACTOR 0.75

typedef struct hash_node
{
    char *key;
    int value;
} HNode;
typedef HNode *HNodePtr;

typedef struct tree_node
{
    HNodePtr data; // each node in the bst should hold a HNode
    struct tree_node *left;
    struct tree_node *right;
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

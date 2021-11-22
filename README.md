# Augmented Hashmaps
A hashmap will be created that uses strings as keys, and anything (int, double, char, pointers) can be stored as a value. A self-balancing binary tree (implemented as an AVL tree) will be used as buckets, with the binary tree being sorted alphabetically based on the key. 

[Flowchart](https://lucid.app/lucidchart/97708b42-f8a6-4c86-858a-336336a771f1/edit?viewport_loc=-539%2C-364%2C3344%2C1912%2C0_0&invitationId=inv_862a9d94-973f-45d0-a7f3-96b0b57e108b)
[Augmented Hashmap Proposal](https://docs.google.com/document/d/16vmH7m28tknDMgWL7Yi4Lc_VVIr36cQQlZQSkLTCZEY/edit?usp=sharing)

## Basic AVL Documentation (`./avl_tree/avl_tree.c`)
**Node Declaration**
```c
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
    size_t height;
} Node;
```

**Inserting a node**

`void avl_insert(NodePtr *<root>, int <data>);`
- `<root>` double pointer to the address of the avl tree you want to add to
- `<data>` integer for the value in the avl tree to add

**Deleting a node**

`void avl_delete(NodePtr *<root>, int <data>);`
- `<root>` double pointer to the address of the avl tree you want to delete from
- `<data>` integer for the value in the avl tree to delete

## Hashmap Documentation
**Hash Node Declaration**
```c
typedef struct hash_node
{
    char *key;
    int value;
} HNode;
typedef HNode *HNodePtr;
```

**Tree Node Declaration**
```c
typedef struct tree_node
{
    HNodePtr data; // each node in the bst should hold a HNode
    struct tree_node *left;
    struct tree_node *right;
    size_t height;
} TreeNode;
typedef TreeNode *TreeNodePtr;
```

**ArrayList Nodes Declaration**
```c
typedef struct arraylist_nodes
{
    TreeNodePtr *array; // array of avl trees
    size_t size;
    size_t capacity;
} ArrayListNodes;
typedef ArrayListNodes *ArrayListNodesPtr;
```

**Inserting a key-value pair**

`void hashmap_insert(ArrayListNodesPtr <list>, char *<key>, int <value>)`

- `<list>` pointer to the arraylist that represents the hashmap
- `<key>` string that is used to access the value
- `<value>` integer that is the value of the key

**Deleting a key-value pair**

`void hashmap_delete(ArrayListNodesPtr <list>, char *<key>);`

- `<list>` pointer to the arraylist that represents the hashmap
- `<key>` string representing the key that you want to delete from the hashmap

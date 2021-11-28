## Integer Hashmap Documentation (`./hashmap_int/hashmap.c`)
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

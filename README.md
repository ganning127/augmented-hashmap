# Augmented Hashmaps
A hashmap will be created that uses strings as keys, and anything (int, double, char, pointers) can be stored as a value. A self-balancing binary tree (implemented as an AVL tree) will be used as buckets, with the binary tree being sorted alphabetically based on the key. 

[Augmented Hashmap Proposal](https://docs.google.com/document/d/16vmH7m28tknDMgWL7Yi4Lc_VVIr36cQQlZQSkLTCZEY/edit?usp=sharing)

## AVL Documentation
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
`void avl_insert(NodePtr *root, int data);`
- `<root>` double pointer to the address of the avl tree you want to add to
- `<data>` integer for the value in the avl tree to add

**Deleting a node**
`void avl_delete(NodePtr *root, int data);`
- `<root>` double pointer to the address of the avl tree you want to delete from
- `<data>` integer for the value in the avl tree to delete


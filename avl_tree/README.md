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
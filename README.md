# Augmented Hashmaps
A hashmap will be created that uses strings as keys, and anything (int, double, char, pointers) can be stored as a value. A self-balancing binary tree (implemented as an AVL tree) will be used as buckets, with the binary tree being sorted alphabetically based on the key. 

- [Flowchart](https://lucid.app/lucidchart/97708b42-f8a6-4c86-858a-336336a771f1/edit?viewport_loc=-539%2C-364%2C3344%2C1912%2C0_0&invitationId=inv_862a9d94-973f-45d0-a7f3-96b0b57e108b)
- [Diagram of Structs](https://lucid.app/lucidchart/63087032-e879-4336-b733-5d66e6890126/edit?viewport_loc=-523%2C-303%2C3072%2C1756%2C0_0&invitationId=inv_714e5a29-1b9d-41ff-bf4a-6608ef753295)
- [Augmented Hashmap Proposal](https://docs.google.com/document/d/16vmH7m28tknDMgWL7Yi4Lc_VVIr36cQQlZQSkLTCZEY/edit?usp=sharing)

## Hashmap Documentation `./hashmap_any/hashmap.c`
This hashmap works with any data type!

**Hash Node Declaration**
```c
typedef struct hash_node
{
    char *key;
    int type;
    void *value;
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

### Inserting a Node
`void hashmap_insert_any(ArrayListNodesPtr <list>, char *<key>, int <type>, void *<value>)`
- `<list>` pointer to the arraylist that represents the hashmap
- `<key>` string that is used to access the value
- `<type>` integer constant that specifies the type of data you want to insert (see below).
- `<value>` pointer to the value you want to store

Avaliable types (users can add as necessary)
```c
enum
{
    INT = 1,
    STRING = 2,
    DOUBLE = 3,
    CHAR = 4,
    UINT = 5,
    ULONG = 6,
};
```

### Getting Values 
`HNodePtr hashmap_get(ArrayListNodesPtr list, char *key);`
**Return type:** Pointer to a hash node (see above).

- `<list>` pointer to the arraylist that represents the hashmap
- `<key>` string that is used to access a previously inserted value

### Deleting Values
`void hashmap_delete(ArrayListNodesPtr list, char *key);`
- `<list>` pointer to the arraylist that represents the hashmap
- `<key>` string that is used to delete a previously inserted value

**Example Usage**
```c
ArrayListNodesPtr list = arln_create(INITIAL_CAPACITY);
char *ins1 = "Ganning";
unsigned int ins2 = 16;

hashmap_insert_any(list, "name", STRING, ins1);
hashmap_insert_any(list, "age", UINT, &ins2);

HNodePtr res1 = hashmap_get(list, "name");
HNodePtr res2 = hashmap_get(list, "age");

displayNodeValue(res1);
displayNodeValue(res2);
```





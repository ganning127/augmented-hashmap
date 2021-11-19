typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
    size_t height;
} Node;
typedef Node *NodePtr;
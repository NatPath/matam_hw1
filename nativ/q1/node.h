#ifndef NODE_H_
#define NODE_H_
#include <stdbool.h>

typedef struct node_t{
    int x;
    struct node_t *next;
} *Node;
typedef enum {
    SUCCESS=0,
    MEMORY_ERROR,
    EMPTY_LIST,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;
Node createNode(int val,Node next);
void destroyNode(Node toDelete);
ErrorCode createAndAdvance(Node *node,int val);
ErrorCode createFromArray(int arr[],int size,Node *res_node);
void printNode(Node node);

int getListLength(Node list);
bool isListSorted(Node list);

Node lastElem(Node list);

//appends list2 after list1
ErrorCode appendLists(Node list1,Node list2);
ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out);

#endif
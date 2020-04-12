#include "node.h"
#include <stdlib.h>
#include <stdio.h>
int main(){
    int arr1[8]={1,2,3,4,5,6,7,8};
    int arr2[3]={3,4,5};
    Node node1=NULL;
    Node node2=NULL;
    ErrorCode ret1=createFromArray(arr1,8,&node1);
    ErrorCode ret2=createFromArray(arr2,3,&node2);
    if (ret1!=SUCCESS){
        printf("Error: %d",ret1);
        return ret1;
    }
    printf("Node1 is:\n");
    printNode(node1);
    printf("Node2 is:\n");
    printNode(node2);
    
    Node node3=NULL;
    mergeSortedLists(node1,node2,&node3);
    printf("Node3:\n");
    printNode(node3);
    destroyNode(node1);
    destroyNode(node2);
    destroyNode(node3);
    return 0;
}
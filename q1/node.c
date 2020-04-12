#include "node.h"
#include <stdlib.h>
#include <stdio.h>


Node createNode(int x,Node next){
    Node new_node=malloc(sizeof(*new_node));
    if(!new_node){
        return NULL;
    }
    new_node->x=x;
    new_node->next=next;
    return new_node;
}
void destroyNode(Node node){
    while(node){
        Node temp=node;
        node=node->next;
        free(temp);
    }
}
ErrorCode createAndAdvance(Node *node,int val){
    Node new_node=createNode(val,NULL);
    if(!new_node){
        return MEMORY_ERROR;
    }
    (*node)->next=new_node;
    *node=new_node;
    return SUCCESS;
}
ErrorCode createFromArray(int arr[],int size,Node *res_node){
    Node head=createNode(arr[0],NULL);
    Node pointer=head;
    if (!head){
        return MEMORY_ERROR;
    }
    for (int i=1;i<size;i++){
        ErrorCode ret=createAndAdvance(&pointer,arr[i]);
        if(ret!=SUCCESS){
            return ret;
        }
    }
    *res_node=head;
    return SUCCESS;
}

void printNode(Node node){
    while(node){
        printf("%d,",node->x);
        node=node->next;
    }
    printf("\n");
}

int getListLength(Node list){
    int i=0;
    while (list){
        i++;
        list=list->next;
    }
    return i;
}
bool isListSorted(Node list){
    if (!list){
        printf("list is empty\n");
        return true;
    }
    int initial_value=list->x;
    list=list->next;
    while(list){
        if (list->x<initial_value){
            return false;
        }
        list=list->next;       
    }
    return true;
}
Node lastElem(Node list){
    while(list->next){
        list=list->next;
    }
    return list;
    
}
ErrorCode appendLists(Node list1, Node list2){
    Node last_of_list1=lastElem(list1);
    while(list2){
        ErrorCode ret=createAndAdvance(&last_of_list1,list2->x);
        if (ret!=SUCCESS){
            return ret;
        }

    }
}
ErrorCode mergeSortedLists(Node list1,Node list2, Node *merged_out){
    Node fake_node=createNode(-1,NULL);
    *merged_out=NULL;
    if (!fake_node){
        return MEMORY_ERROR;
    }
    Node pointer=fake_node;
    while (list1&&list2){
        int list1_val=list1->x;
        int list2_val=list2->x;
        int min_val;
        if (list1_val < list2_val){
            min_val=list1_val; 
            list1=list1->next;
        }
        else{
            min_val=list2_val;
            list2=list2->next;
        }
        ErrorCode ret=createAndAdvance(&pointer,min_val);
        if (ret!=SUCCESS){
            destroyNode(fake_node);
            return ret;
        }
    }
    while(list1){
        ErrorCode ret=createAndAdvance(&pointer,list1->x);
        if (ret!=SUCCESS){
            destroyNode(fake_node);
            return ret;
        }
        list1=list1->next;
    }
    while(list2){
        ErrorCode ret=createAndAdvance(&pointer,list2->x);
        if (ret!=SUCCESS){
            destroyNode(fake_node);
            return ret;
        }
        list2=list2->next;
    }
    *merged_out=fake_node->next;
    free(fake_node);
    if(getListLength(*merged_out)==0){
        return EMPTY_LIST;
    }
    return SUCCESS;
}

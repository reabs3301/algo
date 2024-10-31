#define bool unsigned int
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>



typedef struct node{
    int value ;
    struct node *next;
    struct node *prev;
    
    void (* insert)(struct node * , int);
    void (* delete)(struct node * , int);
    bool (* research)(struct node * , int);
}node;


void insert(node *head , int data){
    
    node *element = (node*)malloc(sizeof(node));

    element->value = data;
    element->next = NULL;
    element->prev = NULL; 
    
    if(head->next == NULL){
        head->next = element;
        element->prev = head;
    }else{
        node *q = head;
        
        while(q->next != NULL && q->next->value < data ){
            q=q->next;
        }
        if(q->next == NULL){
            q->next = element;
            element->prev = q;
        }
        else{
            element->next = q->next ;
            q->next = element;
            element->prev = q;
            element->next->prev = element;
        }
        

    }
}

void delete(node *head , int val){

    node *q = head->next ;

    while(q != NULL && q->value != val){
        q = q->next;
    }

    if(q == NULL){
        printf("data %d not found :( \n",val);
    }
    else{
        q->prev->next = q->next;
        q->next->prev = q->prev;
        q->next = NULL;
        q->prev = NULL;

        free(q);
    }



}
void print(node *head){

    node *q = head ;

    for(q = head->next ; q != NULL ; q = q->next){
        printf("data : %d\n",q->value);
    }

    free(q);
}

int main(){

    node *head = (node*)malloc(sizeof(node));

    head->insert = insert;
    head->delete = delete;
    head->next = NULL;
    head->prev = NULL;
    head->value = 0;
    
    print(head);

    head->insert(head , 3);
    head->insert(head , 4);
    head->insert(head , 7);
    head->insert(head , 6);
    head->insert(head , 5);
    head->insert(head , 2);
    head->insert(head , 1);
    
    print(head);
    printf("after deleting\n");

    head->delete(head , 5);
    head->delete(head , 1);
    head->delete(head , 10);

    print(head);

    return 0;
}

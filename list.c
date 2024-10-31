#define bool unsigned int
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>



typedef struct node{
    int value ;
    struct node *next;
    struct node *prev;
    
    void (* insert)(struct node * , int , struct node *);
    void (* delete)(struct node * , int , struct node *);
    bool (* research)(struct node * , int);
}node;


void insert(node *head , int data , node *tail){
    
    node *element = (node*)malloc(sizeof(node));

    element->value = data;
    element->next = NULL;
    element->prev = NULL; 
    
    if(head->next == NULL){
        head->next = element;
        element->prev = head;
        tail->prev = element;
    }else{
        node *q = head;
        
        while(q->next != NULL && q->next->value < data ){
            q=q->next;
        }
        if(q->next == NULL){
            q->next = element;
            element->prev = q;
            tail->prev = q->next;
        }
        else{
            element->next = q->next ;
            q->next = element;
            element->prev = q;
            element->next->prev = element;
        }
        

    }

    
}

void delete(node *head , int val , node *tail){

    node *q = head->next ;
    //node *p;
    while(q != NULL && q->value != val){
        q = q->next;
    }

    if(q == NULL){
        printf("data %d not found :( \n",val);
    }
    else{
        if(q->next == NULL){
            
            tail->prev = q->prev;
            q->prev->next = NULL;
            free(q);
        }else{
        q->prev->next = q->next;
        q->next->prev = q->prev;
        q->next = NULL;
        q->prev = NULL;
        free(q);
        }
    }

}

bool research(node *head , int val){


    if(val < head->value )

    return false;
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
    node *tail = (node*)malloc(sizeof(node));

    head->insert = insert;
    head->delete = delete;
    head->next = NULL;
    head->prev = NULL;
    head->value = 0;
    
    tail->insert = insert;
    tail->delete = delete;
    tail->next = NULL;
    tail->prev = NULL ;
    tail->value = 0;

    print(head);

    head->insert(head , 3 , tail);
    head->insert(head , 4 , tail);
    head->insert(head , 7 , tail);
    head->insert(head , 6 , tail);
    head->insert(head , 5 , tail);
    head->insert(head , 2 , tail);
    head->insert(head , 1 , tail);
    
    print(head);
    printf("after deleting\n");

    head->delete(head , 5 , tail);
    head->delete(head , 1 , tail);
    head->delete(head , 10 , tail);
    head->delete(head , 7 , tail);

    print(head);
    printf("\n%d\n",tail->prev->value);

    return 0;
}

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct Item{

    int ID,time;
    struct Item *next;

};

struct Queue{

    Item *head;
    Item *tail;
    Item *proc;
    Item *curr;
    int size;
};

struct Stack{

    Item *top;
    int size;
};

Queue *create_queue(){

    Queue *q = new Queue();
    q->size = 0;
    Item *sentinel = new Item();

    q->head = sentinel;
    q->tail = sentinel;
    sentinel->next = NULL;

    return q;
}

void insert_queue(Queue *queue, int id, int time){

    Item *novo = new Item();
    novo->ID=id;
    novo->time=time;

    queue->tail->next=novo;
    queue->tail=novo;
    queue->size++;
}

Item* dequeue(Queue *queue){

    if (queue->size!=0){

        Item *temp = queue->head->next;
        queue->head->next = temp->next;

        if (temp == queue->tail){
            queue->tail = queue->head;
        }
        queue->size--;
        return temp;
    } 
    return NULL;
}

void enqueue_circular(Queue *queue, Item *item){
    
    queue->tail->next=item;
    queue->tail = queue->tail->next;
    
    queue->size++;

}

void spin(Queue *queue){

    Item *temp = dequeue(queue);
    insert_queue(queue, temp->ID, temp->time);

}

Item* dequeue_circular(Queue *queue){

    if(queue->size != 0){
        queue->curr = queue->head->next;
        Item *temp = queue->tail;

        if (queue->size > 1){
            while(queue->curr->next->next != NULL) {
                queue->curr=queue->curr->next;
            }
            queue->tail = queue->curr;
            queue->tail->next= NULL;
        }
        else {
            queue->tail =  queue->head;
        }
        queue->size--;
        return temp;
    }
    return NULL;
}

Stack *create_stack(){

    Stack *s = new Stack();
    s->size = 0;
    Item *sentinel = new Item();

    s->top = sentinel;
    sentinel->next = NULL;

    return s;
}

void push_stack(Stack *stack, Item *item){ 

    Item *novo = new Item();
    novo->ID=item->ID;
    novo->time=item->time;

    novo->next=stack->top->next;
    stack->top->next=novo;

    stack->size++;

}

int pop_stack(Stack *stack){

    if (stack->size!=0){

        Item *temp = stack->top->next;
        int id_temp = stack->top->next->ID; 
        stack->top->next=stack->top->next->next;

        delete temp;
        stack->size--;

        return id_temp;
    }
    return -1;
}

int main (){

    Queue *queue=create_queue();
    Stack *stack=create_stack();
    Queue *circular_queue=create_queue();

    int id, time, k;
    string command = "mila";

    cin >> k;

    while(command != "END"){
        cin >> command;

        if (command == "LOAD"){
            cin >> id >> time;
            insert_queue(queue, id, time);
        }
        else if (command == "PROC"){

            if (circular_queue->size > 0){
                if(circular_queue->tail->time == 0){
                    push_stack(stack, dequeue_circular(circular_queue));
                }
            }

            if(queue->size > 0){
                enqueue_circular(circular_queue, dequeue(queue));
            }

            if(circular_queue->size > 0){
                circular_queue->head->next->time -= k;
                if (circular_queue->head->next->time < 0){
                    circular_queue->head->next->time = 0;
                }

                cout << "PROC " << circular_queue->head->next->ID << " " << circular_queue->head->next->time << endl;

                if(circular_queue->size > 1){
                    spin(circular_queue);
                }
            } else {
                cout << "PROC -1 -1" << endl;
            }
        }
        else if (command == "UNLD") {
            cout << "UNLD" << " " << pop_stack(stack) << endl;
        }

    }

   return 0;
}
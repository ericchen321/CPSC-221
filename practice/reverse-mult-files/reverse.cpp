#include <iostream>
#include "node.h"
#include "reverse.h"
using namespace std;

// requires: a is non-NULL
// effects: inserts node a to the end of the linked list starting from head;
//          returns the head
node* insert_to_end(node* a, node* head){
    a->next = NULL;
    if (head == NULL){
        return a;
    }
    if (head->next == NULL){
        head->next = a;
        return head;
    }
    insert_to_end(a, head->next);
    return head;
}

node* reverse(node* curr){
    if (curr == NULL){
        return curr;
    }
    return insert_to_end(curr, reverse(curr->next));
}
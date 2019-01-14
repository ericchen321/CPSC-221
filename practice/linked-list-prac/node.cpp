#include <iostream>
#include "node.h"

    node::node(int newData){
        data = newData;
        next = NULL;
    }

    void node::print(node* head){
        if (head == NULL){
        return;
    }
        std::cout << head->data << " ";
        print(head->next);
    }

    node* node::reverse(node* curr){
        if (curr != NULL && curr->next != NULL){
        node *t = curr->next;
        node *rR = reverse(curr->next);
        t->next = curr;
        curr->next = NULL;
        return rR;
    }
        return curr;
    }

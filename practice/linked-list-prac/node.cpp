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

    // requires: pos >= 1
    // effects: prints the linked list starting from curr in reversed
    //          order; if pos is odd then print, otherwise do not print
    void printReverseODDS_helper(node* curr, int pos){
        if (curr != NULL){
            printReverseODDS_helper(curr->next, pos+1);
            if (pos % 2 == 1)
                std::cout << curr->data << " ";
        }
    }

    void node::printReverseODDS(node* curr){
        printReverseODDS_helper(curr, 1);
    }

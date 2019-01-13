#include <iostream>
#include "node.h"
#include "print.h"

using namespace std;

void print(node* head){
    if (head == NULL){
        return;
    }
    cout << head->data << " ";
    print(head->next);
}
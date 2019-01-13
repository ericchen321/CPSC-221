/*
practice goal: use debugger
*/

#include <iostream>

using namespace std;

class node{
    public:
        int data;
        node *next;
        node(int newData){
            data = newData;
            next = NULL;
        };
};

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

// effects: returns ptr to the head of the reversed linked list
node* reverse(node* curr){
    if (curr == NULL){
        return curr;
    }
    return insert_to_end(curr, reverse(curr->next));
}

// effects: prints the linked list starting from head
void print(node* head){
    if (head == NULL){
        return;
    }
    cout << head->data << " ";
    print(head->next);
}

int main(){    
    node *n[3];
    n[0] = new node(1);
    n[1] = new node(2);
    n[2] = new node(3);
    for(int i=0; i<=1;i++){
        n[i]->next = n[i+1];
    }
    n[2]->next = NULL;
    
    print(n[0]);
    cout << endl;
    node *n_rev = reverse(n[0]);
    print(n_rev);
    cout << endl;
    
    for(int i=0; i<3; i++){
        delete n[i];
    }
    
}
#ifndef NODE_H
#define NODE_H

class node{
    public:
        int data;
        node *next;
        node(int newData);

        // effects: prints the linked list starting from head
        void print(node* head);

        // effects: returns ptr to the head of the reversed linked list
        node* reverse(node* curr);
};

#endif
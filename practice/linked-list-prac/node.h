#ifndef NODE_H
#define NODE_H

class node{
    public:
        int data;
        node *next;
        node(int newData);

        // effects: prints the linked list starting from head
        static void print(node* head);

        // effects: returns ptr to the head of the reversed linked list
        static node* reverse(node* curr);

        // effects: print the linked list starting from given node in reversed
        //          order, and only prints values at odd indicies (1-based
        //          indexing)
        static void printReverseODDS(node* curr);
    
    private:
        // requires: pos >= 1
        // effects: prints the linked list starting from curr in reversed
        //          order; if pos is odd then print, otherwise do not print
        static void printReverseODDS(node* curr, int pos);
};

#endif
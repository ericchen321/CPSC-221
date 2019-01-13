#ifndef REVERSE_H
#define REVERSE_H

#include "node.h"

// requires: a is non-NULL
// effects: inserts node a to the end of the linked list starting from head;
//          returns the head
node* insert_to_end(node* a, node* head);

// effects: returns ptr to the head of the reversed linked list
node* reverse(node* curr);

#endif
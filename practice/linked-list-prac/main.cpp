#include <iostream>
#include "node.h"
using namespace std;

int main(){
    node *n[5];
    n[0] = new node(8);
    n[1] = new node(2);
    n[2] = new node(4);
    n[3] = new node(6);
    n[4] = new node(3);
    for(int i=0; i<=3;i++){
        n[i]->next = n[i+1];
    }
    n[4]->next = NULL;

    /* testing reverse
    node::print(n[0]);
    cout << endl;
    node *n_rev = node::reverse(n[0]);
    node::print(n_rev);
    cout << endl;
    */

   /* testing printReverseODDS
   */
    node::printReverseODDS(n[0]);
    cout << endl;
    
    for(int i=0; i<5; i++){
        delete n[i];
    }
}

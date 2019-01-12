#include <iostream>
using namespace std;

int main(){
    int * a = new int(5);
    int * b = a;
    delete a;
    cout << *a << endl; // expects random output
    cout << *b << endl; // same as above

    a = NULL;
    cout << *a << endl; // seg fault - invalid mem access
}
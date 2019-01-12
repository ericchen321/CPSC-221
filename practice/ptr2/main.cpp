#include <iostream>

using namespace std;

int main(){
    int size = 5;
    int x[size];

    for(int i=0; i<size; i++){
        x[i] = i;
        cout << x[i];
    }
}
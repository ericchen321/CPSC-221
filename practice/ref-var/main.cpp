#include <iostream>

using namespace std;

int & hello(int n){
    int *num = new int(n);
    return *num;
}

int main(){
    int &a = hello(5);
    cout << a << endl;
    delete &a;
}
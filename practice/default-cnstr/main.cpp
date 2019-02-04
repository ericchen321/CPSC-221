#include <iostream>

using namespace std;

class A{
public:
    int a;
    A(){
      cout << "A's constructor called" << endl;
    }
};

int main(){
  A objA;
}
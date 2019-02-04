#include <iostream>
#include <vector>

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
  int *ptr = new int(3); // check if memory leak happens without explictly delete
                         // result: yes for primary types without explict deletetion, will have mem leak
  delete ptr;
  vector<int> v;
  v.push_back(99);       // vectors of primary types on the other hand don't need to worry about deallocation
}
#include <iostream>

using namespace std;

int main(){
  int** ptr; // ptr to a ptr of type int
  ptr = new int*();
  int num[2]={9,10};
  *ptr = num;
  cout << **ptr << endl;
}
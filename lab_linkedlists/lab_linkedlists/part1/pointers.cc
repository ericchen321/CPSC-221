#include <iostream>

using namespace std;

int main () {
  int x = 5, y = 15;
  int * p1, *p2;

  cout << "\nvalue of\t\tx\ty\tp1\t\tp2" << endl;
  cout << "\t\t\t5\t15\tuninit\t\tuninit" << endl;

  p1 = &x;
  cout << "(1) p1 = &x:\t\t" <<  x << "\t" << y << "\t" << p1 << "\tuninit" << endl; 
 
  p2 = &y;
  cout << "(2) p2 = &y:\t\t" <<  x << "\t" << y << "\t" << p1 << "\t" << p2 << endl; 
  
  *p1 = 6;
  cout << "(3) *p1 = 6:\t\t" <<  x << "\t" << y << "\t" << p1 << "\t" << p2 << endl; 
  
  *p1 = *p2; 
  cout << "(4) *p1 = *p2:\t\t" <<  x << "\t" << y << "\t" << p1 << "\t" << p2 << endl; 
  
  p2 = p1; 
  cout << "(5) p2 = p1:\t\t" <<  x << "\t" << y << "\t" << p1 << "\t" << p2 << endl; 
  
  *p1 = *p2+10;
  cout << "(6) *p1 = *p2+10:\t" <<  x << "\t" << y << "\t" << p1 << "\t" << p2 << endl << endl; 
  
  return 0;
}

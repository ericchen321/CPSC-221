//
// You can change this file by adding additional tests but don't
// remove any existing tests.
//
#include <iostream>
#include <string> 
#include <vector> 
#include <sstream>
#include <initializer_list>
#include "linked_list.h"

using namespace std;

// list_test uses initializer_lists from C++11 to pass the expected
// contents of the list.  This allows writing new tests to be pretty
// straight-forward. See the examples below where list_test is used to
// check the contents of linked lists after operations are performed.
string vectorStr( vector<int>& v ) {
  stringstream os;
  os << "[";
  for( unsigned int i=0; i < v.size(); i++ ) {
    os << v[i];
    if( i < v.size()-1 ) os << ", ";
  }
  os << "]";
  return os.str();
}

void list_test( string msg, Node *actual,
		initializer_list<int> expect ) {
  vector<int> act = to_vector( actual );
  vector<int> exp;
  cout << msg << ": ";
  print( actual );
  for( auto elem : expect ) {
    exp.push_back(elem);
  }
  if( act == exp ) return;
  cerr << "*ERROR* " << vectorStr(act) << " != (expected) "
       << vectorStr(exp) << "\n";
}

int main() {
  Node * list1 = NULL;
  Node * list2 = NULL;
  Node * list3 = NULL;

  insert( list1, 1);
  insert( list1, 2);
  insert( list1, 3);

  list_test("<A> list1", list1, {3,2,1});

  insert( list2, 10);
  insert( list2, 9);
  insert( list2, 8);
  insert( list2, 7);
  insert( list2, 6);

  list_test("<B> list2", list2, {6,7,8,9,10});

  delete_last_element( list1 );

  list_test("<C> delete_last_element(list1)", list1, {3,2});

  delete_last_element( list1 );

  list_test("<D> delete_last_element(list1)", list1, {3});

  delete_last_element( list1 );
  // list1 is now empty

  list_test("<E> delete_last_element(list1)", list1, {});

  insert( list1, 15 ); 
  insert( list1, 10 ); 
  insert( list1,  5 ); 

  list_test("<F> list1", list1, {5,10,15});

  remove( list1, 10 );

  list_test("<F> remove(list1,10)", list1, {5,15});

  remove( list1, 15 ); 

  list_test("<F> remove(list1,15)", list1, {5});

  remove( list1, 5 ); 
  // list1 is now empty again

  list_test("<F> remove(list1,5)", list1, {});

  insert(list1, 11);			// list1 = [11]

  list_test("<G> list1", list1, {11});

  insert_after(list1, 11, 12);		// list1 = [11,12]

  list_test("<G> insert_after(list1,11,12)", list1, {11,12});

  insert_after(list1, 13, 14);

  list_test("<H> insert_after(list1,13,14)", list1, {11,12});

  insert_after(list1, 11, 12);		// list1 = [11,12,12]

  list_test("<I> insert_after(list1,11,12)", list1, {11,12,12});

  delete_last_element( list1 );		// list1 = [11,12]

  list_test("<J> delete_last_element(list1)", list1, {11,12});

  list3 = interleave(list1, list2);

  list_test("<K> interleave(list1,list2)", list3, {11,6,12,7,8,9,10});
  while( list3 ) delete_last_element(list3);

  list3 = interleave(list2, list2);

  list_test("<L> interleave(list2,list2)", list3, {6,6,7,7,8,8,9,9,10,10});
  while( list3 ) delete_last_element(list3);

  list3 = interleave(list1, NULL);

  list_test("<M> interleave(list1,NULL)", list3, {11,12});
  while( list3 ) delete_last_element(list3);

  list3 = interleave(NULL, list2);

  list_test("<N> interleave(NULL,list2)", list3, {6,7,8,9,10});
  while( list3 ) delete_last_element(list3);

  list3 = interleave(NULL, NULL);

  list_test("<O> interleave(NULL,NULL)", list3, {});
  while( list3 ) delete_last_element(list3);


  while( list1 ) delete_last_element(list1);
  while( list2 ) delete_last_element(list2);

#ifdef _WIN32
  system("PAUSE"); // needed for windows to prevent the program from terminating and the command window to close
#endif

  return 0;
}

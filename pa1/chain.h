
/**
 *
 * Circular Doubly Linked List (PA 1)
 * with head sentinel.
 *
 */

#ifndef _CHAIN_H_
#define _CHAIN_H_

#include <algorithm>
#include <iostream>
#include "block.h"
using namespace std;

/**
 * Chain: This is a container class for blocks. It is implemented
 * as a linked list of nodes, each of which contains a block.
 *
 * You should not remove anything from this class definition, but
 * you may find it helpful to add your own private helper functions to it.
 */

class Chain {
private:

   /**
    * The Node class is private to the List class via the principle of
    * encapsulation---the end user does not need to know our node-based
    * implementation details.
    */
   class Node {
   public:
      Node(); // default constructor--GIVEN
      Node(const Block & ndata); // data provided constructor--GIVEN

      Node * next; // ptr to next node in chain if one exists, NULL o/w
      Node * prev; // ptr to prev node in chain if one exists, NULL o/w
      const Block data; // data held by Node. const for this PA
   };

public:

   /* =============== public given functions ====================*/
   /**
    * Default Chain constructor. GIVEN
    * Creates an empty Chain. Implemented for you.
    * Note that in this implementation, the empty chain consists of a head
    * sentinel node and a tail sentinel node, and no data between.
    * @see chain_given.cpp
    */
   Chain();

   /**
    * Constructor that breaks the given PNG into
    * cols blocks and builds a chain of those
    * blocks. This constructor is GIVEN
    * @see chain_given.cpp
    */
   Chain(PNG & imIn, int cols);

   /**
    * Copy constructor for a Chain. GIVEN
    * Since Chains allocate dynamic memory (i.e., they use "new", we
    * must define the Big Three). This depends on your implementation
    * of the copy funtion.
    * @see chain_given.cpp
    *
    * @param other The Chain  we are copying.
    */
   Chain(const Chain & other);

   /**
    * Overloaded assignment operator for Chains. GIVEN
    * Part of the Big Three that we must define because the class
    * allocates dynamic memory. This depends on your implementation
    * of the copy and clear funtions.
    * @see chain_given.cpp
    *
    * @param rhs The right hand side of the assignment statement.
    */
   Chain & operator=(const Chain & rhs);

   /**
    * Gets the size of the Chain. GIVEN
    * Defined as a const function because it promises not to modify
    * the current Chain in any way.
    * @see chain_given.cpp
    *
    * @return The number of data elements in the current Chain.
    */
   int size() const;

   /**
    * Determines if the current Chain is empty. GIVEN
    * Const because it promises not to modify the current Chain.
    * @see chain_given.cpp
    *
    * @return Boolean value of whether the current Chain is empty.
    */
   bool empty() const;

   /**
    * Render returns an image consisting of the first
    * cols blocks in the chain. Returns an empty image if
    * the chain is too short. GIVEN
    * @see chain_given.cpp
    */
   PNG render(int cols);

   /**
    * RenderBack returns an image consisting of the last
    * cols blocks in the chain. Returns an empty image if
    * the chain is too short. GIVEN
    * @see chain_given.cpp
    */
   PNG renderBack(int cols);

   /* =============== end of given functions ====================*/

   /* =============== public PA1 FUNCTIONS =========================*/

   /**
    * Chain destructor.
    * Destroys all of the memory associated with the
    * current Chain. This function should ensure that
    * memory does not leak on destruction of a chain.
    */
   ~Chain();

   /**
    * Inserts a new node at the end of the List.
    * This function **SHOULD** create one new Node.
    *
    * @param ndata The data to be inserted.
    */
   void insertBack(const Block & ndata);

   /**
    * Modifies the Chain by moving the subchain of len Nodes,
    * starting at position startPos, dist positions toward the
    * end of the chain.  If startPos + len - 1 + dist > length
    * then dist = length - startPos - len + 1 (to prevent gaps
    * in the new chain).
    * The subchain occupies positions (startPos + dist) through
    * (startPos + dist + len - 1) of the resulting chain.
    * The order of subchain nodes is not changed in the move.
    * You may assume that: 1 <= startPos <= length - len + 1,
    * 0 <= dist <= length, and 0 <= len <= length. 
    */
   void moveBack(int startPos, int len, int dist);

   /**
    * Rolls the current Chain by k nodes: reorders the current list
    * so that the first k nodes are the (n-k+1)th, (n-k+2)th, ... , nth
    * nodes of the original list followed by the 1st, 2nd, ..., (n-k)th
    * nodes of the original list where n is the length.
    */
   void roll(int k);

   /**
    * Modifies the current chain by reversing the sequence
    * of nodes from pos1 up to and including pos2. You may
    * assume that pos1 and pos2 exist in the given chain,
    * and pos1 <= pos2.
    * The positions are 1-based.
    */
   void reverseSub(int pos1, int pos2);

   /**
    * Modifies both the current chain and the "other" chain by removing
    * nodes from the other chain and adding them between the nodes
    * of the current chain -- one "other" node between two current nodes --
    * until one of the two chains is exhausted.  Then the rest of the
    * nodes in the non-empty chain follow.
    * The length of the resulting chain should be the sum of the lengths
    * of current and other. The other chain should have only
    * the head_ sentinel at the end of the operation.
    * The weave fails and the original
    * chains should be unchanged if block sizes are different.
    * In that case, the result of the function should be:
    * cout << "Block sizes differ." << endl;
    */
   void weave(Chain & other); // leaves other empty.

   /* =============== end of public PA1 FUNCTIONS =========================*/

private:
   /**
    * Private member variables.
    *
    * You must use these as specified in the spec and may not rename them.
    * You may add more if you need them.
    */

   Node* head_;	// ptr to sentinel node of circular doubly-linked list
		// that implements chain.

   int length_; // count of data elts in chain. does not count sentinel.
   int height_; // height of blocks in chain.
   int width_; // width of blocks in chain. (must be consistent.)

   /**
    * Private helper functions.
    *
    * You must use these as specified in the writeup and may not rename them.
    * You may place more functions here as you need them.
    */

   /* =================== private given functions ============== */

   /**
    * Returns a pointer to the node in the kth position of the list,
    * beyond curr. It effectively walks forward k steps from curr.
    * You may use this function in your solutions
    * to the PA1 functions. GIVEN in chain_given.cpp.
    */
   Node * walk(Node * curr, int k);

   /* =================== end of private given functions ============== */

   /* =================== private PA1 functions ============== */

   void printChain( Node * p );
   void printNode( Node * p );


   /**
    * Destroys all dynamically allocated memory associated with the
    * current Chain class (including sentinels). Called by destructor
    * and op=. Complete for PA1.
    */
   void clear();

   /**
    * Copies the parameter other Chain into the current Chain.
    * Does not free any memory. Called by copy constructor and op=.
    * Complete for PA1.
    * @param other The Chain to be copied.
    */
   void copy(const Chain & other);

   /* =================== end of private PA1 functions ============== */
};

#endif

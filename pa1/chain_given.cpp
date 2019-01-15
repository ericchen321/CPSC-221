
#include "chain.h"

/* no-argument constructor for circular doubly-linked list */
Chain::Chain() : length_(0) {
   head_ = new Node();
   head_->next = head_;
   head_->prev = head_;
}

/* Most useful constructor. requires your
 * implementation of Block and insertBack.
 * Builds a chain out of the blocks in the
 * given image. The blocks we create
 * have width equal to imIn.width()/cols,
 * and height equal to imIn.height().
 * Our Chain is a circular doubly-linked list with
 * sentinel node called head_.
 */
Chain::Chain(PNG & imIn, int cols){

   width_ = imIn.width()/cols; // approx width of a block
   height_ = imIn.height();

   head_ = new Node();
   head_->next = head_;
   head_->prev = head_;
   length_ = 0;

   for (int j = 0; j < cols; j++){
      Block b;
      b.build(imIn , j*width_, width_);
      insertBack(b);
   }
}

/**
 * accessor for the length of the chain.
 */
int Chain::size() const {
   return length_;
}

/* copy constructor */
Chain::Chain(Chain const& other) {
  head_ = new Node();
  head_->next = head_;
  head_->prev = head_;
  length_ = 0;

  copy(other);
}

/* assignment operator */
Chain & Chain::operator=(Chain const& rhs) {
   if (this != &rhs) {
      clear(); // you'll implement clear
      copy(rhs);
   }
   return *this;
}
/**
 * checks for empty list
 */
bool Chain::empty() const {
   return length_ == 0;
}

/**
 * Takes the current chain and renders it into a
 * correctly sized PNG. The blocks in the chain
 * are placed in the image across each row,
 * top to bottom. If the chain is not long enough
 * to create a PNG with the right number of rows
 * and columns, the message "Chain is too short."
 * is printed and an empty PNG is returned.
 */
PNG Chain::render(int cols){

   PNG retVal;

   if (cols <= length_){
      retVal.resize(cols*width_,height_);
      Node * curr = head_->next;
      for (int j = 0; j < cols; j++){
         curr->data.render(retVal, j*width_);
         curr = curr->next;
      }
   }
   else {
      cout << "Chain is too short." << endl;
   }
   return retVal;
}

/**
 * Takes the current chain and renders it into a
 * correctly sized PNG. The blocks in the chain
 * are placed end to start, right to left in the
 * image.
 * If the chain is not long enough
 * to create a PNG with the right number of
 * columns, the message "Chain is too short."
 * is printed and an empty PNG is returned.
 */
PNG Chain::renderBack(int cols){

   PNG retVal;

   if (cols <= length_){
      retVal.resize(cols*width_,height_);
      Node * curr = head_->prev;
      for (int j = cols-1; j >=0 ; j--){
         curr->data.render(retVal, j*width_);
         curr = curr->prev;
      }
   }
   else {
      cout << "Chain is too short." << endl;
   }
   return retVal;
}

/* Returns a pointer to the node in the kth position of the list.
 * beyond curr. It effectively walks forward k steps from curr.
 * You may use this function in your solutions
 * to the PA1 functions. GIVEN in chain_given.cpp.
 */
typename Chain::Node * Chain::walk(Node * curr, int k){

   if (k==0)
      return curr;
   else
      return walk(curr->next,k-1);
}

// Node constructors
Chain::Node::Node() : next(NULL), prev(NULL), data(Block())
{ /* nothing */ }

Chain::Node::Node(const Block& ndata) : next(NULL), prev(NULL), data(ndata)
{ /* nothing */ }

#include "chain.h"
#include "chain_given.cpp"
#include <assert.h>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
// TODO: need tests
Chain::~Chain(){
  /* your code here */
  delete_node(head_);
  head_ = NULL;
  length_ = 0;
  height_ = 0;
  width_ = 0;
}

void Chain::delete_node(Node* cursor){
  if(cursor->next == head_){
    if (length_ >= 1)
      length_ -= 1;
    delete cursor;
  }
  else{
    delete_node(cursor->next);
    if (length_ >= 1)
      length_ -= 1;
    delete cursor;
  }
  assert(length_ >= 0);
}

/**
 * Inserts a new node at the end of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
  Node* new_node = new Node(ndata);
  Node* tail = head_->prev;
  new_node->next = head_;
  new_node->prev = tail;
  tail->next = new_node;
  head_->prev = new_node;
  length_ = length_ + 1;
  height_ = ndata.height();
  width_ = ndata.width();
}

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
void Chain::moveBack(int startPos, int len, int dist){
  /* your code here */
  if (startPos + len - 1 + dist > length_){
    dist = length_ - startPos - len + 1;
  }
  if (empty() || len == 0 || dist <= 0){
    return;
  }
  else{
    move_by_one(startPos, len);
    moveBack(startPos+1, len, dist-1);
  }
}

void Chain::move_by_one(int startPos, int len){
  Node* startNode = head_;
  for (int i=0; i<startPos; i++){
    startNode = startNode->next;
  }
  Node* endNode = startNode;
  for (int i=startPos; i<startPos+len-1; i++){
    endNode = endNode->next;
  }
  Node* a = startNode->prev;
  Node* b = endNode->next;
  Node* c = endNode->next->next;
  a->next = b;
  b->prev = a;
  b->next = startNode;
  startNode->prev = b;
  endNode->next = c;
  c->prev = endNode;
}

/**
 * Rolls the current Chain by k nodes: reorders the current list
 * so that the first k nodes are the (n-k+1)th, (n-k+2)th, ... , nth
 * nodes of the original list followed by the 1st, 2nd, ..., (n-k)th
 * nodes of the original list where n is the length.
 */
// TODO: need tests
void Chain::roll(int k){
  /* your code here */
  if(length_==0 || k<=0 || k>=length_){
    return;
  }
  else{
    Node* first_in_roll = walk(head_, (length_-k+1));
    Node* last_in_roll = walk(head_, length_);
    Node* first_to_follow = head_->next;
    Node* last_to_follow = walk(head_, (length_ - k));
    head_->next = first_in_roll;
    head_->prev = last_to_follow;
    first_in_roll->prev = head_;
    last_in_roll->next = first_to_follow;
    first_to_follow->prev = last_in_roll;
    last_to_follow->next = head_;
  }
}

/**
 * Modifies the current chain by reversing the sequence
 * of nodes from pos1 up to and including pos2. You may
 * assume that pos1 and pos2 exist in the given chain,
 * and pos1 <= pos2.
 * The positions are 1-based.
 */
void Chain::reverseSub(int pos1, int pos2){
  /* your code here */
  if (pos1 == pos2){
    return;
  }
  else if (pos1 == (pos2 - 1)){
    swap_node(pos1, pos2);
    return;
  }
  else{
    swap_node(pos1, pos2);
    reverseSub(pos1+1, pos2-1);
  }
}

void Chain::swap_node(int pos1, int pos2){
  Node* pos1_node = walk(head_, pos1);
  Node* pos2_node = walk(head_, pos2);

  Node* pos1_node_prev = pos1_node->prev;
  Node* pos1_node_next = pos1_node->next;
  Node* pos2_node_prev = pos2_node->prev;
  Node* pos2_node_next = pos2_node->next;

  if(pos1 == pos2 - 1){
    pos1_node_prev->next = pos2_node;
    pos2_node_next->prev = pos1_node;
    pos1_node->prev = pos2_node;
    pos1_node->next = pos2_node_next;
    pos2_node->prev = pos1_node_prev;
    pos2_node->next = pos1_node;
  }
  else{
    pos1_node_prev->next = pos2_node;
    pos1_node_next->prev = pos2_node;
    pos1_node->prev = pos2_node_prev;
    pos1_node->next = pos2_node_next;
    pos2_node_prev->next = pos1_node;
    pos2_node_next->prev = pos1_node;
    pos2_node->prev = pos1_node_prev;
    pos2_node->next = pos1_node_next;
  }
}

/*
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
void Chain::weave(Chain & other) { // leaves other empty.
  /* your code here */
  Node* cursor = head_->next;
  if (!(height_ == other.height_ && width_==other.width_)){
    //cout << "current height: " << height_ << endl;
    //cout << "current width: " << width_ << endl;
    //cout << "other's height: " << other.height_ << endl;
    //cout << "other's width: " << other.width_ << endl;
    cout << "Block sizes differ." << endl;
  }
  else {
    weave_recursive(other, cursor);
  }
}

void Chain::weave_recursive(Chain & other, Node* cursor){
  if(other.empty()){
    return;
  }
  else if(cursor->next == head_ && !other.empty()){
    Node* other_first_node = other.head_->next;
    Node* other_first_node_next = other_first_node->next;
    insert_node(cursor, other_first_node);  // insert other's 1st node to after cursor
    cursor = cursor->next;  // increment cursor
    other.head_->next = other_first_node_next;  // remove first node from other
    other_first_node_next->prev = other.head_;
    other.length_ -= 1;
    weave_recursive(other, cursor);
  }
  else{
    Node* other_first_node = other.head_->next;
    Node* other_first_node_next = other_first_node->next;
    insert_node(cursor, other_first_node);  // insert other's 1st node to after cursor
    cursor = cursor->next->next;  // increment cursor
    other.head_->next = other_first_node_next;  // remove first node from other
    other_first_node_next->prev = other.head_;
    other.length_ -= 1;
    weave_recursive(other, cursor);
  }
}

void Chain::insert_node(Node* cursor, Node* inserted){
  Node* cursor_next = cursor->next;
  cursor->next = inserted;
  inserted->prev = cursor;
  inserted->next = cursor_next;
  cursor_next->prev = inserted;
  length_ += 1;
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class except for the sentinel head_. Sets length_
 * to zero.  After clear() the chain represents an empty chain.
 */
// TODO: need tests
void Chain::clear() {
  /* your code here */
  if (head_->next == head_){
    return;
  }
  else{
    delete_node(head_->next);
    head_->next = head_;
    head_->prev = head_;
    length_ = 0;
  }
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const& other) {
  /* your code here */
  height_ = other.height_;
  width_ = other.width_;
  head_ = new Node();
  Node* current_cursor = head_;
  Node* other_cursor = other.head_->next;
  while(other_cursor != other.head_){
    Node* new_node = new Node(other_cursor->data);
    current_cursor->next = new_node;
    new_node->prev = current_cursor;
    current_cursor = current_cursor->next;
    other_cursor = other_cursor->next;
  }
  current_cursor->next = head_;
  head_->prev = current_cursor;
  length_ = other.length_;
}

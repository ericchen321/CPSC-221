/**
 * @file queue.h
 * Definition of the Queue class.
 *
 * You **should not** modify this file for the PA!
 *
 */
#ifndef DEQUE_H
#define DEQUE_H

#include<vector>
using namespace std;

/**
 * Deque class: represents a standard deque, templated to hold elements of
 * any type. **You must only use the private member vector as your
 * storage space! You cannot create new private member variables to hold
 * your objects!** 
 *
 * You **should not** modify this file for the PA!
 *
 */
template <class T>
class Deque
{
  public:

    /**
     * Constructor for the Deque class. Use it to initialize variables.
    */
    Deque();

    /**
     * Adds the parameter object to the "right" end of the Deque.
     *
     * @note This fuction should have O(1) behavior over n operations!
     * You may trust that the vector class resizes the array appropriately
     * for additions to the structure, so no custom resizing is necessary for 
     * function pushR.
     *
     * @param newItem object to be added to the Deque.
     */
    void pushR(const T& newItem);

    /**
     * Removes the object at the left of the Deque, and returns it to
     * the caller. You may assume that this function is only called
     * when the Deque is non-empty.
     *
     * To achieve amortized O(1) cost per operation, we will resize 
     * the array downward at strategic points of the computation. 
     * Specifically, suppose there are L empty cells in the vector
     * to the left of the contiguous block of data.
     * If at any point the data will fit into array indices O..L-1,
     * the array should be reinitialized to hold the data, beginning
     * at index 0, effectively resizing the vector to half its size.
     *
     * @note This function should have O(1) behavior over n operations!
     *
     * @return The item that used to be at the left of the Deque.
     */
    T popL();

    /**
     * Removes the object at the right of the Deque, and returns it to
     * the caller. You may assume that this function is only called
     * when the Deque is non-empty.
     *
     * To achieve amortized O(1) cost per operation, we will resize 
     * the array downward at strategic points of the computation. 
     * Specifically, suppose there are L empty cells in the vector
     * to the left of the contiguous block of data.
     * If at any point the data will fit into array indices O..L-1,
     * the array should be reinitialized to hold the data, beginning
     * at index 0, effectively resizing the vector to half its size.
     *
     * @return The item that used to be at the right of the Deque.
     */
    T popR();

    /**
     * Finds the object at the left of the Deque, and returns it to
     * the caller. Unlike popL(), this operation does not alter the
     * deque. You may assume that this function is only called when the
     * Deque is non-empty.
     *
     * @note This function should have O(1) behavior.
     *
     * @return The item at the left of the deque.
     */
    T peekL();

    /**
     * Finds the object at the right of the Deque, and returns it to
     * the caller. Unlike popR(), this operation does not alter the
     * deque. You may assume that this function is only called when the
     * Deque is non-empty.
     *
     * @note This function should have O(1).
     *
     * @return The item at the right of the deque.
     */
    T peekR();

    /**
     * Determines if the Deque is empty.
     *
     * @note This function should have O(1).
     *
     * @return bool which is true if the Deque is empty, false
     *	otherwise.
     */
    bool isEmpty() const;

  private:
    vector<T> data;  /* Store the deque data here! */

    /* you should decide how to use these two integers */
    int k1;  
    int k2; 
};

#include "deque.cpp"
#endif

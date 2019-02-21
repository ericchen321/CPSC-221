/**
 * @file stack.h
 * Definition of the Stack class.
 *
 * You **should not** modify this file for the PA!
 *
 */
#ifndef STACK_H
#define STACK_H

#include "deque.h"
#include "ordering_structure.h"

/**
 * Stack class: represents a standard stack. Templated to hold elements of
 * any type. **You must only use the private member deque as your
 * storage space! You cannot create new private member variables to hold
 * your objects!** It is up to you to determine how to use the Deque, however.
 *
 * Your Stack class should have O(1) running time over n operations
 * (amortized)for all operations.
 *
 * You **should not** modify this file for the PA!
 *
 */

template <class T>
class Stack : public OrderingStructure<T>
{
  public:
    /**
     * Adds the parameter object to the top of the Stack. That is, the
     * element should go at the beginning of the list.
     *
     * @note This function must be O(1)!
     *
     * @param newItem The object to be added to the Stack.
     */
    void push(const T& newItem);

    /**
     * Removes the object on top of the Stack, and returns it. That is,
     * remove the element at the beginning of the list. You may assume
     * this function is only called when the Stack is not empty.
     *
     * @note This function must be O(1)!
     *
     * @return The element that used to be at the top of the Stack.
     */
    T pop();

    /**
     * Adds an element to the ordering structure.
     *
     * @see OrderingStructure::add()
     */
    void add(const T& theItem);

    /**
     * Removes an element from the ordering structure.
     *
     * @see OrderingStructure::remove()
     */
    T remove();

    /**
     * Finds the object on top of the Stack, and returns it to the caller.
     * Unlike pop(), this operation does not alter the Stack itself. It
     * should look at the beginning of the list. You may assume this
     * function is only called when the Stack is not empty.
     *
     * @note This function must be O(1)!
     *
     * @return The element at the top of the Stack.
     */
    T peek();

    /**
     * Determines if the Stack is empty.
     *
     * @note This function must be O(1)! Note that the std::list's
     *	size() function is O(n), so you should not attempt to use it
     *	here.
     *
     * @return Whether or not the stack is empty (bool).
     */
    bool isEmpty() const;

  private:
    /**
     * The list representing our Stack: the front of the list corresponds to the
     * top of the Stack.
     **/
    Deque<T> myStack;
};

#include "stack.cpp" // needed for template instantiation
#endif

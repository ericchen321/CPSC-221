/**
 * @file stack.cpp
 * Implementation of the Stack class.
 *
 */

/**
 * Adds the parameter object to the top of the Stack. 
 *
 * @param newItem The object to be added to the Stack.
 */
template<class T>
void Stack<T>::push(T const & newItem)
{
    /**
     * @todo Your code here!
     */
    myStack.pushR(newItem);
}

/**
 * Removes the object on top of the Stack, and returns it. 
 * the element at the beginning of the list. You may assume this function
 * is only called when the Stack is not empty.
 *
 * @return The element from the top of the Stack.
 */
template <class T>
T Stack<T>::pop()
{
    /**
     * @todo Your code here! 
     */
    return myStack.popR();
}

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T>
void Stack<T>::add(const T& theItem)
{
    /**
     * @todo Your code here! Hint: this should call another Stack function
     *  to add the element to the Stack.
     */
    push(theItem);
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T>
T Stack<T>::remove()
{
    /**
     * @todo Your code here! Hint: this should call another Stack function
     *  to remove an element from the Stack and return it. 
     */
    return pop();
}

/**
 * Finds the object on top of the Stack, and returns it to the caller.
 * Unlike pop(), this operation does not alter the Stack itself. 
 * You may assume this function is only
 * called when the Stack is not empty.
 *
 * @return The value of the element at the top of the Stack.
 */
template <class T>
T Stack<T>::peek()
{
    /**
     * @todo Your code here! 
     */
    return myStack.peekR();
}

/**
 * Determines if the Stack is empty.
 *
 * @return Whether or not the stack is empty (bool).
 */
template <class T>
bool Stack<T>::isEmpty() const
{
    /**
     * @todo Your code here! 
     */
    return myStack.isEmpty();
}

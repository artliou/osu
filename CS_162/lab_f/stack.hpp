/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 21, 2016
** Description:  NodeController.hpp
*********************************************************************/

#ifndef LAB_F_STACK_HPP
#define LAB_F_STACK_HPP

#include "lib_flip_display.hpp"

//////////////////////////////////////////////////////////////////////
//
// class Stack
//
// Template class for implementing a stack.
//
// void push (const T item) - push item on to stack
// T peek()                 - get item from top of stack
// void pop()               - remove item from top of stack
// bool isEmpty()           - Check if stack is empty
//

template <class T>
class Stack
{
public:
    struct StackNode
    {
        T data;
        struct StackNode * nextNode;
    };

private:
    struct StackNode * topOfStack;

public:
    Stack();
    ~Stack();

    void push(const T item);
    T peek();
    void pop();
    bool isEmpty();
};

///////////////////////////////////////////////////////////////////////////////
//
// Stack<T>::Stack()
//
// Stack class constructor
//
// Parameters:
//        none
//
// Return:
//        none
//

template <class T>
Stack<T>::Stack()
{
    // Initalize topOfStack to null
    topOfStack = __null;
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Stack.\n");
}

///////////////////////////////////////////////////////////////////////////////
//
// Stack<T>::~Stack()
//
// Stack class destructor
//
// Parameters:
//        none
//
// Return:
//        none
//

template <class T>
Stack<T>::~Stack()
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Destroying Stack.\n");
    while (!isEmpty())
    {
        // Responsibly destroy all nodes from stack
        pop();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// void Stack<T>::push (const T item)
//
// Push an item on to the top of the stack.
//
// Parameters:
//        const T item - Push item onto stack.
//
// Return:
//        none
//

template <class T>
void Stack<T>::push(const T item)
{
    // Check if stack is empty
    if (isEmpty())
    {
        // If empty, initalize first node
        topOfStack = new StackNode();

        // The 'bottom' stack node does not contain a next node!
        // Upon removing the this node, topOfStack will become null and the stack will be 'empty'.
        topOfStack->nextNode = __null;
    }
    else
    {
        // If not empty, link new item to old item.
        StackNode * oldStackTop = topOfStack;
        topOfStack = new StackNode();
        topOfStack->nextNode = oldStackTop;
    }

    // Copy the item to the top of stack.
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Pushing object on stack.\n");
    memcpy (&topOfStack->data, &item, sizeof (T));
}

///////////////////////////////////////////////////////////////////////////////
//
// T Stack<T>::peek ()
//
// Get the data for the item on the top of the stack.
//
// Parameters:
//        none
//
// Return:
//        T item - item on top of stack
//

template <class T>
T Stack<T>::peek()
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Peeking object on stack.\n");
    // Check if stack is empty
    if (!isEmpty())
    {
        // Return top node data.
        return topOfStack->data;
    }
    else
    {
        // Empty stack, return null
        DebugConsole::debug_print (0, true, COLOR_YELLOW, "Attempted %s, but Stack is empty.\n", __func__);
        return (T)__null;
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// void Stack<T>::pop ()
//
// Pop item from the top of the stack.
//
// Parameters:
//        none
//
// Return:
//        none
//

template <class T>
void Stack<T>::pop()
{
    // Check if the stack is empty
    if (!isEmpty())
    {
        // Save the next node
        StackNode * nextNode = topOfStack->nextNode;
        
        // Delete the top node class object
        delete topOfStack;

        // Restore the top of the stack to the next node.
        topOfStack = nextNode;
        DebugConsole::debug_print (1, true, COLOR_CYAN, "Popping object from stack.\n");
        
        // Check if the stack is empty now.
        if (isEmpty())
        {
            DebugConsole::debug_print (1, true, COLOR_YELLOW, "Last object popped from stack.\n");
        }
    }   
}

///////////////////////////////////////////////////////////////////////////////
//
// bool Stack<T>::isEmpty()
//
// Check if the stack is empty
//
// Parameters:
//        none
//
// Return:
//        bool empty - true if the stack is empty
//

template <class T>
bool Stack<T>::isEmpty()
{
    // if topOfStack is null, the stack is empty.
    return (topOfStack == __null);
}

#endif // LAB_F_STACK_HPP
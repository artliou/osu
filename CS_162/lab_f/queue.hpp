/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 21, 2016
** Description:  queue.hpp
*********************************************************************/

#ifndef LAB_F_QUEUE_HPP
#define LAB_F_QUEUE_HPP

#include "lib_flip_display.hpp"

//////////////////////////////////////////////////////////////////////
//
// class Queue
//
// Template class for implementing a queue.
//
// void addBack(const T item) - Add an item to the end of the queue
// T getFront()               - Get the item from the front of the queue
// void removeFront()         - Remove the item from the front of the queue
// bool isEmpty()             - Check if a queue is empty
//

template <class T>
class Queue
{
public:
    struct QueueNode
    {
        T data;
        struct QueueNode * nextNode;
    };

private:
    struct QueueNode * headNode;
    struct QueueNode * tailNode;

public:
    Queue();
    ~Queue();

    void addBack(const T item);
    T getFront();
    void removeFront();
    bool isEmpty();
};

///////////////////////////////////////////////////////////////////////////////
//
// Queue<T>::Queue()
//
// Queue class constructor
//
// Parameters:
//        none
//
// Return:
//        none
//

template <class T>
Queue<T>::Queue()
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Queue.\n");
    // Initalize head and tail nodes to null
    headNode = __null;
    tailNode = __null;
}

///////////////////////////////////////////////////////////////////////////////
//
// Queue<T>::~Queue()
//
// Queue class destructor
//
// Parameters:
//        none
//
// Return:
//        none
//

template <class T>
Queue<T>::~Queue()
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Destroying Queue.\n");
    while (!isEmpty())
    {
        // Responsibly destroy all nodes from queue
        removeFront();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// void Queue<T>::addBack(const T item)
//
// Add item to the back of the queue
//
// Parameters:
//        const T item - Item to add to the back of the queue
//
// Return:
//        none
//

template <class T>
void Queue<T>::addBack(const T item)
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Adding object to Queue.\n");
    // Check if queue is empty    
    if (isEmpty())
    {
        // If this is the first node, set head and tail to new node
        headNode = tailNode = new QueueNode();
    }
    else
    {
        // If adding on to the tail node, set the last tail next pointer
        // Set the tail node to the new tail
        tailNode->nextNode = new QueueNode();
        tailNode = tailNode->nextNode;
    }
    // Copy the item into the new node and set the last node next pointer to null.
    memcpy (&tailNode->data, &item, sizeof (T));
    tailNode->nextNode = __null;
}

///////////////////////////////////////////////////////////////////////////////
//
// T Queue<T>::getFront()
//
// Get the item on the front of the queue
//
// Parameters:
//        none
//
// Return:
//        T item - Item at the front of the queue
//

template <class T>
T Queue<T>::getFront()
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Getting head object from Queue.\n");
    // Check if the queue is empty
    if (!isEmpty())
    {
        // return the first node data
        return headNode->data;
    }
    else
    {
        // return node sinde the queue is empty
        DebugConsole::debug_print (0, true, COLOR_YELLOW, "Attempted %s, but Queue is empty.\n", __func__);
        return (T)__null;
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// void Queue<T>::removeFront()
//
// Remove the item on the front of the queue
//
// Parameters:
//        none
//
// Return:
//        none
//

template <class T>
void Queue<T>::removeFront()
{
    if (!isEmpty())
    {
        DebugConsole::debug_print (1, true, COLOR_CYAN, "Removing head object from Queue.\n");
        // Save the head node's next node
        QueueNode * nextNode = headNode->nextNode;

        // Delete the head node object
        delete headNode;

        // Set the head node to the saved next node
        headNode = nextNode;
        
        // Check if the last node was removed
        if (isEmpty())
        {
            // Set tailNode to null also since headNode is null
            DebugConsole::debug_print (1, true, COLOR_YELLOW, "Last object removed from Queue.\n");
            tailNode = __null;
        }                
    }   
}

///////////////////////////////////////////////////////////////////////////////
//
// bool Queue<T>::isEmpty()
//
// Check if the queue is empty
//
// Parameters:
//        none
//
// Return:
//        bool empty - true if the queue is empty
//

template <class T>
bool Queue<T>::isEmpty()
{
    // If the headNode is null, then the queue is empty and return true.
    return (headNode == __null);
}

#endif // LAB_F_QUEUE_HPP
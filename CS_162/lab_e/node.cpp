/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 21, 2016
** Description:  node.cpp
*********************************************************************/

#include "node.hpp"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//
// Node::Node (char newData)
//
// Node class constructor
//
// Parameters:
//        char newData - new data for node payload
//
// Return:
//        none
//

Node::Node (char newData)
{
    payloadData = newData;
    nextNode = __null;
}

///////////////////////////////////////////////////////////////////////////////
//
// void Node::SetNextNode(Node * next)
//
// Set nextNode pointer for linked list.
//
// Parameters:
//        Node * next - Pointer to next node
//
// Return:
//        none
//

void Node::SetNextNode(Node * next)
{
    nextNode = next;
}

///////////////////////////////////////////////////////////////////////////////
//
// Node * Node::GetNextNode()
//
// Get nextNode pointer for linked list.
//
// Parameters:
//        none
//
// Return:
//        Node * - Pointer to next node
//

Node * Node::GetNextNode()
{
    return nextNode;
}

///////////////////////////////////////////////////////////////////////////////
//
// Node * Node::GetNodeData()
//
// Get node's payload
//
// Parameters:
//        none
//
// Return:
//        char - Node payload
//

char Node::GetNodeData()
{
    return payloadData;
}

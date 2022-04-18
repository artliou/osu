/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 21, 2016
** Description:  NodeController.cpp
*********************************************************************/

#include "nodeController.hpp"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//
// NodeController::NodeController()
//
// Node controller class constructor
//
// Parameters:
//        none
//
// Return:
//        none
//

NodeController::NodeController()
{
    headNode = __null;
    lastNode = __null;
    currentNode = __null;
    isLastNode = true;
}

///////////////////////////////////////////////////////////////////////////////
//
// NodeController::~NodeController()
//
// Node controller class destructor
//
// Parameters:
//        none
//
// Return:
//        none
//

NodeController::~NodeController()
{
    while (headNode != __null)
    {
        DeleteNode();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Node * NodeController::AddNode (char dataToAdd)
//
// Add node to linked list
//
// Parameters:
//        char data - new data for new node
//
// Return:
//        Node * - Pointer to new node created.
//

Node * NodeController::AddNode (char dataToAdd)
{
    if (headNode == __null)
    {
        // This is the first Add case.
        headNode = new Node (dataToAdd);
        headNode->SetNextNode(headNode);
        currentNode = headNode;
        lastNode = headNode;
    }
    else
    {
        // Adding nodes to the chain.
        lastNode->SetNextNode (new Node (dataToAdd));
        lastNode = lastNode->GetNextNode();
        lastNode->SetNextNode (headNode);
    }
    isLastNode = false;
    return lastNode;
}

///////////////////////////////////////////////////////////////////////////////
//
//  char NodeController::GetNodeData ()
//
// Get current nodes data
//
// Parameters:
//        None
//
// Return:
//        char - data
//

char NodeController::GetNodeData ()
{
    if (isLastNode)
    {
        return 0;
    }
    else
    {
        return currentNode->GetNodeData();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  void NodeController::RemoveNode ()
//
// Set current node to the next node. If there is no new node, set
// the isLastNode flag to true.
//
// Parameters:
//        None
//
// Return:
//        None
//

void NodeController::RemoveNode ()
{
    if (currentNode->GetNextNode() == headNode)
    {
        isLastNode = true;
    }
    else
    {
        currentNode = currentNode->GetNextNode();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  void NodeController::DeleteNode ()
//
// This deletes the headNode and moves the pointer up.
// If it is the last node, then set all data to null
//
// Parameters:
//        None
//
// Return:
//        None
//

void NodeController::DeleteNode ()
{
    // Check if this is the last node!
    if (lastNode == headNode)
    {
        delete headNode;
        headNode = __null;
        lastNode = __null;
        currentNode = __null;
    }
    else
    {
        // Re-assign last->next to head->next
        lastNode->SetNextNode(headNode->GetNextNode());

        // If the current node is the head node
        if (currentNode == headNode)
        {
            // Move the current node to the next one.
            currentNode = headNode->GetNextNode();
        }
        // Delete the Node
        delete headNode;

        // Reset headNode to the new head.
        headNode = lastNode->GetNextNode();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// char NodeController::GetNodeDataAndRemove()
//
// Get the node data and increment the currentNode pointer
//
// Parameters:
//        None
//
// Return:
//        char - node data
//

char NodeController::GetNodeDataAndRemove()
{
    char data = GetNodeData();
    RemoveNode();
    return data;
}

///////////////////////////////////////////////////////////////////////////////
//
// void NodeController::PrintSingleItem()
//
// Print one item.
//
// Parameters:
//        None
//
// Return:
//        None
//

void NodeController::PrintSingleItem()
{
    if (currentNode != __null)
    {
        std::cout << GetNodeDataAndRemove();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// void NodeController::PrintAllItems()
//
// Print all items.
//
// Parameters:
//        None
//
// Return:
//        None
//

void NodeController::PrintAllItems()
{
    while (isLastNode == false)
    {
        PrintSingleItem();
    }
}

/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 21, 2016
** Description:  NodeController.hpp
*********************************************************************/

#ifndef LAB_E_NODE_CONTROLLER_H
#define LAB_E_NODE_CONTROLLER_H

#include "node.hpp"

//////////////////////////////////////////////////////////////////////
//
// Node Controller Class
//
// A class for managing the linked list and using its contents.
//

class NodeController
{
private:
    Node * headNode;
    Node * currentNode;
    Node * lastNode;

    bool isLastNode;

    char GetNodeData ();
    void RemoveNode ();
    void DeleteNode ();

public:
    NodeController();
    ~NodeController();

    Node * AddNode (char dataToAdd);
    char GetNodeDataAndRemove();

    void PrintSingleItem();
    void PrintAllItems();
};

#endif // LAB_E_NODE_CONTROLLER_H

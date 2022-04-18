/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 21, 2016
** Description:  node.hpp
*********************************************************************/

#ifndef LAB_E_NODE_H
#define LAB_E_NODE_H

//////////////////////////////////////////////////////////////////////
//
// Node Class
//
// A basic class for storing a char in a linked list
//

class Node
{
private:
    Node * nextNode;
    char payloadData;

public:
    Node(char newData);
    ~Node() { }

    char GetNodeData();

    void SetNextNode (Node * next);
    Node * GetNextNode ();
};

#endif // LAB_E_NODE_H

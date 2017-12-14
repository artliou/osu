/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/22/17
 ** Description: Project 9.a

 *********************************************************************/

#include "StringList.hpp"
#include <iostream>

//Copy Constructor; create a completely separate duplicate of a StringList object
StringList::StringList(const StringList &original) {
    head = copyList(original.head);
}

StringList::ListNode * StringList::copyList(ListNode *aList) {
    if (aList == NULL)
        return NULL;
    else {
        ListNode *tail = copyList(aList->next);
        return new ListNode(aList->mainStr, tail);
    }
}

//Destructor; delete any memory that was dynamically allocated by the StringList object.
StringList::~StringList() {
    ListNode *nodePtr = head;
    while (nodePtr != NULL) {
        ListNode *temp = nodePtr;
        nodePtr = nodePtr->next;
        delete temp;
    }
}
//Add function adds a new node containing the value of the parameter to the end of the list.
void StringList::add(std::string stringIn) {
    if (head == NULL)
        head = new ListNode(stringIn);
    else {
        ListNode *nodePtr = head;
        while(nodePtr->next != NULL)
            nodePtr = nodePtr->next;
        nodePtr->next = new ListNode(stringIn);
    }
}

//Returns the (zero-based) position in the list for the first occurrence of the parameter in the list, or -1 if that value is not in the list.
int StringList::positionOf(std::string stringIn) {
    int position = 0;
    ListNode *nodePtr = head;
    while(nodePtr) {
        if(nodePtr->mainStr == stringIn)
            return position;
        nodePtr = nodePtr->next;
        position ++;
    }
    return -1;
}

//Takes a string argument and a zerop-based index. Finds that node and sets it's string to input string.  Returns true if index found, false if not
bool StringList::setNodeVal(int indexIn, std::string stringIn) {
    int nodeIndex = 0;
    ListNode *nodePtr = head;
    while(nodePtr) {
        if(nodeIndex == indexIn) {
            nodePtr->mainStr = stringIn;
            return true;
        }
        nodeIndex ++;
        nodePtr = nodePtr->next;
    }
    return false;
}

//Returns a vector with the same size, values and order as the StringList.
std::vector<std::string> StringList::getAsVector() {
    ListNode *nodePtr = head;
    vector<string> stringVect;
    while(nodePtr) {
        stringVect.push_back(nodePtr->mainStr);
        nodePtr = nodePtr->next;
    }
    return stringVect;
}

//Printing!
void StringList::printAddress() const {
    int count = 0;
    ListNode *nodePtr = head;
    while(nodePtr) {
        cout << "Address of Node" << count << " is " << nodePtr->mainStr << endl;
        nodePtr = nodePtr->next;
        count ++;
    }
}

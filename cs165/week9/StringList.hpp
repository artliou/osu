/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/22/17
 ** Description: Project 9.a

 *********************************************************************/

#ifndef StringList_hpp
#define StringList_hpp

#include <string>
#include <vector>
using namespace std;

class StringList
{
  private:
    struct ListNode
    {
        string mainStr;
        ListNode *next;
        ListNode(string str, ListNode *next1 = NULL)
        {
            mainStr = str;
            next = next1;
        }
    };
    ListNode *head;

  public:
    StringList()
    {
        head = NULL;
    }                                       //Default Constructor
    StringList(const StringList &original); //Copy Constructor; deep copy
    ~StringList();                          //Destructor
    void add(std::string);
    int positionOf(std::string) bool setNodeVal(int, std::string);
    std::vector<std::string> getAsVector();

    ListNode *copyList(ListNode *aList);
    void printAddress() const;
};

#endif /* StringList_hpp */

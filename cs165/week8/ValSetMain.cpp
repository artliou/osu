/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 2/29/17
 ** Description: Project 8.a

 *********************************************************************/

#include "ValSet.hpp"
#include <assert.h>
#include <cassert>
#include <iostream>

int main()
{
    ValSet<int> set1;
    set1.add(-30);
    bool cont1 = set1.contains(-30);
    set1.remove(-30);
    bool cont2 = set1.contains(-30);
    // ASSERT_TRUE(cont1 && !cont2);
    cout << "End Test Case 1: " << (cont1 && !cont2) << endl;

    ValSet<char> newSet;
    newSet.add('A');
    newSet.add('j');
    newSet.add('&');
    newSet.remove('j');
    newSet.add('#');
    int size = newSet.size();
    ValSet<char> mySet2 = newSet;
    bool check1 = mySet2.contains('&');
    bool check2 = mySet2.contains('j');
    ValSet<char> myUnion = newSet + mySet2;
    cout << "End Given Test Case" << endl;

    //Old Test Code
    cout << "Testing old: default constructor" << endl;

    ValSet<char> mySet;
    cout << "Testing Char Set" << endl;

    std::vector<char> testVect;
    cout << "Testing Vector Set" << endl;

    mySet.add('A');
    mySet.add('B');
    mySet.add('C');
    mySet.add('D');
    mySet.add('E');
    mySet.add('F');
    mySet.add('G');
    mySet.add('H');
    mySet.add('j');
    mySet.add('I');
    mySet.add('J');
    mySet.add('K');

    cout << "Before remove()" << endl;
    testVect = mySet.getAsVector();
    cout << "Vector contains: " << testVect.size() << " elements. They are: \n";
    for (unsigned int i = 0; i < testVect.size(); i++)
        cout << testVect[i] << " ";

    mySet.remove('j');

    cout << endl
         << "After remove()" << endl;
    testVect = mySet.getAsVector();
    cout << "Vector contains: " << testVect.size() << " elements. They are: \n";

    for (unsigned int i = 0; i < testVect.size(); i++)
        cout << testVect[i] << " ";

    mySet.add('#');

    testVect = mySet.getAsVector();
    cout << endl
         << "Vector contains: " << testVect.size() << " elements. They are: \n";
    for (unsigned int i = 0; i < testVect.size(); i++)
        cout << testVect[i] << " ";
    cout << endl;

    mySet.remove('#');
    testVect = mySet.getAsVector();
    cout << endl
         << "Vector contains: " << testVect.size() << " elements. They are: \n";
    for (unsigned int i = 0; i < testVect.size(); i++)
        cout << testVect[i] << " ";
    cout << endl;

    mySet.remove('A');
    testVect = mySet.getAsVector();
    cout << endl
         << "Vector contains: " << testVect.size() << " elements. They are: \n";
    for (unsigned int i = 0; i < testVect.size(); i++)
        cout << testVect[i] << " ";
    cout << endl;

    return 0;
}

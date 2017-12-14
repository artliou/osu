/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/22/17
 ** Description: Project 9.a

 *********************************************************************/

#include <iostream>
#include "StringList.cpp"

int main() {
    cout << "testing" << endl;
    StringList strList1;

    cout << "testing add()" << endl;
    strList1.add("Waffles");
    strList1.add("Dork");
    strList1.add("fizzle");
    strList1.add("fizzle");

    //Test Copy constructor
    StringList strList2 = strList1;

    //Test Deep copy (comparing addresses)
    strList1.printAddress();
    strList2.printAddress();

    //Test positionOf()
    int search1 = strList1.positionOf("fizzle");
    int search2 = strList2.positionOf("pizzle");
    cout << "Search for \"fizzle\" found at position (-1 if not found): " << search1 << endl;
    cout << "Search for \"pizzle\" found at position (-1 if not found): " << search2 << endl;

    //Test setNodeVal()
    cout << "testing setNodeVal()" << endl;
    bool setNode1 = strList1.setNodeVal(3,"wizzle");
    bool setNode2 = strList1.setNodeVal(4, "my nizzle");
    cout << "setNodeVal() test one should return true: " << setNode1 <<  endl;
    cout << "setNodeVal() test two should return false: " << setNode2 <<  endl;
    strList1.printAddress();
    strList2.printAddress();

    //Vector1 Test
    cout << "testing getAsVector()" << endl;
    vector<string> testVector;
    testVector = strList1.getAsVector();
    cout << "size of vector1 is: " << testVector.size() << endl;
    cout << "contents of vector1 is: "<< endl;
    for (unsigned int i = 0; i < testVector.size(); i++)
        cout << testVector[i] << " ";
    //Vector 2 Test
    cout << endl;
    vector<string> testVector2;
    testVector2 = strList2.getAsVector();
    cout << "size of vector2 is: " << testVector2.size() << endl;
    cout << "contents of vector2 is: "<< endl;
    for (unsigned int i = 0; i < testVector2.size(); i++)
        cout << testVector2[i] << " ";
    return 0;
}

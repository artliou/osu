/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/8/17
 ** Description: Project 7.b

 *********************************************************************/

#ifndef MyInteger_hpp
#define MyInteger_hpp

#include <iostream>

class MyInteger
{
  private:
    int *pInteger;

  public:
    //MyInteger(int iInteger);
    MyInteger(int x)
    { // constructor
        pInteger = new int;
        *pInteger = x; //new
    }
    ~MyInteger()
    { // destructor
        pInteger = NULL;
        delete pInteger;
    }

    MyInteger(const MyInteger &obj)
    { // copy constructor to overload '='
        pInteger = new int;
        *pInteger = *obj.pInteger;
    }

    void setMyInt(int x);
    int getMyInt();
};

#endif /* MyInteger_hpp */
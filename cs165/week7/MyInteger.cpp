/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/8/17
 ** Description: Project 7.b

 *********************************************************************/

#include "MyInteger.hpp"
#include <iostream>

void MyInteger::setMyInt(int x)
{
    *pInteger = x;
}

int MyInteger::getMyInt()
{
    return *pInteger;
}

// int main(int argc, const char *argv[])
// {
//     MyInteger obj1(17);
//     MyInteger obj2 = obj1;
//     std::cout << obj1.getMyInt() << std::endl;
//     std::cout << obj2.getMyInt() << std::endl;

//     obj2.setMyInt(9);
//     std::cout << obj1.getMyInt() << std::endl;
//     std::cout << obj2.getMyInt() << std::endl;

//     MyInteger obj3(42);
//     obj2 = obj3;
//     std::cout << obj2.getMyInt() << std::endl;
//     std::cout << obj3.getMyInt() << std::endl;

//     obj3.setMyInt(1);
//     std::cout << obj2.getMyInt() << std::endl;
//     std::cout << obj3.getMyInt() << std::endl;

//     return 0;
// }

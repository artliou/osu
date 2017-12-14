/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 9/3/17
 ** Description: Project 2.e

 *********************************************************************/

#include <iostream>
#include <string>

void smallSort(int &a, int &b, int &c)
{
    int holder;
    while (a > b or b > c or a > b)
    {
        if (a > b)
        {
            holder = a;
            a = b;
            b = holder;
        }
        else if (b > c)
        {
            holder = b;
            b = c;
            c = holder;
        }
        else if (a > b)
        {
            holder = a;
            a = b;
            b = holder;
        }
    }
}
/***

int main()
{
    int a, b, c;
    std::cout << "Enter 3 integers." << std::endl;
    std::cin >> a >> b >> c;

    smallSort( a, b, c );
    std::cout << a << ", " << b << ", " << c << std::endl;
}
***/

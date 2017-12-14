/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/18/17
 ** Description: Project 4.c

A void function that takes as parameters the addresses of three int variables and sorts the ints at those addresses into ascending order.

 *********************************************************************/

#include <iostream>
using namespace std;
using std::swap;

void smallSort2(int *a, int *b, int *c)
{
    //Do Nothing since already sorted
    if ((*a <= *b) && (*b <= *c))
    {
        return;
    }
    //if you only need to swap b and c
    if ((*a <= *c) && (*c <= *b))
    {
        swap(*b, *c);
        return;
    }
    //if you only need to swap a and b
    if ((*b <= *a) && (*a <= *c))
    {
        swap(*a, *b);
        return;
    }
    //if you need to move c to the front
    if ((*b <= *c) && (*c <= *a))
    {
        swap(*a, *b);
        swap(*b, *c);
        return;
    }
    //if move a to the end
    if ((*c <= *a) && (*a <= *b))
    {
        swap(*a, *c);
        swap(*b, *c);
        return;
    }
    //if reverse sorted
    if ((*c <= *b) && (*b <= *a))
    {
        swap(*a, *c);
        return;
    }
}

// int main()
// {
//     int a = 14;
//     int b = -90;
//     int c = 2;

//     smallSort2(&a, &b, &c);
//     cout << a << ", " << b << ", " << c << endl;
// }
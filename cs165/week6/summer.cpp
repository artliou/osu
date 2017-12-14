/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/1/17
 ** Description: Project 6.a

 Prompt:
 Write a recursive function named summer that takes two parameters - an array of doubles and the size of the array - and returns the sum of the values in the array.  The size parameter does not have to be the actual size of the array.  It will be at the top level, but at the lower recursive levels it can be the size of the sub-array being worked on at that level.

 PseudoCode:
 Input: Array of doubles, integer (array size)
 Output: Integer - sum of the values in the array
 *********************************************************************/

#include <stdio.h>
#include <iostream>

using namespace std;

double summer(double array[], int size)
{
    if (size == 0)
    {
        return 0;
    }
    else
    {
        return array[size - 1] + summer(array, size - 1);
    }
}

//helper function to show array
void showArray(const double array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i];
    }
    cout << endl;
}

// int main()
// {
//     int size = 4;
//     double list[4] = {1, 2, 3, 4};
//     double total;

//     cout << "Here is the double array " << endl;
//     showArray(list, size);
//     total = summer(list, size);
//     cout << "The sum is " << total << endl;

//     return 0;
// }

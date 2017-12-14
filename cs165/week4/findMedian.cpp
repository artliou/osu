/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/18/17
 ** Description: Project 4.a

 findMedian finds the median within an array of integers.
 It takes in two parameters and returns a double.

 *********************************************************************/

#include <algorithm>
#include <iostream>
using namespace std;
using std::sort;

double findMedian(int array[], int size)
{
    sort(array, array + size);

    int middle;
    double median;
    middle = size / 2;

    if ((size % 2) == 0)
    {
        median = (array[middle] + array[middle - 1]) / 2.0;
        cout << "Sorted Array Even: " << array << endl;
        cout << "The median is: " << median << endl;
    }
    else
    {
        median = array[middle];
        cout << "Sorted Array Odd: " << array << endl;
        cout << "The median is: " << median << endl;
    }

    return median;
}

// int main()
// {
//     int test[] = {3, 4, 8, 9, 2, 9, 5, 9, 4, 2};
//     int arraySize = 10;
//     std::cout << "Median = " << findMedian(test, arraySize) << std::endl;
// }
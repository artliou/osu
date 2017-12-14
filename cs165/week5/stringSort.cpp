/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/25/17
 ** Description: Project 4.c

 Selection sort function that sorts an array of C++ strings (std::string)
 Two parameters: an array of strings, and the size of the array.

 *********************************************************************/

#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void showArray(const string array[], int);
void stringSort(string[], int);

void stringSort(string array[], int size)
{
    int minIndex;
    string minValue;

    for (int startScan = 0; startScan < (size - 1); startScan++)
    {
        minIndex = startScan;
        minValue = array[startScan];

        for (int index = startScan + 1; index < size; index++)
        {
            //toUpperCompare
            string word = array[index];
            word[0] = toupper(word[0]);

            string upperMin = array[minIndex];
            upperMin[0] = toupper(upperMin[0]);

            if (word < upperMin)
            {
                minValue = array[index];
                minIndex = index;
            }
        }
        array[minIndex] = array[startScan];
        array[startScan] = minValue;
    }
}

void showArray(const string array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

// int main()
// {
//     int size = 4;
//     string list[4] = {"zebra", "Zeppelin", "allen", "Flash"};

//     cout << "The unsorted strings are\n";
//     showArray(list, size);
//     stringSort(list, size);
//     cout << "The sorted strings are\n";
//     showArray(list, size);

//     return 0;
// }

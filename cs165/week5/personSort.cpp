/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/25/17
 ** Description: Project 4.b

BubbleSort from Chapter 9
 It should take two parameters, an array of Persons, and the size of the array.  Your function must be named personSort.

 *********************************************************************/
#include <stdio.h>
#include <iostream>
#include "Person.hpp"
// #include "Person.cpp"

using namespace std;

void showArray(Person array[], int);
void personSort(Person array[], int);

void personSort(Person array[], int size)
{
    Person temp;
    bool swap;

    do
    {
        swap = false;
        for (int count = 0; count < (size - 1); count++)
        {
            // cout << "Internal Loop: " << array[count].getName() << endl;
            if (array[count].getAge() < array[count + 1].getAge())
            {
                temp = array[count];
                array[count] = array[count + 1];
                array[count + 1] = temp;
                swap = true;
            }
            showArray(array, size);
        }
    } while (swap); //loop again if a swap occurred on this pass
}

void showArray(Person array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        string name = array[i].getName();
        double age = array[i].getAge();
        cout << name << ": " << age << endl;
    }
    cout << endl;
}

// int main()
// {
//     const int SIZE = 3;
//     Person people[] = {
//         Person("alice", 21),
//         Person("caroline", 18),
//         Person("bob", 30),
//     };
// Person p0("Archibald", 42);
// Person p1("Bertrand", 19);
// Person p2("Charles", 54);
// Person array[] = {p0,p1,p2};
//     personSort(people, SIZE);
//     cout << "\n Sorted Contents of the first array.\n";
//     showArray(people, SIZE);

//     return 0;
// }

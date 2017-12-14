/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/18/17
 ** Description: Project 4.b

Finds the standard deviation for age for an array of Persons.
It takes in an array of persons and an int size and returns a double.

 *********************************************************************/

#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string>
#include "Person.hpp"
using namespace std;

// Given in Mimir Testing
// #include "Person.cpp"
// #include <cmath>

double stdDev(Person array[], int size)
{
    // Syntax of (*array)[] is pointer to array
    double sum, mean, temp;
    mean = 0.0;
    sum = 0.0;

    for (int i = 0; i < size; ++i)
    {
        // double output = array[i].getAge();
        // cout << "Age Added: " << output << endl;
        sum += array[i].getAge();
    }

    mean = sum / size;
    for (int i = 0; i < size; ++i)
        temp += pow(((array)[i].getAge() - mean), 2);

    return sqrt(temp / size);
}

// int main()
// {
//     Person a("alice", 92);
//     Person b("bernice", 77);
//     Person array[] = {a, b};
//     double result = stdDev(array, 2);
//     cout << "Standard Deviation = " << stdDev(array, 2) << " and result: " << result << endl;
//     // cout << "Age: " << a.getAge() << endl;

//     // Mimir Testing where Fabs should equal 0
//     const double EPS = 0.00001;
//     double fab = fabs(result - 7.5);
//     cout << "Fabs: " << fab << endl;
//     // ASSERT_TRUE(fabs(result - 7.5) < EPS);
// }

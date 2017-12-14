
/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 9/26/17
 ** Description: Project 1.c

 1.b
 Please enter five numbers.
 -2.4
 5.1
 6.0
 123.8
 -19.0
 The average of those numbers is:
 22.7

 Ask for 5 numbers,
 Create N and I
 n is total sum
 if i is less than 5, then N + (function (N)
 if i = 5,
 return n/5

 *********************************************************************/

#include <iostream>
#include <string>

// Project 1.c
int main()
{
    double total; //Variable to collect sum of all inputs
    double average; //Variable to hold average
    double number; //Number inputted by user

    //Created a loop, for if counter is under 5 (or not equal), then stores inputs in total
    //Then ends loop after getting 5 numbers
    std::cout << "Please enter five numbers." << std::endl;

    for (int i = 0; i != 5; ++i)
    {
        std::cin >> number;
        total += number;
    }

    average = total / 5.0;

    std::cout << "The average of those numbers is:" <<std::endl;
    std::cout << average << std::endl;

    return 0;
}

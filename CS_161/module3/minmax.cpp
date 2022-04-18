/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 10, 2016
** Description:  Module 3.a assignment
*********************************************************************/

#include <iostream>

/*********************************************************************
** Description: Assignment 3.a
**
** Read n integers and prints out the min/max
**
**
*********************************************************************/

/*********************************************************************
** Definitions
**
*********************************************************************/

#define INT_MAX 0x7FFFFFFF
#define INT_MIN 0x80000000

/*********************************************************************
** int main()
**
** Program entry point
**
*********************************************************************/

int main()
{
    int minimum = INT_MAX;
    int maximum = INT_MIN;
    int counter = 0;
    int test_value;

    std::cout << "How many integers would you like to enter?" << std::endl;
    std::cin >> counter;
    while (counter < 1)
    {
        std::cout << "Invalid input. Please enter an integer greater than 1!" << std::endl;
        std::cin >> counter;
    }

    std::cout << "Please enter " << counter << " integers." << std::endl;

    while (counter)
    {
        std::cin >> test_value;
        if (test_value > maximum)
        {
            maximum = test_value;
        }
        if (test_value < minimum)
        {
            minimum = test_value;
        }
        counter--;
    }
    std::cout << "Minimum: " << minimum << std::endl;
    std::cout << "Maximum: " << maximum << std::endl;
    return 0;
}

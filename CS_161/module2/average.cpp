/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 6, 2016
** Description:  Module 2.a assignment
*********************************************************************/

#include <iostream>
#include <string>

/*********************************************************************
** Description: Assignment 2.a
**
** Read 5 doubles into a temporary variable, then print out the average
**
**
*********************************************************************/

/*********************************************************************
** Definitions
**
*********************************************************************/

#define NUM_VALUES_TO_AVERAGE 5

/*********************************************************************
** int main()
**
** Program entry point
**
*********************************************************************/

int main()
{
	int temp_value_counter = NUM_VALUES_TO_AVERAGE;
	double total_counter = 0;

    std::cout << "Please enter " << NUM_VALUES_TO_AVERAGE << " numbers." << std::endl;
    while (temp_value_counter--)
    {
    	double temp_counter;
        std::cin >> temp_counter;
        total_counter += temp_counter;
    }
    std::cout << "The average of those numbers is:" << std::endl << total_counter / NUM_VALUES_TO_AVERAGE << std::endl;
    return 0;
}

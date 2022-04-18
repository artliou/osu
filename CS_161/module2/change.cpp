/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 6, 2016
** Description:  Module 2.c assignment
*********************************************************************/

#include <iostream>
#include <string>
#include <assert.h>

/*********************************************************************
** Description: Assignment 2.c
**
** Accepts an input from 0-99 and returns an ammount of equivalent
** pocket change
**
**
*********************************************************************/

/*********************************************************************
** Definitions
**
*********************************************************************/

#define VALUE_QUARTER 25
#define VALUE_DIME    10
#define VALUE_NICKEL  5
#define VALUE_PENNY   1

#define RESULT_SUCCESS 0
#define RESULT_FAIL    -1

/*********************************************************************
** void convert_cents (int cents, int * num_quarters, int * num_dimes, int * num_nickles, int * num_pennies)
**
** Convert cents to equivalent coin counts
**
** Inputs : cents (int) (0-99) The ammount of money
**        : output pointers to int objects to increment for coin counts
**
*********************************************************************/

void convert_cents (int cents, int * num_quarters, int * num_dimes, int * num_nickles, int * num_pennies)
{
	cents -= ((*num_quarters) = cents / VALUE_QUARTER) * VALUE_QUARTER;
	cents -= ((*num_dimes)    = cents / VALUE_DIME)    * VALUE_DIME;
	cents -= ((*num_nickles)  = cents / VALUE_NICKEL)  * VALUE_NICKEL;
	cents -= ((*num_pennies)  = cents / VALUE_PENNY)   * VALUE_PENNY;
	assert(!cents);
}


/*********************************************************************
** int main()
**
** Program entry point
**
*********************************************************************/

int main()
{
    int incoming_data_cents = 0;

    int num_quarters = 0;
    int num_dimes = 0;
    int num_nickles = 0;
    int num_pennies = 0;

    std::cout << "Please enter an ammount in cents less than a dollar." << std::endl;
    std::cin >> incoming_data_cents;

    if ((incoming_data_cents < 0) || (incoming_data_cents > 99))
    {
    	std::cout << "Sorry, you entered a value out of range.\n\nExpected 0-99." << std::endl;
    	return RESULT_FAIL;
    }

    convert_cents (incoming_data_cents, &num_quarters, &num_dimes, &num_nickles, &num_pennies);

    std::cout << "Your change wil be:"    << "\n" <<
            "Quarters:\t" << num_quarters << "\n" <<
            "Dimes:\t\t"  << num_dimes    << "\n" <<
            "Nickles:\t"  << num_nickles  << "\n" <<
	    "Pennies:\t"  << num_pennies  << std::endl;
    return RESULT_SUCCESS;
}

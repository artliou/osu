
/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 9/26/17
 ** Description: Project 1.e

 1.e

 Write a program that asks the user for a (integer) number of cents, from 0 to 99, and outputs how many of each type of coin would represent that amount with the fewest total number of coins.  When you run your program, it should match the following format:
 Please enter an amount in cents less than a dollar.
 87
 Your change will be:
 Q: 3
 D: 1
 N: 0
 P: 2

 Hint: You will find the mod operator (%) and integer division useful.

 Strategy (or no recursion?)
 if x>25, then q+1 & x-25; function (x); for quarters
 if x>10, then d+1 & x-10; function (x); for dimes
 if x>5, then d+1 & x-5; function (x); for Nickels
 if x>1, then d+1 & x-5; function (x); for Nickels
 return Q, D, N, P

 *********************************************************************/

#include <iostream>
#include <string>

// Project 1.e
int main()
{
    double amount;
    int quarters;
    int dimes;
    int nickels;
    int pennies;
    double newamount;

    std::cout << "Please enter an amount in cents less than a dollar." << std::endl;
    std::cin >> amount;

    quarters = amount / 25.0;
    newamount = amount - (quarters*25.0);
    dimes = newamount / 10.0;
    newamount = newamount- (dimes*10.0);
    nickels = newamount / 5.0;
    newamount = newamount - (nickels*5.0);
    pennies = newamount / 1.0;

    std::cout << "Your change will be:" <<std::endl;
    std::cout << "Q: " << quarters <<std::endl;
    std::cout << "D: " << dimes <<std::endl;
    std::cout << "N: " << nickels <<std::endl;
    std::cout << "P: " << pennies <<std::endl;

    return 0;
}

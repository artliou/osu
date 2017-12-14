/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/3/17
 ** Description: Project 2.c

 *********************************************************************/

#include <iostream>
#include <string>

// a simple example program
int main()
{
    int tries = 0;
    int number, guess;

    std::cout << "Enter the number for the player to guess." << std::endl;
    std::cin >> number;
    std::cout << "Enter your guess." << std::endl;
    std::cin >> guess;

    while (guess != number)
    {
        if (guess > number)
        {
            std::cout << "Too high - try again." << std::endl;
            tries += 1;
            std::cin >> guess;
        }
        else if (guess < number)
        {
            std::cout << "Too low - try again." << std::endl;
            tries += 1;
            std::cin >> guess;
        }
    }
    //if correct, add one and output it
    tries += 1;

    std::cout << "You guessed it in " << tries;
    std::cout << " tries." << std::endl;

    return 0;
}

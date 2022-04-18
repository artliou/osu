/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 10, 2016
** Description:  Module 3.c assignment
*********************************************************************/

#include <iostream>

/*********************************************************************
** Description: Assignment 3.c
**
** Enter a random number
** Count tries it takes to guess number
** Tell user if high/low and total tries
**
**
*********************************************************************/

/*********************************************************************
** Definitions
**
*********************************************************************/


/*********************************************************************
** int main()
**
** Program entry point
**
*********************************************************************/

int main()
{
    int random_number;
    int total_count = 0;
    int player_guess;
    bool playing = true;

    std::cout << "Enter the number for the player to guess." << std::endl;
    std::cin >> random_number;

    std::cout << "Enter your guess." << std::endl;

    while (playing)
    {
        std::cin >> player_guess;
        total_count++;
        if (player_guess > random_number)
        {
            std::cout << "Too high - try again." << std::endl;
        }
        else if (player_guess < random_number)
        {
            std::cout << "Too low - try again." << std::endl;
        }
        else if (player_guess == random_number)
        {
            playing = false;
            std::cout << "You guessed it in " << total_count << " tries." << std::endl;
        }
    }

    return 0;
}

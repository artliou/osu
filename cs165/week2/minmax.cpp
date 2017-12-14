/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/3/17
 ** Description: Project 2.a

 *********************************************************************/

#include <iostream>
#include <string>

// a simple example program
int main()
{
    int total;
    int counter;
    int current;
    int max, min;

    std::cout << "How many integers would you like to enter?" << std::endl;
    std::cin >> total;

    std::cout << "Please enter " << total;
    std::cout << " integers." << std::endl;
    std::cin >> current;

    max = current;
    min = current;
    counter = 1;

    while (counter < total)
    {
        std::cin >> current;
        counter = counter + 1;
        if (current < min)
        {
            min = current;
        }
        else if (current > max)
        {
            max = current;
        }
    }
    if (current < min)
    {
        min = current;
    }
    else if (current > max)
    {
        max = current;
    }

    std::cout << "min: " << min << std::endl;
    std::cout << "max: " << max << std::endl;

    return 0;
}

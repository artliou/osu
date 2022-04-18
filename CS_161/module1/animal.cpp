/*********************************************************************
** Author:       Jeremy Prater
** Date:         Today
** Description:  Module 1 assignment
*********************************************************************/

#include <iostream>
#include <string>

/*********************************************************************
** Description: Program entry point
**
*********************************************************************/

// a simple example program
int main()
{
    std::string faveAnimal;
    std::cout << "Please enter your favorite animal." << std::endl;
    std::cin >> faveAnimal;
    std::cout << "Your favorite animal is the " << faveAnimal;
    std::cout << "." << std::endl;    
    
    return 0;
}

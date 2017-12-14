
/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 9/26/17
 ** Description: Project 1.b

 1.b

 *********************************************************************/

#include <iostream>
#include <string>

// Project 1.b
int main()
{
    double soil;
    double seeds;
    double fence;
    double cost;

    std::cout << "What does the soil cost?" << std::endl;
    std::cin >> soil;
    std::cout << "What do the flower seeds cost?" << std::endl;
    std::cin >> seeds;
    std::cout << "What does the fence cost?" << std::endl;
    std::cin >> fence;

    cost = soil + seeds + fence;

    std::cout << "The total cost is " << cost;
    std::cout << std::endl;

    return 0;
}

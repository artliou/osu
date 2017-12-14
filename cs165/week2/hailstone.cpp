/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/3/17
 ** Description: Project 2.f


 *********************************************************************/

#include <iostream>
#include <string>
using namespace std;

int hailstone(int start)
{
    int count = 0;
    while (start != 1)
    {
        if (start % 2 == 0)
        { //if event
            start = start / 2;
            count += 1;
            cout << start << endl;
        }
        else
        { //if odd
            start = 3 * start + 1;
            count += 1;
            cout << start << endl;
        }
    }
    //std::cout << count << std::endl;
    return count;
}
/***
int main () {
    int input;
    cout << "How many hailstones?" << endl;
    cin >> input;
    hailstone(input);
    return 0;
}
***/

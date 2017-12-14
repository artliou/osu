/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/1/17
 ** Description: Project 6.b

Prompt
 Write two recursive functions - one should take as a parameter a C++ string of '1's and '0's that are the binary representation of a positive integer, and return the equivalent int value;
 the other should take as a parameter a positive int value, and return a C++ string of '1's and '0's that are the binary representation of that number (no leading zeros).
 The functions should be named binToDec and decToBin. Do not use any number base conversion functionality that is built into C++.
 *********************************************************************/

#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h> //for stoi (convert string to int)

using namespace std;

/***
 * Takea a binary string and converts to integer value
 * **/
int binToDec(string bin)
{
    long len = bin.length();
    if (len == 0)
    {
        return 0;
    }
    else
    {
        std::string now = bin.substr(0, 1);
        std::string later = bin.substr(1);
        return stoi(now) * pow(2, len - 1) + binToDec(later);
    }
}

/***
 *Takea a positive integer num and converts that num to a binary string
 * In this format, there shouldn't be any leading zeros.
 * **/
string decToBin(int num)
{
    if (num == 0)
    {
        return "0";
    }
    else if (num == 1)
    {
        return "1";
    }
    else
    {
        return decToBin(num / 2) + decToBin(num % 2);
    }
}

// int main()
// {
//     //Test binToDec
//     string bin = "100";
//     cout << "The decimal of 100 is " << binToDec(bin) << endl; //0101

//     //Test decToBin
//     cout << "The binary string of 5 is " << decToBin(5) << endl;     //0101
//     cout << "The binary string of 101 is " << decToBin(101) << endl; //01100101

//     return 0;
// }

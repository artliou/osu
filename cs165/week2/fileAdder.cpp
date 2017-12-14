/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/3/17
 ** Description: Project 2.b

 *********************************************************************/

#include <iostream>
#include <fstream> //to read from file
#include <string>
#include <cstdlib> // For exit function
using namespace std;

int main()
{
    ofstream sumfile; //be able to write on sumfile
    ifstream file;    // read from input file
    string name;

    //get file name and try to open it
    std::cout << "Please enter your filename." << std::endl;
    std::cin >> name;
    //Tries to open file
    file.open(name.c_str(), ios::in);

    //if open then gather sum, close file, create sumfile, put sum in, and close sumfile
    if (file.is_open())
    {
        int x = 0;
        int sum = 0;
        while (!file.fail())
        {
            // cout << "Read integer: " << x << endl;
            file >> x;
            sum += x;
            // cout << "The sum of x = " << x << "\t" << sum;
        }
        sum -= x;

        file.close();

        //to create sum.txt
        sumfile.open("sum.txt");
        sumfile << sum;
        sumfile.close();

        cout << "result written to sum.txt" << std::endl;
        return 0;
    }
    //print "could not access file" if unable to open
    else
        std::cout << "could not access file" << std::endl;
    return 0;
}

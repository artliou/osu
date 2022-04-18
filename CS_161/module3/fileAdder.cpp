/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 10, 2016
** Description:  Module 3.b assignment
*********************************************************************/

#include <iostream>
#include <string>
#include <fstream>

/*********************************************************************
** Description: Assignment 3.b
**
** Open a file as entered by the user
** Check if it a valid file
** Read integer contents
** Sum contents
** Close file
** Open output file
** Check if output file is valid
** Write the summation
** Close output
**
**
*********************************************************************/

/*********************************************************************
** Definitions
**
*********************************************************************/

#define OUTPUT_FILE "./sum.txt"

/*********************************************************************
** int main()
**
** Program entry point
**
*********************************************************************/

int main()
{
    std::ofstream output_file;
    std::ifstream input_file;
    std::string input_file_name;
    int temp_input;
    int total_count = 0;
    bool processing = true;

    std::cout << "Enter the filename of the source data." << std::endl;
    std::cin >> input_file_name;
    input_file.open (input_file_name.c_str());
    if (!input_file.is_open())
    {
        std::cout << input_file_name << " not found!!" << std::endl;
        return -1;
    }
    while (processing)
    {
        input_file >> temp_input;
        if (input_file.eof())
        {
            processing = false;
        }
        else
        {
            total_count += temp_input;
        }
    }
    input_file.close();
    output_file.open (OUTPUT_FILE);
    if (output_file.is_open())
    {
        std::cout << "Writing data to : " << OUTPUT_FILE << std::endl;
        output_file << total_count;
        output_file.close();
    }
    else
    {
        std::cout << "Error opening " << OUTPUT_FILE << " for writing!!" << std::endl;
        return -1;    
    }
    return 0;
}

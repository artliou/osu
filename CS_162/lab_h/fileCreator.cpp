/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 12, 2016
** Description:  fileCreator.cpp
*********************************************************************/

#include "fileCreator.hpp"
#include <fstream>
#include <iostream>
#include "lib_flip_display.hpp"

int fileCreator::createFile()
{
    std::string fileName;
    std::string numItemsString;
    bool validNumber;
    int numItems;
    DebugConsole::debug_print(0, true, COLOR_GREEN, "CS_162 Lab-H file creator.\n\n");
    DebugConsole::debug_print(0, true, COLOR_WHITE, "Enter filename: ");
    std::cin >> fileName;
    DebugConsole::debug_print(0, true, COLOR_WHITE, "Enter number of integers to create: ");
    std::cin >> numItemsString;
    try
    {
        numItems = std::stoi (numItemsString, __null, 10);
    }
    catch (const std::exception& error)
    {
        DebugConsole::debug_print(0, true, COLOR_RED, "Invalid Number: %s\n\n", numItemsString.c_str());
        return -1;
    }
    return fileCreator::createFileDirect(fileName, numItems);
}

int fileCreator::createFileDirect(std::string fileName, int numItems)
{
    if (numItems <= 0)
    {
        DebugConsole::debug_print(0, true, COLOR_RED, "Invalid Number: %d\n\n", numItems);
        return -1;
    }
    std::ofstream * outputFile;
    try
    {
        outputFile = new std::ofstream(fileName.c_str());
    }
    catch (const std::exception& ex)
    {
        DebugConsole::debug_print(0, true, COLOR_RED, "File error! Filename:%s, error %s\n\n", fileName.c_str(), ex.what());
        return -1;
    }
    if (!outputFile->good())
    {
        DebugConsole::debug_print(0, true, COLOR_RED, "File access error! %s\n\n", fileName.c_str());
        return -1;
    }
    DebugConsole::debug_print (0, true, COLOR_CYAN, "Generating %d items into file %s!\n\n", numItems, fileName.c_str());
    for (int counter = 0; counter < numItems; counter++)
    {
        *outputFile << rand();
        if (counter < (numItems-1))
        {
            *outputFile << ", ";
        }
        *outputFile << std::endl;
    }
    delete outputFile;
    return 0;
}

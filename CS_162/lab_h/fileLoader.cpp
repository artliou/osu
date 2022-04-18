#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "fileLoader.hpp"
#include <string.h>
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// fileLoader::fileLoader
//
// fileLoader constructor
//
// Parameters:
//        std:string filename - File to load into memory
//
// Return:
//        None
//

fileLoader::fileLoader (std::string filename)
{
    dataBufferCapacity = 5;
    dataBufferCount = 0;
    dataBuffer = (int*)malloc (dataBufferCapacity * sizeof (int));
    fileName = filename;
    std::ifstream file (fileName);
    std::string data;
    while ( file.good() )
    {
        std::getline (file, data, ',' );
        data.erase(std::remove(data.begin(), data.end(), ' '), data.end());
        AddData (std::stoi(data));
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// fileLoader::~fileLoader
//
// fileLoader destructor
//
// Parameters:
//        None
//
// Return:
//        None
//

fileLoader::~fileLoader()
{
    free (dataBuffer);
}

///////////////////////////////////////////////////////////////////////////////
//
// fileLoader::AddData (int data)
//
// Add an integer to the fileData data buffer
//
// Parameters:
//        int data - data to add
//
// Return:
//        None
//

void fileLoader::AddData (int data)
{
    dataBuffer[dataBufferCount++] = data;
    if (dataBufferCount == dataBufferCapacity)
    {
        dataBufferCapacity *= 2;
        dataBuffer = (int*)realloc (dataBuffer, dataBufferCapacity * sizeof (int));           
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// fileLoader::GetBuffer()
//
// Get the raw data pointer
//
// Parameters:
//        None
//
// Return:
//        int * - pointer to data buffer
//

int * fileLoader::GetBuffer()
{
    return dataBuffer;
}

///////////////////////////////////////////////////////////////////////////////
//
// fileLoader::GetCount()
//
// Get the number of items in the buffer
//
// Parameters:
//        None
//
// Return:
//        int - number of items in the buffer
//

int fileLoader::GetCount()
{
    return dataBufferCount;
}

///////////////////////////////////////////////////////////////////////////////
//
// fileLoader::SaveData (std::string filename)
//
// Save the data in the data buffer to a CSV file
//
// Parameters:
//        std:string filename - File to save
//
// Return:
//        None
//

void fileLoader::SaveData(std::string filename)
{
    DebugConsole::debug_print (0, true, COLOR_GREEN, "Saving data to  %s\n\n", filename.c_str());
    std::ofstream output (filename);
    fileName = filename;
    for (int index = 0; index < dataBufferCount; index++)
    {
        output << dataBuffer[index];
        if (index < dataBufferCount - 1)
        {
            output << ", ";
        }
    }        
}

///////////////////////////////////////////////////////////////////////////////
//
// fileLoader::PrintData
//
// Print a linear list of the integers contained in the data buffer
//
// Parameters:
//        None
//
// Return:
//        None
//

void fileLoader::PrintData()
{
    DebugConsole::debug_print (0, true, COLOR_GREEN, "Printing values:\n\n");
    for (int index = 0; index < dataBufferCount; index++)
    {
        DebugConsole::debug_print (0, false, COLOR_WHITE, "%d: %d\n", index, dataBuffer[index]);
    }    
}

///////////////////////////////////////////////////////////////////////////////
//
// fileLoader::LinearSearch
//
// Preform a linear search through data buffer for a value
//
// Parameters:
//        int value - value to find
//
// Return:
//        int - position of the value, or -1 if not found 
//
// References:
//        None - I wrote this function my self. Linear search is not very complicated.
//
// Algorithm:
//        For index = 0 to last array subscript
//          If array[index] is equal to desired value
//              return index
//          End If
//        End For
//

int fileLoader::LinearSearch(int value)
{
    DebugConsole::debug_print (0, true, COLOR_WHITE, "Preforming Linear Search.\n");
    for (int searchIndex = 0; searchIndex < dataBufferCount; searchIndex++)
    {
        if (dataBuffer[searchIndex] == value)
        {
            DebugConsole::debug_print (0, true, COLOR_GREEN, "%d was found at index %d in %s\n",value, searchIndex, fileName.c_str());
            return searchIndex;
        }
    }
    DebugConsole::debug_print (0, true, COLOR_YELLOW, "%d was not found in %s\n",value, fileName.c_str());
    return -1;
}

///////////////////////////////////////////////////////////////////////////////
//
// fileLoader::BubbleSort()
//
// Sort contents of data buffer using a bubble sort algorithm
//
// Parameters:
//        None
//
// Return:
//        None
//
// References:
//        C++ Early Objects, Tony Gaddis, Pg. 598
//
// Algorithm:
//        Do
//          Set swap flag to false
//          For Count = 0 to next-to-last array subscript
//              If array[Count] is greater than array[Count + 1]
//                  Swap the contents of array[Count] and array[Count + 1]
//                  Set swap flag to true
//              End If
//          End For
//        While the swap flag is true                  
//

void fileLoader::BubbleSort()
{
    DebugConsole::debug_print (0, true, COLOR_WHITE, "Preforming Bubble Sort.\n");
    int tempStorage;
    bool sorting = true;
    do
    {
        sorting = false;
        for (int sortIndex = 0; sortIndex < dataBufferCount - 1; sortIndex++)
        {
            if (dataBuffer[sortIndex] > dataBuffer[sortIndex + 1])
            {
                tempStorage = dataBuffer[sortIndex];
                dataBuffer[sortIndex] = dataBuffer[sortIndex + 1];
                dataBuffer[sortIndex + 1] = tempStorage;
                sorting = true;
            }
        }
    } while(sorting);
}

///////////////////////////////////////////////////////////////////////////////
//
// fileLoader::BinarySearch(int value)
//
// fileLoader constructor
//
// Parameters:
//        int value - value to find
//
// Return:
//        int - position of the value, or -1 if not found 
//
// References:
//        C++ Early Objects, Tony Gaddis, Pg. 598
//
// Algorithm:
//
//        Set first to 0
//        Set last to the last subscript of the array
//        Set found to false
//        Set position to -1
//        While found is not true and first is less than or equal to last
//              Set middle to the subscript half way between first and last
//              If array[middle] equals the desired value
//                  Set found to true
//                  Set postion to middle
//              Else If array[middle] is greater than the desired value
//                  Set last to middle - 1
//              Else
//                  Set first to middle + 1
//              End if
//        End While
//        Return position

int fileLoader::BinarySearch (int value)
{
    DebugConsole::debug_print (0, true, COLOR_WHITE, "Preforming Binary Search.\n");
    int firstIndex = 0;
    int lastIndex = dataBufferCount - 1;
    int middleIndex;
    int position = -1;
    bool foundValue = false;
    while (!foundValue && (firstIndex <= lastIndex))
    {
        middleIndex = (firstIndex + lastIndex) / 2;
        if (dataBuffer[middleIndex] == value)
        {
            foundValue = true;
            position = middleIndex;
            DebugConsole::debug_print (0, true, COLOR_GREEN, "%d was found at index %d in %s\n",value, position, fileName.c_str());
        }
        else if (dataBuffer[middleIndex] > value)
        {
            lastIndex = middleIndex - 1;
        }
        else
        {
            firstIndex = middleIndex + 1;
        }
    }
    if (position == -1)
    {
        DebugConsole::debug_print (0, true, COLOR_YELLOW, "%d was not found in %s\n",value, fileName.c_str());
    }
    return position;
}
#ifndef FILE_LOADER_HPP
#define FILE_LOADER_HPP

#include <string>

/////////////////////////////////////////////////
//
// class fileLoader
//
// A class for loading CSV files
//
// This class can preform the following functions
//
//    - Linear Search
//    - Bubble sort
//    - Binary Search
//    - Print Data
//    - Save Data
//    - Get the raw buffer pointer
//

class fileLoader
{
private:
    std::string fileName;
    int * dataBuffer;
    int dataBufferCapacity;
    int dataBufferCount;
    void AddData(int data);

public:
    fileLoader (std::string filename);
    ~fileLoader();

    int * GetBuffer();
    void SaveData(std::string filename);
    void PrintData();
    int LinearSearch(int value);
    void BubbleSort();
    int BinarySearch(int value);
};

#endif /// FILE_LOADER_HPP

/***************************************************
 ** Author: Patrick Mullaney
 ** Description: Function that takes an array as a
 ** parameter and returns a vector in ascending order
 ** Date: 5/9/2016
 ****************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
int main()

{
    int arrayData[] = {3,2,4,2,5,3,6,7,6,1};
    int arraySize = 10;
    //int arrayData[] = {1,7,1,7,6,6,8,7,9,1,9,8};
    //int arraySize = 12;
    vector <int> findMode(int arrayData[], int arraySize);
    
    vector<int> result = findMode(arrayData, arraySize);
    
    cout << "array: ";
    for (int j = 0; j < arraySize; j++)
    {
        cout << arrayData[j] << " ";
    }
    // cout << "array: " << arrayData[1] << "\n"; ***test array wasn't changed
    cout << "\nresult: " << result[1] << "\n";
    
    int numElements = result.size();
    cout << "vector size: " << numElements << "\n";
    
    cout << "vector: ";
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    return 0;
} */

vector<int> findMode(int arrayData[], int arraySize)
{
    // Initial highest frequency
    int highestFrequency = 0;
    
    // Vector that stores modes
    vector<int> result;
    
    // sort(arrayData, arrayData + arraySize);  // sort array
    // cout << "array: " << arrayData[0];
    
    // Outer for loop, count elements in the array
    for(int i = 0; i < arraySize; i++)
    {
        // Initialize to count frequnecy of elements in iteration
        int frequency = 0;
        
        // Inner for loop to count frequency
        for(int j= i + 1; j < arraySize; j++)
        {
            // If number repeats, add to frequency counter
            if (arrayData[i] == arrayData[j])
            {
                frequency++;
                // cout << arrayData[i];
                // highestFrequency = frequency;
            }
        }
        // If the frequency counter matches highest frequency, push to vector
        if (frequency == highestFrequency)
        {
            // Push mode to vector
            result.push_back(arrayData[i]);
        }
/****************************************************************************************
** Else if: If frequency count is greater than highestFrequency, update highestFrequency
** by assigning the value of frequency, clear out the modes previously stored in vector
**(as they are no longer the most frequent integer) and push new modes to vector.
****************************************************************************************/
        else if (frequency > highestFrequency)
        {
            highestFrequency = frequency; //update highestFrequency with new most frequent number
            
            // clear out the modes previously stored in vector as they are no longer most frequent integer
            result.clear();
            
            // push new mode to vector
            result.push_back(arrayData[i]);
        }
    }
    
    //use sort to place in ascending order
    std::sort(result.begin(), result.end());
    
    /*******************************************************************
     ** Extra for loop to ensure removal of duplicate numbers in vector,
     ** seem to cause runtime errors, so removing
     ********************************************************************
     // for (int k = 0; k < arraySize; k++) {
     for (int l = k+1; l < arraySize; l++)
     if (result[k] == result[l]){
     result.pop_back();
     }
     }
     ********************************************************************/
    return result;
}
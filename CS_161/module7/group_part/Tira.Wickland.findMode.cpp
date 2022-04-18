/****************************************************************************
**  Author: Tira Wickland
**  Date: 05/05/16
**  Description:  findMode function iterates through an array to find the 
**  mode of the array and returns it in a vector.
****************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> findMode(const int[], int);  //prototype of function


vector<int> findMode(const int array[], int size)
{
    int highest = 0;  //highest will keep track of mode
    vector<int> mode;  //mode is an empty int vector

    //iterate through the elements of the array
    for (int element = 0; element < size; element++)
    {
        int temp = array[element];  //set the current element to temp
        int total = 0;  //accumulator

        //iterate through the elements to compare them to temp
        for (int compare = 0; compare < size; compare++)
        {
            if (temp ==array[compare])  //if the element is present
                total++;  //increase the count
        }
        if (total>= highest)  //if the count exceeds the current highest
            highest = total;  //set the count as now the most frequent element
    }

    //iterate through the elements of the array again
    for (int element = 0; element < size; element++)
    {
        int current = array[element];  //set the current element to current
        int total = 0;  //accumulator

        //iterate through the elements to compare them
        for (int compare = 0; compare < size; compare++)
        {
            if (current == array[compare])  //if the element is present
                total++;  //increase the count
        }
        if (total == highest)  //now if the current element is most frequent
        {
            mode.push_back(current);  //add its value to the vector

            bool present = false;  //initiate present to false

            //iterate through the vector (except the recent value added)
            for (int count=0; count <mode.size()-1; count++)

                //if the current element has already been added
                if(current == mode[count])
                    present = true;   //change present to true

            //if it has been is already present
            if (present)
                mode.pop_back();  //remove the copy
        }
    }

    sort(mode.begin(), mode.end());  //sort the vector
    return mode;  //return the vector
}

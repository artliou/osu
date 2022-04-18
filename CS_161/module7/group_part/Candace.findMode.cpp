//
//  findMode.cpp
//  Assignment 7
// Samuel Morey
//  Candace Stofer, 5/11/16.
//
//

#include <iostream>
#include <vector>
#include <math.h>


//typedef int arraySorted[];

void findMode(int array[], int n);
std::vector<int> result;

const int Num=10000; //*********what happens if we dont know what this is? IE what if there were >>10000 instances??
int arrayMode[Num];

/*********************MAIN COMMENT OUT
int main()
{

    int n; //n=numbers in array, arrayIndex is counter
    
    std::cout<<"Enter number of digits in array: ";
    std::cin>>n;
    
    int array[n];
    
    for (int arrayIndex=0; arrayIndex<n; arrayIndex++) //populate array of n integets
    {
        std::cout<<"Int #"<<(arrayIndex+1)<<": ";  //index initialize to 1
        std::cin>>array[arrayIndex];
    }


findMode(array, n);

    return 0;
}
 *********************MAIN COMMENT OUT****/


void findMode(int array[], int n)
{
    int arrayMode[Num]={0}; //initialized to 0
    int modeOccur=0, max=0;
    std::vector<int> result;
    std::vector<int>::iterator val;
    
        for(int k=0; k<n-1; k++)
    {
        int count=0; //have to redeclare in case no ints are in array. test
        int arrayLength=array[k]; //number digits in array
        
        for(int i=k; i<n; i++)
        {
            if(arrayLength==array[i])
                count++;
        }
        arrayMode[k]=count;
    }
    
    //find highest number in array
    for(int j=0; j<n; j++)
    {
        if(arrayMode[j]>max)
            max=arrayMode[j];
    }
    
    for(int m=0; m<n; m++) //frequency
    {
        if(max==arrayMode[m])
            modeOccur++;
    }
    
    //send to result vector
    for (int m=0; m < n; m++)
    {
        if(max == arrayMode[m])
            result.push_back(array[m]);
    }
    
    std::sort(result.begin(), result.end());
    std::cout<< "The mode(s) are: ";
    for (val=result.begin(); val!=result.end(); ++val)
    {
        std::cout<<*val<< " ";
    }
}

/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/18/17
 ** Description: Project 4.d

 This function replaces the array with one that is twice as large, with the values from the original array appearing twice.

 *********************************************************************/

#include <iostream>
using std::cout;
using std::endl;

void repeatArray(double *&array, int size)
{
  int newSize = size * 2;
  //create new array and set to new size.
  double *newArray = new double[newSize];

  for (int i = 0; i < newSize; i++)
  {
    if (i < size)
    {
      newArray[i] = array[i];
    }
    else if (i >= size)
    {
      newArray[i] = array[i - size];
    }
  }

  //To Free Heap Memory & Prevent Memory Leaks
  delete[] array;
  array = newArray;
}

// int main()
// {
//   double *myArray = new double[3];
//   for (int i = 0; i < 3; i++)
//     myArray[i] = (i + 1) * 2;

//   repeatArray(myArray, 3);

//   for (int i = 0; i < 6; i++)
//     cout << myArray[i] << endl;

//   delete[] myArray;
// }
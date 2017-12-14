/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/15/17

 ** Description: Project 8.a

 *********************************************************************/

#ifndef ValSet_hpp
#define ValSet_hpp

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class ValSet
{
private:
  T *aptr;       //Pointer-To-T
  int arraySize; //Current Array Size
  int numValue;  //Number of Values Current Part of Set
public:
  //Constructor
  ValSet()
  {
    arraySize = 10;
    numValue = 0;
    aptr = new T[arraySize];
  }

  //Copy Constructor
  ValSet(const ValSet &obj)
  {
    arraySize = obj.arraySize;
    aptr = new T[arraySize];
    numValue = 0;

    for (int count = 0; count < arraySize; count++)
    {
      aptr[count] = obj.aptr[count];
      numValue++;
    }
  }

  //Overloaded [] operator
  ValSet<T> &operator=(const ValSet &assignSet)
  {
    arraySize = assignSet.arraySize;
    numValue = assignSet.numValue;
    aptr = new T[arraySize];

    for (int i = 0; i < arraySize; i++)
    {
      aptr[i] = assignSet.aotr[i];
    }
    delete[] aptr;
    return *this;
  }

  //Destructor
  ~ValSet()
  {
    delete[] aptr;
  }

  //Size - return number of values
  int size()
  {
    return numValue;
  }

  //isEmpty(); True if no values
  bool isEmpty()
  {
    if (numValue == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  //contains(); returns true if contains item
  bool contains(T value)
  {
    for (int count = 0; count < numValue; count++)
    {
      if (aptr[count] == value)
        return true;
    }
    return false;
  }

  //Adds
  void add(T value)
  {
    if (!contains(value))
    {
      if (numValue < arraySize)
      {
        aptr[numValue] = value;
        numValue++;
      }
      else
      {
        T *temp = new T[arraySize * 2];

        for (int i = 0; i < arraySize; i++)
        {
          temp[i] = aptr[i];
        }

        //Redirect Data Member to Pointer and deallocate old array
        delete[] aptr;

        aptr = new T[arraySize * 2];
        aptr = temp;
        arraySize = arraySize * 2; //update size

        //add in the new value
        aptr[numValue] = value;
        numValue++;
      }
    }
  }

  //Removes value(s)
  void remove(T item)
  {
    int removedIndex = 0;
    if (contains(item))
    {
      for (int i = 0; i < arraySize; i++)
      {
        if (aptr[i] == item)
        {
          removedIndex = i;
        }
      }
      //Move all other elements over
      for (int j = removedIndex; j < numValue; j++)
      {
        aptr[j] = aptr[j + 1];
      }
      numValue--;
    }
  }

  //getAsVector; Return as vector, which contains all of the values in ValSet and only those values
  vector<T> getAsVector()
  {
    vector<T> vectorArray;
    for (int count = 0; count < numValue; count++)
      vectorArray.push_back(aptr[count]);
    return vectorArray;
  }

  //Overloaded + operator for union
  ValSet<T> operator+(ValSet<T> addSet)
  {
    ValSet<T> newSet;

    for (int j = 0; j < arraySize; j++)
    {
      newSet.add(aptr[j]);
    }

    for (int i = 0; i < addSet.arraySize; i++)
    {
      if (!newSet.contains(addSet.aptr[i]))
        newSet.add(addSet.aptr[i]);
    }

    return newSet;
  }

  //Overloaded * operator for intersection
  ValSet<T> operator*(ValSet<T> mulSet)
  {
    ValSet<T> newSet;

    for (int j = 0; j < numValue; j++)
    {
      for (int i = 0; i < mulSet.numValue; i++)
      {
        if (aptr[j] == mulSet.aptr[i])
          newSet.add(mulSet.aptr[i]);
      }
    }

    return newSet;
  }

  //Overloaded / operator for Symetric Difference
  ValSet<T> operator/(ValSet<T> diffSet)
  {
    ValSet<T> unionSet;
    unionSet = this->unionWith(diffSet);
    ValSet<T> intersectSet;
    intersectSet = this->intersectWith(diffSet);

    for (int i = 0; i < intersectSet.numValue; i++)
    {
      for (int j = 0; j < unionSet.numValue; j++)
      {
        if (intersectSet.aptr[i] == unionSet.aptr[j])
          unionSet.remove(aptr[i]);
      }
    }

    ValSet<T> newSet = unionSet;
    return newSet;
  }
};

#endif /* ValSet_hpp */

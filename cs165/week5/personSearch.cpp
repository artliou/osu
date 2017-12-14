
/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/25/17
 ** Description: Project 4.a

BubbleSort from Chapter 9
const vector of person's (already sorted by name),name of person being serached for

Because the vector of Persons is being passed by const, you'll need to make the getName() method a constant member function, to reassure the compiler that the getName() method isn't changing any Person objects.

 *********************************************************************/

using namespace std;
#include <iostream>
#include <vector>
#include "Person.hpp"
// #include "Person.cpp"

int personSearch(const Person[], string);

int personSearch(const vector<Person> array, std::string name)
{
  int size = array.size();
  int first = 0,
      last = size - 1,
      middle,
      position = -1;
  bool found = false;

  while (!found && first <= last)
  {
    middle = (first + last) / 2;

    string retreivedName = array[middle].getName();

    if (retreivedName == name)
    {
      found = true;
      position = middle;
    }
    else if (retreivedName > name)
      last = middle - 1;
    else
      first = middle + 1;
  }
  return position;
}

// int main()
// {
//   Person p0("Andre", 42);
//   Person p1("Batholomew", 19);
//   Person p2("Connor", 54);
//   std::vector<Person> vec;
//   vec.push_back(p0);
//   vec.push_back(p1);
//   vec.push_back(p2);
//   int index = personSearch(vec, "Connor");

//   cout << "element " << index << " of the array.\n";
//   return 0;
// }
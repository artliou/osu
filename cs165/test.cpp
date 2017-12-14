/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/22/17
 ** Description:

************************************/

#include <iostream>
using namespace std;

class Square
{
private:
  double sideLength;

public:
  double getArea();
};

double Square::getArea()
{
  return sideLength * sideLength;
}

// Exam Prep/Trivia Question: sideLength is inaccessible, so the output of this main method will result in an error message.
int main()
{
  Square sq;
  sq.sideLength = 5.0;
  cout << sq.getArea() << endl;
  return 0;
}

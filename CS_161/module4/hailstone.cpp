/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 18, 2016
** Description:  Module 4.c assignment
*********************************************************************/

#include <iostream>

/*********************************************************************
** Description: Assignment 4.c
**
** Write a function called hailstone to compute steps to reach 1
**
**
*********************************************************************/

/*********************************************************************
** Definitions
**
*********************************************************************/


/*********************************************************************
** hailstone sequence
**
** Count the iterations until sequence == 1
**
*********************************************************************/

int hailstone (int sequence)
{
  int counter = 0;
  while (sequence != 1)
  {
    if (!(sequence % 2)) // Even
    {
      sequence /= 2;
      counter++;
    }
    else // Odd
    {
      sequence *= 3;
      sequence++;
      counter++;
    }
  }
  return counter;
}


#ifdef Debug
int main(void)
{
  std::cout << "Hailstone: " << hailstone (3) << std::endl;
  std::cout << "Hailstone: " << hailstone (1) << std::endl;
  return 0;
}
#endif

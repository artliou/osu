/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 18, 2016
** Description:  Module 4.b assignment
*********************************************************************/

#include <iostream>
#include <cmath>

/*********************************************************************
** Description: Assignment 4.b
**
** Write a function called smallSort, which sorts 3 numbers
** by reference
**
**
*********************************************************************/

/*********************************************************************
** Definitions
**
*********************************************************************/


/*********************************************************************
** void smallSort (int &x, int &y, int &z)
**
** Sort small to large, by reference.
**
*********************************************************************/

void smallSort (int &x, int &y, int &z)
{
  int old_x=x;
  int old_y=y;
  int old_z=z;

  if (x<y)
  {
    if (x<z)
    {
      if (y<z)
      {
        x=old_x;
        y=old_y;
        z=old_z;
        return;
      }
      else
      {
        x=old_x;
        y=old_z;
        z=old_y;
        return;
      }
    }
    else
    {
      x=old_z;
      y=old_x;
      z=old_y;
      return;
    }
  }
  else
  {
    if (y<z)
    {
      if (x<z)
      {
        x=old_y;
        y=old_x;
        z=old_z;
        return;
      }
      else
      {
        x=old_y;
        y=old_z;
        z=old_x;
        return;
      }
    }
    else
    {
      x=old_z;
      y=old_y;
      z=old_x;
      return;
    }
  }
}

#ifdef Debug
int main()
{
  int a = 14;
  int b = -90;
  int c = 2;
  smallSort(a, b, c);
  std::cout << a << ", " << b << ", " << c << std::endl;

  return 0;
}
#endif

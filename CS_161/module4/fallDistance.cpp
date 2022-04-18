/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 18, 2016
** Description:  Module 4.a assignment
*********************************************************************/

#include <iostream>
#include <cmath>

/*********************************************************************
** Description: Assignment 4.a
**
** Write a function called fallDistance that takes time as an
** argument and returns distance.
**
**
*********************************************************************/

/*********************************************************************
** Definitions
**
*********************************************************************/


/*********************************************************************
** float fallDistance (float time)
**
** Compute the distance fallen based on time
**
*********************************************************************/

float fallDistance (float time)
{
  return (1.0/2)*(9.8)*pow(time,2);
}

#ifdef Debug
int main(void)
{
  std::cout << fallDistance (sqrt(2)) << std::endl;
  std::cout << fallDistance (2.0) << std::endl;
  std::cout << fallDistance (3.0) << std::endl;

  return 0;
}
#endif

/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 21, 2016
** Description:  Lab Aa
*********************************************************************/

#include "average.h"
#include "lib_flip_display.h"
#include <stdlib.h>

/*********************************************************************
** Description: Lab Aa lab1-1.cpp
**
** Implementation for lab1-1.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// int main (void)
//
// Program entry point for lab1-1.cpp
//

int main (void)
{
  init_display();
  debug_print (true, COLOR_GREEN, "CS_162: Lab Aa  Testing...\n\n");

  double testResult;

  double testArray1[10] = {0,1,2,3,4,5,6,7,8,9};
  double testArray2[10] = {-5,-4,-3,-2,-1,1,2,3,4,5};

  unsigned int userArrayLength;
  double * userArray;

  debug_print (false, COLOR_WHITE, "Average of zero length array...");
  debug_test_result (avg (testArray1, 0) == 0);

  debug_print (false, COLOR_WHITE, "Average of nullptr array...");
  debug_test_result (avg (__null, ARRAY_SIZE (testArray1)) == 0);

  debug_print (false, COLOR_WHITE, "Average of testArray1...");
  debug_test_result (avg (testArray1, ARRAY_SIZE (testArray1)) == 4.5);

  debug_print (false, COLOR_WHITE, "Average of testArray1 with incorrect length...");
  debug_test_result (avg (testArray1, ARRAY_SIZE (testArray1)-1) != 4.5);

  debug_print (false, COLOR_WHITE, "Average of testArray2...");
  debug_test_result (avg (testArray2, ARRAY_SIZE (testArray2)) == 0);

  debug_print (false, COLOR_WHITE,"Enter user defined array test:\n\nEnter number of elements: ");

  scanw ((char*)"%u", &userArrayLength);

  userArray = (double*)malloc (userArrayLength * sizeof (double));
  for (unsigned int userCount = 0;userCount < userArrayLength; userCount++)
  {
    debug_print (false, COLOR_WHITE,"Enter data (%u/%u): ", userCount+1, userArrayLength);
    scanw ((char*)"%lf", &userArray[userCount]);
  }

  debug_print (false, COLOR_WHITE, "User Average : %lf\n\n", avg(userArray, userArrayLength));

  free (userArray);

  debug_print (false, COLOR_WHITE, "Summation of zero length array...");
  debug_test_result (sum (testArray1, 0) == 0);

  debug_print (false, COLOR_WHITE, "Summation of nullptr array...");
  debug_test_result (sum (__null, ARRAY_SIZE (testArray1)) == 0);

  debug_print (false, COLOR_WHITE, "Summation of testArray1...");
  debug_test_result (sum (testArray1, ARRAY_SIZE (testArray1)) == 45);

  debug_print (false, COLOR_WHITE, "Summation of testArray1 with incorrect length...");
  debug_test_result (sum (testArray1, ARRAY_SIZE (testArray1)-1) != 45);

  debug_print (false, COLOR_WHITE, "Summation of testArray2...");
  debug_test_result (sum (testArray2, ARRAY_SIZE (testArray1)) == 0);

  debug_print (false, COLOR_WHITE,"Enter user defined array test:\n\nEnter number of elements: ");

  scanw ((char*)"%u", &userArrayLength);

  userArray = (double*)malloc (userArrayLength * sizeof (double));
  for (unsigned int userCount = 0;userCount < userArrayLength; userCount++)
  {
    debug_print (false, COLOR_WHITE,"Enter data (%u/%u): ", userCount+1, userArrayLength);
    scanw ((char*)"%lf", &userArray[userCount]);
  }

  debug_print (false, COLOR_WHITE, "User Sum : %lf\n\n", sum(userArray, userArrayLength));

  free (userArray);

  debug_print (false, COLOR_WHITE, "Test Complete! Press any key to exit.");
  getch();
  shutdown_display();
  return 0;
}

/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 9, 2016
** Description:  Module 7 assignment
*********************************************************************/

#ifndef FINDMODE_HPP
#define FINDMODE_HPP

/*********************************************************************
** Description: Assignment 7
**
** A structure to hold temporary frequency data
**
*********************************************************************/

#define ARRAY_LENGTH(x) (sizeof(x)/sizeof(x[0]))

struct int_frequency
{
  int value;
  int count;
};

#endif // FINDMODE_HPP

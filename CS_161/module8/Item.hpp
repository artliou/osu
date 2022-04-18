/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 17, 2016
** Description:  Module 8 assignment
*********************************************************************/

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

/*********************************************************************
** Description: Assignment 8
**
** class definition for Item
**
*********************************************************************/

class Item
{
private:
  std::string name;
  double      price;
  int         quantity;

public:
  void setName (std::string new_name);
  std::string getName ();

  void setPrice (double new_price);
  double getPrice ();

  void setQuantity (int new_quantity);
  int getQuantity ();

  Item ();
  Item (std::string name, double price, int quantity);
};

#endif // ITEM_HPP

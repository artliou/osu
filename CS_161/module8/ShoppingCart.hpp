/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 17, 2016
** Description:  Module 8 assignment
*********************************************************************/

#ifndef SHOPPINGCART_HPP
#define SHOPPINGCART_HPP

#include "Item.hpp"
#include <string>

/*********************************************************************
** Description: Assignment 8
**
** class definition for ShoppingCart
**
*********************************************************************/

#define MAX_ITEMS 100

class ShoppingCart
{
private:
  Item * cartItems [MAX_ITEMS];
  int arrayEnd;

public:
  void addItem (Item * itemAdd);
  double totalPrice();

  ShoppingCart();
  ~ShoppingCart();
};

#endif // SHOPPINGCART_HPP

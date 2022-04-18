/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 17, 2016
** Description:  Module 8 assignment
*********************************************************************/

#include <string.h> // For memset
#include "ShoppingCart.hpp"

#ifdef Debug
#include <iostream>
#endif

/*********************************************************************
** Description: Assignment 8
**
** Implementation for ShoppingCart.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// ShoppingCart constructors
//

/////////////////////////////////////////////////////////////////
//
// ShoppingCart::ShoppingCart ()
//
// Class constructor/destructor with default variables
//

ShoppingCart::ShoppingCart ()
{
  this->arrayEnd = 0;
  memset (cartItems, 0, sizeof (cartItems));
}

ShoppingCart::~ShoppingCart()
{
  for (int clearCartCounter=0; clearCartCounter<this->arrayEnd; clearCartCounter++)
  {
    delete this->cartItems[clearCartCounter];
  }
}

/////////////////////////////////////////////////////////////////
//
// ShoppingCart functions
//

/////////////////////////////////////////////////////////////////
//
// void ShoppingCart::AddItem (Item * itemAdd)
//
// Add a new Item and pass itemAdd properties into it.
//

void ShoppingCart::addItem (Item * itemAdd)
{
  this->cartItems[(this->arrayEnd)++] = new Item(itemAdd->getName(), itemAdd->getPrice(), itemAdd->getQuantity());
}

/////////////////////////////////////////////////////////////////
//
// double ShoppingCart::totalPrice()
//
// Calculate the total cost of the items in the cart.
//

double ShoppingCart::totalPrice()
{
  double totalPrice = 0;
  for (int cartCounter=0; cartCounter<this->arrayEnd; cartCounter++)
  {
    totalPrice += (this->cartItems[cartCounter]->getQuantity() * this->cartItems[cartCounter]->getPrice());
  }
  return totalPrice;
}

#ifdef Debug
// Enable super debug test mode
//
//

int main()
{
  Item a("affidavit", 179.99, 12);
  Item b("Bildungsroman", 0.7, 20);
  Item c("capybara", 4.5, 6);
  Item d("dirigible", 0.05, 16);
  ShoppingCart sc1;
  sc1.addItem(&a);
  sc1.addItem(&b);
  sc1.addItem(&c);
  sc1.addItem(&d);
  double diff = sc1.totalPrice();

  std::cout << diff << std::endl;
  return 0;
}
#endif // Super debug mode

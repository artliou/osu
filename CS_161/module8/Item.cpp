/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 17, 2016
** Description:  Module 8 assignment
*********************************************************************/
#include "Item.hpp"

/*********************************************************************
** Description: Assignment 8
**
** Implementation for Item.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// Item constructors
//

/////////////////////////////////////////////////////////////////
//
// Item::Item ()
//
// Class constructor with default variables
//

Item::Item ()
{
  Item ("", 0.0, 0);
}

/////////////////////////////////////////////////////////////////
//
// Item::Item (std::string name, double price, int quantity)
//
// Class constructor with initial variables
//

Item::Item (std::string name, double price, int quantity)
{
  this->setName (name);
  this->setPrice(price);
  this->setQuantity(quantity);
}

/////////////////////////////////////////////////////////////////
//
// Item Functions
//

/////////////////////////////////////////////////////////////////
//
// void Item::setName (std::string new_name)
//
// Set the name of the item
//

void Item::setName (std::string new_name)
{
  this->name = new_name;
}

/////////////////////////////////////////////////////////////////
//
// std::string Item::getName ()
//
// Get the name of the item
//

std::string Item::getName ()
{
  return this->name;
}

/////////////////////////////////////////////////////////////////
//
// void Item::setPrice (double new_price)
//
// Set the price of the item
//

void Item::setPrice (double new_price)
{
  this->price = new_price;
}

/////////////////////////////////////////////////////////////////
//
// double Item::getPrice ()
//
// Get the price of the item
//

double Item::getPrice ()
{
  return this->price;
}

/////////////////////////////////////////////////////////////////
//
// void Item::setQuantity (int new_quantity)
//
// Set the quantity of the item
//

void Item::setQuantity (int new_quantity)
{
  this->quantity = new_quantity;
}

/////////////////////////////////////////////////////////////////
//
// void Item::getQuantity ()
//
// Get the quantity of the item
//

int Item::getQuantity ()
{
  return this->quantity;
}

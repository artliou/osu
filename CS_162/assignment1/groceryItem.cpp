/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 27, 2016
** Description:  groceryItem.cpp
*********************************************************************/

#include "groceryItem.hpp"

/*********************************************************************
** Description: groceryItem class implementation
**
** Function implementation for groceryItem
**
*********************************************************************/

using namespace std;

////////////////////////////////////////////////////////////
//
// groceryItem constructor
//
// Parameters:
//        string itemName - Name of new item
//        string unitType - The unit type of new item
//        double unitPrice - Price per unit of new item
//        double unitQuantity - How many units to buy
//
// Return:
//        None
//

groceryItem::groceryItem (const string &newItemName, const string &newUnitType, double newUnitPrice, double newUnitQuantity)
{
  this->itemName = string(newItemName);
  this->unitType = string(newUnitType);
  this->unitPrice = newUnitPrice;
  this->unitQuantity = newUnitQuantity;
}

////////////////////////////////////////////////////////////
//
// groceryItem::getItemName
//
// Parameters:
//        None
//
// Return:
//        string itemName - Name of item
//

string groceryItem::getItemName()
{
  return this->itemName;
}

////////////////////////////////////////////////////////////
//
// groceryItem::getUnitType
//
// Parameters:
//        None
//
// Return:
//        string unitType - The unit type of new item
//

string groceryItem::getUnitType()
{
  return this->unitType;
}

////////////////////////////////////////////////////////////
//
// groceryItem::getUnitPrice
//
// Parameters:
//        None
//
// Return:
//        double unitPrice - Price per unit of new item
//

double groceryItem::getUnitPrice()
{
  return this->unitPrice;
}

////////////////////////////////////////////////////////////
//
// groceryItem::getUnitQuantity
//
// Parameters:
//        None
//
// Return:
//        double unitQuantity - How many units to buy
//

double groceryItem::getUnitQuantity()
{
  return this->unitQuantity;
}

////////////////////////////////////////////////////////////
//
// groceryItem::getTotalPrice
//
// Parameters:
//        None
//
// Return:
//        double totalPrice - Total cost of n items
//

double groceryItem::getTotalPrice()
{
  return (this->unitPrice * this->unitQuantity);
}

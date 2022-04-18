/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 27, 2016
** Description:  groceryItem.hpp
*********************************************************************/

#ifndef GROCERY_ITEM
#define GROCERY_ITEM

#include <string>

/*********************************************************************
** Description: groceryItem class definition
**
** Function declarations for average.cpp
**
*********************************************************************/

using namespace std;

class groceryItem
{
private:
  string itemName;
  string unitType;
  double unitPrice;
  double unitQuantity;

public:
  groceryItem (const string &newItemName, const string &newUnitType, double newUnitPrice, double newUnitQuantity);

  string getItemName();
  string getUnitType();
  double getUnitPrice();
  double getUnitQuantity();
  double getTotalPrice();
};

#endif // GROCERY_ITEM

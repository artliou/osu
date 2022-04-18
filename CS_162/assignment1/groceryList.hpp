/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 27, 2016
** Description:  groceryList.hpp
*********************************************************************/

#ifndef GROCERY_LIST
#define GROCERY_LIST

#include "groceryItem.hpp"

/*********************************************************************
** Description: groceryItem class definition
**
** Function declarations for average.cpp
**
*********************************************************************/

using namespace std;

class groceryList
{
private:
  unsigned int groceryListMaxCount;
  unsigned int groceryListCurrentCount;
  groceryItem ** currentGroceryList;

  void ResizeGroceryList();

public:
  groceryList ();
  ~groceryList();

  void CreateGroceryList();
  void RemoveAllListItems();
  void AddListItem(const string &newItemName, const string &newUnitType, double newUnitPrice, double newUnitQuantity);
  void RemoveListItem (unsigned int itemIndex);
  unsigned int GetItemCount();
  void PrintGroceryList();
  double GetTotalPrice();
};

#endif // GROCERY_LIST

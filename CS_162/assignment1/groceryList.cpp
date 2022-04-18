/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 27, 2016
** Description:  groceryList.cpp
*********************************************************************/

/*********************************************************************
** Description: groceryList class implementation
**
** Function implementation for groceryList
**
*********************************************************************/

#include "groceryList.hpp"
#include "lib_flip_display.hpp"
#include <cstdlib>
#include <cstring>

using namespace std;

////////////////////////////////////////////////////////////
//
// groceryItem constructor
//
// Parameters:
//        None
//
// Return:
//        None
//

groceryList::groceryList ()
{
  this->groceryListCurrentCount = 0;
  this->groceryListMaxCount = 0;
  this->currentGroceryList = __null;
}

groceryList::~groceryList()
{
  // Destroying the groceryList
  // Remove all items
  this->RemoveAllListItems();
  if (this->currentGroceryList != __null)
  {
    // If the grocery list storage exists, free it.
    free (this->currentGroceryList);
  }
}

void groceryList::RemoveAllListItems()
{
  // Check if the groceryList is already created...
  if ((this->groceryListCurrentCount != 0) && (this->currentGroceryList != __null))
  {
    // Delete all items from the current list...
    while (this->groceryListCurrentCount > 0)
    {
      this->RemoveListItem(0);
    }
  }
}

void groceryList::CreateGroceryList()
{
  this->RemoveAllListItems();
  // No need to free currentGroceryList since we are using realloc
  // Reset groceryListMaxCount to zero and initialize the pointer storage memory.
  this->groceryListMaxCount = 0;
  this->ResizeGroceryList();
}

void groceryList::ResizeGroceryList()
{
  if (this->groceryListMaxCount == 0)
  {
    // This is a new list.
    this->groceryListMaxCount = 4;
  }
  else
  {
    // This an old list, double its size.
    this->groceryListMaxCount *= 2;
  }

  // Realloc will make sure the contents are preserved if the memory address changes.
  this->currentGroceryList = (groceryItem **)realloc (this->currentGroceryList, sizeof (groceryItem *) * this->groceryListMaxCount);
}

void groceryList::AddListItem(const string &newItemName, const string &newUnitType, double newUnitPrice, double newUnitQuantity)
{
  // Make sure there is room in the pointer storage array.
  if ((this->groceryListCurrentCount + 1) >= this->groceryListMaxCount)
  {
    // If not, resize the array
    this->ResizeGroceryList();
  }
  // Add the new item to the storage array.
  this->currentGroceryList[this->groceryListCurrentCount++] = new groceryItem (newItemName, newUnitType, newUnitPrice, newUnitQuantity);
}

void groceryList::RemoveListItem (unsigned int itemIndex)
{
  // Make sure the item to delete exists
  if ((this->currentGroceryList) && (itemIndex < this->groceryListCurrentCount) && (this->currentGroceryList[itemIndex] != __null))
  {
    // Delete the grocery Item
    delete this->currentGroceryList[itemIndex];

    // If there is more than one item in the buffer, and it is not the last.
    if ((this->groceryListCurrentCount > 1) && (itemIndex != (this->groceryListCurrentCount - 1)))
    {
      // memcpy the tail of the array back into the deleted item position.
      memmove (&this->currentGroceryList[itemIndex], &this->currentGroceryList[itemIndex + 1], sizeof(groceryItem *) * (this->groceryListCurrentCount - 1));
    }
    this->groceryListCurrentCount--;
  }
}

double groceryList::GetTotalPrice()
{
  unsigned int currentItemIndex = 0;
  double totalPrice = 0;
  for (currentItemIndex = 0; currentItemIndex < this->groceryListCurrentCount; currentItemIndex++)
  {
    totalPrice += ((groceryItem *)this->currentGroceryList[currentItemIndex])->getTotalPrice();
  }
  return totalPrice;
}

unsigned int groceryList::GetItemCount()
{
  return this->groceryListCurrentCount;
}

void groceryList::PrintGroceryList()
{
  unsigned int currentItemIndex = 0;

  debug_print (true, COLOR_WHITE, "\n\n");
  debug_print (true, COLOR_WHITE, "  Grocery List contents:\n");
  debug_print (true, COLOR_WHITE, "---------------------------\n\n");

  for (currentItemIndex = 0; currentItemIndex < this->groceryListCurrentCount; currentItemIndex++)
  {
    groceryItem * currentItem = this->currentGroceryList[currentItemIndex];
    debug_print (false, COLOR_WHITE, "Item name:\t\t");
    debug_print (true,  COLOR_WHITE, "%s\n", currentItem->getItemName().c_str());
    debug_print (false, COLOR_WHITE, "Item unit:\t\t");
    debug_print (true,  COLOR_WHITE, "%s\n", currentItem->getUnitType().c_str());
    debug_print (false, COLOR_WHITE, "Unit quantity:\t\t");
    debug_print (true,  COLOR_WHITE, "%01.2lf\n", currentItem->getUnitQuantity());
    debug_print (false, COLOR_WHITE, "Unit price:\t\t");
    debug_print (true,  COLOR_GREEN, "%01.2lf\n", currentItem->getUnitPrice());
    debug_print (false, COLOR_WHITE, "Total price:\t\t");
    debug_print (true,  COLOR_GREEN, "%01.2lf\n\n", currentItem->getTotalPrice());
  }
  debug_print (true, COLOR_WHITE, "---------------------------\n");
  debug_print (true, COLOR_WHITE, " Total price: ");
  debug_print (true, COLOR_GREEN, "%01.2lf\n\n",this->GetTotalPrice());
}

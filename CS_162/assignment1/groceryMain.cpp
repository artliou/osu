/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 27, 2016
** Description:  groceryMain.cpp
*********************************************************************/

#include "groceryList.hpp"
#include "lib_flip_display.hpp"

/*********************************************************************
** Description: groceryMain implementation
**
**
*********************************************************************/

using namespace std;

////////////////////////////////////////////////////////////
//
// int main() - program entry point
//
// Parameters:
//        None
//
// Return:
//        Success
//

int main()
{
  init_display();
  debug_print (true, COLOR_CYAN, "Grocery List V1.0 Testing...\t\t\n\n");

  groceryList * myList = new groceryList();

  debug_print (false, COLOR_WHITE, "Remove all items from empty storage.\t\t");
  myList->RemoveAllListItems();
  debug_test_result (myList->GetItemCount() == 0);

  debug_print (false, COLOR_WHITE, "Total price from empty storage.\t\t\t");
  debug_test_result (myList->GetTotalPrice() == 0);


  debug_print (false, COLOR_WHITE, "Adding item 1\t\t\t\t\t");
  myList->AddListItem ("Bananas", "lb", 0.99, 2.32);
  debug_test_result (myList->GetItemCount() == 1);

  debug_print (false, COLOR_WHITE, "Adding item 2\t\t\t\t\t");
  myList->AddListItem ("Tomatoes", "ea", 0.99, 4);
  debug_test_result (myList->GetItemCount() == 2);

  debug_print (false, COLOR_WHITE, "Adding item 3\t\t\t\t\t");
  myList->AddListItem ("Life cereal", "box", 3.19, 1);
  debug_test_result (myList->GetItemCount() == 3);

  debug_print (false, COLOR_WHITE, "Adding item 4\t\t\t\t\t");
  myList->AddListItem ("Frozen pizza", "ea", 6.79, 2);
  debug_test_result (myList->GetItemCount() == 4);

  debug_print (false, COLOR_WHITE, "Adding item 5\t\t\t\t\t");
  myList->AddListItem ("Apples", "lb", 0.79, 180);
  debug_test_result (myList->GetItemCount() == 5);

  debug_print (false, COLOR_WHITE, "Adding item 6\t\t\t\t\t");
  myList->AddListItem ("Ice cream", "pack", 5.19, 1);
  debug_test_result (myList->GetItemCount() == 6);


  debug_print (false, COLOR_WHITE, "Remove item(7) from used storage (out of index).");
  myList->RemoveListItem(7);
  debug_test_result (myList->GetItemCount() == 6);


  debug_print (false, COLOR_WHITE, "Remove item(1) from used storage.\t\t");
  myList->RemoveListItem(1);
  debug_test_result (myList->GetItemCount() == 5);

  myList->PrintGroceryList();

  debug_print (false, COLOR_WHITE, "Remove all items from used storage.\t\t");
  myList->RemoveAllListItems();
  debug_test_result (myList->GetItemCount() == 0);

  debug_print (false, COLOR_WHITE, "Adding item 1\t\t\t\t\t");
  myList->AddListItem ("Bananas", "lb", 0.99, 2.32);
  debug_test_result (myList->GetItemCount() == 1);

  delete myList;
  debug_print (false, COLOR_WHITE, "Test Complete! Press any key to exit.");
  
  shutdown_display();
  return 0;
}

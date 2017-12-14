/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/30/17
 ** Description: Project 10.b

 *********************************************************************/

#include "Library.hpp"
#include <vector>
#include <string>

//Library constructor to init currentDate to 0
Library::Library() {
  currentDate = 0;
}

//Adds items the vector of pointers
void Library::addLibraryItem(LibraryItem* item) {
  holdings.push_back(item);
}

//Adds Patron to a vector of members
void Library::addPatron(Patron* member) {
  members.push_back(member);
}

/***Checkout LibraryItem
 * if the specified LibraryItem is not in the Library, return "item not found"
if the specified Patron is not in the Library, return "patron not found"
if the specified LibraryItem is already checked out, return "item already checked out"
if the specified LibraryItem is on hold by another Patron, return "item on hold by other patron"
otherwise update the LibraryItem's checkedOutBy, dateCheckedOut and Location; if the LibraryItem was on hold for this Patron, update requestedBy; update the Patron's checkedOutItems; return "check out successful"
***/
std::string Library::checkOutLibraryItem(std::string PatronID, std::string ItemID) {
  LibraryItem * item = getLibraryItem(ItemID);
  Patron * patron = getPatron(PatronID);

  if(item == NULL)
    return "item not found";

  if(patron == NULL)
    return "patron not found";

  // the right item is already checked out
  if (getLibraryItem(ItemID)->getLocation() == CHECKED_OUT) {
    return "item already checked out";
  }
  // if the item is on hold by another patron
  if (getLibraryItem(ItemID)->getLocation() == ON_HOLD_SHELF) {
    return "item on hold by other patron";
  }

  if (item->getRequestedBy() == patron) {
    item->setCheckedOutBy(patron);
    item->setDateCheckedOut(this->currentDate);
    patron->addLibraryItem(item);
    item->setLocation(CHECKED_OUT);
    item->setRequestedBy(NULL);
    return "check out successful";
  }
  else {
    item->setCheckedOutBy(patron);
    item->setDateCheckedOut(this->currentDate);
    patron->addLibraryItem(item);
    item->setLocation(CHECKED_OUT);
    return "check out successful";
    }
}
/***Checkout LibraryItem
if the specified LibraryItem is not in the Library, return "item not found"
if the LibraryItem is not checked out, return "item already in library"
update the Patron's checkedOutItems; update the LibraryItem's location depending on whether another Patron has requested it; update the LibraryItem's checkedOutBy; return "return successful"
***/

std::string Library::returnLibraryItem(std::string ItemID) {
  LibraryItem* item = getLibraryItem(ItemID);

  if(item == NULL)
    return "item not found";

  //returns who checked it out and removes the item from their list
  Patron *patron = item->getCheckedOutBy();
  if(item->getLocation() == ON_SHELF)
    return "Item already in library";

  patron->removeLibraryItem(item);

  if(item->getRequestedBy() != NULL) {
    item->setLocation(ON_HOLD_SHELF);
    return "item placed on hold shelf for another patron";
  }
  else {
    item->setLocation(ON_SHELF);
    item->setCheckedOutBy(NULL);
    return "return successful";
  }

}

/***requestLibraryItem
if the specified LibraryItem is not in the Library, return "item not found"
if the specified Patron is not in the Library, return "patron not found"
if the specified LibraryItem is already requested, return "item already on hold"
update the LibraryItem's requestedBy; if the LibraryItem is on the shelf, update its location to on hold; return "request successful" ***/
std::string Library::requestLibraryItem(std::string PatronID, std::string ItemID) {
  // set the item and patron to make it easier
  LibraryItem* item = getLibraryItem(ItemID);
  Patron* patron = getPatron(PatronID);

  if(item == NULL)
    return "item not found";

  if(patron == NULL)
    return "patron not found";

  if (getLibraryItem(ItemID)->getRequestedBy() != NULL) {
    return "item already on hold";
  }
  else {
    getLibraryItem(ItemID)->setRequestedBy(getPatron(PatronID));

    if ((getLibraryItem(ItemID)->getLocation()) == ON_SHELF) {
      getLibraryItem(ItemID)->setLocation(ON_HOLD_SHELF);
    }
    return "request successful";
  }
}

/***PayFine
takes as a parameter the amount that is being paid (not the negative of that amount)
if the specified Patron is not in the Library, return "patron not found"
use amendFine to update the Patron's fine; return "payment successful"***********************************************************************/
std::string Library::payFine(std::string patronID, double payment) {
  Patron* patron = getPatron(patronID);
  //if the patron is not found
  if (patron == NULL)
   return "patron not found";
  getPatron(patronID)->amendFine(-payment);
  return "payment successful";
}

//increment current date; increase each Patron's fines by 10 cents for each overdue LibraryItem they have checked out (using amendFine)
void Library::incrementCurrentDate() {
  currentDate++;
  for (int x = 0; x < members.size(); x++) {
    for (int i = 0; i < members[x]->getCheckedOutItems().size(); i++) {
    if(currentDate - members[x]->getCheckedOutItems().at(i)->getDateCheckedOut() > members[x]->getCheckedOutItems().at(i)->getCheckOutLength()) {
     members[x]->amendFine(0.10);
     }
   }
 }
}

//Returns the patron of the ID number given
Patron* Library::getPatron(std::string PatronID) {
  for (int x = 0; x < members.size(); x++) {
    if (members[x]->getIdNum() == PatronID) {
      return members[x];
    }
  }
}

//Returns item from the ID Code
LibraryItem* Library::getLibraryItem(std::string ItemID) {
  for (int x = 0; x < holdings.size(); x++) {
    if(holdings[x]->getIdCode() == ItemID) {
      return holdings[x];
    }
  }
}

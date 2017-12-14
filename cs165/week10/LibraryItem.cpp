#include "LibraryItem.hpp"
#include <string>

//LibraryItem Constructor
LibraryItem::LibraryItem(std::string idc, std::string t) {
  idCode = idc;
  title = t;
  checkedOutBy = NULL;
  requestedBy = NULL;
  location = ON_SHELF;
}

//Returns ID Code
std::string LibraryItem::getIdCode() {
  return idCode;
}

//Returns LibraryItem Title
std::string LibraryItem::getTitle() {
  return title;
}

//Returns item location
Locale LibraryItem::getLocation() {
  return location;
}

//Set Location of item
void LibraryItem::setLocation(Locale loc) {
  location = loc;
}

//Returns a pointer to the person who checked out the item
Patron* LibraryItem::getCheckedOutBy() {
  return checkedOutBy;
}

//Sets the checkedoutbymethod to the person who checked the item out
void LibraryItem::setCheckedOutBy(Patron *p) {
  checkedOutBy = p;
}

//Returns a pointer to the patron class
Patron* LibraryItem::getRequestedBy() {
  return requestedBy;
}

//Sets the requestedBy pointer to the patron
void LibraryItem::setRequestedBy(Patron *p) {
  requestedBy = p;
}

//Returns the date the item was checkedout
int LibraryItem::getDateCheckedOut() {
  return dateCheckedOut;
}

//Sets the date an item was checkedout
void LibraryItem::setDateCheckedOut(int date) {
  dateCheckedOut = date;
}

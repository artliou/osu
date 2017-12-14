/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/30/17
 ** Description: Project 10.b

 *********************************************************************/

#include "Patron.hpp"
#include <string>
#include <vector>

//Patron Constructor
Patron::Patron (std::string idIn, std::string nameIn) {
  idNum = idIn;
  name = nameIn;
}

//Returns Patron's ID Number
std::string Patron::getIdNum() {
  return idNum;
}

//Returns Patron's Name
std::string Patron::getName() {
  return name;
}

//Returns the checkedout items of the patron
std::vector<LibraryItem*> Patron::getCheckedOutItems() {
  return checkedOutItems;
}

//Adds an item to the vector of the patron's checkedout items
void Patron::addLibraryItem (LibraryItem* item) {
  checkedOutItems.push_back(item);
}

//Removes item from the vector of checkouted items
void Patron::removeLibraryItem(LibraryItem* item) {
  for (int x = 0; x < checkedOutItems.size(); x++) {
    if (checkedOutItems[x] == item) {
      checkedOutItems.erase(checkedOutItems.begin() + x-1);
    }
  }
}

//Returns fine amount
double Patron::getFineAmount() {
  return fineAmount;
}

// a positive argument increases the fineAmount, a negative one decreases it; this is allowed to go negative
void Patron::amendFine(double amount) {
  fineAmount += amount;
}




/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 31, 2016
** Description:  Module 10 assignment
*********************************************************************/
#include "Patron.hpp"
#include <algorithm>

/*********************************************************************
** Description: Assignment 10
**
** Implementation for Patron.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// Patron constructors
//

/////////////////////////////////////////////////////////////////
//
// Patron::Patron()
//
// Class constructor with default variables.
//

Patron::Patron(std::string idn, std::string n)
{
  this->idNum = idn;
  this->name = n;
  this->fineAmount = 0;
  this->checkedOutBooks.clear();
}

/////////////////////////////////////////////////////////////////
//
// std::string Patron::getIdNum()
//
// return the unique ID of the patron.
//

std::string Patron::getIdNum()
{
  return this->idNum;
}

/////////////////////////////////////////////////////////////////
//
// std::string Patron::getName()
//
// return the name of the patron.
//

std::string Patron::getName()
{
  return this->name;
}

/////////////////////////////////////////////////////////////////
//
// std::vector<Book*> Patron::getCheckedOutBooks()
//
// return a vector of the checked out books of the patron.
//

std::vector<Book*> Patron::getCheckedOutBooks()
{
  return this->checkedOutBooks;
}

/////////////////////////////////////////////////////////////////
//
// void Patron::addBook(Book* b)
//
// Add a book to the patrons checke out book vector.
//

void Patron::addBook(Book* b)
{
  this->checkedOutBooks.push_back (b);
}

/////////////////////////////////////////////////////////////////
//
// void Patron::removeBook(Book* b)
//
// Remove a book to the patrons checke out book vector.
//

void Patron::removeBook(Book* b)
{
  this->checkedOutBooks.erase(std::remove (this->checkedOutBooks.begin(), this->checkedOutBooks.end(), b), this->checkedOutBooks.end());
}

/////////////////////////////////////////////////////////////////
//
// double Patron::getFineAmount()
//
// Return the fine ammount that a patron owes.
//

double Patron::getFineAmount()
{
  return this->fineAmount;
}

/////////////////////////////////////////////////////////////////
//
// void Patron::amendFine(double amount)
//
// Add amount to the patrons fineAmount.
//

void Patron::amendFine(double amount)
{
  this->fineAmount += amount;
}

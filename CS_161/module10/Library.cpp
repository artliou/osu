/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 31, 2016
** Description:  Module 10 assignment
*********************************************************************/
#include "Library.hpp"
#include "Patron.hpp"
#include <vector>
#include <iostream>

/*********************************************************************
** Description: Assignment 10
**
** Implementation for Library.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// Libray constructors
//

/////////////////////////////////////////////////////////////////
//
// Library::Library()
//
// Class constructor with default variables.
//

Library::Library()
{
  this->holdings.clear();
  this->members.clear();
  this->currentDate = 0;
}

/////////////////////////////////////////////////////////////////
//
// void Library::addBook(Book* newBook)
//
// Add a book to the library holdings.
//

void Library::addBook(Book* newBook)
{
  this->holdings.push_back (newBook);
}

/////////////////////////////////////////////////////////////////
//
// void Library::addPatron(Patron* newPatron)
//
// Add a patron to the library members.
//

void Library::addPatron(Patron* newPatron)
{
  this->members.push_back (newPatron);
}

/////////////////////////////////////////////////////////////////
//
// std::string Library::checkOutBook(std::string pID, std::string bID)
//
// Checkout out a book to a patron.
//

std::string Library::checkOutBook(std::string pID, std::string bID)
{
  Book * curBook = this->getBook(bID);
  Patron * curPatron = this->getPatron(pID);

  if (curPatron == 0)
  {
    return "patron not found";
  }

  if (curBook == 0)
  {
    return "book not found";
  }

  switch (curBook->getLocation())
  {
    case CHECKED_OUT:
      return "book already checked out";
      break;

    case ON_HOLD_SHELF:
      if (curBook->getRequestedBy())
      {
        if (curBook->getRequestedBy()->getIdNum() == pID)
        {
          // Book is on for hold for current patron.
          // Clear the book hold member.
          curBook->setRequestedBy(0);
        }
        else
        {
          return "book on hold by other patron";
        }
      }

      break;
  }

  curBook->setCheckedOutBy(curPatron);
  curBook->setDateCheckedOut(this->currentDate);
  curBook->setLocation (CHECKED_OUT);
  curPatron->addBook (curBook);
  return "check out successful";
}

/////////////////////////////////////////////////////////////////
//
// std::string Library::returnBook(std::string bID)
//
// Return a book to the library.
//

std::string Library::returnBook(std::string bID)
{
  Book * curBook = this->getBook(bID);

  if (curBook == 0)
  {
    return "book not found";
  }

  if (curBook->getLocation() != CHECKED_OUT)
  {
    return "book already in library";
  }

  curBook->getCheckedOutBy()->removeBook(curBook);
  curBook->setCheckedOutBy(0);

  if (curBook->getRequestedBy() == 0)
  {
    curBook->setLocation (ON_SHELF);
  }
  else
  {
    curBook->setLocation (ON_HOLD_SHELF);
  }
  return "return successful";
}

/////////////////////////////////////////////////////////////////
//
// std::string Library::requestBook(std::string pID, std::string bID)
//
// Mark a book for holding for another patron.
//

std::string Library::requestBook(std::string pID, std::string bID)
{
  Book * curBook = this->getBook(bID);
  Patron * curPatron = this->getPatron(pID);

  if (curPatron == 0)
  {
    return "patron not found";
  }

  if (curBook == 0)
  {
    return "book not found";
  }

  if (curBook->getRequestedBy() != 0)
  {
    return "book already on hold";
  }

  curBook->setRequestedBy(curPatron);

  if (curBook->getLocation() == ON_SHELF)
  {
      curBook->setLocation (ON_HOLD_SHELF);
  }

  return "request successful";

}

/////////////////////////////////////////////////////////////////
//
// std::string Library::payFine(std::string pID, double payment)
//
// Adjust patron fineAmount by payment.
//

std::string Library::payFine(std::string pID, double payment)
{
  Patron * curPatron = this->getPatron(pID);

  if (curPatron == 0)
  {
    return "patron not found";
  }

  curPatron->amendFine (-payment);
  return "payment successful";
}

/////////////////////////////////////////////////////////////////
//
// void Library::incrementCurrentDate()
//
// Add one day to the currentDate and preform logic for checking
// for overdue books.
//

void Library::incrementCurrentDate()
{
  this->currentDate++;
  // Loop through all members, check all books for (date + checkout length) > currentDate
  for (int patronCounter = 0; patronCounter < this->members.size(); patronCounter++)
  {
    Patron * curPatron = this->members[patronCounter];
    for (int bookCounter = 0; bookCounter < curPatron->getCheckedOutBooks().size(); bookCounter++)
    {
      Book * curBook = curPatron->getCheckedOutBooks()[bookCounter];
      if ((curBook->getDateCheckedOut() + curBook->getCheckOutLength()) > this->currentDate);
      {
        curPatron->amendFine(0.10);
      }
    }
  }
}

/////////////////////////////////////////////////////////////////
//
// Patron* Library::getPatron(std::string pID)
//
// Find a patron from members based on patron ID.
//

Patron* Library::getPatron(std::string pID)
{
  for (int patronCounter = 0; patronCounter < this->members.size(); patronCounter++)
  {
    Patron * curPatron = this->members[patronCounter];
    if (curPatron->getIdNum() == pID)
    {
      return curPatron;
    }
  }
  return 0;
}

/////////////////////////////////////////////////////////////////
//
// Book* Library::getBook(std::string bID)
//
// Find a book from holdings based on book ID.
//

Book* Library::getBook(std::string bID)
{
  for (int bookCounter = 0; bookCounter < this->holdings.size(); bookCounter++)
  {
    Book * curBook = this->holdings[bookCounter];
    if (curBook->getIdCode() == bID)
    {
      return curBook;
    }
  }
  return 0;
}

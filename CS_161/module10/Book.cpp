/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 31, 2016
** Description:  Module 10 assignment
*********************************************************************/
#include "Book.hpp"

/*********************************************************************
** Description: Assignment 10
**
** Implementation for Book.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// Book constructors
//

/////////////////////////////////////////////////////////////////
//
// Book::Book(std::string idc, std::string t, std::string a)
//
// Class constructor with default variables.
//

Book::Book(std::string idc, std::string t, std::string a)
{
  // Create a new book with the input parameters.
  this->idCode = idc;
  this->title = t;
  this->author = a;
  this->location = ON_SHELF;
  this->setCheckedOutBy(0);
  this->setRequestedBy(0);
  this->setDateCheckedOut(0);
}

/////////////////////////////////////////////////////////////////
//
// int Book::getCheckOutLength()
//
// get the length of a book checkout.
//

int Book::getCheckOutLength()
{
  return this->CHECK_OUT_LENGTH;
}

/////////////////////////////////////////////////////////////////
//
// std::string Book::getIdCode()
//
// get the id code of a book.
//
std::string Book::getIdCode()
{
  return this->idCode;
}

/////////////////////////////////////////////////////////////////
//
// std::string Book::getTitle()
//
// get the title of a book.
//
std::string Book::getTitle()
{
  return this->title;
}

/////////////////////////////////////////////////////////////////
//
// std::string Book::getAuthor()
//
// get the author of a book.
//
std::string Book::getAuthor()
{
  return this->author;
}

/////////////////////////////////////////////////////////////////
//
// Locale Book::getLocation()
//
// get the location of a book.
//
Locale Book::getLocation()
{
  return this->location;
}

/////////////////////////////////////////////////////////////////
//
// void Book::setLocation(Locale)
//
// set the location of a book.
//
void Book::setLocation(Locale newLocation)
{
  this->location = newLocation;
}

/////////////////////////////////////////////////////////////////
//
// Patron* Book::getCheckedOutBy()
//
// get the patron that has checked out the book.
//
Patron* Book::getCheckedOutBy()
{
  return this->checkedOutBy;
}

/////////////////////////////////////////////////////////////////
//
// int Book::getCheckOutLength()
//
// set the patron that has checked out the book.
//
void Book::setCheckedOutBy(Patron* newPatron)
{
  this->checkedOutBy = newPatron;
}

/////////////////////////////////////////////////////////////////
//
// Patron* Book::getRequestedBy()
//
// get the patron who has requested the book.
//
Patron* Book::getRequestedBy()
{
  return this->requestedBy;
}

/////////////////////////////////////////////////////////////////
//
// void Book::setRequestedBy(Patron* newPatron)
//
// set the patron who is requesting the book
//
void Book::setRequestedBy(Patron* newPatron)
{
  this->requestedBy = newPatron;
}

/////////////////////////////////////////////////////////////////
//
// int Book::getDateCheckedOut()
//
// get the date the book was checked out.
//
int Book::getDateCheckedOut()
{
  return this->dateCheckedOut;
}

/////////////////////////////////////////////////////////////////
//
// void Book::setDateCheckedOut(int)
//
// set the date the book was checked out.
//
void Book::setDateCheckedOut(int date)
{
  this->dateCheckedOut = date;
}

/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 31, 2016
** Description:  Module 10 assignment
*********************************************************************/
#include "Library.hpp"
#include <iostream>

/*********************************************************************
** Description: Assignment 10
**
** Implementation for main.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// int main()
//
// Program entry point
//

int main()
{
  Book b1("123", "War and Peace", "Tolstoy");
  Book b2("234", "Moby Dick", "Melville");
  Book b3("345", "Phantom Tollbooth", "Juster");
  Patron p1("abc", "Felicity");
  Patron p2("bcd", "Waldo");
  Patron p3("123", "Jeremy");
  Library lib;
  lib.addBook(&b1);
  lib.addBook(&b2);
  lib.addBook(&b3);
  lib.addPatron(&p1);
  lib.addPatron(&p2);
  lib.addPatron(&p3);
  std::cout << lib.checkOutBook("bcd", "234") << std::endl;
  for (int i=0; i<7; i++)
     lib.incrementCurrentDate();
  std::cout << lib.checkOutBook("bcd", "123") << std::endl;
  std::cout << lib.checkOutBook("abc", "345") << std::endl;
  for (int i=0; i<24; i++)
     lib.incrementCurrentDate();
  std::cout << lib.payFine("bcd", 0.4) << std::endl;
  double p1Fine = p1.getFineAmount();
  double p2Fine = p2.getFineAmount();
  std::cout << "p1 fine: " << p1Fine << std::endl;
  std::cout << "p2 fine: " << p2Fine << std::endl;

  std::cout << "request: " << lib.requestBook ("123", "123") << std::endl;
  std::cout << "request: " << lib.requestBook ("12b", "123") << std::endl;
  std::cout << "request: " << lib.requestBook ("abc", "123") << std::endl;

  for (int i=0; i<10; i++)
     lib.incrementCurrentDate();

  std::cout << "return book: " << lib.returnBook ("123") << std::endl;
  std::cout << lib.payFine("bcd", 1.0) << std::endl;
  p1Fine = p1.getFineAmount();
  p2Fine = p2.getFineAmount();
  std::cout << "p1 fine: " << p1Fine << std::endl;
  std::cout << "p2 fine: " << p2Fine << std::endl;

  std::cout << "checkout book: " << lib.checkOutBook("123", "345") << std::endl;
  std::cout << "checkout book: " << lib.checkOutBook("123", "123") << std::endl;
  return 0;
}

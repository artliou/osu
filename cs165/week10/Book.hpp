/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/30/17
 ** Description: Project 10.b

 *********************************************************************/

#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include "LibraryItem.hpp"

class Book : public LibraryItem {
  private:
    static const int CHECK_OUT_LENGTH;
    std::string author;
  public:
    Book(std::string idc, std::string t, std::string auth);
    std::string getAuthor();
    virtual int getCheckOutLength();
};

#endif
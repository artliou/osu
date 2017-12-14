/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/30/17
 ** Description: Project 10.b

 *********************************************************************/

#include "Book.hpp"
#include "LibraryItem.hpp"
#include <string>

//Constructor for Book class
Book::Book(std::string idc, std::string t, std::string auth) : LibraryItem( idc, t) {
  author = auth;
}

//Return book author
std::string Book::getAuthor() {
  return author;
}

//Returns CheckOutLength
int Book::getCheckOutLength() {
  return this-> CHECK_OUT_LENGTH;
}

const int Book::CHECK_OUT_LENGTH = 21;
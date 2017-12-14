/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/30/17
 ** Description: Project 10.b

 *********************************************************************/

#include "Movie.hpp"
#include "LibraryItem.hpp"
#include <string>

//Constructor for Movie class
Movie::Movie(std::string idc, std::string t, std::string dir) : LibraryItem(idc, t) {
  director = dir;
}

//Return movie director
std::string Movie::getDirector() {
  return director;
}

//Returns CheckOutLength
int Movie::getCheckOutLength() {
  return this->CHECK_OUT_LENGTH;
}

const int Movie::CHECK_OUT_LENGTH = 7;
/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/30/17
 ** Description: Project 10.b

 *********************************************************************/

#include "LibraryItem.hpp"
#include "Album.hpp"
#include <string>

//Constructor for Album class
Album::Album (std::string idc, std::string t, std::string artistIn) : LibraryItem(idc, t) {
  artist = artistIn;
}

//Returns Album Artist
std::string Album::getArtist() {
  return artist;
}

//Returns CheckOutLength
int Album::getCheckOutLength() {
  return this->CHECK_OUT_LENGTH;
}

const int Album::CHECK_OUT_LENGTH = 14;
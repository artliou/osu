/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/30/17
 ** Description: Project 10.b

 *********************************************************************/

#ifndef ALBUM_HPP
#define ALBUM_HPP

#include <string>
#include "LibraryItem.hpp"

class Album : public LibraryItem {
  private:
    static const int CHECK_OUT_LENGTH;
    std::string artist;
  public:
    //constructor
    Album(std::string idc, std::string t, std::string artistIn);
    std::string getArtist();
    int getCheckOutLength();
};

#endif
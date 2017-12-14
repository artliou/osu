/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/30/17
 ** Description: Project 10.b

 *********************************************************************/

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>
#include "LibraryItem.hpp"

class Movie : public LibraryItem {
  public:
    static const int CHECK_OUT_LENGTH;
    std::string director;
  public:
    Movie(std::string idc, std::string t, std::string dir);
    std::string getDirector();
    int getCheckOutLength();
};

#endif
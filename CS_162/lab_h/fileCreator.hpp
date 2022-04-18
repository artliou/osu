/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 12, 2016
** Description:  fileCreator.hpp
*********************************************************************/

#ifndef FILE_CREATOR_HPP
#define FILE_CREATOR_HPP

#include <string>

class fileCreator
{
public:
    static int createFile();
    static int createFileDirect(std::string fileName, int numItems);
};

#endif //FILE_CREATOR_HPP
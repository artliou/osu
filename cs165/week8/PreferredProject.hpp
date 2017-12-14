/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/15/17
 ** Description: Project 8.b

 *********************************************************************/

#ifndef PreferredProject_hpp
#define PreferredProject_hpp
#include "CustomerProject.hpp"

class PreferredProject : public CustomerProject
{
  public:
    PreferredProject(double hoursIn, double materialsIn, double transportationIn) : CustomerProject(hoursIn, materialsIn, transportationIn){};
    double billAmount();
};

/*
int main() {
    PreferredProject proj1(40, 20, 10); //3226
    PreferredProject proj2(100, 10, 40); //8044.5
    PreferredProject proj3(200, 100, 5); //8089.5
    cout << proj1.billAmount() << endl;
    cout << proj2.billAmount() << endl;
    cout << proj3.billAmount() << endl;
    return 0;
}
*/

#endif /* PreferredProject_hpp */

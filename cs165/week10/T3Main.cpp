#include "T3Reader.hpp"
#include "T3Reader.cpp"
#include "Board.cpp"

#include <fstream>
#include <string>
using std::string;
using std::ifstream;
using std::ostream;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main() {
    Board testGame;

    T3Reader one('x');
    T3Reader two('x');
    T3Reader three('x');
    T3Reader four('x');

    bool result1, result2, result3, result4;
    result1 = one.readGameFile("fileO");
    cout << "Completed Game 1: " << result1 << endl;
    result2 = two.readGameFile("fileX");
    cout << "Completed Game 2: " << result2 << endl;
    result3 = three.readGameFile("invalid");
    cout << "Game 3: " << result3 << endl;
    result4 = four.readGameFile("over");
    cout << "Game 4: " << result4 << endl;
}

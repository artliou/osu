#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "Stack.hpp"

////////////////////////////////////////////////////////////////////////////////
//
// class Calculator
//
// A class that preforms RNP notation calculations
//

class Calculator
{
private:
    Stack * calcStack;
    int stackDepth;
    bool running;

    void add();
    void subtract();
    void multiply();
    void divide();

public:
    Calculator();
    ~Calculator();

    void PrintStack();
    void ProcessInput();
    void CalculatorLoop();
};

#endif // CALCULATOR_HPP
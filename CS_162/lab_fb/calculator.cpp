#include "calculator.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// Calculator::Calculator()
//
// Calculator constructor
//
// Create calcStack object (dynamic allocation)
//
// Parameters:
//        none
//
// Return:
//        none
//

Calculator::Calculator()
{
    stackDepth = 0;
    running = true;
    calcStack = new Stack;
}

///////////////////////////////////////////////////////////////////////////////
//
// Calculator::~Calculator()
//
// Calculator destructor
//
// Delete calcStack object
//
// Parameters:
//        none
//
// Return:
//        none
//

Calculator::~Calculator()
{
    delete calcStack;
}

///////////////////////////////////////////////////////////////////////////////
//
// Calculator::Add()
//
// Add and pop the top 2 stack items. Push result onto stack
//
// Parameters:
//        none
//
// Return:
//        none
//

void Calculator::add()
{
    if (stackDepth >= 2)
    {
        int value1 = calcStack->peek(); calcStack->pop();
        int value2 = calcStack->peek(); calcStack->pop();
        calcStack->push (value1 + value2);
        stackDepth--;
    }
    else
    {
        DebugConsole::debug_print (0, true, COLOR_RED, "\n\nInput Error. Insufficent input for %s\n\n", __func__);
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// Calculator::subtract()
//
// Subtract and pop the top 2 stack items. Push result onto stack
//
// Parameters:
//        none
//
// Return:
//        none
//

void Calculator::subtract()
{
    if (stackDepth >= 2)
    {
        int value1 = calcStack->peek(); calcStack->pop();
        int value2 = calcStack->peek(); calcStack->pop();
        calcStack->push (value1 - value2);
        stackDepth--;
    }
    else
    {
        DebugConsole::debug_print (0, true, COLOR_RED, "\n\nInput Error. Insufficent input for %s\n\n", __func__);
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// Calculator::multiply()
//
// multiply and pop the top 2 stack items. Push result onto stack
//
// Parameters:
//        none
//
// Return:
//        none
//

void Calculator::multiply()
{
    if (stackDepth >= 2)
    {
        int value1 = calcStack->peek(); calcStack->pop();
        int value2 = calcStack->peek(); calcStack->pop();
        calcStack->push (value1 * value2);
        stackDepth--;
    }
    else
    {
        DebugConsole::debug_print (0, true, COLOR_RED, "\n\nInput Error. Insufficent input for %s\n\n", __func__);
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// Calculator::divide()
//
// Divide and pop the top 2 stack items. Push result onto stack
//
// Parameters:
//        none
//
// Return:
//        none
//

void Calculator::divide()
{
    if (stackDepth >= 2)
    {
        int value1 = calcStack->peek(); calcStack->pop();
        int value2 = calcStack->peek(); calcStack->pop();
        calcStack->push (value1 / value2);
        stackDepth--;
    }
    else
    {
        DebugConsole::debug_print (0, true, COLOR_RED, "\n\nInput Error. Insufficent input for %s\n\n", __func__);
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// Calculator::PrintStack()
//
// Print the stack depth and stack contents.
//
// This has to re-create the stack because reading the stack will pop the items off.
// The stack will be backwards, so we have to pop/rebuild it one last time.
//
// Implementing a function to traverse the stack with out popping nodes would be very helpful in
// this function, but that function is not included in the stack class.
//
// Parameters:
//        none
//
// Return:
//        none
//

void Calculator::PrintStack()
{
    DebugConsole::debug_print (0, true, COLOR_CYAN, "Stack Depth: %d. Stack Contents:\n\n", stackDepth);
    Stack * newStack = new Stack;
    while (!calcStack->isEmpty())
    {
        DebugConsole::debug_print (0, false, COLOR_WHITE, "\t%d\n", calcStack->peek());
        newStack->push (calcStack->peek());
        calcStack->pop();
    }
    delete calcStack;
    calcStack = newStack;

    // Now the stack is reversed...
    newStack = new Stack;
    while (!calcStack->isEmpty())
    {
        newStack->push (calcStack->peek());
        calcStack->pop();
    }
    delete calcStack;
    
    // Now the stack is back to normal.
    calcStack = newStack;
    DebugConsole::debug_print (0, false, COLOR_WHITE, "\n\n");
}

///////////////////////////////////////////////////////////////////////////////
//
// Calculator::ProcessInput()
//
// Get input from user and process it.
//
// Parameters:
//        none
//
// Return:
//        none
//

void Calculator::ProcessInput()
{
    std::string input;
    DebugConsole::debug_print (0, false, COLOR_WHITE, "\n\tEnter numerical input, or +, -, *, / for operations, or q to quit.\n\n\tEnter Input >");
    std::cin >> input;
    char * resultString;
    long numberInput = 0;
    bool isNumber = true;
    try
    {
       numberInput = stoi (input, __null, 10);
    }
    catch (const std::exception & e)
    {
        isNumber = false;
    }
    if (isNumber)
    {
        // The result is a number.
        // Push it onto the stack.
        calcStack->push (numberInput);
        stackDepth++;
    }
    else
    {
        // The result is a string. Compare it to +-*/
        if (input.compare ("+") == 0)
        {
            add();
        }
        if (input.compare ("-") == 0)
        {
            subtract();
        }
        if (input.compare ("*") == 0)
        {
            multiply();
        }
        if (input.compare ("/") == 0)
        {
            divide();
        }
        if (input.compare ("q") == 0)
        {
            running = false;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// Calculator::CalculatorLoop()
//
// Main processing loop for the Calculator class.
//
// Parameters:
//        none
//
// Return:
//        none
//

void Calculator::CalculatorLoop()
{
    while (running)
    {
        ProcessInput();
        PrintStack();
    }
}

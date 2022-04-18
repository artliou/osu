/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  lab_f.cpp
*********************************************************************/

#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "lib_flip_display.hpp"
#include "lib_arg_parse.hpp"

#include "stack.hpp"
#include "queue.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// Local function definitions
//


///////////////////////////////////////////////////////////////////////////////
//
// int main()
//
// Program entry point.
//
// Parameters:
//        int argc - number of command line parameters
//        char * argvp[] - char array of command line parameters
//
// Return:
//        int return code - zero for success
//

int main(int argc, char * argv[])
{
    // Parse command line rguments
    customArgParser::InitalizeArguments();
    argp_parse (&customArgParser::argp, argc, argv, 0, 0, &customArgParser::arguments);

    DebugConsole::debug_print (0, true, COLOR_GREEN, "CS_162 lab_f\n\n");

    if (customArgParser::arguments.debugEnable == true)
    {
      DebugConsole::SetDebugLevel (1);
    }

    DebugConsole::debug_print (0, true, COLOR_WHITE, "Starting Automated tests...\n");

    // Create a stack and a queue

    Queue<int> * myQueue = new Queue<int>();
    Stack<int> * myStack = new Stack<int>();

    // Test functions on empty stack/queue
    // Check for segment violation

    myQueue->getFront();
    myQueue->removeFront();
    
    myStack->peek();
    myStack->pop();

    // Populate data

    myStack->push (1);
    myStack->push (2);
    myStack->push (3);

    // This should pop the number 3

    DebugConsole::debug_print (0, true, COLOR_WHITE, "stack pop: %d\n", myStack->peek());
    myStack->pop();

    // push more data

    myStack->push (4);
    myStack->push (5);

    // Print all data, empty stack

    while (!myStack->isEmpty())
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "stack pop: %d\n", myStack->peek());
      myStack->pop();
    }

    // Push more items onto stack

    myStack->push (6);
    myStack->push (7);
    myStack->push (8);
    
    // Add items to the queue

    myQueue->addBack(1);
    myQueue->addBack(2);
    myQueue->addBack(3);

    // Get the first item from the queue and remove the first one

    DebugConsole::debug_print (0, true, COLOR_WHITE, "queue getFront: %d\n", myQueue->getFront());
    myQueue->removeFront();

    // Add more items to the queue

    myQueue->addBack(4);
    myQueue->addBack(5);

    // Print all queue items
    // Empty the queue

    while (!myQueue->isEmpty())
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "queue getFront: %d\n", myQueue->getFront());
      myQueue->removeFront();
    }

    // Add new items to an empty queue

    myQueue->addBack(6);
    myQueue->addBack(7);
    myQueue->addBack(8);

    // Print all items from queue and stack
    // Remove all stack/queue items.

    while (!myStack->isEmpty())
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "stack pop: %d\n", myStack->peek());
      myStack->pop();
    }
    while (!myQueue->isEmpty())
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "queue getFront: %d\n", myQueue->getFront());
      myQueue->removeFront();
    }

    // Add more items to the stack and queues.

    myStack->push (10);
    myStack->push (11);
    myStack->push (12);
    myQueue->addBack(10);
    myQueue->addBack(11);
    myQueue->addBack(12);

    // Leave the data in the stack and queue to test for proper clean up when the Stack/Queue class is destroyed.
    // Delete stack and queue to test class destructors.
    delete myStack;
    delete myQueue;
    
    DebugConsole::debug_print (0, true, COLOR_WHITE, "Automated tests complete. Entering user mode.\n");

    // Create new class objects
    myStack = new Stack<int>();
    myQueue = new Queue<int>();

    string input;

    bool enteringStack = true;
    bool enteringQueue = true;
    int stackCounter = 0;
    int queueCounter = 0;
    while (enteringStack)
    {
      DebugConsole::debug_print (0, false, COLOR_WHITE, "Enter stack contents (int). %d entered. Enter 'q' to finish. : ", stackCounter);
      cin >> input;
      if (input.compare("q") == 0)
      {
        enteringStack = false;
        break;
      }
      try
      {
        int result = stoi (input);
        myStack->push (result);
        stackCounter++;
      }
      catch (...)
      {
        std::cout << "Invalid input!" << std::endl;
      }
    }

    DebugConsole::debug_print (0, false, COLOR_WHITE, "Printing stack contents.\n\n");
    while (!myStack->isEmpty())
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "stack pop: %d\n", myStack->peek());
      myStack->pop();
    }
    DebugConsole::debug_print (0, false, COLOR_WHITE, "Printing stack contents (n+1).\n\n");
    DebugConsole::debug_print (0, true, COLOR_WHITE, "stack pop: %d\n", myStack->peek());
    myStack->pop();

    while (enteringQueue)
    {
      DebugConsole::debug_print (0, false, COLOR_WHITE, "Enter queue contents (int). %d entered. Enter 'q' to finish. : ", queueCounter);
      cin >> input;
      if (input.compare("q") == 0)
      {
        enteringQueue = false;
        break;
      }
      try
      {
        int result = stoi (input);
        myQueue->addBack (result);
        queueCounter++;
      }
      catch (...)
      {
        std::cout << "Invalid input!" << std::endl;
      }
    }

    DebugConsole::debug_print (0, false, COLOR_WHITE, "Printing queue contents.\n\n");
    while (!myQueue->isEmpty())
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "queue getFront: %d\n", myQueue->getFront());
      myQueue->removeFront();
    }
    DebugConsole::debug_print (0, false, COLOR_WHITE, "Printing queue contents (n+1).\n\n");
    DebugConsole::debug_print (0, true, COLOR_WHITE, "queue getFront: %d\n", myQueue->getFront());
    myQueue->removeFront();


    // Destroy class objects
    delete myStack;
    delete myQueue;

    // Exit and return success.
    return 0;
}

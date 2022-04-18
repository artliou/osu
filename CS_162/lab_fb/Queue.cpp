#include <iostream>
#include <cstdlib>
#include <cstddef>
#include "Queue.hpp"

using std::cout;

/*********************************************************************
** Function: Queue
** Description: Constructor sets front and back pointers to NULL
** Parameters: N/A
*********************************************************************/
Queue::Queue()
{
	front = NULL;
	back = NULL;
}

/*********************************************************************
** Function: ~Queue
** Description: Destructor
** Parameters: N/A
*********************************************************************/
Queue::~Queue()
{
	while (!isEmpty())
		removeFront();
}

/*********************************************************************
** Function: addBack
** Description: Puts on item at end of structure
** Parameters: int input
*********************************************************************/
void Queue::addBack(int input)
{
	if (isEmpty())
	{
		front = new QueueNode(input);
		back = front;
	}
	else
	{
		back->next = new QueueNode(input);
		back = back->next;
	}
}

/*********************************************************************
** Function: getFront
** Description: Returns the value at the front of the structure
*********************************************************************/
int Queue::getFront()
{
	if (isEmpty())
	{
		cout << "The queue is empty.\n";

		// This is disabled because an empty queue should not cause the program for force exit
		//exit(1);
		return 0;
	}
	else
		return front->value;

	//Code for Exception
	/*if (isEmpty()) throw Queue::Underflow();
	return front->value;*/
}

/*********************************************************************
** Function: removeFront
** Description: Removes the value at the front of the structure
*********************************************************************/
void Queue::removeFront()
{
	QueueNode* temp;
	
	if (isEmpty())
	{
		cout << "The queue is empty.\n";
		
		// This is disabled because an empty queue should not cause the program for force exit
		//exit(1);
	}
	else
	{
		temp = front;
		front = front->next;
		delete temp;
	}

	//Code for Exception
	/*if (isEmpty()) throw Queue::Underflow();
	temp = front;
	front = front->next;
	delete temp;*/

}

/*********************************************************************
** Function: isEmpty
** Description: returns true if the queue is empty or false if stack
is not empty
*********************************************************************/
bool Queue::isEmpty() const
{
	if (front == NULL)
		return true;
	else
		return false;
}
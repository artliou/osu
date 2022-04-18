#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <cstddef>
#include "Stack.hpp"


class Queue
	{
	private:
		class QueueNode
		{
			friend class Queue;
			int value;
			QueueNode* next;
			//Constructor
			QueueNode(int value1, QueueNode* next1 = NULL)
			{
				value = value1;
				next = next1;
			}
		};
		QueueNode* front;
		QueueNode* back;

	public:
		Queue();
		~Queue();
		void addBack(int input);
		int getFront();
		void removeFront();
		bool isEmpty() const;

		//Queue Exception
		//class Underflow {};

};
#endif

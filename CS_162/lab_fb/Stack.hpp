#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <cstddef>


class Stack
{
	private:
		class StackNode
		{
			friend class Stack;
			int value;
			StackNode* next;
			//Constructor
			StackNode(int value1, StackNode* next1 = NULL)
			{
				value = value1;
				next = next1;
			}
		};
		StackNode* top;

	public:
		Stack();
		void push(int input);
		int peek();
		void pop();
		bool isEmpty() const;
		
		//Stack Exception
		//class Underflow {};

};
#endif

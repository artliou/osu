/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"

DynArr * balancedArray;

/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string
	pre: s is not null
*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s+i);
	if ( c == '\0' )
		return '\0';
	else
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	pre: s is not null
	post:
*/
int isBalanced(char* s)
{
	if (s == 0)
		return 1;

	char test;
	while ((test = nextChar(s)) != 0)
	{
		if (test == '(')
		{
			pushDynArr (balancedArray, test);
		}
		if (test == ')')
		{
			if (isEmptyDynArr(balancedArray))
			{
				return 0;
			}
			popDynArr (balancedArray);
		}
		printf ("%c", test);
	}
	printf ("\n");
	return isEmptyDynArr(balancedArray);
}

int main(int argc, char* argv[]){

	char* s=argv[1];
	int res;

	printf("Assignment 2\n");

	balancedArray = newDynArr (16);
	res = isBalanced(s);
	deleteDynArr(balancedArray);

	if (res)
		printf("The string %s is balanced\n",s);
	else
		printf("The string %s is not balanced\n",s);

	return 0;
}


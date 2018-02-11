#include "circularList.h"
#include <stdio.h>

int main()
{
	struct CircularList *deque = circularListCreate();
	circularListAddBack(deque, (TYPE)1);
	circularListAddBack(deque, (TYPE)2);
	circularListAddBack(deque, (TYPE)3);
	circularListAddFront(deque, (TYPE)4);
	circularListAddFront(deque, (TYPE)5);
	circularListAddFront(deque, (TYPE)6);
	circularListPrint(deque);
	printf("\n"); //New Line
	printf("Front: %g\n", circularListFront(deque));
	printf("Back: %g\n", circularListBack(deque));

	circularListRemoveFront(deque);
	circularListRemoveBack(deque);
	circularListPrint(deque);
	printf("\n"); //New Line
	circularListReverse(deque);
	circularListPrint(deque);
	printf("\n"); //New Line
	circularListDestroy(deque);

	return 0;
}

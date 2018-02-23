/*
 * Name: Arthur Liou
 * Email: lioua@oregonstate.edu
 * Function: Create a Stack from using Two Queues
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef __TYPE
#define __TYPE
#define TYPE int
#endif

/***
 * Implementation of Queue
 * ***/
struct link
{
  TYPE value;
  struct link *next;
};

struct queue
{
  struct link *frontSentinel;
  struct link *backLink;
};

/***
 * DESCRIPTION: Initializes a queue, the front sentinel
 * ***/
void _queueInitialize(struct queue *q)
{
  struct link *newLink = malloc(sizeof(struct link));
  assert(newLink != 0);
  newLink->next = 0;
  q->frontSentinel = q->backLink = newLink;
}

/***
 * DESCRIPTION: returns a pointer to the initialized queue.
 * ***/
struct queue *_queueCreate()
{
  struct queue *q = malloc(sizeof(struct queue));
  assert(q != 0);
  _queueInitialize(q);
  return q;
}

/***
 * DESCRIPTION: Returns 1 if the queue is empty, 0 if not.
 * ***/
int _queueIsEmpty(struct queue *q)
{
  //If the frontSentinel is the same as the backLink, the queue is empty
  return q->frontSentinel == q->backLink;
}

/***
 * DESCRIPTION: Adds (pushes) the input value to the back of a queue.
 * ***/
void _queuePush(struct queue *q, TYPE value)
{
  struct link *oldBack = q->backLink;
  q->backLink = malloc(sizeof(struct link));
  assert(q->backLink != 0);
  q->backLink->value = value;
  q->backLink->next = 0;
  oldBack->next = q->backLink;
}

/***
 * DESCRIPTION: Returns the value of the first Link.
 * ***/
TYPE _queueFront(struct queue *q)
{
  assert(!_queueIsEmpty(q));
  return q->frontSentinel->next->value;
}

/***
 * DESCRIPTION: Removes the first/front item of the queue.
 * ***/
void _queueShift(struct queue *q)
{
  assert(!_queueIsEmpty(q));
  struct link *oldLink = q->frontSentinel->next;
  q->frontSentinel->next = oldLink->next;
  //Edge Case where the queue is length of 1
  if (q->frontSentinel->next == 0)
  {
    q->backLink = q->frontSentinel;
  }
  free(oldLink);
}

/***
 * DESCRIPTION: Cleans memory allocated for the queue.
 * ***/
void _queueDestroy(struct queue *q)
{
  assert(q != 0);
  while (!_queueIsEmpty(q))
  {
    _queueShift(q);
  }
  free(q->frontSentinel);
  free(q);
}

/***
 * Implementation of Stack
 * ***/
struct stack
{
  //Utilizing two queues, one represents a "holder" queue that represents the top of the stack
  struct queue *q1;
  struct queue *q2;
};

/***
 * DESCRIPTION: Initializes an empty stack.
 * ***/
void _stackInit(struct stack *s)
{
  s->q1 = _queueCreate();
  s->q2 = _queueCreate();
}

/***
 * DESCRIPTION: Returns a pointer to memory for the empty stack
 * ***/
struct stack *stackCreate()
{
  struct stack *s = malloc(sizeof(struct stack));
  assert(s != 0);
  _stackInit(s);
  return s;
}

/***
 * DESCRIPTION: Returns 1 if the stack is empty and 0 if the stack is not empty.
 * ***/
int stackIsEmpty(struct stack *s)
{
  return _queueIsEmpty(s->q1);
}

/***
 * DESCRIPTION: Pushes a value to the top of the stack
 * ***/
void stackPush(struct stack *s, TYPE value)
{
  _queuePush(s->q1, value);
}

/***
 * DESCRIPTION: Returns the top of the stack
 * ***/
TYPE stackTop(struct stack *s)
{
  assert(!stackIsEmpty(s));
  //Transfer q1 to q2 in reverse order, except for least recently added link.
  while (s->q1->frontSentinel->next->next != 0)
  {
    TYPE value = _queueFront(s->q1);
    _queueShift(s->q1);
    _queuePush(s->q2, value);
  }
  //We are able to take the least recently added link and return it after organizing the queues
  TYPE top = _queueFront(s->q1);
  _queueShift(s->q1);
  _queuePush(s->q2, top);
  //moves q2 to q1, so q1 is a true stack
  struct queue *temp = s->q2;
  s->q2 = s->q1;
  s->q1 = temp;
  return top;
}

/***
 * DESCRIPTION: Pops the top of the stack off
 * ***/
void stackPop(struct stack *s)
{
  assert(!stackIsEmpty(s));
  //Similar in funciton to stackTop, but doens't transfer the least recently added link
  while (s->q1->frontSentinel->next->next != 0)
  {
    TYPE value = _queueFront(s->q1);
    _queueShift(s->q1);
    _queuePush(s->q2, value);
  }
  _queueShift(s->q1);
  struct queue *temp = s->q2;
  s->q2 = s->q1;
  s->q1 = temp;
  //returns nothing
}

/***
 * DESCRIPTION: Cleans up memory allocated for the stack.
 * ***/
void stackDestroy(struct stack *s)
{
  _queueDestroy(s->q1);
  _queueDestroy(s->q2);
  free(s);
}

// /*
int main()
{
  //Stack Test Case 1: Push, Top, and Pop.
  struct stack *sample = stackCreate();
  stackPush(sample, 1);
  stackPush(sample, 2);
  stackPush(sample, 3);
  printf("Stack: %d\n", stackTop(sample)); //Expected 3
  stackPush(sample, 4);
  printf("Stack: %d\n", stackTop(sample)); //Expected 4
  stackPop(sample);                        //Removes 4
  printf("Stack: %d\n", stackTop(sample)); //Expected 3
  stackPop(sample);                        //Removes 3
  printf("Stack: %d\n", stackTop(sample)); //Expected 2
  stackPop(sample);                        //Removes 2
  printf("Stack: %d\n", stackTop(sample)); //Expected 1
  stackDestroy(sample);
  printf("Stack: Destroyed \n");
  return 0;
}
// * /
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	assert(list != 0);
	list->size = 0;
	list->frontSentinel = (struct Link*)malloc (sizeof (struct Link));
	list->backSentinel = (struct Link*)malloc (sizeof (struct Link));
	list->frontSentinel->next = list->frontSentinel->prev = list->backSentinel;
	list->backSentinel->next = list->backSentinel->prev = list->frontSentinel;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	assert (list != 0);
	list->size++;
	struct Link * newLink = (struct Link*)malloc (sizeof (struct Link));
	struct Link * leftLink = link->prev;
	newLink->value = value;
	newLink->prev = leftLink;
	newLink->next = link;
	link->prev = newLink;
	leftLink->next = newLink;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert (list != 0);
	assert (list->size > 0);
	list->size--;
	struct Link * leftLink = link->prev;
	struct Link * rightLink = link->next;
	leftLink->next = rightLink;
	rightLink->prev = leftLink;
	free (link);
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	assert (list != 0);
	list->size++;
	struct Link * rightLink = list->frontSentinel->next;
	struct Link * newLink = (struct Link*)malloc (sizeof (struct Link));
	newLink->value = value;
	newLink->prev = list->frontSentinel;
	newLink->next = rightLink;
	list->frontSentinel->next = newLink;
	rightLink->prev = newLink;
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	assert (list != 0);
	list->size++;
	struct Link * leftLink = list->backSentinel->prev;
	struct Link * newLink = (struct Link*)malloc (sizeof (struct Link));
	newLink->value = value;
	newLink->next = list->backSentinel;
	newLink->prev = leftLink;
	list->backSentinel->prev = newLink;
	leftLink->next = newLink;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list != 0);
	assert(list->size > 0);
	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	assert(list != 0);
	assert(list->size > 0);
	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list != 0);
	assert(list->size > 0);
	list->size--;
	struct Link * rightLink = list->frontSentinel->next->next;
	free (list->frontSentinel->next);
	list->frontSentinel->next = rightLink;
	rightLink->prev = list->frontSentinel;
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list != 0);
	assert(list->size > 0);
	list->size--;
	struct Link * leftLink = list->backSentinel->prev->prev;
	free (list->backSentinel->prev);
	list->backSentinel->prev = leftLink;
	leftLink->next = list->backSentinel;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	assert(list != 0);
	return !(list->size > 0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	assert (list != 0);
	assert (list->size > 0);
	struct Link * currentLink = list->frontSentinel->next;
	while (currentLink != list->backSentinel)
	{
		printf ("%p - next=%p, prev=%p, value=%u\n", currentLink, currentLink->next, currentLink->prev, currentLink->value);
		currentLink = currentLink->next;
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	linkedListAddBack (list, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert (list != 0);
	assert (list->size > 0);
	struct Link * currentLink = list->frontSentinel->next;
	while (currentLink != list->backSentinel)
	{
		if (currentLink->value == value)
		{
			return 1;
		}
		currentLink = currentLink->next;
	}
	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	assert (list != 0);
	assert (list->size > 0);
	struct Link * currentLink = list->frontSentinel->next;
	while (currentLink != list->backSentinel)
	{
		if (currentLink->value == value)
		{
			removeLink(list, currentLink);
			return;
		}
		currentLink = currentLink->next;
	}
}

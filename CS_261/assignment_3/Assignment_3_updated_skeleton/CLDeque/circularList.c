#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	assert (list != 0);
	list->size = 0;
	list->sentinel = (struct Link *)malloc (sizeof (struct Link));
	list->sentinel->next = list->sentinel->prev = list->sentinel;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link * newLink = (struct Link *)malloc (sizeof (struct Link));
	newLink->value = value;
	newLink->next = newLink->prev = 0;
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert (list != 0);
	list->size++;
	struct Link * newLink = createLink(value);
	struct Link * rightLink = link->next;
	newLink->prev = link;
	newLink->next = rightLink;
	link->next = newLink;
	rightLink->prev = newLink;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert (list != 0);
	assert (list->size > 0);
	struct Link * leftLink = link->prev;
	struct Link * rightLink = link->next;
	free (link);
	leftLink->next = rightLink;
	rightLink->prev = leftLink;
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	assert (list != 0);
	while (list->size > 0)
	{
		removeLink (list, list->sentinel->next);
	}
	free (list->sentinel);
	free (list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	assert (list != 0);
	list->size++;
	struct Link * newLink = createLink(value);
	struct Link * rightLink = list->sentinel->next;
	newLink->prev = list->sentinel;
	newLink->next = rightLink;
	list->sentinel->next = newLink;
	rightLink->prev = newLink;
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	assert (list != 0);
	list->size++;
	struct Link * newLink = createLink(value);
	struct Link * leftLink = list->sentinel->prev;
	newLink->next = list->sentinel;
	newLink->prev = leftLink;
	list->sentinel->prev = newLink;
	leftLink->next = newLink;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	assert (list != 0);
	assert (list->size > 0);
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert (list != 0);
	assert (list->size > 0);
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert (list != 0);
	assert (list->size > 0);
	list->size--;
	struct Link * rightLink = list->sentinel->next->next;
	free (list->sentinel->next);
	rightLink->prev = list->sentinel;
	list->sentinel->next = rightLink;
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	assert (list != 0);
	assert (list->size > 0);
	list->size--;
	struct Link * leftLink = list->sentinel->prev->prev;
	free (list->sentinel->prev);
	leftLink->next = list->sentinel;
	list->sentinel->prev = leftLink;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	assert (list != 0);
	return !(list->size > 0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	assert (list != 0);
	assert (list->size > 0);
	struct Link * currentLink = list->sentinel->next;
	printf ("-- Printing CircularList\n");
	while (currentLink != list->sentinel)
	{
		printf ("%p next=%p, prev=%p, value=%f\n", currentLink, currentLink->next, currentLink->prev, currentLink->value);
		currentLink = currentLink->next;
	}
	printf ("\n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	assert (list != 0);
	assert (list->size > 0);
	struct Link * endLink = list->sentinel;
	struct Link * curLink = list->sentinel->prev;
	struct Link * lastLink = list->sentinel;
	while (curLink != endLink)
	{
		lastLink->next = curLink;
		struct Link * cacheLink = curLink->prev;
		curLink->prev = lastLink;
		lastLink = curLink;
		curLink = cacheLink;
	}
	lastLink->next = list->sentinel;
	list->sentinel->prev = lastLink;
}

#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H
#include "LinkedQueueTypeIterator.h"
class LinkedQueueType
{
public: 
	LinkedQueueType();
    // Class constructor.
    // Because there is a default constructor, the precondition 
    // that the queue has been initialized is omitted.
	LinkedQueueType(const LinkedQueueType& qt);
	//Copy Constructor
	LinkedQueueType operator=(const LinkedQueueType& rhs);
	//Overloaded assignment operator=
    ~LinkedQueueType();
    // Class destructor.
    void MakeEmpty();
    // Function: Initializes the queue to an empty state.
    // Post: Queue is empty.
    bool IsEmpty() const;
    // Function: Determines whether the queue is empty.
    // Post: Function value = (queue is empty)
    bool IsFull() const;
    // Function: Determines whether the queue is full.
    // Post: Function value = (queue is full)
    void Enqueue(ItemType newItem);
    // Function: Adds newItem to the rear of the queue.
    // Post: If (queue is full) FullQueue exception is thrown
    //       else newItem is at rear of queue.
    void Dequeue(ItemType& item);
    // Function: Removes front item from the queue and returns it in item.
    // Post: If (queue is empty) EmptyQueue exception is thrown
    //       and item is undefined
    //       else front element has been removed from queue and
    //       item is a copy of removed element.
    void Print();
    //Print function

    // Customize with the associated ADT Iterator.
    LinkedQueueTypeIterator begin();
    LinkedQueueTypeIterator end();

private:
    NodeType* rear;
    int length;
};
#endif


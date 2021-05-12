#ifndef QUETYPE_H
#define QUETYPE_H
// Header file for Queue ADT. 
#include <new>
#include <iostream>
using namespace std;

class FullQueue
{};  

class EmptyQueue
{};  
 
template <class QType>
struct NodeType;

template <class QType>
class QueType
{
public: 
    QueType();
    // Class constructor.
    // Because there is a default constructor, the precondition 
    // that the queue has been initialized is omitted.
    QueType(int max);
    // Parameterized class constructor.
    ~QueType();
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
    void Enqueue(QType newItem);
    // Function: Adds newItem to the rear of the queue.
    // Post: If (queue is full) FullQueue exception is thrown
    //       else newItem is at rear of queue.
    void Dequeue(QType& item);
    // Function: Removes front item from the queue and returns it in item.
    // Post: If (queue is empty) EmptyQueue exception is thrown
    //       and item is undefined
    //       else front element has been removed from queue and
    //       item is a copy of removed element.
private:
  NodeType<QType>* front;
  NodeType<QType>* rear;
};

template <class QType>
struct NodeType
{
  QType info;
  NodeType* next;
};


template <class QType>
QueType<QType>::QueType()          // Class constructor.
// Post:  front and rear are set to NULL.
{
  front = NULL;
  rear = NULL;
}

template <class QType>
void QueType<QType>::MakeEmpty()
// Post: Queue is empty; all elements have been deallocated.
{
  NodeType<QType>* tempPtr;

  while (front != NULL)
  {
    tempPtr = front;
    front = front->next;
    delete tempPtr;
  }
  rear = NULL;
}

template <class QType>          // Class destructor.
QueType<QType>::~QueType()
{
  MakeEmpty();
}

template<class QType>
bool QueType<QType>::IsFull() const
// Returns true if there is no room for another QType
//  on the free store; false otherwise.
{
  NodeType<QType>* location;
  try
  {
    location = new NodeType<QType>;
    delete location;
    return false;
  }
  catch(std::bad_alloc& exception)
  {
    return true;
  }
}

template <class QType>
bool QueType<QType>::IsEmpty() const
// Returns true if there are no elements on the queue; false otherwise.
{
  return (front == NULL);
}

template <class QType>
void QueType<QType>::Enqueue(QType newItem)
// Adds newItem to the rear of the queue.
// Pre:  Queue has been initialized.
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown.  

{
  if (IsFull())
    throw FullQueue();
  else
  {
    NodeType<QType>* newNode;

    newNode = new NodeType<QType>;
    newNode->info = newItem;
    newNode->next = NULL;
    if (rear == NULL)
      front = newNode;
    else
      rear->next = newNode;
    rear = newNode;
  }
}

template <class QType>
void QueType<QType>::Dequeue(QType& item)
// Removes front item from the queue and returns it in item.
// Pre:  Queue has been initialized and is not empty.
// Post: If (queue is not empty) the front of the queue has been 
//       removed and a copy returned in item; 
//       othersiwe a EmptyQueue exception has been thrown.
{
  if (IsEmpty())
    throw EmptyQueue();
  else
  {
    NodeType<QType>* tempPtr;

    tempPtr = front;
    item = front->info;
    front = front->next;
    if (front == NULL)
      rear = NULL;
    delete tempPtr;
  }
}
#endif

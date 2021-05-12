#ifndef PQTYPE_H
#define PQTYPE_H
// Definition of class PQType, which represents the Priority Queue ADT
class FullPQ{};
class EmptyPQ{};
#include <iostream>
#include "Heap.h"
#include "MaxItem.h"
using namespace std;

template<class ItemType>
class PQType
{
public:
  PQType();				//default constructor
  PQType(int);          // parameterized class constructor
  ~PQType();            // class destructor
  
  PQType operator=(const PQType& rhs);

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
  // Post: if (the priority queue is full) exception FullPQ is thrown;
  //       else newItem is in the queue.
  
  void Dequeue(ItemType& item);
  // Function: Removes element with highest priority from the queue
  // and returns it in item.
  // Post: If (the priority queue is empty) exception EmptyPQ is thrown;
  //       else highest priority element has been removed from queue.
  //       item is a copy of removed element.
  template <class ItemPQ>
  friend ostream& operator<<(ostream& out, const PQType<ItemPQ>& pq);
private:
  //const int MAX_ITEMS = 10;
  int length;
  HeapType<ItemType> items;
  int maxItems;
};

template<class ItemType>
PQType<ItemType>::PQType(){
	maxItems = MAX_ITEMS;
	items.elements = new ItemType[maxItems];
	length = 0;
}

template<class ItemType>
PQType<ItemType>::PQType(int max)
{
  maxItems = max;
  items.elements = new ItemType[maxItems];
  length = 0;
}

template<class ItemType>
PQType<ItemType> PQType<ItemType>::operator=(const PQType<ItemType>& rhs){
	//assignment operator=
	if(this == &rhs){
		return *this;
	}
	else{
		//delete old contents of this
		delete [] items.elements;
		length = 0;
		maxItems = rhs.maxItems;
		items.elements = new ItemType[rhs.maxItems];

		//copy new contents over to this from rhs
		int count = 0;
		while(count < rhs.length){
			items.elements[count] = rhs.items.elements[count];
			count++;
		}
	}
	return *this;
}

template<class ItemType>
void PQType<ItemType>::MakeEmpty()
{
  length = 0;
}

template<class ItemType>
PQType<ItemType>::~PQType()
{
  delete [] items.elements;
}
template<class ItemType>
void PQType<ItemType>::Dequeue(ItemType& item)
// Post: element with highest priority has been removed 
//       from the queue; a copy is returned in item.
{
  if (length == 0)
    throw EmptyPQ();
  else
  {
    item = items.elements[0];
    items.elements[0] = items.elements[length-1];
    length--;
    items.ReheapDown(0, length-1);
  }
}

template<class ItemType>
void PQType<ItemType>::Enqueue(ItemType newItem)
// Post: newItem is in the queue.
{
  if (length == maxItems)
    throw FullPQ();
  else
  {
    length++;
    items.elements[length-1] = newItem;
    items.ReheapUp(0, length-1);
  }
}
template<class ItemType>
bool PQType<ItemType>::IsFull() const
// Post: Returns true if the queue is full; false, otherwise.
{
  return length == maxItems;
}

template<class ItemType>
bool PQType<ItemType>::IsEmpty() const
// Post: Returns true if the queue is empty; false, otherwise.
{
  return length == 0;
}

template <class ItemPQ>
ostream& operator<<(ostream& out, const PQType<ItemPQ>& pq){
	for(int i = 0; i < pq.length; i++){
		out << pq.items.elements[i] << " ";
	}
	out << endl;
	return out;
}
#endif

#include "LinkedQueueType.h"
#include <iostream>
using namespace std;

LinkedQueueType::LinkedQueueType(const LinkedQueueType& qt){
	// copy constructor
}

LinkedQueueType LinkedQueueType::operator=(const LinkedQueueType& rhs){
	//assignment operator=
}

LinkedQueueType::LinkedQueueType()          // Default class constructor
// Post: maxQue, front, and rear have been initialized.
//       The array to hold the queue elements has been dynamically
//       allocated.
{

}
LinkedQueueType::~LinkedQueueType()         // Class destructor
{

}

void LinkedQueueType::MakeEmpty()
// Post: rear and length have been reset to the empty state.
{

}

bool LinkedQueueType::IsEmpty() const
// Returns true if the queue is empty; false otherwise.
{
  return (length == 0);
}

bool LinkedQueueType::IsFull() const
// This structure can net get full.
{
  return false;
}

void LinkedQueueType::Enqueue(ItemType newItem)
// Post: If (queue is not full) newItem is at the rear of the queue; newItem's next is front
//       otherwise a FullQueue exception is thrown.  
{

}

void LinkedQueueType::Dequeue(ItemType& item)
// Post: If (queue is not empty) the front of the queue has been 
//       removed and a copy returned in item; 
//       othersiwe a EmptyQueue exception has been thrown.
{

}

void LinkedQueueType::Print(){
	NodeType* node = rear->next;
	int count = 0;
	while(count < length){
		cout << node->info << " ";
		node = node->next;
		count++;
	}
	cout << endl;
}

//
// The methods below provide the range-based for loop support. These would
// be customized with the companion LinkedQueueTypeIterator class that is returned.
//
LinkedQueueTypeIterator LinkedQueueType::begin()
{
	//Complete this.
}

LinkedQueueTypeIterator LinkedQueueType::end()
{
	//Complete this.
}

#ifndef STACKTYPE_H
#define STACKTYPE_H
#include "MaxItem.h"
// The class definition for StackType using templates 
class FullStack
// Exception class thrown by Push when stack is full.
{};

class EmptyStack
// Exception class thrown by Pop and Top when stack is emtpy.
{};


// MaxItems.h must be provided by the user of this class.
// This file must contains the definition of MAX_ITEMS,
// themaximum number ofitems on the stack.

template<class ItemType>		
class StackType
{
public:

    StackType();
    // Class constructor.
    bool IsFull() const;
    // Function: Determines whether the stack is full.
    // Pre:  Stack has been initialized.
    // Post: Function value = (stack is full)
    bool IsEmpty() const;
    // Function: Determines whether the stack is empty.
    // Pre:  Stack has been initialized.
    // Post: Function value = (stack is empty)
    void Push(ItemType item);
    // Function: Adds newItem to the top of the stack.
    // Pre:  Stack has been initialized.
    // Post: If (stack is full), FullStack exception is thrown;
    //       otherwise, newItem is at the top of the stack.
    void Pop(ItemType& popedItem);
    // Function: Removes top item from the stack.
    // Pre:  Stack has been initialized.
    // Post: If (stack is empty), EmptyStack exception is thrown;
    //       otherwise, top element has been removed from stack.
    //       popedItem holds the data of the most recently popped item from the stack.
    ItemType Top();
    // Function: Returns a copy of top item on the stack.
    // Pre:  Stack has been initialized.
    // Post: If (stack is empty), EmptyStack exception is thrown;
    //       otherwise, top element has been removed from stack.
           
private:
    int top;
    ItemType  items[MAX_ITEMS];	
};


// The function definitions for class StackType.

// The function definitions for class StackType.
template<class ItemType>
StackType<ItemType>::StackType()
{
  top = -1;
}

template<class ItemType>
bool StackType<ItemType>::IsEmpty() const
{
  return (top == -1);
}

template<class ItemType>
bool StackType<ItemType>::IsFull() const
{
  return (top == MAX_ITEMS-1);
}

template<class ItemType>
void StackType<ItemType>::Push(ItemType newItem) 
{
	if (IsFull())
		throw FullStack();
	top++;
	items[top] = newItem;
}

//IT 5/1/2019 Modified Pop
template<class ItemType>
void StackType<ItemType>::Pop(ItemType& pI)
{
  if( IsEmpty() )
    throw EmptyStack();
  pI = items[top];
  top--;
}

template<class ItemType>
ItemType StackType<ItemType>::Top()
{
  if (IsEmpty())
    throw EmptyStack();
  return items[top];
}  

#endif

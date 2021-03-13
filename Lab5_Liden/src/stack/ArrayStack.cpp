/**
 * ArrayStack Implementation
 *
 * Mostly unaltered from the D2L materials.
 *
 * See new additions: ReplaceItem, Identical
 *
 * Benjamin Liden 3/13
 */



#include "./ArrayStack.h"

ArrayStack::ArrayStack(int max) :
		maxStack { max }, top { -1 }, items { new ItemType[maxStack] } {
}

ArrayStack::ArrayStack() :
		maxStack { 500 }, top { -1 }, items { new ItemType[maxStack] } {
}

bool ArrayStack::IsEmpty() const {
	return (top == -1);
}

bool ArrayStack::IsFull() const {
	return (top == maxStack - 1);
}

void ArrayStack::Push(ItemType newItem) {
	if (IsFull())
		throw FullStack();
	top++;
	items[top] = newItem;
}

void ArrayStack::Pop() {
	if (IsEmpty())
		throw EmptyStack();
	top--;
}

ItemType ArrayStack::Top() {
	if (IsEmpty())
		throw EmptyStack();
	return items[top];
}

ArrayStack::~ArrayStack() {
	delete[] items;
}

void ArrayStack::Print(std::ostream& out) {
	if (IsEmpty()) {
		 out << "Stack is empty." << std::endl;
		 return;
	}
	for (int i = 0; i < this->top; ++i) {
		out << items[i];
	}
	out << std::endl;
}

void ReplaceItem(ArrayStack& stack, ItemType oldItem, ItemType newItem) {
	ArrayStack tempStack; // this SHOULD be the same length as the incoming Stack

	while (!stack.IsEmpty()) { // unload stack into a temporary stack
		tempStack.Push(stack.Top());
		stack.Pop();
	}
	while (!tempStack.IsEmpty()) { // re-load stack, changing any values as needed
		auto tempItem = tempStack.Top();
		tempItem == oldItem
			? stack.Push(newItem)
			: stack.Push(tempItem);
		tempStack.Pop();
	}
}

bool Identical(const ArrayStack& stack1, const ArrayStack& stack2) {
	// if lengths aren't same
	if (stack1.top != stack2.top) return false;

	// check each index, step by step
	for (int i = 0; i < stack1.top; i++) {
		if (stack1.items[i] != stack2.items[i]) {
			return false; // short-circuit function if anything doesn't match
		}
	}

	return true;
}


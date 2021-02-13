/**
 * Test Driver for SplitLists member function
 * 		in both ArrayBacked and LinkedList unsorted lists.
 *
 * Written by Benjamin Liden
 * 		for Prof. I. Temesvari's CS240 course.
 * 		Exercise 2.
 */
#include <iostream>
#include <sstream>
#include <assert.h>

#include "LinkedList/linked_unsorted.h"
#include "ArrayList/array_unsorted.h"
#include "ItemType.h"

using namespace Item;

constexpr int testData[] =
		{ 5, -12, 34, 34, 5, 45, 8, -6, 15, 40, 20, 2, 1, 12 };
constexpr char lessThanSolution[] = "5, -12, 5, 8, -6, 2, 1";
constexpr char greaterThanSolution[] = "34, 34, 45, 15, 40, 20, 12";

void testArrayList();
void testLinkedList();
void testCloneLinkedList();

int main() {
	testArrayList();
	testLinkedList();
	testCloneLinkedList();
	std::cout << "Tests Finished. Success!" << std::endl;
	return 0;
}

void testArrayList() {
	// load initial list
	auto arrayList = ArrayBackedUnsortedType { };
	arrayList.ResetList();
	for (const auto number : testData) {
		ItemType item = ItemType { };
		item.Initialize(number);
		arrayList.PutItem(item);
	}

	// make secondary lists and median item
	auto lessThanOrEqual = ArrayBackedUnsortedType { };
	auto greaterThan = ArrayBackedUnsortedType { };
	auto qualifier = ItemType { };
	qualifier.Initialize(8);
	ArrayBackedUnsortedType::SplitLists(arrayList, qualifier, lessThanOrEqual,
			greaterThan);

	// print onto streams
	std::stringstream less;
	lessThanOrEqual.Print(less);
	std::stringstream greater;
	greaterThan.Print(greater);

	// assert that less/greater streams match solutions
	assert(less.str() == lessThanSolution);
	assert(greater.str() == greaterThanSolution);
}

void testLinkedList() {
	// load initial list
	auto linkedList = LinkedListUnsortedType { };

	for (const auto number : testData) {
		ItemType item = ItemType { };
		item.Initialize(number);
		linkedList.PutItem(item);
	}

	// make secondary lists and qualifier item
	auto lessThanOrEqual = LinkedListUnsortedType { };
	auto greaterThan = LinkedListUnsortedType { };
	auto qualifier = ItemType { };
	qualifier.Initialize(8);
	LinkedListUnsortedType::SplitLists(linkedList, qualifier, lessThanOrEqual,
			greaterThan);

	// print onto streams
	std::stringstream less;
	lessThanOrEqual.Print(less);
	std::stringstream greater;
	greaterThan.Print(greater);

	// assert that less/greater streams match solutions
	assert(less.str() == lessThanSolution);
	assert(greater.str() == greaterThanSolution);
}

void testCloneLinkedList() {
	/**
	 * Here we test that the copy constructor
	 * 		not only copies the data,
	 * 		but the current position as well.
	 */
	auto list = LinkedListUnsortedType{};
	for (const auto number : testData) {
		ItemType item = ItemType { };
		item.Initialize(number);
		list.PutItem(item);
	}

	// increment a few times so currentPos is not null
	list.GetNextItem();
	list.GetNextItem();
	list.GetNextItem();

	auto clonedList = list; // this will trigger the copy constructor

	// both next items should be in sync
	assert(list.GetNextItem().ComparedTo(clonedList.GetNextItem()) == Item::RelationType::EQUAL);
}


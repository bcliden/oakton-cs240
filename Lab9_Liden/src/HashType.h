#pragma once

//============================================================================
// Name        : Lab 9
// Author      : Benjamin Liden
// Date        : April 18, 2021
// Professor   : Ivan Temesvari
// Course 	   : CS240 C++ Data Structures
//============================================================================

/*
 * Note:
 * This file is originally from the provided CS240_HashingIntegers zip archive.
 * I have made further modifications to suit the lab. See the bottom "Additions" Section.
 *
 * Originally written by Ivan Temesvari on 4/10/2019
 */

#include <string>
#include <iostream>
#include <bitset>
#include <exception>

const unsigned int MAX_ITEMS = 11;
constexpr int DEFAULT_FACTOR = 31;

template<class T>
class HashType {
public:
	// Constructor
	HashType();
	HashType(unsigned int s);
	HashType(unsigned int s, int factor);

	// Function: Returns the list to the empty state.
	// Post:  List is empty.
	void MakeEmpty();

	// Function:  Determines whether list is full.
	// Pre:  List has been initialized.
	// Post: Function value = (list is full)
	bool IsFull() const;

	// Function: Determines the number of elements in list.
	// Pre:  List has been initialized.
	// Post: Function value = number of elements in list
	int GetNumItems() const;

	// Function: Retrieves list element whose key matches item's key (if
	//           present).
	// Pre:  List has been initialized.
	//       Key member of item is initialized.
	// Post: If there is an element someItem whose value matches
	//       item's value, then found = true and item contains the contents of
	//       the item if it is found.
	// 	     otherwise found = false and item is returned unchanged.
	//       List is unchanged.
	void RetrieveItem(T item, bool &found);

	// Function: Adds item to list and uses a linear probing technique to
	// resolve collisions.  If the flag is true, a random hash method will be used.
	//If the flag is false, the division method will be used.
	// Pre:  List has been initialized.
	//       List is not full.
	//       item is not in list.
	// Post: item is in list.
	void Insert(T item);

	void InsertItemLinear(T item);
	void InsertItemQuadratic(T item);

	// Function: Deletes the element whose key matches item's key.
	// Pre:  List has been initialized.
	//       Key member of item is initialized.
	//       One and only one element in list has a key matching item's key.
	// Post: No element in list has a key matching item's key.
	void DeleteItem(T item);

	//This is the hash function for this class. If the flag is true, a random hash method will be used.
	//If the flag is false, the division method will be used.
	unsigned int Hash(T item) const;

	//return the number of collisions that occured during the build of the hash table
	unsigned long int GetCollisions() const;

	// add'l template declaration for friend function found here: https://stackoverflow.com/a/4661372
	template<class U>
	friend std::ostream& operator<<(std::ostream &out,
			const HashType<U> &items);

private:
	unsigned long int numCollisions;
	int a; // factor used for polynomial hash fn
	int numItems;
	unsigned int size;
	T *info;
	T emptyItem;
};

template<class T>
HashType<T>::HashType() {
	numItems = 0;
	numCollisions = 0;
	a = DEFAULT_FACTOR;
	size = MAX_ITEMS;
	info = new T[size];
	for (int i = 0; i < size; i++)
		info[i] = emptyItem;
}

template<class T>
HashType<T>::HashType(unsigned int s) {
	numItems = 0;
	numCollisions = 0;
	a = DEFAULT_FACTOR;
	size = s;
	info = new T[size];
	for (unsigned int i = 0; i < size; i++) {
		info[i] = emptyItem;
	}
}

template<class T>
HashType<T>::HashType(unsigned int s, int factor) {
	numItems = 0;
	numCollisions = 0;
	a = factor;
	size = s;
	info = new T[size];
	for (unsigned int i = 0; i < size; i++) {
		info[i] = emptyItem;
	}
}

template<class T>
bool HashType<T>::IsFull() const {
	return (numItems == size);
}

template<class T>
int HashType<T>::GetNumItems() const {
	return numItems;
}

template<class T>
void HashType<T>::MakeEmpty()
// Post: list is empty.
{
	numItems = 0;
	for (int i = 0; i < size; i++)
		info[i] = emptyItem;
}

template<class T>
//Updated IT via Dale 1/31/2019
void HashType<T>::DeleteItem(T item) {
	int location = 0;
	int startLoc;

	startLoc = Hash(item);
	location = startLoc;
	do {
		if (info[location] == item || info[location] == emptyItem) {
			info[location] = -1;
			numItems--;
			return;
		} else
			location = (location + 1) % size;
	} while (location != startLoc);

	if (location == startLoc) {
		std::cout << "Item to delete not found." << std::endl;
	}
}

template<class T>
unsigned long int HashType<T>::GetCollisions() const {
	return numCollisions;
}

template<class T>
void HashType<T>::Insert(T item)
// Post: item is stored in the array at position item.Hash()
//       or the next free spot.
		{
	int location;
	location = Hash(item);

	while (info[location] != emptyItem) {
		location = (location + 1) % size;   //linear probing
		numCollisions++;
	}

	info[location] = item;
	numItems++;
}

template<class T>
void HashType<T>::RetrieveItem(T item, bool &found) {
	int location;
	int startLoc;
	bool moreToSearch = true;

	startLoc = Hash(item);
	location = startLoc;
	do {
		if (info[location] == item || info[location] == emptyItem)
			moreToSearch = false;
		else
			location = (location + 1) % size;
	} while (location != startLoc && moreToSearch);
	found = (info[location] == item);
	if (found)
		item = info[location];
}

/*
 *
 * Additions and changes by Benjamin Liden on 4/18/2021 found below
 *
 */

template<class T> // slightly updated to skip empty slots
std::ostream& operator<<(std::ostream &out, const HashType<T> &items) {
	out << "HashTable [ ";
	/*
	 * This was changed from items.numItems to items.size so all
	 * 		array indices would have a chance to print.
	 */
	for (unsigned int i = 0; i < items.size; i++) {
		if (i == 0) {
			out << items.info[i];
		} else if (items.info[i] == items.emptyItem) {
			// Additionally, if the slot is empty, skip printing it.
			continue;
		} else {
			out << ", " << items.info[i];
		}
	}
	out << " ]" << std::endl;
	return out;
}

/*
 * This is actually very similar to HashTable::Insert above.
 * I didn't find many changes to be necessary.
 */
template<class T>
void HashType<T>::InsertItemLinear(T item) {
	unsigned int location = Hash(item);
	while (info[location] != emptyItem) {
		location = (location + 1) % size;
		numCollisions += 1;
	}
	info[location] = item;
	numItems += 1;
}

/*
 * Hashing references and quadratic method from here:
 * https://www.cpp.edu/~ftang/courses/CS240/lectures/hashing.htm
 */
template<class T>
void HashType<T>::InsertItemQuadratic(T item) {
	int location = Hash(item); // equivalent to c = 0

	int c = 1;
	while (info[location] != emptyItem) {
		// use a higher constant to add each time
		location = (location + (c * c)) % size; // std::pow(c, 2) isn't really needed here
		numCollisions += 1;
		c++;
	}
	info[location] = item;
	numItems += 1;
}

template<class T> // generic hash function. not currently supported in context of this lab.
unsigned int HashType<T>::Hash(T item) const {
	return 0;
}

template<> // Specialized hash for ints, from CSC240_Hashing_Integers.zip
unsigned int HashType<int>::Hash(int item) const
// Post: Returns an integer between 0 and MAX_ITEMS -1.
		{
	std::bitset<64> input(item);
	//convert the item to a bit string and XOR it with a random 64-bit bit string: x12345678
	std::bitset<64> randBits(0x12345678);
	std::bitset<64> place(input ^ randBits);
	int placeInt = int(place.to_ulong());
	return placeInt % size;
}

// Hash a given string using a given array size and factor
unsigned int hashString(std::string s, int size, int a) {
	unsigned int hash = 0;
	unsigned int n = s.length();
	for (unsigned int i = 0; i < n; i++) {
		hash = a * hash + s.at(i);
	}
	int retval = hash % size;
	return retval;
}

template<> // Specialized hash method only for strings
unsigned int HashType<std::string>::Hash(std::string item) const {
	return hashString(item, this->size, this->a);
}

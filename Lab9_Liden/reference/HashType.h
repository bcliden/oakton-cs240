#ifndef HASHTYPE_H
#define HASHTYPE_H
// File ItemType.h must be provided by the user of this class. 
//  ItemType.h must contain the following definitions: 
//  MAX_ITEMS:     the maximum number of items on the list 
//  ItemType:      generic data type
// Author: Ivan Temesvari
// Date 4/10/2019
#include <string>
#include <cmath>
#include <iostream>
#include <bitset>
using namespace std;
const int MAX_ITEMS = 11;
const int A = 33;
class HashType
{
	public:
		HashType();
		// Constructor
		HashType(int s);
		//Dynamic size constructor
		void SetHashType(bool flag);
		void MakeEmpty();
		// Function: Returns the list to the empty state.
		// Post:  List is empty.
		bool IsFull() const;
		// Function:  Determines whether list is full.
		// Pre:  List has been initialized.
		// Post: Function value = (list is full)
		int GetNumItems() const;
		// Function: Determines the number of elements in list.
		// Pre:  List has been initialized.
		// Post: Function value = number of elements in list
		void RetrieveItem(int item, bool& found);
		// Function: Retrieves list element whose key matches item's key (if
		//           present).
		// Pre:  List has been initialized.
		//       Key member of item is initialized.
		// Post: If there is an element someItem whose value matches
		//       item's value, then found = true and item contains the contents of
		//       the item if it is found.
		// 	     otherwise found = false and item is returned unchanged.
		//       List is unchanged.
		void Insert(int item);
		// Function: Adds item to list and uses a linear probing technique to
		// resolve collisions.  If the flag is true, a random hash method will be used.
		//If the flag is false, the division method will be used.
		// Pre:  List has been initialized.
		//       List is not full.
		//       item is not in list.
		// Post: item is in list.
		void DeleteItem(int item);
		// Function: Deletes the element whose key matches item's key.
		// Pre:  List has been initialized.
		//       Key member of item is initialized.
		//       One and only one element in list has a key matching item's key.
		// Post: No element in list has a key matching item's key.
		int Hash(int item) const;
		//This is the hash function for this class. If the flag is true, a random hash method will be used.
		//If the flag is false, the division method will be used.

		unsigned long int GetCollisions() const;
		//return the number of collisions that occured during the build of the hash table
		friend ostream& operator<<(ostream& out, const HashType& items);

	private:
		bool hashType;  //false is division method, true is a random folding method. default is false.
		unsigned long int numCollisions;
		int numItems;
		int size;
		int* info;
		int emptyItem = -1;
};

void HashType::SetHashType(bool flag){
	hashType = flag;
}

HashType::HashType()
{
  hashType = false;
  numCollisions = 0;
  numItems = 0;
  size = MAX_ITEMS;
  info = new int[size];
  for(int i = 0; i < size; i++)
	  info[i] = emptyItem;
}

HashType::HashType(int s){
	hashType = false;
	numItems = 0;
	numCollisions = 0;
	size = s;
	info = new int[size];
	for(int i = 0; i < size; i++){
		info[i] = emptyItem;
	}
}

bool HashType::IsFull() const
{
  return (numItems == size);
}

int HashType::GetNumItems() const
{
  return numItems;
}

void HashType::MakeEmpty()
// Post: list is empty.
{
  numItems = 0;
  for(int i = 0; i < size; i++)
	  info[i] = emptyItem;
}

//Updated IT via Dale 1/31/2019
void HashType::DeleteItem(int item)
{
	int location = 0;
	int startLoc;

	startLoc = Hash(item);
    location = startLoc;
    do
    {
      if (info[location] == item || info[location] == emptyItem){
    	  info[location] = -1;
    	  numItems--;
    	  return;
      }
      else
    	  location = (location + 1) % size;
    } while (location != startLoc);

    if(location == startLoc){
    	cout << "Item to delete not found." << endl;
    }
}


int HashType::Hash(int item) const
// Post: Returns an integer between 0 and MAX_ITEMS -1.
{
	if(hashType){
		std::bitset< 64 > input(item);
		//convert the item to a bit string and XOR it with a random 64-bit bit string: x12345678
		std::bitset< 64 > randBits(0x12345678);
		std::bitset< 64 > place(input ^ randBits);
		int placeInt = int(place.to_ulong());
		return abs(placeInt % size);
	}
	else{
		//prevent overflow negative values as an index.
		return abs((item % size));
	}
}


unsigned long int HashType::GetCollisions() const{
	return numCollisions;
}


void HashType::Insert(int item)
// Post: item is stored in the array at position item.Hash()
//       or the next free spot.
{
  int location;
  location = Hash(item);

  while (info[location] != emptyItem){
    location = (location + 1) % size;   //linear probing
    numCollisions++;
  }

  info[location] = item;
  numItems++;
}


void HashType::RetrieveItem(int item, bool& found)
{
  int location;
  int startLoc;
  bool moreToSearch = true;

  startLoc = Hash(item);
  location = startLoc;
  do
  {
    if (info[location] == item || info[location] == emptyItem)
      moreToSearch = false;
    else
      location = (location + 1) % size;
  } while (location != startLoc && moreToSearch);
  found = (info[location] == item);
  if (found)
    item = info[location];
}


ostream& operator<<(ostream& out, const HashType& items){
	out << "[ ";
	for(int i = 0; i < items.numItems; i++){
		if(i == 0)
			out << items.info[i];
		else
			out << ", " << items.info[i];
	}
	out << " ]" << endl;
	return out;
}

#endif

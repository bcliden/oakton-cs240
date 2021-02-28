#ifndef SORTED
#define SORTED
//Modified by: Ivan Temesvari
// 2/26/2020
#include "ItemType.h" 
class ArrayLengthMismatch{   //used as an exception class for dot product error.
	public:
		ArrayLengthMismatch(){
			myError = "Array lengths are not the same.";
		}
		string what(){
			return myError;
		}

	private:
		string myError;
};
// File ItemType.h must be provided by the user of this class. 
//  ItemType.h must contain the following definitions: 
//  MAX_ITEMS:     the maximum number of items on the list 
//  ItemType:      the definition of the objects on the list 
//  RelationType:  {LESS, GREATER, EQUAL}
//  Member function ComparedTo(ItemType item) which returns 
//       LESS, if self "comes before" item 
//       GREATER, if self "comes after" item 
//       EQUAL, if self and item are the same 

class SortedType{
	public:
		friend ostream& operator<<(ostream& out, const SortedType list);
		SortedType();
		SortedType operator++();  //pre
		SortedType operator++(int);  //post
		int operator*(const SortedType&);


		void MakeEmtpy();
		  // Function: Returns list to the empty state
		  // Post:  List is empty.

		  bool IsFull() const;
		  // Function:  Determines whether list is full.
		  // Pre:  List has been initialized.
		  // Post: Function value = (list is full)

		  int GetLength() const;
		  // Function: Determines the number of elements in list.
		  // Pre:  List has been initialized.
		  // Post: Function value = number of elements in list

		  int GetMaxLength() const;

		  ItemType GetItem(ItemType item, bool& found);
		  // Function: Retrieves list element whose key matches item's key (if
		  //           present).
		  // Pre:  List has been initialized.
		  //       Key member of item is initialized.
		  // Post: If there is an element someItem whose key matches
		  //       item's key, then found = true and item is returned;
		  //       someItem; otherwise found = false and item is returned.
		  //       List is unchanged.

		  void PutItem(ItemType item);
		  // Function: Adds item to list.
		  // Pre:  List has been initialized.
		  //       List is not full.
		  //       item is not in list.
		  //       List is sorted.
		  // Post: item is in list.
		  //       List is sorted

		  void DeleteItem(ItemType item);
		  // Function: Deletes the element whose key matches item's key.
		  // Pre:  List has been initialized.
		  //       Key member of item is initialized.
		  //       One and only one element in list has a key matching item's key.
		  // Post: No element in list has a key matching item's key.
		  //       List is sorted.

		  void ResetList();
		  // Function: Initializes current position for an iteration through the list.
		  // Pre:  List has been initialized.
		  // Post: Current position is prior to list.

		  ItemType GetNextItem();
		  // Function: Gets the next element in list.
		  // Pre:  List has been initialized and has not been changed since last call.
		  //       Current position is defined.
		  //       Element at current position is not last in list.
		  //
		  // Post: Current position is updated to next position.
		  //       Returns a copy of element at current position.

		  void MakeEmpty();
		  // Function: Make the list empty
		  // Pre:  List has been initialized.
		  // Post: The list is empty

	private:
		  int length;
		  ItemType* info;
		  int currentPos;
		  int MAX_ITEMS;
};

int SortedType::operator*(const SortedType& op){
	int product = 0;
//try{
	if(length == op.length){
		for(int i = 0; i < length; i++){
			product += info[i].GetValue()*op.info[i].GetValue();
		}
	}
	else{
		throw ArrayLengthMismatch();
	}
//}
//catch(ArrayLengthMismatch& err){
//	cout << err.what() << endl;
//}

	return product;
}


SortedType SortedType::operator++(){   //pre-increment: increases the size of the info array by 1.
	ItemType* infoCopy = new ItemType[MAX_ITEMS + 1];
	for(int i = 0; i < MAX_ITEMS; i++){
		infoCopy[i] = info[i];
	}
	delete[] info;
	MAX_ITEMS++;
	info = infoCopy;
	return *this;
}

SortedType SortedType::operator++(int){   //post-increment: increases the size of the info array by 1.
	ItemType* infoCopy = new ItemType[MAX_ITEMS + 1];
	for(int i = 0; i < MAX_ITEMS; i++){
		infoCopy[i] = info[i];
	}
	delete[] info;
	MAX_ITEMS++;
	info = infoCopy;
	return *this;
}

ostream& operator<<(ostream& out, const SortedType list){
	if(list.length == 0){
		out << "Empty list.";
	}
	for(int i = 0; i < list.length; i++){
		list.info[i].Print(out);
		out << " ";
	}
	out << endl;
	return out;
}


SortedType::SortedType(){
	MAX_ITEMS = 5;
	info = new ItemType[MAX_ITEMS];
	currentPos = -1;
	length = 0;
}

void SortedType::MakeEmpty()
{
  length = 0;
}

bool SortedType::IsFull() const
{
  return (length == MAX_ITEMS);
}

int SortedType::GetLength() const
{
  return length;
}

int SortedType::GetMaxLength() const
{
  return MAX_ITEMS;
}

ItemType SortedType::GetItem(ItemType item, bool& found)
{
  int midPoint;
  int first = 0;
  int last = length - 1;

  bool moreToSearch = first <= last;
  found = false;
  while (moreToSearch && !found)
  {
    midPoint = ( first + last) / 2;
    switch (item.ComparedTo(info[midPoint]))
    {
      case LESS    : last = midPoint - 1;
                     moreToSearch = first <= last;
                     break;
      case GREATER : first = midPoint + 1;
                     moreToSearch = first <= last;
                     break;
      case EQUAL   : found = true;
                     item = info[midPoint];
                     break;
    }
  }
  return item;
}

void SortedType::DeleteItem(ItemType item)
{
  int location = 0;

  while (item.ComparedTo(info[location]) != EQUAL)
    location++;
  for (int index = location + 1; index < length; index++)
    info[index - 1] = info[index];
  length--;
}

void SortedType::PutItem(ItemType item)
{
  bool moreToSearch;
  int location = 0;
  //Make some room for one more.
  if(IsFull()){
	  //enlarge the list by 1
	  ++(*this);   //use pre-increment
	  //(*this)++:   //use post-increment
  }
  moreToSearch = (location < length);
  while (moreToSearch)
  {
	switch (item.ComparedTo(info[location]))
	{
	  case LESS    : moreToSearch = false;
					 break;
	  case GREATER : location++;
					 moreToSearch = (location < length);
					 break;
	}
  }
  for (int index = length; index > location; index--)
	info[index] = info[index - 1];
  info[location] = item;
  length++;
}

void SortedType::ResetList()
// Post: currentPos has been initialized.
{
  currentPos = -1;
}

ItemType SortedType::GetNextItem()
// Post: item is current item.
//       Current position has been updated.
{
  currentPos++;
  return info[currentPos];
}
#endif

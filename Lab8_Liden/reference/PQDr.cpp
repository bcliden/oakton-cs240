//Ivan Temesvari
//4/1/2019
//Lab 8 driver
#include <iostream>
#include <fstream>
typedef int ItemType;
#include "PQType.h"

using namespace std;

int main()
{
	//sample code for using a PQType
  ItemType item;
  PQType<int> queue(50);
  queue.Enqueue(5);
  queue.Enqueue(10);
  queue.Enqueue(4);
  cout << queue << endl;
  return 0;
}



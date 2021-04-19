/*
 * HashTest.cpp
 *
 *  Created on: Apr 9, 2020
 *      Author: Ivan Temesvari
 */
#include "HashType.h"
#include <cmath>
#include <iostream>
using namespace std;

int main(){
	HashType myHashTableDivision(11);
	myHashTableDivision.Insert(45);
	myHashTableDivision.Insert(34);
	myHashTableDivision.Insert(12);
	myHashTableDivision.Insert(2);
	myHashTableDivision.Insert(3);
	myHashTableDivision.Insert(56);
	myHashTableDivision.Insert(78);
	myHashTableDivision.Insert(99);
	myHashTableDivision.Insert(22);
	myHashTableDivision.Insert(54);
	cout << myHashTableDivision;
	cout << "Number of collisions: " << myHashTableDivision.GetCollisions() << endl << endl;

	HashType myHashTableRandom(11);
	myHashTableRandom.SetHashType(true);
	myHashTableRandom.Insert(45);
	myHashTableRandom.Insert(34);
	myHashTableRandom.Insert(12);
	myHashTableRandom.Insert(2);
	myHashTableRandom.Insert(3);
	myHashTableRandom.Insert(56);
	myHashTableRandom.Insert(78);
	myHashTableRandom.Insert(99);
	myHashTableRandom.Insert(22);
	myHashTableRandom.Insert(54);
	cout << myHashTableRandom;
	cout << "Number of collisions: " << myHashTableRandom.GetCollisions() << endl;
}




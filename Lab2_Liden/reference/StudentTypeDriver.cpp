/*
 * StudentTypeDriver.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: igt88
 */
#include "unsorted.h"
#include <iostream>
using namespace std;

int main(){
	StudentType student1, student2, student3;
	DateType student1DOB, student2DOB,student3DOB;

	student1DOB.Initialize(7, 15, 1978);
	student2DOB.Initialize(6, 23, 1980);
	student3DOB.Initialize(3, 4, 1945);

	student1.Initialize("Ivan", student1DOB, ENROLLED);
	student2.Initialize("Jim", student2DOB, GRADUATED);
	student3.Initialize("Billy", student3DOB, NON_ATTENDING);

	UnsortedType classList;

	classList.PutItem(student1);
	classList.PutItem(student2);

	//NON_ATTENDING = 0, ENROLLED = 1, GRADUATED = 2
	cout << "Compare student1 to student1: " << student1.ComparedTo(student1) << endl;  //expect 1 for same status
	cout << "Compare student1 to student2: " << student1.ComparedTo(student2) << endl;  //expect 0 when status is not the same

	cout << "Print list 0:\n";
	classList.ResetList();  //reset the current position to NULL
	classList.Print();
	cout << "Print list 1:\n";
	classList.DeleteItem(student1);
	classList.ResetList();  //this must be reset before printing the list everytime
	classList.Print();
	cout << "Print list 2:\n";
	classList.PutItem(student3);
	classList.ResetList();  //this must be reset before printing the list everytime
	classList.Print();
	cout << "Print list 3:\n";
	classList.DeleteItem(student2);
	classList.DeleteItem(student3);
	classList.ResetList();
	classList.Print();
}

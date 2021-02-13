/**
 * Test Driver for List.Print and Student.ComparedTo member functions.
 *
 * Largely untouched from igt88's original implementation.
 *
 * Written by Benjamin Liden
 * 		for Prof. I. Temesvari's CS240 course.
 * 		Lab 2.
 * 		2/13/2021
 */
#include "LinkedList/linked_unsorted.h"
#include "StudentType.h"

#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

using namespace std;

// raw string literal syntax found in: https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=msvc-160
const std::string expectedPrint = R"(Compare student1 to student1: Same
Compare student1 to student2: Different
Print list 0:
Name: Jim
Status: Graduated
Name: Ivan
Status: Enrolled
Print list 1:
Name: Jim
Status: Graduated
Print list 2:
Name: Billy
Status: Non-Attending
Name: Jim
Status: Graduated
Print list 3:
Empty.
)";

int main(){
	std::stringstream testOutput;

	StudentType student1, student2, student3;
	DateType student1DOB, student2DOB,student3DOB;

	student1DOB.Initialize(7, 15, 1978);
	student2DOB.Initialize(6, 23, 1980);
	student3DOB.Initialize(3, 4, 1945);

	student1.Initialize("Ivan", student1DOB, StudentStatus::ENROLLED);
	student2.Initialize("Jim", student2DOB, StudentStatus::GRADUATED);
	student3.Initialize("Billy", student3DOB, StudentStatus::NON_ATTENDING);

	LinkedListUnsortedType classList;

	classList.PutItem(student1);
	classList.PutItem(student2);

	testOutput << "Compare student1 to student1: " << compareRelationToString(student1.ComparedTo(student1)) << endl;
	testOutput << "Compare student1 to student2: " << compareRelationToString(student1.ComparedTo(student2)) << endl;

	testOutput << "Print list 0:\n";
	classList.ResetList();  //reset the current position to NULL
	classList.Print(testOutput);
	testOutput << "Print list 1:\n";
	classList.DeleteItem(student1);
	classList.ResetList();  //this must be reset before printing the list everytime
	classList.Print(testOutput);
	testOutput << "Print list 2:\n";
	classList.PutItem(student3);
	classList.ResetList();  //this must be reset before printing the list everytime
	classList.Print(testOutput);
	testOutput << "Print list 3:\n";
	classList.DeleteItem(student2);
	classList.DeleteItem(student3);
	classList.ResetList();
	classList.Print(testOutput);

	assert(testOutput.str() == expectedPrint);
	std::cout << "Test Finished Successfully." << std::endl;
}

/**
 * StudentType Header.
 *
 * See new Print function and add'l enum->string functions.
 *
 * Written by Benjamin Liden
 * 		for Prof. I. Temesvari's CS240 course.
 * 		Lab 2.
 * 		2/13/2021
 */
#include "StudentType.h"
#include <iostream>

using namespace std;

std::string studentStatusToString(const StudentStatus &status) {
	switch (status) {
	case StudentStatus::NON_ATTENDING:
		return "Non-Attending";
	case StudentStatus::ENROLLED:
		return "Enrolled";
	case StudentStatus::GRADUATED:
		return "Graduated";
	default:
		// this should really be an error
		return "";
	}
}

std::string compareRelationToString(const CompareRelation& relation) {
	switch (relation) {
	case CompareRelation::SAME:
		return "Same";
	case CompareRelation::DIFFERENT:
		return "Different";
	default:
		// this should really be an error
		return "";
	}
}

void StudentType::Initialize(string newName, DateType newBirthdate,
		StudentStatus newStatus) {
	status = newStatus;
	PersonType::Initialize(newName, newBirthdate);
}

StudentStatus StudentType::GetStatus() const {
	return status;
}

CompareRelation StudentType::ComparedTo(StudentType &someStudent) {
	//Compare two StudentType objects based on their status here.
	return status == someStudent.GetStatus()
			? CompareRelation::SAME
			: CompareRelation::DIFFERENT;
}

DateType StudentType::BirthdateIs() {
	return PersonType::BirthdateIs(); //notice the use of the scope for PersonType here.
}

void StudentType::Print(std::ostream &out) {
	PersonType::Print(out);   //use the Print function of PersonType here.
	out << "Status: " << studentStatusToString(status) << endl;
}

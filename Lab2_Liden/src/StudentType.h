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
#pragma once

#include <iostream>

#include "PersonType.h"

enum class StudentStatus {
	NON_ATTENDING, ENROLLED, GRADUATED
};

std::string studentStatusToString(const StudentStatus& status);

enum class CompareRelation {
	SAME, DIFFERENT
};

std::string compareRelationToString(const CompareRelation& relation);

class StudentType: public PersonType {

public:
	StudentStatus GetStatus() const;
	void Initialize(string, DateType, StudentStatus);
	CompareRelation ComparedTo(StudentType &someStudent);
	DateType BirthdateIs();
	void Print(std::ostream &out = std::cout);

private:
	StudentStatus status;
};

typedef StudentType ItemType; //notice this is used to allow ItemType to be identified as a StudentType
//The only way around this line of code above would be to use a template, 
//but the author doesn't get into it until Chapter 6...

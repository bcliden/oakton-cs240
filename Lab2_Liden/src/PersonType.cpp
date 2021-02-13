/*
 * PersonType.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: igt88
 */

#include "PersonType.h"
#include <iostream>

void PersonType::Initialize(string n, DateType dob) {
	name = n;
	birthdate = dob;
}

string PersonType::NameIs() {
	return name;
}

DateType PersonType::BirthdateIs() {
	return birthdate;
}

RelationType PersonType::ComparedTo(PersonType &somePerson) {
	return birthdate.ComparedTo(somePerson.birthdate);
}

void PersonType::Print(std::ostream &out) {
	out << "Name: " << name << endl;
}


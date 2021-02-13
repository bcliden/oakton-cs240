#pragma once

#include <string>
#include <iostream>
#include "DateType.h"

class PersonType {
public:
	void Initialize(std::string, DateType);
	std::string NameIs();
	RelationType ComparedTo(PersonType &somePerson);
	DateType BirthdateIs();
	void Print(std::ostream &out = std::cout);

private:
	std::string name;
	DateType birthdate;
};

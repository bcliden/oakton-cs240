#ifndef PERSONTYPE_H
#define PERSONTYPE_H
#include <string>
using namespace std;
#include "DateType.h"
class PersonType
{
public:
  void Initialize(string, DateType);
  string NameIs();
  RelationType ComparedTo(PersonType& somePerson);
  DateType BirthdateIs();
  void Print();
private:
  string name;
  DateType birthdate;
};

#endif

#ifndef STUDENTTYPE_H
#define STUDENTTYPE_H
#include "PersonType.h"
enum StudentStatus {NON_ATTENDING, ENROLLED, GRADUATED};   //notice the enumeration here for status
class StudentType : public PersonType
{
public: 
  int GetStatus() const;
  void Initialize(string, DateType, int);
  RelationType ComparedTo(StudentType& someStudent);
  DateType BirthdateIs();
  void Print();
private:
  int status;
};
typedef StudentType ItemType;  //notice this is used to allow ItemType to be identified as a StudentType
//The only way around this line of code above would be to use a template, 
//but the author doesn't get into it until Chapter 6...
#endif

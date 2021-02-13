// File DateType.cpp  contains the implementation of class DateType
#include "DateType.h"
#include <fstream>
#include <iostream>
using namespace std;

// Nmber of days in each month
static int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30,
                            31, 30, 31};	

// Nmaes of the months
static string conversionTable[] = {"Error", "January", "February", 
    "March", "April", "May", "June", "July", "August", "September",
    "October", "November", "December"};

void DateType::Initialize
     (int newMonth, int newDay, int newYear)
// Post: If newMonth, newDay and newYear represent a valid date,
//       year is set to newYear;
//       month is set to newMonth;
//       day is set to newDay;
//       otherwise a string exception is thrown, stating the
//       first incorrect parameter.
{
  if (newMonth < 1 || newMonth > 12)
     throw string("Month is invalid");
  else if (newDay < 1 || newDay > daysInMonth[newMonth])
     throw string("Day is invalid");
  else if (newYear < 1583)
     throw string("Year is invalid");
  year = newYear;
  month = newMonth;
  day = newDay;
}
int DateType::GetMonth() const
// Accessor function for data member month.
{
   return month;
}

string DateType::GetMonthAsString() const
// Returns data member as a string
{
  return conversionTable[month];
}

int DateType::GetYear() const
// Accessor function for data member year.
{
  return year;
}

int DateType::GetDay() const
// Accessor function for data member day.
{
  return day;
}

RelationType DateType::ComparedTo(DateType aDate) const
// Pre:  Self and aDate have been initialized.
// Post: Function value = LESS, if self comes before aDate.
//                      = EQUAL, if self is the same as aDate.
//                      = GREATER, if self comes after aDate.
{
  if (year < aDate.year)
    return LESS;
  else if (year > aDate.year)
    return GREATER;
  else if (month < aDate.month)
    return LESS;
  else if (month > aDate.month)
    return GREATER;
  else if (day < aDate.day)
    return LESS;
  else if (day > aDate.day)
    return  GREATER;
  else return EQUAL;
}

DateType DateType::Adjust(int daysAway) const
// Pre:  Self has been initialized
// Post: Function value = newDate daysAway from self
{
  int newDay = day + daysAway;
  int newMonth = month;
  int newYear = year;
  bool finished = false;
  int daysInThisMonth;
  DateType returnDate;
  while (! finished)
  {
    daysInThisMonth = daysInMonth[newMonth];
	 if (newMonth == 2)
	   if (((newYear % 4 == 0) && !(newYear % 100 == 0)) 
          || (newYear % 400 == 0))
	     daysInThisMonth++;
	 if (newDay <= daysInThisMonth)
	   finished = true;
	 else
	 {
	   newDay = newDay - daysInThisMonth;
	   newMonth = (newMonth % 12) + 1;
	   if (newMonth == 1)
	     newYear++;
	 }
  }
  
  returnDate.Initialize(newMonth, newDay, newYear);
  return returnDate;
}

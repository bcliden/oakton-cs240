/**
 * Original FractionType implementation.
 */

#include <iostream>

#include "frac.h"

void FractionType::Initialize(int numerator, int denominator)
// Function: Initialize the fraction
// Pre:  None
// Post: numerator is stored in num; denominator is stored in 
//       denom
		{
	num = numerator;
	denom = denominator;
}

int FractionType::NumeratorIs()
// Function: Returns the value of the numerator
// Pre:  Fraction has been initialized
// Post: numerator is returned
{
	return num;
}

int FractionType::DenominatorIs()
// Function: Returns the value of the denominator
// Pre:  Reaction has been initialized 
// Post: denominator is returned
{
	return denom;
}

bool FractionType::IsZero()
// Function: Determines if fraction is zero
// Pre:  Fraction has been initialized
// Post: Returns true if numerator is zero
{
	return (num == 0);
}

bool FractionType::IsNotProper()
// Function: Determines if fraction is a proper fraction
// Pre:  Fraction has been initialized
// Post: Returns true if num is greater than or equal to denom
{
	return (num >= denom);
}

int FractionType::ConvertToProper()
// Function: Converts the fraction to a whole number and a 
//       fractional part
// Pre:  Fraction has been initialized, is in reduced form, and
//       is not a proper fraction
// Post: Returns num divided by denom
//       num is original num % denom; denom is not changed
{
	int result;
	result = num / denom;
	num = num % denom;
	return result;
}

/**
 * BELOW: Additions by Benjamin Liden for
 * 	Prof. Temesvari's CS240 Ex. 1
 *
 * 	- Operator Overloads
 * 		- (+)
 * 		- (-)
 * 		- (*)
 * 		- (/)
 * 	- Extra Credit
 * 		- reduce
 * 		- print
 */

FractionType FractionType::operator+(const FractionType &addend) {
	FractionType newFrac;
	int newNumerator;
	int newDenominator;

	if (denom == addend.denom) {
		// denominators are the same, proceed normally
		newNumerator = num + addend.num;
		newDenominator = denom;
	} else {
		// otherwise we need to multiply into the same form
		newNumerator = (num * addend.denom) + (addend.num * denom);
		newDenominator = denom * addend.denom;
	}

	newFrac.Initialize(newNumerator, newDenominator);
	return newFrac;
}

FractionType FractionType::operator-(const FractionType &minuend) {
	FractionType newFrac;
	int newNumerator;
	int newDenominator;

	if (denom == minuend.denom) {
		// denominators are the same, proceed normally
		newNumerator = num - minuend.num;
		newDenominator = denom;
	} else {
		// otherwise we need to multiply into the same form
		newNumerator = (num * minuend.denom) - (minuend.num * denom);
		newDenominator = denom * minuend.denom;
	}

	newFrac.Initialize(newNumerator, newDenominator);
	return newFrac;
}

FractionType FractionType::operator*(const FractionType &multiplier) {
	FractionType newFrac;
	int newNumerator = num * multiplier.num;
	int newDenominator = denom * multiplier.denom;

	newFrac.Initialize(newNumerator, newDenominator);
	return newFrac;
}

FractionType FractionType::operator/(const FractionType &divisor) {
	// invert the divisor
	FractionType inverse;
	inverse.Initialize(divisor.denom, divisor.num);

	// then reuse our multiplication operator
	return this->operator*(inverse);
}

/*
 * Extra Credit functions:
 * - reduce
 * - print
 */

/**
 * Extracted Greatest Common Divisor code from below.
 * 
 * Returns the GCD of two provided ints.
 * 
 * Example: gcd(462, 1071) = 21
 *
 * Algorithm translated from: https://en.wikipedia.org/wiki/Euclidean_algorithm#Procedure
 */
int gcd(int p, int q) {
	// 1. find which number is larger
	int larger, smaller;
	if (p > q) {
		larger = p;
		smaller = q;
	} else {
		larger = q;
		smaller = p;
	}

	// 2. take remainder of large / small
	int remainder = larger % smaller;

	// 3. Determine next iteration
	if (remainder == 0) {
		// indicates we found the GCD
		return smaller;
	} else {
		// or, keep looking recursively
		return gcd(smaller, remainder);
	}
}

/**
 * Reduce the given fraction into it's smallest form.
 *
 * Algorithm translated from: https://en.wikipedia.org/wiki/Euclidean_algorithm
 * Lambda syntax below from: https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp
 */
void FractionType::reduce() {

	// get GCD
	int greatestDivisor = gcd(num, denom);

	// write these into this FractionType instance, dividing by GCD
	num = num / greatestDivisor;
	denom = denom / greatestDivisor;
}

/**
 * Print the fraction into cout.
 *
 * If
 */
void FractionType::print() {
	if (num % denom == 0) { // if denom evenly divides num
		int wholeNumber = num / denom;
		std::cout << wholeNumber << std::endl;
		return;
	}
	// otherwise, print the fraction
	std::cout << num << '/' << denom << std::endl;
}


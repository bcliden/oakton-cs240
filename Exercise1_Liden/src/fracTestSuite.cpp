//============================================================================
// Name        : fracTestSuite.cpp
// Author      : Benjamin Liden
// Description : Test Suite for the included FractionType operator overloads
//			   : 	and add'l member functions.
// Course	   : CS240
// Professor   : I. Temesvari
//============================================================================

#include <iostream>
#include <assert.h>

#include "frac.h"


/**
 * Adds 3/4 + 3/5 = 27/20
 */
void testAddition() {
	FractionType frac1;
	frac1.Initialize(3, 4);

	FractionType frac2;
	frac2.Initialize(3, 5);

	FractionType result = frac1 + frac2;

	assert(result.NumeratorIs() == 27);
	assert(result.DenominatorIs() == 20);
}

/**
 * Subtracts 3/4 - 3/5 = 3/20
 */
void testSubtraction() {
	FractionType frac1;
	frac1.Initialize(3, 4);

	FractionType frac2;
	frac2.Initialize(3, 5);

	FractionType result = frac1 - frac2;

	assert(result.NumeratorIs() == 3);
	assert(result.DenominatorIs() == 20);
}

/**
 * Multiply 1/3 * 3/4 = 3/12
 */
void testMultiplication(){
	FractionType frac1;
	frac1.Initialize(1, 3);

	FractionType frac2;
	frac2.Initialize(3, 4);

	FractionType result = frac1 * frac2;

	assert(result.NumeratorIs() == 3);
	assert(result.DenominatorIs() == 12);
}

/**
 * Divides 1/2 / 3/4 = 4/6
 */
void testDivision(){
	FractionType frac1;
	frac1.Initialize(1, 2);

	FractionType frac2;
	frac2.Initialize(3, 4);

	FractionType result = frac1 / frac2;

	assert(result.NumeratorIs() == 4);
	assert(result.DenominatorIs() == 6);
}

/**
 * Reduce fractions. 462 / 1071 = 22 / 51
 */
void testReduce(){
	FractionType frac;
	frac.Initialize(462, 1071);

	frac.reduce(); // reduces original Fraction

	assert(frac.NumeratorIs() == 22);
	assert(frac.DenominatorIs() == 51);
}

/**
 * Print a fraction to stdout.
 * Whole numbers will print if fraction divides cleanly.
 * 
 * 12/27 prints 12/27
 * 24/12 prints 2
 */
// void testPrint(){
// 	FractionType frac;
// 	frac.Initialize(12, 27);
// 	frac.print(); // print 12/27

// 	FractionType frac1;
// 	frac1.Initialize(24, 12);
// 	frac1.print(); // print 2
// }

int main() {
	testAddition();
	testSubtraction();
	testMultiplication();
	testDivision();
	testReduce();
//	testPrint(); // not terribly helpful on its own

	std::cout << "Tests ran successfully." << std::endl;
	return 0;
}

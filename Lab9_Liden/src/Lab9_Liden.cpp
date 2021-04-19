//============================================================================
// Name        : Lab 9
// Author      : Benjamin Liden
// Date        : April 18, 2021
// Professor   : Ivan Temesvari
// Course 	   : CS240 C++ Data Structures
//============================================================================

#include "HashType.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cctype>

enum class probing {
	Linear, Quadratic
};

constexpr int keyNumbers[] = { 33, 37, 39, 41 };
const std::string files[] = { "hashText1.txt", "hashText2.txt", "hashText3.txt",
		"hashText4.txt" };

void buildHashTable(std::ifstream &inFile, HashType<std::string> &hashTable,
		probing type);
void testIntHashTable();
void testStringHashTable(std::string, int, probing, std::ostream& = std::cout);
void testTextWithPrimes();

int main() {
	std::cout << "Tests are running. Please be patient..." << std::endl;
//	testIntHashTable();
//	testStringHashTable("hashText1.txt", keyNumbers[0], probing::Linear);
	testTextWithPrimes();
	std::cout << "Tests completed without error." << std::endl;
}

// this is the original test from the int-specific HashType from CSC240_Hashing_Integers.zip
void testIntHashTable() {
	HashType<int> myHashTableDivision(11);
	myHashTableDivision.Insert(45);
	myHashTableDivision.Insert(34);
	myHashTableDivision.Insert(12);
	myHashTableDivision.Insert(2);
	myHashTableDivision.Insert(3);
	myHashTableDivision.Insert(56);
	myHashTableDivision.Insert(78);
	myHashTableDivision.Insert(99);
	myHashTableDivision.Insert(22);
	myHashTableDivision.Insert(54);
	std::cout << myHashTableDivision;
	std::cout << "Number of collisions: " << myHashTableDivision.GetCollisions()
			<< std::endl << std::endl;

	HashType<int> myHashTableRandom(11);
	myHashTableRandom.Insert(45);
	myHashTableRandom.Insert(34);
	myHashTableRandom.Insert(12);
	myHashTableRandom.Insert(2);
	myHashTableRandom.Insert(3);
	myHashTableRandom.Insert(56);
	myHashTableRandom.Insert(78);
	myHashTableRandom.Insert(99);
	myHashTableRandom.Insert(22);
	myHashTableRandom.Insert(54);
	std::cout << myHashTableRandom;
	std::cout << "Number of collisions: " << myHashTableRandom.GetCollisions()
			<< std::endl << std::endl;
}

// This is the provided function to build hash tables from the files.
void buildHashTable(std::ifstream &inFile, HashType<std::string> &hashTable,
		probing type) {
	std::string word;
	if (inFile.is_open()) {
		while (inFile >> word) {
			// This for loop was taken from:
			// https://www.geeksforgeeks.org/removing-punctuations-given-string/
			for (int i = 0, len = word.size(); i < len; i++) {
				// check whether parsing character is punctuation or not
				if (std::ispunct(word[i])) {
					word.erase(i--, 1);
					len = word.size();
				}
			}

			if (type == probing::Linear)
				hashTable.InsertItemLinear(word);
			else
				hashTable.InsertItemQuadratic(word);
		}
	}
}

// test a single text file, given a filename and some params
void testStringHashTable(std::string filename, int factor, probing probe,
		std::ostream &out) {
	// build file name
	std::stringstream ss;
	ss << "src\\text\\" << filename;

	// open stream
	std::ifstream stream { ss.str() };

	if (!stream.fail()) {
		// first word is the needed size of array
		unsigned int size;
		stream >> size;

		// build table
		out << "Testing " << filename << " with size=" << size << ", a="
				<< factor << std::endl;
		HashType<std::string> hashTable { size, factor };

		// stream table into hash using chosen probing type
		buildHashTable(stream, hashTable, probe);
		out << "Number of collisions with a=" << factor << ": "
				<< hashTable.GetCollisions() << std::endl << std::endl;
	} else {
		out << "An error occurred with " << filename
				<< " while testing factor a=" << factor << std::endl;
	}
}

// test all files with all key numbers, print results to file
void testTextWithPrimes() {
	std::stringstream log;
	log
			<< "=======================> [ Testing Linear ] <========================"
			<< std::endl << std::endl;
	for (auto file : files) {
		log << "--------> ( " << file << " ) <--------" << std::endl;
		for (auto num : keyNumbers) {
			testStringHashTable(file, num, probing::Linear, log);
		}
	}

	log
			<< "======================> [ Testing Quadratic ] <======================="
			<< std::endl << std::endl;
	for (auto file : files) {
		log << "--------> ( " << file << " ) <--------" << std::endl;
		for (auto num : keyNumbers) {
			testStringHashTable(file, num, probing::Quadratic, log);
		}
	}

	// print
	std::ofstream out { "./previousTestRun.txt" };
	out << log.rdbuf();
}

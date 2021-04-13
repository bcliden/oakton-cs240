//============================================================================
// Name        : Lab 8
// Author      : Benjamin Liden
// Date        : April 9, 2021
// Professor   : Ivan Temesvari
// Course	   : CS240 C++ Data Structures
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <cassert>

#include "PQType.h"
#include "Simulator.h"

// TEST DECLARATIONS
void testPriorityQueue();
void testJobOperators();
void testRandomInt();
void testSimulatorOnce();
void testSimulator1kTimes();

int main() {
//	testPriorityQueue();
//	testJob();
//	testRandomInt();
//	testSimulatorOnce();
	testSimulator1kTimes();
	std::cout << "Tests finished successfully." << std::endl;
	return 0;
}

/*
 * The original Priority Queue test provided.
 */
void testPriorityQueue() {
	std::stringstream ss;
	const std::string output = R"(10
5
4
)";
	PQType<int> queue(50);
	queue.Enqueue(5);
	queue.Enqueue(10);
	queue.Enqueue(4);
	ss << queue;
	assert(ss.str() == output);
}

/*
 * Tests for the operator overloads in Job
 */
void testJobOperators() {
	Job j { 20, 20 };
	Job j2 { 0, 100 };
	Job j3 { -19, 5 };
	Job j4 { 0, 90 };

	// less than operator
	assert(j3 < j2);
	assert(j2 < j);
	assert(j3 < j2);
	assert(j2 < j4);

	// less than or equal to
	assert(j3 <= j2);
	assert(j2 <= j);
	assert(j3 <= j2);
	assert(j2 <= j4); // priority is same, but it is shorter

	// greater than
	assert(j2 > j3);
	assert(j > j2);
	assert(j2 > j3);
	assert(j4 > j2); // same priority, different length

	// equality
	Job j5 { 20, 20 };
	assert(j5 == j);
}

/*
 * Testbed for RandomInt class.
 */
void testRandomInt() {
	RandomInt r { -19, 20 }; // priority values, for instance
	for (int i = 0; i < 50; i++) {
		std::cout << r.getNumber() << std::endl;
	}
	// i guess there isn't much to test really...
}

/*
 * Run simulator a single time.
 */
void testSimulatorOnce() {
	simulator::simulatorMetrics metrics = simulator::runSimulator();
	std::cout << metrics << std::endl;
}

/*
 * Run simulator one thousand times.
 */
void testSimulator1kTimes() {
	constexpr int thousand = 1'000;
	simulator::simulatorMetrics suite[thousand];
	for (int i = 0; i < thousand; i++) {
		suite[i] = simulator::runSimulator();
	}

	int completed = 0;
	simulator::simulatorMetrics avgMetrics;
	for (int i = 0; i < thousand; i++) {
		simulator::simulatorMetrics &m = suite[i];
		m.printReport(std::cout);

		if (m.jobsCompleted == 50) {
			completed++;
		}
		avgMetrics.timeTaken += m.timeTaken;
		avgMetrics.jobsCompleted += m.jobsCompleted;
		avgMetrics.avgHeapSize += m.avgHeapSize;
	}
	avgMetrics.timeTaken /= thousand;
	avgMetrics.jobsCompleted /= thousand;
	avgMetrics.avgHeapSize /= thousand;

	std::cout << "| AVERAGE METRICS |" << std::endl;
	std::cout << avgMetrics << std::endl;

	std::cout << "Completed simulations: " << completed << std::endl;
	std::cout << "Incomplete simulations: " << (thousand - completed) << std::endl;
}

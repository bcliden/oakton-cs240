#pragma once

//============================================================================
// Name        : Lab 8
// Author      : Benjamin Liden
// Date        : April 9, 2021
// Professor   : Ivan Temesvari
// Course	   : CS240 C++ Data Structures
//============================================================================

/*
 * Code for the simulator and the metrics collected by it
 */

#include <iostream>
#include <exception> // for std::exception

#include "PQType.h"
#include "Job.h"
#include "RandomInt.h"
#include "Scheduler.h"

namespace simulator {

class simulatorMetrics {
public:
	int timeTaken = 0;
	int jobsCompleted = 0;
	int avgHeapSize = 0;
	friend std::ostream& operator<<(std::ostream&, const simulatorMetrics&);
	std::ostream& printReport(std::ostream& = std::cout);
};

std::ostream& operator<<(std::ostream &out, const simulatorMetrics &m) {
	out << "Time taken: " << m.timeTaken << " cycles" << "\n"
			<< "Jobs Completed: " << m.jobsCompleted << "\n"
			<< "avgHeapSize: " << m.avgHeapSize
			<< std::endl;
	return out;
}

std::ostream& simulatorMetrics::printReport(std::ostream& out) {
	out << "Average number of jobs in the heap per cycle: " << avgHeapSize
			<< std::endl;
	if (jobsCompleted >= 50) {
		out << "The scheduler completed all 50 jobs." << std::endl;
		out << "It took " << timeTaken << " cycles to complete them."
				<< std::endl;
	} else {
		out << "The scheduler did not complete all 50 jobs." << std::endl;
		out << "Jobs processed: " << jobsCompleted << std::endl;
	}
	return out;
}

simulatorMetrics runSimulator() {
	// metrics to be collected
	simulatorMetrics m;

	// RNG for various parts of the sim
	RandomInt priorityGen { -19, 20 };
	RandomInt lengthGen { 1, 100 };
	RandomInt coinFlipGen { 0, 1 };

	constexpr int maxNumberOfJobs = 50;
	Scheduler<Job> scheduler { maxNumberOfJobs };

	/*
	 * Start with no jobs queued (just a single 0 length one).
	 * We could start with a single job in the PQ, but I have not implemented that.
	 * There is a chance a job will be generated on the first cycle (#2700).
	 */

	constexpr int timeAllotted = 2700; // nanoseconds
	int numberOfJobsGenerated = 0; // used to
	int heapSum = 0; // this will later be used to calculate the avg size.
	Job job { }; // will hold the active job

	while (m.timeTaken < timeAllotted && m.jobsCompleted < 50) {
		try {
			// one cycle
			scheduler.getCurrentJob(job);

			// if job is empty, try to get another job
			if (job.getLength() <= 0) {
				if (scheduler.getNumJobs() <= 0) {
					// do nothing this time. no currentJob and no queued jobs
				} else {
					// grab top item and set it as new current job
					scheduler.removeJob(job);
					scheduler.setCurrentJob(job);
				}
			} else {
				// do work
				job.decrementLength();

				// if job is finished, remove it and add set new one
				if (job.getLength() <= 0) {
					m.jobsCompleted += 1;

					// remove another job and set it as current if one exists
					if (!scheduler.IsEmpty()) {
						scheduler.removeJob(job);
						scheduler.setCurrentJob(job);
					}
				}

				// don't forget to save your work
				scheduler.setCurrentJob(job);
			}

			// if we haven't generated 50 jobs yet, the scheduler isn't full,
			// and if time is a multiple of 20 and you get heads flipping a coin...
			if (numberOfJobsGenerated < maxNumberOfJobs
					&& !scheduler.IsFull()
					&& m.timeTaken % 20 == 0
					&& (bool) coinFlipGen.getNumber() /* this bool cast is unneeded, i think */) {
				// add a random job
				Job j { priorityGen.getNumber(), lengthGen.getNumber() };
				scheduler.addJob(j);
				numberOfJobsGenerated += 1;
			}

			// update metrics
			m.timeTaken += 1;
			heapSum += scheduler.getNumJobs();

			// what follows is some iffy error handling, though it should not be needed now
		} catch (const FullPQ &e) {
			std::cout << "something bad happened" << std::endl;
		} catch (const EmptyPQ &e) {
			std::cout << "something bad happened" << std::endl;
		} catch (const std::exception &e) {
			std::cout << "something bad happened" << std::endl;
		} catch (...) {
			std::cout << "something bad happened" << std::endl;
		}
	}

	// finally calculate the average size of the heap
	m.avgHeapSize = heapSum / m.timeTaken;
	return m;
}
}

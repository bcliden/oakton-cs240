#pragma once

//============================================================================
// Name        : Lab 8
// Author      : Benjamin Liden
// Date        : April 9, 2021
// Professor   : Ivan Temesvari
// Course	   : CS240 C++ Data Structures
//============================================================================

/*
 * The Job is a simple task with priority (-19 -> 20) and length (0 -> 100).
 */

#include <iostream>

class Job {
public:
	Job();
	Job(int, int);
	// shouldn't need copy constructor/assignment overload if all we have are primitive members

	int getLength() const;
	void decrementLength();
	int getPriority() const;

	friend std::ostream& operator<<(std::ostream &out, const Job &j);
	bool operator<(Job otherJob);
	bool operator>(Job otherJob);
	bool operator==(Job otherJob);
	bool operator<=(Job otherJob);
private:
	int priority;
	int length;
};

Job::Job() :
		priority(-19), length(0) {
	// this is a zero-value, non-prority item
}

Job::Job(int priority, int length) :
		priority(priority), length(length) {
}

int Job::getLength() const {
	return length;
}

void Job::decrementLength() {
	// this cannot go below zero
	if (length > 0) {
		length -= 1;
	}
}

int Job::getPriority() const {
	return priority;
}

std::ostream& operator<<(std::ostream &out, const Job &j) {
	out << "Job{ priority: " << j.getPriority() << ", length: " << j.getLength()
			<< " }" << std::endl;
	return out;
}

bool Job::operator<(Job otherJob) {
	bool priorityIsSame = this->priority == otherJob.getPriority();
	bool priorityLessThan = this->priority < otherJob.getPriority();
	bool lengthGreaterThan = this->length > otherJob.getLength();

	if (priorityIsSame) {
		return lengthGreaterThan; // shorter jobs rank higher
	}
	return priorityLessThan;
}

bool Job::operator>(Job otherJob) {
	bool priorityIsSame = this->priority == otherJob.getPriority();
	bool priorityGreaterThan = this->priority > otherJob.getPriority();
	bool lengthLessThan = this->length < otherJob.getLength();

	if (priorityIsSame) {
		return lengthLessThan; // shorter jobs rank higher
	}
	return priorityGreaterThan;
}

bool Job::operator==(Job otherJob) {
	bool priorityIsSame = this->priority == otherJob.getPriority();
	bool lengthIsSame = this->priority == otherJob.getPriority();

	if (priorityIsSame) {
		return lengthIsSame;
	}
	return priorityIsSame;
}

bool Job::operator<=(Job otherJob) {
	return *this < otherJob || *this == otherJob;
}


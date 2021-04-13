#pragma once

//============================================================================
// Name        : Lab 8
// Author      : Benjamin Liden
// Date        : April 9, 2021
// Professor   : Ivan Temesvari
// Course	   : CS240 C++ Data Structures
//============================================================================

/*
 * The Scheduler manages a heap,
 * 		providing a "current job" slot
 * 		and access to the top of the heap.
 */

#include "PQType.h"

template<class T>
class Scheduler: public PQType<T> {
public:
	Scheduler(int);
	int getNumJobs() const;
	void getCurrentJob(T&);
	void setCurrentJob(T&);
	void addJob(T&);
	void removeJob(T&);
private:
	int numJobs;
	T currentJob;
};

template<class T>
Scheduler<T>::Scheduler(int size) :
		PQType<T>(size), numJobs(0), currentJob() {
}

template<class T>
int Scheduler<T>::getNumJobs() const {
	return numJobs;
}
template<class T>
void Scheduler<T>::getCurrentJob(T& job) {
	job = currentJob;
}

template<class T>
void Scheduler<T>::setCurrentJob(T& job) {
	currentJob = job;
}

template<class T>
void Scheduler<T>::addJob(T& job) {
	this->Enqueue(job);
	numJobs++;
}

template<class T>
void Scheduler<T>::removeJob(T &j) {
	this->Dequeue(j);
	numJobs--;
}

#pragma once


//
//  Thread_Sort
//
//  Created by Charles Weems on 1/12/16.
//  Copyright © 2016 Charles Weems. All rights reserved.
//

// Altered to be flexible with concurrent threading by Benjamin Carl Liden on 4/25/21

#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <vector>

const int MAX_THREADS = std::thread::hardware_concurrency() == 0
	? 2 // need fallback if MAX_THREADS isn't supported
	: std::thread::hardware_concurrency();

const int MAX_ITEMS = 20000000;
int numbers[MAX_ITEMS];
int temp[MAX_ITEMS];
int chunk;

template<class ItemType>
void Merge(ItemType values[], int leftFirst, int leftLast, int rightFirst,
		int rightLast, ItemType tempArray[])
// Post: values[leftFirst]..values[leftLast] and
//       values[rightFirst]..values[rightLast] have been merged.
//       values[leftFirst]..values[rightLast] are now sorted.
		{
	int index = leftFirst;
	int saveFirst = leftFirst;
	while ((leftFirst <= leftLast) && (rightFirst <= rightLast)) {
		if (values[leftFirst] < values[rightFirst]) {

			tempArray[index] = values[leftFirst];
			leftFirst++;
		} else {
			tempArray[index] = values[rightFirst];
			rightFirst++;
		}
		index++;
	}
	while (leftFirst <= leftLast)
	// Copy remaining items from left half.
	{
		tempArray[index] = values[leftFirst];
		leftFirst++;
		index++;
	}
	while (rightFirst <= rightLast)
	// Copy remaining items from right half.
	{
		tempArray[index] = values[rightFirst];
		rightFirst++;
		index++;
	}
	for (index = saveFirst; index <= rightLast; index++)
		values[index] = tempArray[index];
}

template<class ItemType>
void SerialMergeSort(ItemType values[], int first, int last,
		ItemType tempArray[])
// Post: The elements in values are sorted by key.
		{
	if (first < last) {
		int middle = (first + last) / 2;
		SerialMergeSort<ItemType>(values, first, middle, tempArray);
		SerialMergeSort<ItemType>(values, middle + 1, last, tempArray);
		Merge<ItemType>(values, first, middle, middle + 1, last, tempArray);
	}
}

template<class ItemType>
void ParallelMergeSort(ItemType values[], int first, int last,
		ItemType tempArray[], int chunkSize)
// Post: The elements in values are sorted by key.
		{
	if (first < last) { // if out of range, do nothing
		if (last - first > chunkSize) // If enough work left, launch more threads
				{

			// threads to be loaded
			std::thread local_threads[MAX_THREADS];

			// the size of current work to be split up
			int workSize = last - first;

			// put work in threads
			for (int i = 0; i < MAX_THREADS; i++) {
				int begin = first + ((i * workSize)/MAX_THREADS);
				int end = first + (((i+1) * workSize)/MAX_THREADS);
				local_threads[i] = std::thread (
					ParallelMergeSort<ItemType>,
					values,
					begin,
					end,
					tempArray,
					chunkSize
				);
			}

			// join threads
			for (int i = 0; i < MAX_THREADS; i++) {
				local_threads[i].join();
			}

			// merge all pieces from threads
			for (int i = 1; i < MAX_THREADS; i++){
				// beginning at 1, merge the previous with the current
				int leftStart =((i-1) * MAX_ITEMS)/MAX_THREADS;
				int leftEnd = ((i) * MAX_ITEMS)/MAX_THREADS;
				int rightStart = ((i * MAX_ITEMS)/MAX_THREADS) + 1;
				int rightEnd = ((i+1) * MAX_ITEMS)/MAX_THREADS;
				Merge<ItemType>(
						values,
						leftStart,
						leftEnd,
						rightStart,
						rightEnd,
						tempArray);
			}
		} else // Otherwise finish sorting locally
		{
			int middle = (first + last) / 2;
			SerialMergeSort<ItemType>(values, first, middle, tempArray);
			SerialMergeSort<ItemType>(values, middle + 1, last, tempArray);
			Merge<ItemType>(values, first, middle, middle + 1, last, tempArray);
		}
	}
}

void gather_and_run_merge(std::istream &in = std::cin, std::ostream &out =
		std::cout) {
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;

	// Initialize the array with random integers
	for (int index = 0; index < MAX_ITEMS; index++) {
		numbers[index] = rand() % 1000000000;
	}

	// modified to check for chunk size at or below items divided by threads. BCL 4/26
	do {
		out << "Enter chunk size (<= " << (MAX_ITEMS / MAX_THREADS) << "): ";
		in >> chunk;
	} while (chunk > (MAX_ITEMS / MAX_THREADS));

	out << "Beginning sort with " << MAX_THREADS << " threads." << std::endl;

	start = std::chrono::system_clock::now();           // Record start time

	ParallelMergeSort<int>(numbers, 0, MAX_ITEMS - 1, temp, chunk); // Run the sort

	end = std::chrono::system_clock::now();             // Record end time

	std::chrono::duration<float> elapsed = end - start; // Calculate and report time
	out << "Done sorting\n";
	out << "Execution time in seconds = " << elapsed.count() << "\n";
}

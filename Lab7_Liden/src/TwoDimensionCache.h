#pragma once

//============================================================================
// Name        : Lab 7
// Author      : Benjamin Liden
// Date        : Mar 29, 2021
// Professor   : Ivan Temesvari
// Course	   : CS240 Data Structures
//============================================================================

#include <cstring>

template<class T>
class TwoDimensionCache {
	public:
		TwoDimensionCache(int size, T default_value) :
				size(size), default_value(default_value) {
			// this is an annoying way to initialize the dynamic array
			this->data = new T*[size];
			for (int i = 0; i < size; i++) {
				this->data[i] = new T[size];
			}
			this->makeEmpty();
		}

		~TwoDimensionCache() {
			// I can't figure out how to get Valgrind on my windows computer
			// 		(or if it's possible?)
			// This appears to delete correctly though.
			for (int i = 0; i < size; i++) {
				delete[] this->data[i];
			}
			delete[] this->data;
		}

		/**
		 * Set all values in array to the default "non-answer" value.
		 *
		 * Something like memset or std::array.fill is likely more efficient.
		 */
		void makeEmpty() {
			for (auto i = 0; i < size; i++) {
				for (auto j = 0; j < size; j++) {
					this->data[i][j] = default_value;
				}
			}
		}

		// store an answer into the cache
		void store(int row, int col, T item) {
			this->data[row][col] = item;
		}

		// is there an answer for this position in the cache?
		bool has(int row, int col) {
			T result = this->data[row][col];
			return result != default_value;
		}

		// get answer from cell
		T get(int row, int col) {
			return this->data[row][col];
		}

	private:
		T **data; // a pointer to pointer to T
		int size;
		T default_value;
};

//============================================================================
// Name        : Lab7_Liden.cpp
// Author      : Benjamin Liden
// Version     :
// Copyright   : n/a
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <optional>
#include <vector>

template<class T, int size>
class Memoized {
public:
	Memoized()
//	: data(new T[size][size])
	{
		// this is an annoying way to initialize the dynamic array
		this->data = new T* [size];
		for (int i = 0; i < size; i++){
			this->data[i] = new T*[size];
		}
		this->makeEmpty();
	}

	~Memoized(){
		delete[] this->data;
	}

	void makeEmpty() {
		for (auto i = 0; i < size; i++) {
			for (auto j = 0; j < size; j++) {
				*this->data[i][j] = nullptr;
			}
		}
	}

	void storeAnswer(int row, int col, T item) {
		*this->data[row][col] = item;
	}

	bool hasAnswer(int row, int col) {
		T result = this->data[row][col];
		return result == nullptr;
	}

	T getAnswer(int row, int col) {
		return *this->data[row][col];
	}

private:
	T **data;
};

template <class M, int n>
int NumPaths(int row, int col, M m) {
	if (row == n || col == n) {
		return 1;
	}
	return NumPaths<M, n>(row + 1, col, m) + NumPaths<M, n>(row, col + 1, m);
}

int const max_len = 6;

int main() {
	Memoized<int, max_len> m {};
	int res = NumPaths<Memoized<int, max_len>, max_len>(1, 1, m);
	std::cout << res << std::endl;
	return 0;
}


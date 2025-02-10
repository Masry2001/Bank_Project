#pragma once

#include <iostream>
using namespace std;

template <class T>
class clsDynamicArray
{
private:

	int _Size = 0;
	T* _TempArray;

public:

	T* originalArray;
	
	clsDynamicArray(int size = 0) {

		if (size < 0) {
			size = 0;
		}

		_Size = size;

		originalArray = new T[_Size];

	}

	~clsDynamicArray() {
		delete[] originalArray;
	}

	bool SetItem(int index, T value) {

		if (index >= _Size || index < 0) {
			return false;
		}

		//*(originalArray + index) = value;
		originalArray[index] = value;

		return true;

	}

	bool IsEmpty() {
		return (_Size == 0);
	}

	int Size() {
		return _Size;
	}

	void printList() {

		for (int i = 0; i < _Size; i++) {
			cout << originalArray[i] << " ";
		}

		cout << endl;
	}

	void Resize(int newSize) {

		if (newSize < 0) {
			newSize = 0;
		}

		_TempArray = new T[newSize];

		if (newSize < _Size) {
			_Size = newSize;
		}

		for (int i = 0; i < _Size; i++) {

			_TempArray[i] = originalArray[i];

		}

		_Size = newSize;

		delete[] originalArray;

		originalArray = _TempArray;

	}

	T GetItem(int index) {

			return originalArray[index];
	}

	void Reverse() {

		int halfSize = floor(_Size / 2);
		// first element index = 0
		// last element index = _Size - 1;

		for (int i = 0; i < halfSize; i++) {


			int temp = originalArray[i];
			originalArray[i] = originalArray[_Size - 1 - i];
			originalArray[_Size - 1 - i] = temp;

		}

	}

	void Clear() {

		_Size = 0;
		_TempArray = new T[0];

		delete[] originalArray;
		originalArray = _TempArray;

	}

	bool DeleteItemAt(int index) {
		// Check if the index is valid
		if (index >= _Size || index < 0) {
			return false;
		}

		_Size--;

		_TempArray = new T[_Size];

		// Copy elements before the index
		for (int i = 0; i < index; i++) {
			_TempArray[i] = originalArray[i];
		}

		// Copy elements after the index
		for (int i = index + 1; i < _Size + 1; i++) {

			_TempArray[i - 1] = originalArray[i];
		}

		// Free memory allocated for the original array
		delete[] originalArray;

		// Assign the new array to the original array pointer
		originalArray = _TempArray;

		return true;
	}

	bool DeleteFirstItem() {
		return DeleteItemAt(0);
	}

	bool DeleteLastItem() {
		return DeleteItemAt(_Size - 1);
	}

	int Find(T value) {
		// take value and return index

		for (int i = 0; i < _Size; i++) {
			if (value == originalArray[i]) {
				return i;
			}
		}
		return -1;

	}

	bool DeleteItem(T value) {
		// delete item by value
		int index = Find(value);
		return DeleteItemAt(index);

	}

	bool InsertAt(int index, T value) {

		// Check if the index is valid
		if (index > _Size || index < 0) {
			return false;
		}

		_Size++;

		_TempArray = new T[_Size];

		// Copy elements before the index
		for (int i = 0; i < index; i++) {
			_TempArray[i] = originalArray[i];
		}

		_TempArray[index] = value;

		// Copy elements after the index
		for (int i = index; i < _Size - 1 ; i++) {
			_TempArray[i + 1] = originalArray[i];
		}


		// Free memory allocated for the original array
		delete[] originalArray;

		// Assign the new array to the original array pointer
		originalArray = _TempArray;

		return true;

	}

	bool InsertAtBegining(T value) {

		return InsertAt(0, value);

	}	
	
	bool InsertAtEnd (T value) {

		return InsertAt(_Size, value);

	}

	bool InsertBefore(int index, T value) {

		if (index < 1) {

			return InsertAt(0, value);
		}
		else {

			return InsertAt(index - 1, value);
		}

	}	
	
	bool InsertAfter(int index, T value) {

		if (index >= _Size) {

			return InsertAt(index - 1, value);

		}
		else {

			return InsertAt(index + 1, value);
		}


	}


};


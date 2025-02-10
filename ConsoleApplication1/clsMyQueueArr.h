#pragma once

#include <iostream>
#include "clsDynamicArray.h"

using namespace std;

template <class T>
class clsMyQueueArr
{

protected:

	clsDynamicArray <T> myDynamicArr;

public:

	void push(T item)
	{
		myDynamicArr.InsertAtEnd(item);
	}


	void pop()
	{
		myDynamicArr.DeleteFirstItem();
	}

	void Print()
	{
		myDynamicArr.printList();
	}

	int Size()
	{
		return myDynamicArr.Size();
	}

	bool IsEmpty()
	{
		return myDynamicArr.IsEmpty();
	}

	T front()
	{
		return myDynamicArr.GetItem(0);
	}

	T back()
	{
		return myDynamicArr.GetItem(Size() - 1);
	}

	T GetItem(int index)
	{
		return myDynamicArr.GetItem(index);
	}

	void Reverse() {
		myDynamicArr.Reverse();
	}

	void UpdateItem(int index, T newValue) {

		myDynamicArr.SetItem(index, newValue);

	}

	void InsertAfter(int index, T value) {
		myDynamicArr.InsertAfter(index, value);
	}

	void InsertAtFront(T value) {
		myDynamicArr.InsertAtBegining(value);
	}

	void InsertAtBack(T value) {
		myDynamicArr.InsertAtEnd(value);
	}

	void clear() {
		myDynamicArr.Clear();
	}


};


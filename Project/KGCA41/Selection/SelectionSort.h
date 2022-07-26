#pragma once

#include "Array.h"

class SelectionSort : public Custom::Array
{
public:
	SelectionSort(int length) : Array(length) { }
	void Sort();
};


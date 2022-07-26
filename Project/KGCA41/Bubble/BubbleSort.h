#pragma once

#include "Array.h"

class BubbleSort : public Custom::Array
{
public:
	BubbleSort(int length) : Array(length) { }
	void Sort();
};


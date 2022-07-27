#pragma once

#include "Array.h"

class QuickSort : public Custom::Array
{
private:
	void Quick(int start, int end);
public:
	QuickSort(int length) : Array(length) { }
	void Sort();
};


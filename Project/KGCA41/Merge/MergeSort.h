#pragma once

#include "Array.h"

class MergeSort : public Custom::Array
{
private:
	void Merge(int start, int end);

public:
	MergeSort(int length) : Array(length) { }
	void Sort();
};


#pragma once

#include "Array.h"

class InsertSort : public Custom::Array
{
public:
	InsertSort(int length) : Array(length) { }
	void Sort();
};


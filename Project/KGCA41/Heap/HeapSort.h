#pragma once

#include "Array.h"

class HeapSort : public Custom::Array
{
public:
	HeapSort(int length) : Array(length) { }
	virtual void Push(int val) override;
	void Sort();
};


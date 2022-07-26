#pragma once

#include "Array.h"

class ShellSort : public Custom::Array
{
private:
	int GetGap(int val);

public:
	ShellSort(int length) : Array(length) { }
	void Sort();
};


#include "CustomMath.h"
#include <math.h>

float CustomFloat::S_EPSILON = 0.001f;

CustomFloat CustomFloat::operator==(const CustomFloat& f)
{
	return fabs(f._val - _val) <= S_EPSILON;
}

#include "Volume1.h"
#include "HCCalculator.h"

void SSB::Volume1::Rotate(HMatrix44 rotate)
{
	_matrix = _matrix * rotate;
}

void SSB::Volume1::Rotate(Quaternion quaternion)
{
	HMatrix44 rot{ (Float33)quaternion.GetRotateMatrix(), Float3{ 0, 0, 0} };
	_matrix = _matrix * rot;
}

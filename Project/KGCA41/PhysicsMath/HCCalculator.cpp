#include "HCCalculator.h"

namespace SSB
{
	Vector2 SSB::operator*(Vector2 vec, Matrix22 mat)
	{
		return Vector2(vec.Dot(mat.GetColumn(0)), vec.Dot(mat.GetColumn(1)));
	}

	Vector3 SSB::operator*(Vector3 vec, Matrix33 mat)
	{
		return Vector3(vec.Dot(mat.GetColumn(0)), vec.Dot(mat.GetColumn(1)), vec.Dot(mat.GetColumn(2)));
	}

	HVector3 SSB::operator*(HVector3 vec, HMatrix33 mat)
	{
		return HVector3(vec.Dot(mat.GetColumn(0)), vec.Dot(mat.GetColumn(1)), vec.Dot(mat.GetColumn(2)));
	}

	HVector4 SSB::operator*(HVector4 vec, HMatrix44 mat)
	{
		return HVector4(vec.Dot(mat.GetColumn(0)), vec.Dot(mat.GetColumn(1)), vec.Dot(mat.GetColumn(2)), vec.Dot(mat.GetColumn(3)));
	}
}

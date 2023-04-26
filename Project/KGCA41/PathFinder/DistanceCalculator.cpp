#include "DistanceCalculator.h"

namespace SSB
{
	NavigationUnit EuclidCalculator::Cost(NavigationNode from, NavigationNode to)
	{
		int width = to.X - from.X;
		int height = to.Y - from.Y;
		return sqrt(width * width + height * height) * 10;
	}
}

#pragma once

#include "NavigationResource.h"

namespace SSB
{
	class DistanceCostCalculator
	{
	public:
		virtual NavigationUnit Cost(NavigationNode from, NavigationNode to) = 0;
	};

	class EuclidCalculator : public DistanceCostCalculator
	{
	public:
		NavigationUnit Cost(NavigationNode from, NavigationNode to) override;
	};
}

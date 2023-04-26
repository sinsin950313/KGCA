#pragma once

#include "NavigationResource.h"
#include "DistanceCalculator.h"
#include <vector>

namespace SSB
{
	class PathFinder
	{
	protected:
		NavigationGraph* _graph;
		EuclidCalculator _calculator;

	public:
		PathFinder(NavigationGraph* graph);
		~PathFinder();

	public:
		virtual std::vector<NavigationNode> Find(NavigationNode from, NavigationNode to) = 0;
	};
}

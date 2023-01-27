#pragma once

#include "NavigationResource.h"
#include <vector>

namespace SSB
{
	class PathFinder
	{
	protected:
		NavigationGraph* _graph;

	public:
		PathFinder(NavigationGraph* graph);
		~PathFinder();

	public:
		virtual std::vector<NavigationNode> Find(NavigationNode from, NavigationNode to) = 0;
	};
}

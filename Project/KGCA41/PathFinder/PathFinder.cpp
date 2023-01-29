#include "PathFinder.h"

namespace SSB
{
	PathFinder::PathFinder(NavigationGraph* graph) : _graph(graph)
	{
	}
	PathFinder::~PathFinder()
	{
		_graph = nullptr;
	}
}
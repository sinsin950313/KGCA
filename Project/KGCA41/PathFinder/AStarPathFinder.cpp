#include "AStarPathFinder.h"

namespace SSB
{
	const AStarPathFinder::AStarValueUnit AStarPathFinder::AStarValueUnitMaxValue = -1;

	AStarPathFinder::AStarPathFinder(NavigationGraph* graph) : PathFinder(graph)
	{
	}
	std::vector<NavigationNode> AStarPathFinder::Find(NavigationNode from, NavigationNode to)
	{
		std::vector<NavigationNode> ret;

		if (_graph->IsAble(from) && _graph->IsAble(to))
		{
			_openSet.Clear();
			_closeSet.Clear();

			_openSet.Add(from);
			while (!_openSet.Empty())
			{
				doSomething!!
			}
		}

		return ret;
	}
	AStarPathFinder::AStarNode AStarPathFinder::AStarNodeClass::Get()
	{
		return _node;
	}
	AStarPathFinder::AStarNodeSet::AStarNodeSet(int length)
	{
		_array = (AStarNode*)malloc(sizeof(AStarNode) * length);
	}
	AStarPathFinder::AStarNodeSet::~AStarNodeSet()
	{
		free(_array);
	}
	void AStarPathFinder::AStarNodeSet::Clear()
	{
		_count = 0;
	}
}

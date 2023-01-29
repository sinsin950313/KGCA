#include "NavigationResource.h"
#include "AStarPathFinder.h"
#include <iostream>

int main()
{
	SSB::ArrayBaseNavigationGraph graph({ 0, 0 }, { 4, 7 });
	graph.AddDisableNode({ 1, 1 });
	graph.AddDisableNode({ 2, 1 });
	graph.AddDisableNode({ 3, 1 });
	graph.AddDisableNode({ 3, 2 });
	graph.AddDisableNode({ 3, 3 });
	graph.AddDisableNode({ 3, 4 });
	graph.AddDisableNode({ 2, 4 });
	graph.AddDisableNode({ 1, 4 });
	graph.AddDisableNode({ 0, 4 });

	SSB::AStarPathFinder pathFinder(&graph);
	auto ret = pathFinder.Find({ 2, 2 }, { 2, 6 });
	for (auto pos : ret)
	{
		std::cout << pos.X << ", " << pos.Y << std::endl;
	}
}
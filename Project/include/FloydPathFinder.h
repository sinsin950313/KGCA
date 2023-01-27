#pragma once

#include "PathFinder.h"

namespace SSB
{
	class FloydPathFinder : public PathFinder
	{
	public:
		std::vector<NavigationNode> Find(NavigationNode from, NavigationNode to) override;
	};
}

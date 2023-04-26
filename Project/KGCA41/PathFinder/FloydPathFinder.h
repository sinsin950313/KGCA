#pragma once

#include "PathFinder.h"

namespace SSB
{
	class FloydPathFinder : public PathFinder
	{
		typedef unsigned long long FloydValueUnit;
		static const FloydValueUnit FloydValueUnitMaxValue;

	private:
		struct FloydNode
		{
			FloydValueUnit Weight = FloydValueUnitMaxValue;
			int Child;
		};

	private:
		FloydNode* _array;
		int _length;

	public:
		FloydPathFinder(NavigationGraph* graph);
		~FloydPathFinder();

	private:
		FloydNode* GetNode(NavigationNode from, NavigationNode to);

	public:
		std::vector<NavigationNode> Find(NavigationNode from, NavigationNode to) override;
	};
}

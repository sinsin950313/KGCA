#pragma once

#include "PathFinder.h"
#include "DistanceCalculator.h"

namespace SSB
{
	class AStarPathFinder : public PathFinder
	{
	private:
		typedef unsigned long long AStarValueUnit;
		static const AStarValueUnit AStarValueUnitMaxValue;

		class AStarNode
		{
		private:
			DistanceCostCalculator* _calculator;
			NavigationNode _node;
			AStarValueUnit _gValue = AStarValueUnitMaxValue;
			AStarValueUnit _hValue = AStarValueUnitMaxValue;
			NavigationNode _parent;

		public:
			void Link(AStarNode parent);
			AStarValueUnit GetF();
			AStarValueUnit GetG();
			AStarValueUnit GetH();
			NavigationNode GetParent();
		};

		class AStarNodeSet
		{
		public:
			void Add(AStarNode node);
			void Remove(AStarNode node);
			AStarNode Get();
			bool Contains(AStarNode node);
		};

	private:
		AStarNodeSet _openSet;
		std::set<NavigationNode> _closeSet;

	public:
		AStarPathFinder(NavigationNode leftTop, NavigationNode rightBottom);

	public:
		std::vector<NavigationNode> Find(NavigationNode from, NavigationNode to) override;
	};
}

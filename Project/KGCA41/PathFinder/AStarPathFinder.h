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

		struct AStarNode
		{
			NavigationNode Node;
			AStarValueUnit GValue = AStarValueUnitMaxValue;
			AStarValueUnit HValue = AStarValueUnitMaxValue;
			NavigationNode Parent;
		};

		class AStarNodeClass
		{
		private:
			AStarNode _node;

		public:
			void Link(DistanceCostCalculator& calculator, AStarNode parent);

		public:
			AStarNode Get();
		};

		class AStarNodeSet
		{
		private:
			AStarNode* _array;
			int _count;

		public:
			AStarNodeSet(int length);
			~AStarNodeSet();

		public:
			void Add(NavigationNode node);
			void Remove(NavigationNode node);
			bool Contains(NavigationNode node);
			AStarNode Top();
			void Clear();
			bool Empty();
		};

	private:
		EuclidCalculator _calculator;
		AStarNodeSet _openSet;
		AStarNodeSet _closeSet;

	public:
		AStarPathFinder(NavigationGraph* graph);

	public:
		std::vector<NavigationNode> Find(NavigationNode from, NavigationNode to) override;
	};
}

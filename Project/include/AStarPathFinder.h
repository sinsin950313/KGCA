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
			AStarNodeClass(NavigationNode node);
			AStarNodeClass(AStarNode node);

		public:
			void Link(DistanceCostCalculator& calculator, AStarNode parent, AStarNode destination);
			AStarNode Get();
			AStarValueUnit FValue();

		public:
			bool operator!=(const AStarNodeClass& node) const;
			bool operator==(const AStarNodeClass& node) const;
			operator NavigationNode();
			operator AStarPathFinder::AStarNode();
		};

		class AStarNodeSet
		{
		private:
			AStarNode* _array;
			AStarNode* _tmp;
			int _count;

		public:
			AStarNodeSet(int length);
			~AStarNodeSet();

		public:
			void Add(AStarNode node);
			void Remove(AStarNode node);
			bool Contains(AStarNode node);
			AStarNode Get();
			AStarNode Find(AStarNode node);
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

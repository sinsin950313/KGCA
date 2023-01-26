#pragma once

#include <vector>
#include <set>

namespace SSB
{
	typedef int NavigationUnit;

	struct NavigationNode
	{
		NavigationUnit X;
		NavigationUnit Y;
	};

	class PathFinder
	{
	private:
		class NavigationNodeClass
		{
		private:
			NavigationNode _node;

		public:
			NavigationNodeClass(NavigationNode node);

		public:
			bool operator<(NavigationNodeClass& r);
		};

		NavigationNode** _grid;
		NavigationUnit _width;
		NavigationUnit _height;
		std::set<NavigationNodeClass> _disableNode;

	public:
		PathFinder(NavigationNode leftTop, NavigationNode rightBottom);
		~PathFinder();

	public:
		void AddDisableNode(NavigationNode node);
		void RemoveDisableNode(NavigationNode node);
		bool IsDisable(NavigationNode node);

	public:
		virtual std::vector<NavigationNode> Find(NavigationNode from, NavigationNode to) = 0;
	};
}

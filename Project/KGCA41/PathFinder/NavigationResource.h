#pragma once

#include <set>
#include <vector>

namespace SSB
{
	typedef int NavigationUnit;

	struct NavigationNode
	{
		NavigationUnit X;
		NavigationUnit Y;
	};

	class NavigationGraph
	{
	protected:
		class NavigationNodeClass
		{
		private:
			NavigationNode _node;

		public:
			NavigationNodeClass(NavigationNode node);

		public:
			bool operator<(const NavigationNodeClass& r) const;
			NavigationNode operator()();

		public:
			NavigationNode Get();
		};

	private:
		NavigationNode _zero;
		NavigationUnit _width;
		NavigationUnit _height;
		std::set<NavigationNodeClass> _disableNode;

	public:
		NavigationGraph(NavigationNode leftTop, NavigationNode rightBottom);

	public:
		void AddDisableNode(NavigationNode node);
		void RemoveDisableNode(NavigationNode node);
		bool IsDisable(NavigationNode node);

	public:
		NavigationNode GetZero();
		NavigationUnit GetWidth();
		NavigationUnit GetHeight();

	public:
		virtual std::vector<NavigationNode> GetConnectedNode(NavigationNode node) = 0;
		virtual bool IsAble(NavigationNode node) = 0;
	};

	class ArrayBaseNavigationGraph : public NavigationGraph
	{
	private:
		NavigationNode** _grid;

	public:
		ArrayBaseNavigationGraph(NavigationNode leftTop, NavigationNode rightBottom);
		~ArrayBaseNavigationGraph();

	private:
		NavigationUnit GetArrayWidth();
		NavigationUnit GetArrayHeight();
		int GetIndexX(NavigationNode node);
		int GetIndexY(NavigationNode node);
		bool IsIn(NavigationNode node);

	public:
		std::vector<NavigationNode> GetConnectedNode(NavigationNode node) override;
	};

	class ListBaseNavigationGraph : public NavigationGraph
	{
	public:
		ListBaseNavigationGraph(NavigationNode leftTop, NavigationNode rightBottom);

	public:
		std::vector<NavigationNode> GetConnectedNode(NavigationNode node) override;
	};
}

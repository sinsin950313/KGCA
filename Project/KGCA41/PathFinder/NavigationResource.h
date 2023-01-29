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
		virtual int GetSize() = 0;
		virtual NavigationNode GetNode(int index) = 0;
		virtual int GetIndex(NavigationNode node) = 0;
	};

	//	(0, 0) (0, 1) (0, 2) (0, 3) (0, 4) (0, 5) (0, 6)
	//	(1, 0) (1, 1) (1, 2) (1, 3) (1, 4) (1, 5) (1, 6)
	//	(2, 0) (2, 1) (2, 2) (2, 3) (2, 4) (2, 5) (2, 6)
	//	(3, 0) (3, 1) (3, 2) (3, 3) (3, 4) (3, 5) (3, 6)
	//	(4, 0) (4, 1) (4, 2) (4, 3) (4, 4) (4, 5) (4, 6)
	class ArrayBaseNavigationGraph : public NavigationGraph
	{
	private:
		NavigationNode* _grid;

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
		bool IsAble(NavigationNode node) override;
		int GetSize() override;
		NavigationNode GetNode(int index) override;
		int GetIndex(NavigationNode node) override;
	};

	class ListBaseNavigationGraph : public NavigationGraph
	{
	public:
		ListBaseNavigationGraph(NavigationNode leftTop, NavigationNode rightBottom);

	public:
		std::vector<NavigationNode> GetConnectedNode(NavigationNode node) override;
		bool IsAble(NavigationNode node) override;
	};
}

#include "NavigationResource.h"

namespace SSB
{
	NavigationGraph::NavigationNodeClass::NavigationNodeClass(NavigationNode node) : _node(node)
	{
	}
	bool NavigationGraph::NavigationNodeClass::operator<(const NavigationNodeClass& r) const
	{
		if (_node.Y < r._node.Y)
		{
			return true;
		}
		else if (r._node.Y < _node.Y)
		{
			return false;
		}
		else
		{
			if (_node.X < r._node.X)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	NavigationNode NavigationGraph::NavigationNodeClass::Get()
	{
		return _node;
	}
	NavigationNode NavigationGraph::NavigationNodeClass::operator()()
	{
		return _node;
	}
	NavigationGraph::NavigationGraph(NavigationNode leftTop, NavigationNode rightBottom) : _zero(leftTop)
	{
		_width = abs(rightBottom.Y - leftTop.Y);
		_height = abs(rightBottom.X - leftTop.X);
	}
	void NavigationGraph::AddDisableNode(NavigationNode node)
	{
		_disableNode.insert(node);
	}
	void NavigationGraph::RemoveDisableNode(NavigationNode node)
	{
		_disableNode.erase(node);
	}
	bool NavigationGraph::IsDisable(NavigationNode node)
	{
		return _disableNode.contains(node);
	}
	NavigationNode NavigationGraph::GetZero()
	{
		return _zero;
	}
	NavigationUnit NavigationGraph::GetWidth()
	{
		return _width;
	}
	NavigationUnit NavigationGraph::GetHeight()
	{
		return _height;
	}
	ArrayBaseNavigationGraph::ArrayBaseNavigationGraph(NavigationNode leftTop, NavigationNode rightBottom) : NavigationGraph(leftTop, rightBottom)
	{
		_grid = (NavigationNode*)malloc(sizeof(NavigationNode) * GetArrayWidth() * GetArrayHeight());
		for (int row = 0; row < GetArrayHeight(); ++row)
		{
			for (int col = 0; col < GetArrayWidth(); ++col)
			{
				_grid[row * GetArrayWidth() + col] = {GetZero().X + row, GetZero().Y + col};
			}
		}
	}
	ArrayBaseNavigationGraph::~ArrayBaseNavigationGraph()
	{
		free(_grid);
	}
	NavigationUnit ArrayBaseNavigationGraph::GetArrayWidth()
	{
		return GetWidth() + 1;
	}
	NavigationUnit ArrayBaseNavigationGraph::GetArrayHeight()
	{
		return GetHeight() + 1;
	}
	int ArrayBaseNavigationGraph::GetIndexX(NavigationNode node)
	{
		return node.X - GetZero().X;
	}
	int ArrayBaseNavigationGraph::GetIndexY(NavigationNode node)
	{
		return node.Y - GetZero().Y;
	}
	bool ArrayBaseNavigationGraph::IsIn(NavigationNode node)
	{
		int col = GetIndexY(node);
		int row = GetIndexX(node);
		if (row < 0 || GetArrayHeight() < row || col < 0 || GetArrayWidth() < col)
		{
			return false;
		}
		return true;
	}
	std::vector<NavigationNode> ArrayBaseNavigationGraph::GetConnectedNode(NavigationNode node)
	{
		std::vector<NavigationNode> ret;
		if (IsIn(node) && !IsDisable(node))
		{
			int dx[]{ -1, -1, +1, +1, -1, +1, 0, 0 };
			int dy[]{ -1, +1, -1, +1, 0, 0, -1, +1 };
			for (int i = 0; i < 8; ++i)
			{
				int indexX = GetIndexX(node) + dx[i];
				int indexY = GetIndexY(node) + dy[i];
				if (!(indexX < 0 || GetHeight() < indexX || indexY < 0 || GetWidth() < indexY))
				{
					NavigationNode connected = _grid[indexX * GetArrayWidth() + indexY];
					if (IsIn(connected) && !IsDisable(connected))
					{
						ret.push_back(connected);
					}
				}
			}
		}
		return ret;
	}
	bool ArrayBaseNavigationGraph::IsAble(NavigationNode node)
	{
		return IsIn(node) && !IsDisable(node);
	}
	int ArrayBaseNavigationGraph::GetSize()
	{
		return GetArrayWidth() * GetArrayHeight();
	}
}
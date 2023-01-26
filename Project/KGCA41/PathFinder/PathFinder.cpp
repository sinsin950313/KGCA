#include "PathFinder.h"

namespace SSB
{
	PathFinder::NavigationNodeClass::NavigationNodeClass(NavigationNode node) : _node(node)
	{
	}
	bool PathFinder::NavigationNodeClass::operator<(NavigationNodeClass& r)
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
	PathFinder::PathFinder(NavigationNode leftTop, NavigationNode rightBottom)
	{
		_width = rightBottom.X - leftTop.X + 3;
		_height = rightBottom.Y - leftTop.Y + 3;

		_grid = (NavigationNode**)malloc(sizeof(NavigationNode) * _width * _height);

		for (int i = 0; i < _width; ++i)
		{
			for (int j = 0; i < _height; ++j)
			{
				_grid[i][j] = { x, y };
			}
		}
	}
	PathFinder::~PathFinder()
	{
		free(_grid);
	}
	void PathFinder::AddDisableNode(NavigationNode node)
	{
		_disableNode.insert(node);
	}
	void PathFinder::RemoveDisableNode(NavigationNode node)
	{
		_disableNode.erase(node);
	}
	bool PathFinder::IsDisable(NavigationNode node)
	{
		return _disableNode.contains(node);
	}
}
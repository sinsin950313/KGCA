#include "AStarPathFinder.h"
#include <stack>

namespace SSB
{
	const AStarPathFinder::AStarValueUnit AStarPathFinder::AStarValueUnitMaxValue = -1;

	AStarPathFinder::AStarPathFinder(NavigationGraph* graph) : PathFinder(graph), _openSet(graph->GetSize()), _closeSet(graph->GetSize())
	{
	}
	std::vector<NavigationNode> AStarPathFinder::Find(NavigationNode from, NavigationNode to)
	{
		std::vector<NavigationNode> ret;

		if (_graph->IsAble(from) && _graph->IsAble(to))
		{
			_openSet.Clear();
			_closeSet.Clear();

			AStarNodeClass source(from);
			_openSet.Add(source);
			while (!_openSet.Empty())
			{
				AStarNodeClass current = _openSet.Get();
				_openSet.Remove(current);
				_closeSet.Add(current);

				if (current == AStarNodeClass(to))
				{
					break;
				}

				std::vector<NavigationNode> connectedList = _graph->GetConnectedNode(current);
				for (auto iter : connectedList)
				{
					if (!_closeSet.Contains(AStarNodeClass(iter)))
					{
						AStarNode connectedNode;
						if (_openSet.Contains(AStarNode(iter)))
						{
							connectedNode = _openSet.Find(AStarNodeClass(iter));
							_openSet.Remove(AStarNodeClass(iter));
						}
						else
						{
							connectedNode = AStarNode(iter);
						}
						AStarNodeClass connectedNodeClass(connectedNode);
						connectedNodeClass.Link(_calculator, current, AStarNodeClass(to));
						_openSet.Add(connectedNodeClass);
					}
				}
			}

			std::stack<AStarNode> reverse;
			if (_closeSet.Contains(AStarNodeClass(to)))
			{
				AStarNode node = _closeSet.Find(AStarNodeClass(to));
				do
				{
					reverse.push(node);
					node = _closeSet.Find(AStarNodeClass(node.Parent));
				} while (AStarNodeClass(node) != AStarNodeClass(from));
			}

			ret.push_back(from);
			while (!reverse.empty())
			{
				AStarNodeClass node(reverse.top());
				reverse.pop();

				ret.push_back(node);
			}
		}

		return ret;
	}
	AStarPathFinder::AStarNodeClass::AStarNodeClass(NavigationNode node)
	{
		_node.Node = node;
	}
	AStarPathFinder::AStarNodeClass::AStarNodeClass(AStarNode node) : _node(node)
	{
	}
	void AStarPathFinder::AStarNodeClass::Link(DistanceCostCalculator& calculator, AStarNode parent, AStarNode destination)
	{
		int newGVAlue = calculator.Cost(AStarNodeClass(parent), AStarNodeClass(this->_node)) + parent.GValue;
		if (newGVAlue < _node.GValue)
		{
			_node.GValue = newGVAlue;
			_node.Parent = AStarNodeClass(parent);
		}
		_node.HValue = calculator.Cost(AStarNodeClass(this->_node), AStarNodeClass(destination));
	}
	AStarPathFinder::AStarNode AStarPathFinder::AStarNodeClass::Get()
	{
		return _node;
	}
	AStarPathFinder::AStarValueUnit AStarPathFinder::AStarNodeClass::FValue()
	{
		return _node.GValue + _node.HValue;
	}
	bool AStarPathFinder::AStarNodeClass::operator!=(const AStarNodeClass& node) const
	{
		return !operator==(node);
	}
	bool AStarPathFinder::AStarNodeClass::operator==(const AStarNodeClass& node) const
	{
		return _node.Node.X == node._node.Node.X && _node.Node.Y == node._node.Node.Y;
	}
	AStarPathFinder::AStarNodeClass::operator NavigationNode()
	{
		return _node.Node;
	}
	AStarPathFinder::AStarNodeClass::operator AStarPathFinder::AStarNode()
	{
		return _node;
	}
	AStarPathFinder::AStarNodeSet::AStarNodeSet(int length) : _count(0)
	{
		_array = (AStarNode*)malloc(sizeof(AStarNode) * length);
		_tmp = (AStarNode*)malloc(sizeof(AStarNode) * length);
	}
	AStarPathFinder::AStarNodeSet::~AStarNodeSet()
	{
		free(_array);
		free(_tmp);
	}
	void AStarPathFinder::AStarNodeSet::Add(AStarNode node)
	{
		int index = _count;
		_array[index] = node;

		int parentIndex = index / 2;
		int currentIndex = index;
		while(currentIndex != 0)
		{
			if (currentIndex % 2 == 0)
			{
				parentIndex = (currentIndex - 1) / 2;
			}
			AStarNodeClass parent(_array[parentIndex]);
			AStarNodeClass current(_array[currentIndex]);
			AStarNode tmp;

			if (current.FValue() < parent.FValue())
			{
				tmp = _array[parentIndex];
				_array[parentIndex] = _array[currentIndex];
				_array[currentIndex] = tmp;
			}
			currentIndex = currentIndex >> 1;
		}

		++_count;
	}
	void AStarPathFinder::AStarNodeSet::Remove(AStarNode node)
	{
		int index = 0;
		for (int i = 0; i < _count; ++i)
		{
			if (AStarNodeClass(_array[i]) != AStarNodeClass(node))
			{
				memcpy(_tmp + index, _array + i, sizeof(AStarNode));
				++index;
			}
		}

		_count = 0;
		for (int i = 0; i < index; ++i)
		{
			Add(_tmp[i]);
		}
	}
	bool AStarPathFinder::AStarNodeSet::Contains(AStarNode node)
	{
		for (int i = 0; i < _count; ++i)
		{
			if (AStarNodeClass(_array[i]) == AStarNodeClass(node))
			{
				return true;
			}
		}
		return false;
	}
	AStarPathFinder::AStarNode AStarPathFinder::AStarNodeSet::Get()
	{
		return _array[0];
	}
	AStarPathFinder::AStarNode AStarPathFinder::AStarNodeSet::Find(AStarNode node)
	{
		AStarNode ret;
		for (int i = 0; i < _count; ++i)
		{
			if (AStarNodeClass(_array[i]) == AStarNodeClass(node))
			{
				ret = _array[i];
				break;
			}
		}
		return ret;
	}
	void AStarPathFinder::AStarNodeSet::Clear()
	{
		_count = 0;
	}
	bool AStarPathFinder::AStarNodeSet::Empty()
	{
		return _count == 0;
	}
}

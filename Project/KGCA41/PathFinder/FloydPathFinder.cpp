#include "FloydPathFinder.h"

namespace SSB
{
	const FloydPathFinder::FloydValueUnit FloydPathFinder::FloydValueUnitMaxValue = -1;

	FloydPathFinder::FloydPathFinder(NavigationGraph* graph) : PathFinder(graph)
	{
		_length = _graph->GetSize();
		_array = (FloydNode*)malloc(sizeof(FloydPathFinder::FloydNode) * _length * _length);

		for (int i = 0; i < _length; ++i)
		{
			for (int j = 0; j < _length; ++j)
			{
				FloydNode* node = GetNode(_graph->GetNode(i), _graph->GetNode(j));
				node->Weight = FloydValueUnitMaxValue >> 1;
				node->Child = -1;
			}
		}

		for (int i = 0; i < _length; ++i)
		{
			auto connectedNodeList = _graph->GetConnectedNode(_graph->GetNode(i));
			for (auto connectedNode : connectedNodeList)
			{
				int j = _graph->GetIndex(connectedNode);
				FloydNode* node = GetNode(_graph->GetNode(i), _graph->GetNode(j));
				node->Weight = _calculator.Cost(_graph->GetNode(i), _graph->GetNode(j));
				node->Child = j;
			}
		}

		for (int k = 0; k < _length; ++k)
		{
			for (int i = 0; i < _length; ++i)
			{
				for (int j = 0; j < _length; ++j)
				{
					FloydPathFinder::FloydNode* nodeIK = GetNode(_graph->GetNode(i), _graph->GetNode(k));
					FloydNode* nodeKJ = GetNode(_graph->GetNode(k), _graph->GetNode(j));
					FloydNode* nodeIJ = GetNode(_graph->GetNode(i), _graph->GetNode(j));
					if (nodeIK->Weight + nodeKJ->Weight < nodeIJ->Weight)
					{
						nodeIJ->Weight = nodeIK->Weight + nodeKJ->Weight;
						nodeIJ->Child = nodeIK->Child;
					}
				}
			}
		}
	}
	FloydPathFinder::~FloydPathFinder()
	{
		free(_array);
	}
	FloydPathFinder::FloydNode* FloydPathFinder::GetNode(NavigationNode from, NavigationNode to)
	{
		return &_array[_graph->GetIndex(from) * _length + _graph->GetIndex(to)];
	}
	std::vector<NavigationNode> FloydPathFinder::Find(NavigationNode from, NavigationNode to)
	{
		std::vector<NavigationNode> ret;

		NavigationNode node(from);
		while (!((node.X == to.X) && (node.Y == to.Y)))
		{
			ret.push_back(node);
			FloydNode* current = GetNode(node, to);
			node = _graph->GetNode(current->Child);
		}
		ret.push_back(to);
		return ret;
	}
}

#include "QuadTree.h"

Node::Node(int xStart, int yStart, int width, int height, int depth, int maxDepth)
	: _xStart(xStart), _yStart(yStart), _width(width), _height(height), _depth(depth)
{
	if (depth + 1 < maxDepth)
	{
		width = width >> 1;
		height = height >> 1;

		_child[0] = new Node(xStart, yStart, width, height, depth + 1, maxDepth);
		_child[1] = new Node(xStart + width, yStart, width, height, depth + 1, maxDepth);
		_child[2] = new Node(xStart, yStart + height, width, height, depth + 1, maxDepth);
		_child[3] = new Node(xStart + width, yStart + height, width, height, depth + 1, maxDepth);
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			_child[i] = nullptr;
		}
	}
}

Node::~Node()
{
	for (int i = 0; i < 4; ++i)
	{
		delete _child[i];
	}
}

bool Node::IsIn(Object* object)
{
	if (GetXStart() <= object->GetXStart())
	{
		if (object->GetXEnd() <= GetXEnd())
		{
			if (GetYStart() <= object->GetYStart())
			{
				if (object->GetYEnd() <= GetYEnd())
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Node::AddObject(Object* object)
{
	if (IsIn(object))
	{
		bool success = false;
		for (int i = 0; i < 4; ++i)
		{
			if (_child[i] != nullptr && _child[i]->IsIn(object))
			{
				_child[i]->AddObject(object);
				success = true;
			}
		}

		if (!success)
		{
			_objects.push_back(object);
		}
	}
}

Object::Object(int width, int height)
{
	_xStart = rand() % width;
	_width = 2.0f + rand() % 10;
	if (width < _xStart + _width)
	{
		_xStart = width - _width;
	}

	_yStart = rand() % height;
	_height = 2.0f + rand() % 10;
	if (height < _yStart + _height)
	{
		_yStart = height - _height;
	}
}

void QuadTree::AddObject(Object* object)
{
	_root->AddObject(object);
}

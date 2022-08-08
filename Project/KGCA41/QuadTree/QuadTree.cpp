#include "QuadTree.h"

QuadTree::Node::Node(int left, int top, int width, int height, int depth, int maxDepth)
	: _rect(left, top, width, height), _depth(depth)
{
	if (depth + 1 < maxDepth)
	{
		width = width >> 1;
		height = height >> 1;

		_child[0] = new Node(left, top, width, height, depth + 1, maxDepth);
		_child[1] = new Node(left + width, top, width, height, depth + 1, maxDepth);
		_child[2] = new Node(left, top + height, width, height, depth + 1, maxDepth);
		_child[3] = new Node(left + width, top + height, width, height, depth + 1, maxDepth);
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			_child[i] = nullptr;
		}
	}
}

QuadTree::Node::~Node()
{
	for (int i = 0; i < 4; ++i)
	{
		delete _child[i];
	}
}

bool QuadTree::Node::IsIn(Object* object)
{
	const Rect* volume = static_cast<const Rect*>(object->GetVolume());
	if (GetLeft() <= volume->GetLeft())
	{
		if (volume->GetRight() <= GetRight())
		{
			if (GetTop() <= volume->GetTop())
			{
				if (volume->GetBottom() <= GetBottom())
				{
					return true;
				}
			}
		}
	}
	return false;
}

void QuadTree::Node::AddObject(Object* object)
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
			_containingObjects.push_back(object);
		}
	}
}

std::vector<Object*> QuadTree::Node::GetCollidedObjects(Object* obj)
{
	const Rect* objectVolume = obj->GetVolume();
	std::vector<Object*> ret;
	for (auto iter = _containingObjects.begin(); iter != _containingObjects.end(); ++iter)
	{
		if (Collision::IsCollide(_rect, *objectVolume))
		{
			ret.push_back(*iter);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		if (Collision::IsCollide(*_child[i]->GetVolume(), *objectVolume))
		{
			auto collisionObjects = _child[i]->GetCollidedObjects(obj);
			ret.insert(ret.end(), collisionObjects.begin(), collisionObjects.end());
		}
	}
	return ret;
}

void QuadTree::AddObject(Object* object)
{
	_root->AddObject(object);
}

std::vector<Object*> QuadTree::GetCollidedObjects(Object* obj)
{
	return _root->GetCollidedObjects(obj);
}

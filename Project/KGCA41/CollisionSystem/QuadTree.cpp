#include "QuadTree.h"
#include "Object.h"
#include "Collision.h"

QuadTree::Node::Node(float left, float top, float _width, float _height, float depth, int maxDepth)
	: _rect(left + (_width/2), top + (_height/2), _width, _height), _depth(depth)
{
	if (depth + 1 < maxDepth)
	{
		_width = _width / 2;
		_height = _height / 2;

		_child[0] = new Node(left, top, _width, _height, depth + 1, maxDepth);
		_child[1] = new Node(left + _width, top, _width, _height, depth + 1, maxDepth);
		_child[2] = new Node(left, top + _height, _width, _height, depth + 1, maxDepth);
		_child[3] = new Node(left + _width, top + _height, _width, _height, depth + 1, maxDepth);
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
	//how about Collision::IsOverlap()
	const Rectangle* volume = static_cast<const Rectangle*>(object->GetVolume());
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

void QuadTree::Node::AddObjectForce(Object* object)
{
	_containingObjects.push_back(object);
}

std::vector<Object*> QuadTree::Node::GetCollidedObjects(Object* obj)
{
	const Volume* objectVolume = obj->GetVolume();
	std::vector<Object*> ret;
	for (auto iter = _containingObjects.begin(); iter != _containingObjects.end(); ++iter)
	{
		if (Collision::IsCollide(*(*iter)->GetVolume(), *objectVolume))
		{
			ret.push_back(*iter);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		if (_child[i] != nullptr)
		{
			if (Collision::IsCollide(*_child[i]->GetVolume(), *objectVolume))
			{
				auto collisionObjects = _child[i]->GetCollidedObjects(obj);
				ret.insert(ret.end(), collisionObjects.begin(), collisionObjects.end());
			}
		}
	}
	return ret;
}

QuadTree::QuadTree(float _width, float _height, int maxDepth) : _maxDepth(maxDepth)
{
	float halfWidth = _width / 2;
	float halfHeight = _height / 2;
	_root = new Node(-halfWidth, -halfHeight, _width, _height, 0, maxDepth);
}

void QuadTree::AddObject(Object* object)
{
	if (_root->IsIn(object))
	{
		_root->AddObject(object);
	}
	else
	{
		_root->AddObjectForce(object);
	}
}

std::vector<Object*> QuadTree::GetCollidedObjects(Object* obj)
{
	return _root->GetCollidedObjects(obj);
}

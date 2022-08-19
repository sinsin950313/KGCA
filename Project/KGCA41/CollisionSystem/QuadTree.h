#pragma once

#include "VolumeInterface.h"
#include "Rectangle.h"
#include <vector>
#include "Object.h"
#include "Collision.h"

template<int dimension>
class QuadTree
{
private:
	class Node : public VolumeInterface<2>
	{
	private:
		Node* _child[4];
		Rectangle _rect;
		int _depth;
		std::vector<Object<dimension>*> _containingObjects;

	private:
		float GetLeft() { return _rect.GetLeft(); }
		float GetTop() { return _rect.GetTop(); }
		float GetRight() { return _rect.GetRight(); }
		float GetBottom() { return _rect.GetBottom(); }
		float GetWidth() { return _rect.GetWidth(); }
		float GetHeight() { return _rect.GetHeight(); }

	public:
		Node(float left, float top, float _width, float _height, float depth, int maxDepth);
		~Node();
		//Consider totally in stuation, not overlap
		bool IsIn(Object<dimension>* object);
		void AddObject(Object<dimension>* object);
		void AddObjectForce(Object<dimension>* object);
		std::vector<Object<dimension>*> GetCollidedObjects(Object<dimension>* obj);

	public:
		const Volume<2>* GetVolume() override { return &_rect; }
	};

private:
	Node* _root;
	int _maxDepth;

public:
	QuadTree(float _width, float _height, int maxDepth);
	~QuadTree() { delete _root; }
	void AddObject(Object<dimension>* object);
	std::vector<Object<dimension>*> GetCollidedObjects(Object<dimension>* obj);
};

template<int dimension>
QuadTree<dimension>::Node::Node(float left, float top, float _width, float _height, float depth, int maxDepth)
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

template<int dimension>
QuadTree<dimension>::Node::~Node()
{
	for (int i = 0; i < 4; ++i)
	{
		delete _child[i];
	}
}

template<int dimension>
bool QuadTree<dimension>::Node::IsIn(Object<dimension>* object)
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

template<int dimension>
void QuadTree<dimension>::Node::AddObject(Object<dimension>* object)
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

template<int dimension>
void QuadTree<dimension>::Node::AddObjectForce(Object<dimension>* object)
{
	_containingObjects.push_back(object);
}

template<int dimension>
std::vector<Object<dimension>*> QuadTree<dimension>::Node::GetCollidedObjects(Object<dimension>* obj)
{
	const Volume<dimension>* objectVolume = obj->GetVolume();
	std::vector<Object<dimension>*> ret;
	for (auto iter = _containingObjects.begin(); iter != _containingObjects.end(); ++iter)
	{
		if (Collision::IsCollide<dimension>(*(*iter)->GetVolume(), *objectVolume))
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

template<int dimension>
QuadTree<dimension>::QuadTree(float _width, float _height, int maxDepth) : _maxDepth(maxDepth)
{
	float halfWidth = _width / 2;
	float halfHeight = _height / 2;
	_root = new Node(-halfWidth, -halfHeight, _width, _height, 0, maxDepth);
}

template<int dimension>
void QuadTree<dimension>::AddObject(Object<dimension>* object)
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

template<int dimension>
std::vector<Object<dimension>*> QuadTree<dimension>::GetCollidedObjects(Object<dimension>* obj)
{
	return _root->GetCollidedObjects(obj);
}

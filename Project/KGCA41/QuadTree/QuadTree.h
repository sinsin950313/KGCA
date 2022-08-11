#pragma once

#include <vector>
#include "Rectangle.h"
#include "VolumeInterface.h"

class Object;

class QuadTree
{
private:
	class Node : public VolumeInterface
	{
	private:
		Node* _child[4];
		Rectangle _rect;
		int _depth;
		std::vector<Object*> _containingObjects;

	private:
		float GetLeft() { return _rect.GetLeft(); }
		float GetTop() { return _rect.GetTop(); }
		float GetRight() { return _rect.GetRight(); }
		float GetBottom() { return _rect.GetBottom(); }
		float GetWidth() { return _rect.GetWidth(); }
		float GetHeight() { return _rect.GetHeight(); }

	public:
		Node(float left, float top, float width, float height, float depth, int maxDepth);
		~Node();
		//Consider totally in stuation, not overlap
		bool IsIn(Object* object);
		void AddObject(Object* object);
		void AddObjectForce(Object* object);
		std::vector<Object*> GetCollidedObjects(Object* obj);

	public:
		const Rectangle* GetVolume() override { return &_rect; }
	};

private:
	Node* _root;
	int _maxDepth;

public:
	QuadTree(float width, float height, int maxDepth);
	~QuadTree() { delete _root; }
	void AddObject(Object* object);
	std::vector<Object*> GetCollidedObjects(Object* obj);
};

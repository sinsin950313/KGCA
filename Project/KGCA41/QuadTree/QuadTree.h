#pragma once

#include <vector>
#include "Rectangle.h"
#include "VolumeInterface.h"
#include "CustomMath.h"

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
		CustomFloat GetLeft() { return _rect.GetLeft(); }
		CustomFloat GetTop() { return _rect.GetTop(); }
		CustomFloat GetRight() { return _rect.GetRight(); }
		CustomFloat GetBottom() { return _rect.GetBottom(); }
		CustomFloat GetWidth() { return _rect.GetWidth(); }
		CustomFloat GetHeight() { return _rect.GetHeight(); }

	public:
		Node(CustomFloat left, CustomFloat top, CustomFloat width, CustomFloat height, CustomFloat depth, int maxDepth);
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
	QuadTree(CustomFloat width, CustomFloat height, int maxDepth);
	~QuadTree() { delete _root; }
	void AddObject(Object* object);
	std::vector<Object*> GetCollidedObjects(Object* obj);
};

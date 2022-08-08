#pragma once

#include <vector>
#include "Object.h"
#include "VolumeInterface.h"

class QuadTree
{
private:
	class Node : public VolumeInterface
	{
	private:
		Node* _child[4];
		Rect _rect;
		int _depth;
		std::vector<Object*> _containingObjects;

	private:
		int GetLeft() { return _rect.GetLeft(); }
		int GetTop() { return _rect.GetTop(); }
		int GetRight() { return _rect.GetRight(); }
		int GetBottom() { return _rect.GetBottom(); }
		int GetWidth() { return _rect.GetWidth(); }
		int GetHeight() { return _rect.GetHeight(); }

	public:
		Node(int left, int top, int width, int height, int depth, int maxDepth);
		~Node();
		//Consider totally in stuation, not overlap
		bool IsIn(Object* object);
		void AddObject(Object* object);
		std::vector<Object*> GetCollidedObjects(Object* obj);

	public:
		const Rect* GetVolume() override { return &_rect; }
	};

private:
	Node* _root;
	int _maxDepth;

public:
	QuadTree(int width, int height, int maxDepth) : _maxDepth(maxDepth) { _root = new Node(0, 0, width, height, 0, maxDepth); }
	~QuadTree() { delete _root; }
	void AddObject(Object* object);
	std::vector<Object*> GetCollidedObjects(Object* obj);
};

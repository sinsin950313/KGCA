#pragma once

#include <vector>

class Object
{
private:
	int _xStart;
	int _yStart;
	int _width;
	int _height;

public:
	Object(int width, int height);
	int GetXStart() { return _xStart; }
	int GetYStart() { return _yStart; }
	int GetXEnd() { return _xStart + _width; }
	int GetYEnd() { return _yStart + _height; }
};

class Node
{
private:
	Node* _child[4];
	int _xStart;
	int _yStart;
	int _width;
	int _height;
	int _depth;
	std::vector<Object*> _objects;

private:
	int GetXStart() { return _xStart; }
	int GetYStart() { return _yStart; }
	int GetXEnd() { return _xStart + _width; }
	int GetYEnd() { return _yStart + _height; }

public:
	Node(int xStart, int yStart, int width, int height, int depth, int maxDepth);
	~Node();
	bool IsIn(Object* object);
	void AddObject(Object* object);
};

class QuadTree
{
private:
	Node* _root;
	int _maxDepth;

public:
	QuadTree(int width, int height, int maxDepth) : _maxDepth(maxDepth) { _root = new Node(0, 0, width, height, 0, maxDepth); }
	~QuadTree() { delete _root; }
	void AddObject(Object* object);
};


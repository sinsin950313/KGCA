#pragma once

#include <vector>
//#include "QuadTree.h"

class Object;

class Core
{
private:
	const int _width = 100;
	const int _height = 100;
	const int _maxDepth = 3;
	//QuadTree qt;
	std::vector<Object*> _objects;
	Object* _player;
	std::vector<Object*> _collidedObjects;

public:
	Core();
	~Core();
	void Init();
	void Simulate(float deltaTime);
	void Render();
	void Run();
};


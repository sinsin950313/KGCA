#include "QuadTree.h"
#include <vector>

int main()
{
	int mapWidth = 100;
	int mapHeight = 100;
	int maxDepth = 3;

	QuadTree qt(mapWidth, mapHeight, maxDepth);
	
	int objectCount = 10;
	std::vector<Object*> objects;
	for (int i = 0; i < objectCount; ++i)
	{
		Object* object = new Object(mapWidth, mapHeight);
		objects.push_back(object);
		qt.AddObject(object);
	}
	
	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		delete (*iter);
	}
}

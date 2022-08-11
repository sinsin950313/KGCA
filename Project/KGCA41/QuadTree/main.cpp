#include "QuadTree.h"
#include <vector>
#include "Object.h"
#include <iostream>
#include "CustomMath.h"

using namespace std;

int main()
{
	int mapWidth = 100;
	int mapHeight = 100;
	int maxDepth = 3;

	QuadTree qt(mapWidth, mapHeight, maxDepth);
	
	int objectCount = 100;
	std::vector<Object*> objects;
	for (int i = 0; i < objectCount; ++i)
	{
		CustomFloat centerX = rand() % mapWidth - (mapWidth / 2);
		CustomFloat centerY = rand() % mapHeight - (mapHeight / 2);
		CustomFloat width = rand() % 10;
		CustomFloat height = rand() % 10;
		Object* object = new Object(centerX, centerY, width, height);
		objects.push_back(object);
		qt.AddObject(object);
	}

	Object* player = new Object(0, 0, 10, 10);
	std::vector<Object*> collidedObjects = qt.GetCollidedObjects(player);
	for (auto iter = collidedObjects.begin(); iter != collidedObjects.end(); ++iter)
	{
		const Rectangle* tmp = (*iter)->GetVolume();
		cout << tmp->GetLeft() << ", " << tmp->GetTop() << ", " << tmp->GetRight() << ", " << tmp->GetBottom() << endl;
	}

	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		delete (*iter);
	}
	delete player;
}

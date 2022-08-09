#include "QuadTree.h"
#include <vector>
#include "Object.h"
#include <iostream>

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
		float left = rand() % mapWidth;
		float top = rand() % mapHeight;
		float width = rand() % 10;
		float height = rand() % 10;
		Object* object = new Object(left, top, width, height);
		objects.push_back(object);
		qt.AddObject(object);
	}

	Object* player = new Object();
	player->Resize(20, 20);
	player->Reposition(50, 50);
	std::vector<Object*> collidedObjects = qt.GetCollidedObjects(player);
	for (auto iter = collidedObjects.begin(); iter != collidedObjects.end(); ++iter)
	{
		const Rect* tmp = (*iter)->GetVolume();
		cout << tmp->GetLeft() << ", " << tmp->GetTop() << ", " << tmp->GetRight() << ", " << tmp->GetBottom() << endl;
	}

	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		delete (*iter);
	}
	delete player;
}

#include <Windows.h>
#include "CollisionTree.h"
#include "Rectangle.h"

using namespace std;

int main()
{
	int mapWidth = 100;
	int mapHeight = 100;
	QuadTree qt(mapWidth, mapHeight, 3);
	std::vector<Object2D*> objects;

	int objectCount = 100;
	for (int i = 0; i < objectCount; ++i)
	{
		float centerX = (rand() % mapWidth) - (mapWidth / 2);
		float centerY = (rand() % mapHeight) - (mapHeight / 2);
		float width = rand() % 10 + 1.0f;
		float height = rand() % 10 + 1.0f;
		Object2D* object = new Object2D(new Custom::Rectangle(centerX, centerY, width, height), Rigidbody2D());

		objects.push_back(object);
		qt.AddObject(object);
	}

	Object2D* player = new Object2D(new Custom::Rectangle(0, 0, 20, 20), Rigidbody2D());
	player->GetRigidBody()->AddForce(Vector2D(Vector2DData{ 30, 30 }));

	float deltaTime = 0.1;
	while (1)
	{
		cout << "Player : ";
		player->GetVolume()->Print();

		auto collideObjects = qt.GetCollidedObjects(player);
		for (auto object : collideObjects)
		{
			object->GetVolume()->Print();
		}

		Sleep(100);
		system("cls");

		player->GetRigidBody()->Calculate(deltaTime);
		Vector2D pos = player->GetVolume()->GetCenter() + player->GetRigidBody()->GetVelocity() * deltaTime;
		player->GetVolume()->Reposition(pos);
	}

	for (auto object : objects)
	{
		delete object;
	}
}

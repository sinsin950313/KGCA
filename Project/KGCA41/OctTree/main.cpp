#include <Windows.h>
#include "CollisionTree.h"
#include "Rectangle.h"

using namespace std;

int main()
{
	int mapWidth = 100;
	int mapHeight = 100;
	int mapDepth = 100;
	OctTree ot(mapWidth, mapHeight, mapDepth, 3);
	std::vector<Object3D*> staticObjects;
	std::vector<Object3D*> dynamicObjects;

	int objectCount = 100;
	for (int i = 0; i < objectCount; ++i)
	{
		float centerX = (rand() % mapWidth) - (mapWidth / 2);
		float centerY = (rand() % mapHeight) - (mapHeight / 2);
		float centerZ = (rand() % mapDepth) - (mapDepth / 2);
		float width = rand() % 10 + 1.0f;
		float height = rand() % 10 + 1.0f;
		float depth = rand() % 10 + 1.0f;
		Object3D* object = new Object3D(new Box(Vector3D(Vector3DData{ centerX, centerY, centerZ }), width, height, depth), Rigidbody3D());

		staticObjects.push_back(object);
		ot.AddStaticObject(object);
	}
	for (int i = 0; i < objectCount; ++i)
	{
		float centerX = (rand() % mapWidth) - (mapWidth / 2);
		float centerY = (rand() % mapHeight) - (mapHeight / 2);
		float centerZ = (rand() % mapDepth) - (mapDepth / 2);
		float width = rand() % 10 + 1.0f;
		float height = rand() % 10 + 1.0f;
		float depth = rand() % 10 + 1.0f;
		Object3D* object = new Object3D(new Box(Vector3D(Vector3DData{ centerX, centerY, centerZ }), width, height, depth), Rigidbody3D());

		float forceX = rand() % 50;
		float forceY = rand() % 50;
		float forceZ = rand() % 50;
		object->GetRigidBody()->AddForce(Vector3D(Vector3DData{ forceX, forceY, forceZ }));

		dynamicObjects.push_back(object);
		ot.AddDynamicObject(object);
	}

	Object3D* player = new Object3D(new Box(Vector3D(Vector3DData{ 0, 0, 0 }), 30, 30, 30), Rigidbody3D());
	player->GetRigidBody()->AddForce(Vector3D(Vector3DData{ 30, 30, 30 }));

	float deltaTime = 0.1;
	while (1)
	{
		cout << "Player : ";
		player->GetVolume()->Print();

		auto collideObjects = ot.GetCollidedObjects(player);
		for (auto object : collideObjects)
		{
			object->GetVolume()->Print();
		}

		Sleep(100);
		system("cls");

		player->GetRigidBody()->Calculate(deltaTime);
		Vector3D pos = player->GetVolume()->GetCenter() + player->GetRigidBody()->GetVelocity() * deltaTime;
		player->GetVolume()->Reposition(pos);

		ot.Frame();
		for (auto object : dynamicObjects)
		{
			object->GetRigidBody()->Calculate(deltaTime);
			Vector3D pos = object->GetVolume()->GetCenter() + object->GetRigidBody()->GetVelocity() * deltaTime;
			object->GetVolume()->Reposition(pos);
		}
	}

	for (auto object : staticObjects)
	{
		delete object;
	}
	for (auto object : dynamicObjects)
	{
		delete object;
	}
}
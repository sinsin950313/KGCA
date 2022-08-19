#include "Rigidbody.h"
#include <iostream>
#include "QuadTree.h"

int main()
{
	Rigidbody2D r2d;
	r2d.AddForce(Vector2D(Vector2DData{100, 0}));
	r2d.Calculate(0.1);
	Vector2D velocity = r2d.GetVelocity();
	std::cout << velocity.Get(0) << ", " << velocity.Get(1) << std::endl;

	constexpr int dimension = 2;
	const int width = 100;
	const int height = 100;
	const int maxDepth = 3;
	QuadTree<dimension> qt(width, height, maxDepth);
	std::vector<Object<dimension>*> objects;
	Object<dimension>* player;
	std::vector<Object<dimension>*> collidedObjects;

	int objectCount = 100;
	for (int i = 0; i < objectCount; ++i)
	{
		float centerX = (rand() % width) - (width / 2);
		float centerY = (rand() % height) - (height / 2);
		float tmpWidth = rand() % 10 + 1.0f;
		float tmpHeight = rand() % 10 + 1.0f;
		Object<dimension>* object = new Object<dimension>(new Rectangle(centerX, centerY, tmpWidth, tmpHeight), Rigidbody2D());
		objects.push_back(object);
		qt.AddObject(object);
	}

	player = new Object<dimension>(new Rectangle(0, 0, 10, 10), Rigidbody2D());

	float deltaTime = 0.1f;
	player->GetRigidBody()->Calculate(deltaTime);
	Vector2D pos = player->GetVolume()->GetCenter() + (player->GetRigidBody()->GetVelocity() * deltaTime);
	player->GetVolume()->Reposition(pos);

	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		(*iter)->GetRigidBody()->Calculate(deltaTime);
		Vector2D pos = (*iter)->GetVolume()->GetCenter() + (*iter)->GetRigidBody()->GetVelocity() * deltaTime;
		(*iter)->GetVolume()->Reposition(pos);
	}

	collidedObjects = qt.GetCollidedObjects(player);

	const Volume<dimension>* playerVolume = player->GetVolume();
	playerVolume->Print();
	
	for (auto iter = collidedObjects.begin(); iter != collidedObjects.end(); ++iter)
	{
		const Volume<dimension>* tmp = (*iter)->GetVolume();
		tmp->Print();
	}
}
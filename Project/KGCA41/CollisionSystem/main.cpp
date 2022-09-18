#include "Rigidbody.h"
#include <iostream>
#include "CollisionTree.h"
//#include "ObjectFactory.h"

//#define QUADTREE

using namespace SSB;

int main()
{
	Rigidbody2D r2d;
	r2d.AddForce(Vector2D(Vector2DData{100, 0}));
	r2d.Calculate(0.1);
	Vector2D velocity = r2d.GetVelocity();
	std::cout << velocity.Get(0) << ", " << velocity.Get(1) << std::endl;

#ifdef QUADTREE
	constexpr int dimension = 2;
#else
	constexpr int dimension = 3;
#endif
	const int width = 100;
	const int height = 100;
#ifndef QUADTREE
	const int depth = 100;
#endif
	const int maxLayer = 3;
#ifdef QUADTREE
	CollisionTree<dimension>* ct = new QuadTree(width, height, maxLayer);
#else
	CollisionTree<dimension>* ct = new OctTree(width, height, depth, maxLayer);
#endif
	std::vector<Object<dimension>*> objects;
	Object<dimension>* player;
	std::vector<Object<dimension>*> collidedObjects;

	{
		float centerX = 0;
		float centerY = 0;
#ifndef	QUADTREE
		float centerZ = 0;
#endif
		float tmpWidth = 10.0f;
		float tmpHeight = 10.0f;
#ifndef	QUADTREE
		float tmpDepth = 10.0f;
#endif
#ifdef QUADTREE
		Object<dimension>* topObject = new Object<dimension>(new Custom::Rectangle(centerX, centerY, tmpWidth, tmpHeight), Rigidbody2D());
#else
		Object<dimension>* topObject = new Object<dimension>(new Box(Vector3D(Vector3DData{centerX, centerY, centerZ}), tmpWidth, tmpHeight, tmpDepth), Rigidbody3D());
#endif
		objects.push_back(topObject);
		ct->AddStaticObject(topObject);
	}
	{
		float centerX = 25;
		float centerY = 25;
#ifndef	QUADTREE
		float centerZ = 25;
#endif
		float tmpWidth = 1.0f;
		float tmpHeight = 1.0f;
#ifndef	QUADTREE
		float tmpDepth = 1.0f;
#endif
#ifdef QUADTREE
		Object<dimension>* midObject = new Object<dimension>(new Custom::Rectangle(centerX, centerY, tmpWidth, tmpHeight), Rigidbody2D());
#else
		Object<dimension>* midObject = new Object<dimension>(new Box(Vector3D(Vector3DData{centerX, centerY, centerZ}), tmpWidth, tmpHeight, tmpDepth), Rigidbody3D());
#endif
		objects.push_back(midObject);
		ct->AddStaticObject(midObject);
	}
	{
		float centerX = 12;
		float centerY = 12;
#ifndef	QUADTREE
		float centerZ = 12;
#endif
		float tmpWidth = 1.0f;
		float tmpHeight = 1.0f;
#ifndef	QUADTREE
		float tmpDepth = 1.0f;
#endif
#ifdef QUADTREE
		Object<dimension>* inObject = new Object<dimension>(new Custom::Rectangle(centerX, centerY, tmpWidth, tmpHeight), Rigidbody2D());
#else
		Object<dimension>* inObject = new Object<dimension>(new Box(Vector3D(Vector3DData{centerX, centerY, centerZ}), tmpWidth, tmpHeight, tmpDepth), Rigidbody3D());
#endif
		objects.push_back(inObject);
		ct->AddStaticObject(inObject);
	}
	{
		float centerX = -12;
		float centerY = -12;
#ifndef	QUADTREE
		float centerZ = -12;
#endif
		float tmpWidth = 1.0f;
		float tmpHeight = 1.0f;
#ifndef	QUADTREE
		float tmpDepth = 1.0f;
#endif
#ifdef QUADTREE
		Object<dimension>* outObject = new Object<dimension>(new Custom::Rectangle(centerX, centerY, tmpWidth, tmpHeight), Rigidbody2D());
#else
		Object<dimension>* outObject = new Object<dimension>(new Box(Vector3D(Vector3DData{centerX, centerY, centerZ}), tmpWidth, tmpHeight, tmpDepth), Rigidbody3D());
#endif
		objects.push_back(outObject);
		ct->AddStaticObject(outObject);
	}

//	int objectCount = 100;
//	for (int i = 0; i < objectCount; ++i)
//	{
//		float centerX = (rand() % width) - (width / 2);
//		float centerY = (rand() % height) - (height / 2);
//#ifndef	QUADTREE
//		float centerZ = (rand() % depth) - (depth / 2);
//#endif
//		float tmpWidth = rand() % 10 + 1.0f;
//		float tmpHeight = rand() % 10 + 1.0f;
//#ifndef	QUADTREE
//		float tmpDepth = rand() % 10 + 1.0f;
//#endif
//
//#ifdef QUADTREE
//		Object<dimension>* object = new Object<dimension>(new Custom::Rectangle(centerX, centerY, tmpWidth, tmpHeight), Rigidbody2D());
//#else
//		Object<dimension>* object = new Object<dimension>(new Box(Vector3D(Vector3DData{centerX, centerY, centerZ}), tmpWidth, tmpHeight, tmpDepth), Rigidbody3D());
//#endif
//		objects.push_back(object);
//		ct->AddObject(object);
//	}

#ifdef QUADTREE
	player = new Object<dimension>(new Custom::Rectangle(15, 15, 30, 30), Rigidbody2D());
#else
	player = new Object<dimension>(new Box(Vector3D(Vector3DData{ 15, 15, 15 }), 30, 30, 30), Rigidbody3D());
#endif

	//float deltaTime = 0.1f;
	//player->GetRigidBody()->Calculate(deltaTime);
	//PhysicsVector<dimension> pos = player->GetVolume()->GetCenter() + (player->GetRigidBody()->GetVelocity() * deltaTime);
	//player->GetVolume()->Reposition(pos);

	//for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	//{
	//	(*iter)->GetRigidBody()->Calculate(deltaTime);
	//	PhysicsVector<dimension> pos = (*iter)->GetVolume()->GetCenter() + (*iter)->GetRigidBody()->GetVelocity() * deltaTime;
	//	(*iter)->GetVolume()->Reposition(pos);
	//}

	collidedObjects = ct->GetCollidedObjects(player);

	const Volume<dimension>* playerVolume = player->GetVolume();
	playerVolume->Print();
	
	for (auto iter = collidedObjects.begin(); iter != collidedObjects.end(); ++iter)
	{
		const Volume<dimension>* tmp = (*iter)->GetVolume();
		tmp->Print();
	}
}
#pragma once

#include <vector>
#include "CollisionTree.h"
#include "Object.h"

template<int dimension>
class Core
{
private:
	//template<int dimension>
	//class ObjectGenerator
	//{
	//public:
	//	Object<2>* Create(int centerX, int centerY, int width, int height);
	//	Object<3>* Create(int centerX, int centerY, int centerZ, int width, int height, int depth);
	//	Object<2>* Create(int width, int height);
	//	Object<3>* Create(int width, int height, int depth);
	//};

private:
	const int _width = 100;
	const int _height = 100;
	const int _depth = 100;
	const int _maxLayer = 3;
	CollisionTree<dimension>* _ct = nullptr;
	std::vector<Object<dimension>*> _objects;
	Object<dimension>* _player;
	std::vector<Object<dimension>*> _collidedObjects;

public:
	Core();
	~Core();

private:
	void Simulate(float deltaTime);
	void Render();

public:
	void Init();
	void Run();

public:
	void UseQuadTree();
	void UseOctTree();
};

template<int dimension>
Core<dimension>::Core()
{
}

template<int dimension>
Core<dimension>::~Core()
{
	for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
	{
		delete (*iter);
	}
	delete _player;
}

template<int dimension>
void Core<dimension>::Init()
{
	int objectCount = 100;
	for (int i = 0; i < objectCount; ++i)
	{
		float centerX = (rand() % _width) - (_width / 2);
		float centerY = (rand() % _height) - (_height / 2);
		float width = rand() % 10 + 1.0f;
		float height = rand() % 10 + 1.0f;
		//void* object = nullptr;
		//if (dimension == 2)
		//{
		//	object = ObjectGenerator<2>().Create(_width, _height);
		//}
		//if (dimension == 3)
		//{
		//	object = ObjectGenerator<3>().Create(_width, _height, _depth);
		//}
		//_objects.push_back(static_cast<Object<dimension>*>(object));
		//_ct->AddObject(static_cast<Object<dimension>*>(object));
	}

	//void* player = nullptr;
	//if (dimension == 2)
	//{
	//	player = ObjectGenerator<2>().Create(0, 0, 10, 10);
	//}
	//if (dimension == 3)
	//{
	//	player = ObjectGenerator<3>().Create(0, 0, 0, 10, 10, 10);
	//}
	//_player = static_cast<Object<dimension>*>(player);
}

template<int dimension>
void Core<dimension>::Simulate(float deltaTime)
{
	_player->GetRigidBody()->Calculate(deltaTime);
	PhysicsVector<dimension> pos = _player->GetVolume()->GetCenter() + (_player->GetRigidBody()->GetVelocity() * deltaTime);
	_player->GetVolume()->Reposition(pos);

	for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
	{
		(*iter)->GetRigidBody()->Calculate(deltaTime);
		PhysicsVector<dimension> pos = (*iter)->GetVolume()->GetCenter() + (*iter)->GetRigidBody()->GetVelocity() * deltaTime;
		(*iter)->GetVolume()->Reposition(pos);
	}

	_collidedObjects = _ct->GetCollidedObjects(_player);
}

template<int dimension>
void Core<dimension>::Render()
{
	const Volume<dimension>* playerVolume = _player->GetVolume();
	playerVolume->Print();
	
	for (auto iter = _collidedObjects.begin(); iter != _collidedObjects.end(); ++iter)
	{
		const Volume<dimension>* tmp = (*iter)->GetVolume();
		tmp->Print();
	}
}

template<int dimension>
void Core<dimension>::Run()
{
	Simulate(0.1f);
	Render();

	_player->GetRigidBody()->AddForce(PhysicsVector<dimension>(10, 10));
}

template<int dimension>
inline void Core<dimension>::UseQuadTree()
{
	_ct = new QuadTree(100, 100, 3);
}

template<int dimension>
inline void Core<dimension>::UseOctTree()
{
	_ct = new OctTree(100, 100, 100, 3);
}
//
//inline Object<2>* Core<2>::ObjectGenerator<2>::Create(int centerX, int centerY, int width, int height)
//{
//	return nullptr;
//}
//
//inline Object<3>* Core<3>::ObjectGenerator<2>::Create(int centerX, int centerY, int centerZ, int width, int height, int depth)
//{
//	return nullptr;
//}
//
//inline Object<2>* Core<2>::ObjectGenerator<2>::Create(int width, int height)
//{
//	return nullptr;
//}
//
//inline Object<3>* Core<3>::ObjectGenerator<3>::Create(int width, int height, int depth)
//{
//	return nullptr;
//}

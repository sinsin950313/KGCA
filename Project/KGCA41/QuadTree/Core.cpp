#include "Core.h"
#include <iostream>
#include "Object.h"

Core::Core() : qt(_width, _height, _maxDepth)
{
}

Core::~Core()
{
	for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
	{
		delete (*iter);
	}
	delete _player;
}

void Core::Init()
{
	int objectCount = 100;
	for (int i = 0; i < objectCount; ++i)
	{
		float centerX = (rand() % _width) - (_width / 2);
		float centerY = (rand() % _height) - (_height / 2);
		float width = rand() % 10 + 1.0f;
		float height = rand() % 10 + 1.0f;
		Object* object = new Object(centerX, centerY, width, height);
		_objects.push_back(object);
		qt.AddObject(object);
	}

	_player = new Object(0, 0, 10, 10);
}

void Core::Simulate(float deltaTime)
{
	_player->GetRigidBody()->Calculate(deltaTime);
	Vector2D pos = _player->GetVolume()->GetCenter() + (_player->GetRigidBody()->GetVelocity() * deltaTime);
	_player->Reposition(pos.GetX(), pos.GetY());

	for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
	{
		(*iter)->GetRigidBody()->Calculate(deltaTime);
		Vector2D pos = (*iter)->GetVolume()->GetCenter() + (*iter)->GetRigidBody()->GetVelocity() * deltaTime;
		(*iter)->Reposition(pos.GetX(), pos.GetY());
	}

	_collidedObjects = qt.GetCollidedObjects(_player);
}

void Core::Render()
{
	const Rectangle* playerVolume = _player->GetVolume();
	std::cout << playerVolume->GetLeft() << ", " << playerVolume->GetTop() << ", " << playerVolume->GetRight() << ", " << playerVolume->GetBottom() << std::endl << std::endl;
	
	for (auto iter = _collidedObjects.begin(); iter != _collidedObjects.end(); ++iter)
	{
		const Rectangle* tmp = (*iter)->GetVolume();
		std::cout << tmp->GetLeft() << ", " << tmp->GetTop() << ", " << tmp->GetRight() << ", " << tmp->GetBottom() << std::endl;
	}
}

void Core::Run()
{
	Simulate(0.1f);
	Render();

	_player->GetRigidBody()->AddForce(Vector2D(10, 10));
}

#include "DX2DGameObjectFactory.h"
#include "DX2DGameObject.h"
#include "ObjectFactory.h"
#include "DX2DMapObject.h"
#include "CollisionTree.h"

namespace SSB
{
	DX2DGameObject* DX2DGameObjectFactory::CreateStaticGameObject(Position2D center, float width, float height, float mass)
	{
		DX2DGameObject* ret = new DX2DGameObject(center, width, height, mass);
		_mapObject->RegisterStaticObject(ret->GetPhysicsObject(), ret);

		return ret;
	}

	DX2DGameObject* DX2DGameObjectFactory::CreateDynamicGameObject(Position2D center, float width, float height, float mass)
	{
		DX2DGameObject* ret = new DX2DGameObject(center, width, height, mass);
		_mapObject->RegisterDynamicObject(ret->GetPhysicsObject(), ret);

		return ret;
	}
}

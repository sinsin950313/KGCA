#include "DX2DGameObjectFactory.h"
#include "DX2DGameObject.h"
#include "ObjectFactory.h"
#include "DX2DMapObject.h"
#include "CollisionTree.h"

namespace SSB
{
	DX2DInGameObject* DX2DGameObjectFactory::CreateStaticGameObject(Position2D center, float width, float height, float mass)
	{
		DX2DInGameObject* ret = new DX2DInGameObject(center, width, height, mass);
		_mapObject->RegisterStaticObject(ret);

		return ret;
	}

	DX2DInGameObject* DX2DGameObjectFactory::CreateDynamicGameObject(Position2D center, float width, float height, float mass)
	{
		DX2DInGameObject* ret = new DX2DInGameObject(center, width, height, mass);
		_mapObject->RegisterDynamicObject(ret);

		return ret;
	}
}

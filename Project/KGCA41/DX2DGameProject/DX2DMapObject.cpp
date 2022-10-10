#include "DX2DMapObject.h"
#include "CollisionTree.h"
#include "DX2DGameObject.h"
#include "DX2DCamera.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "DXWindow.h"

namespace SSB
{
	extern DXWindow* g_dxWindow;

	DX2DMapObject::DX2DMapObject(Vector2D center, float width, float height)
	{
		_object = new Object2D(new Rectangle(center.Get(0), center.Get(1), width, height), Rigidbody2D(0));
		_terrain = new Terrain(width, height);

		int treeMaxLayer = 0;
		float wTmp = width;
		float hTmp = height;
		while (wTmp / 2 < 2 || hTmp / 2 < 2)
		{
			++treeMaxLayer;
			wTmp /= 2;
			hTmp /= 2;
		}

		_layer.resize(_maxLayer);
		for (int i = 0; i < _maxLayer; ++i)
		{
			_layer[i] = new QuadTree(width, height, treeMaxLayer);
		}
	}

	DX2DMapObject::~DX2DMapObject()
	{
		Release();
	}

	std::vector<DX2DInGameObject*> DX2DMapObject::GetCollideObjectList(DX2DInGameObject* object)
	{
		int currentLayer = object->GetCurrentMapLayer();
		std::vector<DX2DInGameObject*> collidedObjectList;

		QuadTree* currentLayerTree = _layer[currentLayer];
		auto collidePhysicsObjectList = currentLayerTree->GetCollidedObjects(object->GetPhysicsObject());
		for (auto physicsObject : collidePhysicsObjectList)
		{
			collidedObjectList.push_back(_physicsToDX2DMatch.find(physicsObject)->second);
		}

		return collidedObjectList;
	}

	std::vector<DX2DInGameObject*> DX2DMapObject::GetCollideObjectList(DX2DCamera* camera)
	{
		std::vector<DX2DInGameObject*> collidedObjectList;

		for (auto currentLayer : _layer)
		{
			auto collidePhysicsObjectList = currentLayer->GetCollidedObjects(camera->GetCaptureArea());
			for (auto physicsObject : collidePhysicsObjectList)
			{
				collidedObjectList.push_back(_physicsToDX2DMatch.find(physicsObject)->second);
			}
		}

		return collidedObjectList;
	}

	bool DX2DMapObject::IsCollide(DX2DInGameObject* object)
	{
		int currentLayer = object->GetCurrentMapLayer();
		return !_layer[currentLayer]->GetCollidedObjects(object->GetPhysicsObject()).empty();
	}

	bool DX2DMapObject::IsHit(DX2DInGameObject* attack, DX2DInGameObject* defense)
	{
		int attackerLayer = attack->GetCurrentMapLayer();

		auto hitboxDatas = attack->GetHitBoxData();
		for (int i = 0; i < hitboxCount; ++i)
		{
			int layer = attackerLayer + hitboxDatas[i]->GetRelativeLayer();
			if (0 <= layer && layer < _maxLayer)
			{
				auto collideList = _layer[layer]->GetCollidedObjects(hitboxDatas[i]->GetPhysicsObject());
				for (auto collideObject : collideList)
				{
					if (collideObject == defense->GetPhysicsObject())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	void DX2DMapObject::RegisterStaticObject(DX2DInGameObject* dxObject)
	{
		_physicsToDX2DMatch.insert(std::make_pair(dxObject->GetPhysicsObject(), dxObject));
		int currentLayer = dxObject->GetCurrentMapLayer();
		_layer[currentLayer]->AddStaticObject(dxObject->GetPhysicsObject());
	}

	void DX2DMapObject::RegisterDynamicObject(DX2DInGameObject* dxObject)
	{
		_physicsToDX2DMatch.insert(std::make_pair(dxObject->GetPhysicsObject(), dxObject));
		int currentLayer = dxObject->GetCurrentMapLayer();
		_layer[currentLayer]->AddDynamicObject(dxObject->GetPhysicsObject());
		_dynamicObjectList.push_back(dxObject);
	}

	bool DX2DMapObject::Init()
	{
		_terrain->Init();

		return true;
	}

	bool DX2DMapObject::Frame()
	{
		_terrain->Frame();
		for (auto layer : _layer)
		{
			layer->ClearDynamicObject();
		}

		int playerCurrentLayer = _player->GetCurrentMapLayer();
		for (auto object : _dynamicObjectList)
		{
			int currentLayer = GetCurrentMapLayer(object, playerCurrentLayer);
			object->SetCurrentLayer(currentLayer);
			_layer[currentLayer]->AddDynamicObject(object->GetPhysicsObject());
		}

		return true;
	}

	bool DX2DMapObject::Render()
	{
		_terrain->Render();

		return true;
	}

	bool DX2DMapObject::Release()
	{
		for (auto layer : _layer)
		{
			delete layer;
		}
		_layer.clear();
		_dynamicObjectList.clear();

		if (_terrain)
		{
			_terrain->Release();
			delete _terrain;
			_terrain = nullptr;
		}

		if (_object)
		{
			delete _object;
			_object = nullptr;
		}

		_physicsToDX2DMatch.clear();

		return true;
	}

	int DX2DMapObject::GetCurrentMapLayer(DX2DInGameObject* object, int playerCurrentLayer)
	{
		int objectLayer = object->GetCurrentMapLayer();
		int diff = objectLayer - playerCurrentLayer;

		int halfLayer = _maxLayer / 2;
		diff = max(diff, -halfLayer);
		diff = min(diff, halfLayer);

		return diff + halfLayer;
	}
}

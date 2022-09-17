#include "DX2DMapObject.h"
#include "CollisionTree.h"
#include "DX2DGameObject.h"
#include "DX2DCamera.h"
#include "TextureManager.h"
#include "ShaderManager.h"

namespace SSB
{
	DX2DMapObject::DX2DMapObject(Vector2D center, float width, float height)
	{
		_object = new Object2D(new Rectangle(center.Get(0), center.Get(1), width, height), Rigidbody2D(0));
		_dxObject = new DX2DObject(Position2D{ 0, 0 }, width, height);

		int maxLayer = 0;
		float wTmp = width;
		float hTmp = height;
		while (wTmp / 2 < 2 || hTmp / 2 < 2)
		{
			++maxLayer;
			wTmp /= 2;
			hTmp /= 2;
		}
		_qt = new QuadTree(width, height, maxLayer);
	}

	DX2DMapObject::~DX2DMapObject()
	{
		_physicsToDX2DMatch.clear();

		Release();
	}

	std::vector<DX2DGameObject*> DX2DMapObject::GetCollideObjectList(DX2DGameObject* object)
	{
		std::vector<DX2DGameObject*> collidedObjectList;

		auto collidePhysicsObjectList = _qt->GetCollidedObjects(object->GetPhysicsObject());
		for (auto physicsObject : collidePhysicsObjectList)
		{
			collidedObjectList.push_back(_physicsToDX2DMatch.find(physicsObject)->second);
		}

		return collidedObjectList;
	}

	std::vector<DX2DGameObject*> DX2DMapObject::GetCollideObjectList(DX2DCamera* camera)
	{
		std::vector<DX2DGameObject*> collidedObjectList;

		auto collidePhysicsObjectList = _qt->GetCollidedObjects(camera->GetCaptureArea());
		for (auto physicsObject : collidePhysicsObjectList)
		{
			collidedObjectList.push_back(_physicsToDX2DMatch.find(physicsObject)->second);
		}

		return collidedObjectList;
	}

	bool DX2DMapObject::IsCollide(DX2DGameObject* object)
	{
		return !_qt->GetCollidedObjects(object->GetPhysicsObject()).empty();
	}

	void DX2DMapObject::RegisterStaticObject(Object2D* object, DX2DGameObject* dxObject)
	{
		_physicsToDX2DMatch.insert(std::make_pair(object, dxObject));
		_qt->AddStaticObject(object);
	}

	void DX2DMapObject::RegisterDynamicObject(Object2D* object, DX2DGameObject* dxObject)
	{
		_physicsToDX2DMatch.insert(std::make_pair(object, dxObject));
		_qt->AddDynamicObject(object);
	}

	bool DX2DMapObject::Init()
	{
		_dxObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "main", "vs_5_0"));
		_dxObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "withoutMask", "ps_5_0"));
		_dxObject->SetTexture(TextureManager::GetInstance().Load(L"KGCABK.bmp"));
		_dxObject->Init();
		_dxObject->GetTexture()->Tile(7, 9);

		return true;
	}

	bool DX2DMapObject::Frame()
	{
		_dxObject->Frame();
		return true;
	}

	bool DX2DMapObject::Render()
	{
		_dxObject->Render();
		return true;
	}

	bool DX2DMapObject::Release()
	{
		if (_qt)
		{
			delete _qt;
			_qt = nullptr;
		}

		if (_dxObject)
		{
			_dxObject->Release();
			delete _dxObject;
			_dxObject = nullptr;
		}

		return true;
	}
}

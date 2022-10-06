#pragma once

#include "Common.h"
#include <vector>
#include <map>
#include "Object.h"
#include "DX2DObject.h"
#include "DX2DGameObject.h"
#include "Terrain.h"

namespace SSB
{
	class QuadTree;
	class DX2DGameObject;
	class DX2DCamera;

	class DX2DMapObject : public Common
	{
	private:
		const int _maxLayer = 5;
		std::vector<QuadTree*> _layer;
		Terrain* _terrain;
		std::map<Object2D*, DX2DInGameObject*> _physicsToDX2DMatch;
		Object2D* _object;
		DX2DInGameObject* _player;
		std::vector<DX2DInGameObject*> _dynamicObjectList;

	public:
		DX2DMapObject(Vector2D center, float width, float height);
		~DX2DMapObject();

	public:
		std::vector<DX2DInGameObject*> GetCollideObjectList(DX2DInGameObject* object);
		std::vector<DX2DInGameObject*> GetCollideObjectList(DX2DCamera* camera);
		bool IsCollide(DX2DInGameObject* object);
		bool IsHit(DX2DInGameObject* attack, DX2DInGameObject* defense);
		void RegisterStaticObject(DX2DInGameObject* dxObject);
		void RegisterDynamicObject(DX2DInGameObject* dxObject);
		//DX2DObject* GetDXObject() { return _dxObject; }
		Object2D* GetPhysicsObject() { return _object; }
		Vector2D GetCenter() { return _object->GetVolume()->GetCenter(); }
		void SetPlayer(DX2DInGameObject* player) { _player = player; }
		Terrain* GetTerrain() { return _terrain; }

	private:
		int GetCurrentMapLayer(DX2DInGameObject* object, int playerCurrentLayer);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
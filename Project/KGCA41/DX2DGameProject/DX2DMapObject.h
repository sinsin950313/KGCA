#pragma once

#include "Common.h"
#include <vector>
#include <map>
#include "Object.h"
#include "DX2DObject.h"

namespace SSB
{
	class QuadTree;
	class DX2DGameObject;
	class DX2DCamera;

	class DX2DMapObject : public Common
	{
	private:
		QuadTree* _qt = nullptr;
		DX2DObject* _dxObject;
		std::map<Object2D*, DX2DGameObject*> _physicsToDX2DMatch;
		Object2D* _object;

	public:
		DX2DMapObject(Vector2D center, float width, float height);
		~DX2DMapObject();

	public:
		std::vector<DX2DGameObject*> GetCollideObjectList(DX2DGameObject* object);
		std::vector<DX2DGameObject*> GetCollideObjectList(DX2DCamera* camera);
		bool IsCollide(DX2DGameObject* object);
		void RegisterStaticObject(Object2D* object, DX2DGameObject* dxObject);
		void RegisterDynamicObject(Object2D* object, DX2DGameObject* dxObject);
		DX2DObject* GetDXObject() { return _dxObject; }
		Object2D* GetPhysicsObject() { return _object; }
		Vector2D GetCenter() { return _object->GetVolume()->GetCenter(); }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
#pragma once

#include "CommonClass.h"
#include <vector>
#include <map>
#include "Object.h"

class QuadTree;
class DX2DGameObject;
class TDX2DObject;

class DX2DMapObject : public Common
{
private:
	QuadTree* _qt = nullptr;
	TDX2DObject* _dxObject;
	std::map<Object2D*, DX2DGameObject*> _physicsToDX2DMatch;

public:
	DX2DMapObject(Position2D pos, float width, float height);
	~DX2DMapObject();

public:
	std::vector<DX2DGameObject*> GetCollideObjectList(DX2DGameObject* object);
	bool IsCollide(DX2DGameObject* object);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
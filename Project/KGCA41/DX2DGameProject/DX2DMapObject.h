#pragma once

#include "CommonClass.h"
#include "CollisionTree.h"
#include "TDX2DObject.h"

class DX2DMapObject : public Common
{
private:
	QuadTree* _qt = nullptr;
	TDX2DObject _dxObject;

public:
	DX2DMapObject();
	~DX2DMapObject();

public:
	void SetMapSize(float width, float height);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

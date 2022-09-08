#include "DX2DMapObject.h"

DX2DMapObject::DX2DMapObject()
{
}

DX2DMapObject::~DX2DMapObject()
{
	delete _qt;
}

void DX2DMapObject::SetMapSize(float width, float height)
{
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

bool DX2DMapObject::Init()
{
	return true;
}

bool DX2DMapObject::Frame()
{
	return true;
}

bool DX2DMapObject::Render()
{
	return true;
}

bool DX2DMapObject::Release()
{
	return true;
}

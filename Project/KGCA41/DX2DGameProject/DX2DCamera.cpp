#include "DX2DCamera.h"

void DX2DCamera::Move(Vector2D center)
{
	_lensArea.Reposition(center);
}

bool DX2DCamera::Init()
{
	return true;
}

bool DX2DCamera::Frame()
{
	return true;
}

bool DX2DCamera::Render()
{
	return true;
}

bool DX2DCamera::Release()
{
	return true;
}

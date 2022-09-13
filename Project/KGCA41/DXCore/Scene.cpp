#include "Scene.h"

bool Scene::Init()
{
	return true;
}

bool Scene::Frame()
{
	return true;
}

bool Scene::Render()
{
	return true;
}

bool Scene::Release()
{
	_nextScene = nullptr;
	_linkedScenes.clear();
	return true;
}

#include "Model.h"
#include "HCCalculator.h"
#include "DXWindow.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

	//const AnimationName kDefaultAnimaionName = "DefaultAnimation";
	//Animation Model::DefaultAnimation;

	Model::Model()
	{
		//_sprites.push_back(SpriteLoader::GetInstance().GetDefaultSprite());
		//_animations.insert(std::make_pair(kDefaultAnimaionName, &DefaultAnimation));
		//_currentAnimation = &DefaultAnimation;
	}
	Model::~Model()
	{
		Release();
	}
	void Model::SizeCheck()
	{
		float minX = (std::numeric_limits<float>::max)();
		float minY = (std::numeric_limits<float>::max)();
		float minZ = (std::numeric_limits<float>::max)();
		float maxX = (std::numeric_limits<float>::min)();
		float maxY = (std::numeric_limits<float>::min)();
		float maxZ = (std::numeric_limits<float>::min)();
		for (auto vertex : _meshElementMinMaxVertexList)
		{
			minX = min(minX, vertex.GetX());
			minY = min(minY, vertex.GetY());
			minZ = min(minZ, vertex.GetZ());

			maxX = max(maxX, vertex.GetX());
			maxY = max(maxY, vertex.GetY());
			maxZ = max(maxZ, vertex.GetZ());
		}

		_minVertex = { minX, minY, minZ };
		_maxVertex = { maxX, maxY, maxZ };
	}
	void Model::RegisterMesh(MeshIndex index, MeshInterface* mesh)
	{
		_meshes.insert(std::make_pair(index, mesh));
	}
	void Model::RegisterMaterial(MaterialIndex index, Material* material)
	{
		_materials.insert(std::make_pair(index, material));
	}
	//void Model::RegisterAnimation(AnimationName name, Animation* animation)
	//{
	//	_animations.insert(std::make_pair(name, animation));
	//}
	//void Model::SetCurrentAnimation(AnimationName name)
	//{
	//	_currentAnimation = _animations.find(name)->second;
	//}
	void Model::SetVertexShader(VertexShader* shader)
	{
		_vs = shader;
		for (auto mesh : _meshes)
		{
			mesh.second->SetVertexShader(shader);
		}
	}
	void Model::SetPixelShader(PixelShader* shader)
	{
		_ps = shader;
	}
	Model::operator OBBData()
	{
		Vector3 tmp = _maxVertex - _minVertex;
		return OBBData{
			Vector3(), Matrix33(), Vector3(),
			tmp.GetX(), tmp.GetY(), tmp.GetZ()
		};
	}
	bool Model::Init()
	{
		//for (auto iter : _animations)
		//{
		//	iter.second->Init();
		//}

		for (auto mesh : _meshes)
		{
			mesh.second->Init();
			_meshElementMinMaxVertexList.push_back(mesh.second->GetMaxVertex());
			_meshElementMinMaxVertexList.push_back(mesh.second->GetMinVertex());
		}
		SizeCheck();

		return false;
	}
	bool Model::Frame()
	{
		//_currentAnimation->Frame();

		for (auto material : _materials)
		{
			material.second->Frame();
		}

		for (auto mesh : _meshes)
		{
			mesh.second->Frame();
		}

		return false;
	}
	bool Model::Render()
	{
		auto dc = g_dxWindow->GetDeviceContext();

		//_currentAnimation->Render();

		for (auto material : _materials)
		{
			material.second->Render();
		}

		for (auto mesh : _meshes)
		{
			mesh.second->Render();
		}

		_vs->Render();
		_ps->Render();

		return false;
	}
	bool Model::Release()
	{
		//_currentAnimation = &DefaultAnimation;
		//for (auto animation : _animations)
		//{
		//	if (animation.second != &DefaultAnimation)
		//	{
		//		animation.second->Release();
		//		delete animation.second;
		//	}
		//}
		//_animations.clear();


		for (auto mesh : _meshes)
		{
			mesh.second->Release();
		}
		_meshElementMinMaxVertexList.clear();

		_vs = nullptr;
		_ps = nullptr;

		return false;
	}
}

#include "Model.h"
#include "HCCalculator.h"
#include "DXWindow.h"
#include "ShaderManager.h"
#include "Mesh.hpp"

namespace SSB
{
    extern DXWindow* g_dxWindow;
	Animation Model::DefaultAnimation;

	Model::Model()
	{
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
	void Model::Initialize_RegisterMesh(MeshIndex index, MeshInterface* mesh)
	{
		_meshes.insert(std::make_pair(index, mesh));
	}
	void Model::Initialize_RegisterMaterial(MaterialIndex index, Material* material)
	{
		_materials.insert(std::make_pair(index, material));
	}
	void Model::Initialize_RegisterAnimation(AnimationName name, Animation* animation)
	{
		_animations.insert(std::make_pair(name, animation));
	}
	void Model::SetCurrentAnimation(AnimationName name)
	{
		if (_animations.find(name) != _animations.end())
		{
			_currentAnimation = _animations.find(name)->second;
		}
		else
		{
			_currentAnimation = &DefaultAnimation;
		}
	}
	void Model::SetVertexShader(VertexShader* shader)
	{
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
		DefaultAnimation.Init();
		_currentAnimation = &DefaultAnimation;

		for (auto mesh : _meshes)
		{
			_meshElementMinMaxVertexList.push_back(mesh.second->GetMaxVertex());
			_meshElementMinMaxVertexList.push_back(mesh.second->GetMinVertex());
		}
		SizeCheck();

		return false;
	}
	bool Model::Frame()
	{
		_currentAnimation->Frame();

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

		_currentAnimation->Render();

		_ps->Render();

		for (auto material : _materials)
		{
			material.second->Render();
		}

		for (auto mesh : _meshes)
		{
			mesh.second->Render();
		}

		return false;
	}
	bool Model::Release()
	{
		for (auto material : _materials)
		{
			material.second->Release();
			delete material.second;
		}
		_materials.clear();

		_currentAnimation = &DefaultAnimation;
		for (auto animation : _animations)
		{
			if (animation.second != &DefaultAnimation)
			{
				animation.second->Release();
				delete animation.second;
			}
		}
		_animations.clear();

		for (auto mesh : _meshes)
		{
			mesh.second->Release();
			delete mesh.second;
		}
		_meshes.clear();
		_meshElementMinMaxVertexList.clear();

		_ps = nullptr;

		return false;
	}
	std::string Model::Serialize(int tabCount)
	{
		std::string ret;

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "[\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _minVertexStr;
		ret += Serializeable::Serialize(tabCount + 2, _minVertex);
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _maxVertexStr;
		ret += Serializeable::Serialize(tabCount + 2, _maxVertex);
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _materialStr;
		for (auto iter : _materials)
		{
			ret += Serializeable::GetTabbedString(tabCount + 2);
			ret += _materialIndexStr;
			ret += "{\"";
			ret += std::to_string(iter.first);
			ret += "\"}\n";

			auto materialStr = iter.second->Serialize(tabCount + 2);
			ret += materialStr;
			ret += GetTabbedString(tabCount + 2);
			ret += ",\n";
		}
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _meshStr;
		for (auto iter : _meshes)
		{
			ret += Serializeable::GetTabbedString(tabCount + 2);
			ret += _meshIndexStr;
			ret += "{\"";
			ret += std::to_string(iter.first);
			ret += "\"}\n";

			auto meshStr = iter.second->Serialize(tabCount + 2);
			ret += meshStr;
			ret += GetTabbedString(tabCount + 2);
			ret += ",\n";
		}
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _animationStr;
		for (auto iter : _animations)
		{
			ret += Serializeable::GetTabbedString(tabCount + 2);
			ret += _animationNameStr;
			ret += "{\"";
			ret += iter.first;
			ret += "\"}\n";

			auto animationStr = iter.second->Serialize(tabCount + 2);
			ret += animationStr;
			ret += GetTabbedString(tabCount + 2);
			ret += ",\n";
		}
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _pixelShaderStr;
		ret += "{\"";
		ret += _ps->GetFileName();
		ret += "\"},\n";

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "]";

		return ret;
	}
	void Model::Deserialize(std::string serialedString)
	{
		serialedString = GetUnitObject(serialedString, 0).str;

		int offset = 0;
		{
			offset = serialedString.find(_minVertexStr);
			auto data = GetUnitElement(serialedString, offset);
			offset = data.offset;
			Float3 tmp;
			Serializeable::Deserialize(data.str, tmp);
			_minVertex = tmp;
		}

		{
			offset = serialedString.find(_maxVertexStr);
			auto data = GetUnitElement(serialedString, offset);
			offset = data.offset;
			Float3 tmp;
			Serializeable::Deserialize(data.str, tmp);
			_maxVertex = tmp;
		}

		while (serialedString.find(_materialIndexStr, offset) != std::string::npos)
		{
			int materialIndex;
			{
				offset = serialedString.find(_materialIndexStr, offset);
				auto data = GetUnitElement(serialedString, offset);
				offset = data.offset;
				Serializeable::Deserialize(data.str, materialIndex);
			}

			auto objectData = GetUnitObject(serialedString, offset);
			std::string objectStr = objectData.str;
			offset = objectData.offset;
			Material* mat = new Material;
			mat->Deserialize(objectStr);
			mat->Init();
			_materials.insert(std::make_pair(materialIndex, mat));
		}

		while (serialedString.find(_meshIndexStr, offset) != std::string::npos)
		{
			int meshIndex;
			{
				offset = serialedString.find(_meshIndexStr, offset);
				auto data = GetUnitElement(serialedString, offset);
				offset = data.offset;
				Serializeable::Deserialize(data.str, meshIndex);
			}

			auto objectData = GetUnitObject(serialedString, offset);
			std::string objectStr = objectData.str;

			std::string vertexType;
			{
				int tmpOffset = serialedString.find(_vertexTypeStr, offset);
				std::string tmp = GetUnitElement(serialedString, tmpOffset).str;
				vertexType = GetUnitAtomic(tmp, 0).str;
			}
			offset = objectData.offset;

			MeshInterface* mesh;
			if (vertexType == Vertex_PCNT_Keyword)
			{
				mesh = new Mesh_Vertex_PCNT;
			}
			else if (vertexType == Vertex_PCNT_Animatable_Keyword)
			{
				mesh = new Mesh_Vertex_PCNT_Animatable;
			}
			else if (vertexType == Vertex_PCNT_Skinning_Keyword)
			{
				mesh = new Mesh_Vertex_PCNT_Skinning;
			}
			else if (vertexType == Vertex_PCNTs_Keyword)
			{
				mesh = new Mesh_Vertex_PCNTs;
			}
			else if (vertexType == Vertex_PCNTs_Animatable_Keyword)
			{
				mesh = new Mesh_Vertex_PCNTs_Animatable;
			}
			else if (vertexType == Vertex_PCNTs_Skinning_Keyword)
			{
				mesh = new Mesh_Vertex_PCNTs_Skinning;
			}
			//if (vertexType == Vertex_PC_Keyword)
			else
			{
				mesh = new Mesh_Vertex_PC;
			}

			mesh->Deserialize(objectStr);
			mesh->Init();
			_meshes.insert(std::make_pair(meshIndex, mesh));
		}

		while (serialedString.find(_animationNameStr, offset) != std::string::npos)
		{
			AnimationName animationName;
			{
				offset = serialedString.find(_animationNameStr, offset);
				auto atomic = GetUnitElement(serialedString, offset);
				offset = atomic.offset;
				animationName = std::string(GetUnitAtomic(atomic.str, 0).str);
			}

			auto objectData = GetUnitObject(serialedString, offset);
			std::string objectStr = objectData.str;
			offset = objectData.offset;
			Animation* anim = new Animation;
			anim->Deserialize(objectStr);
			anim->Init();
			_animations.insert(std::make_pair(animationName, anim));
		}

		{
			offset = serialedString.find(_pixelShaderStr, offset);
			auto atomicData = GetUnitElement(serialedString, offset);
			std::string atomic = atomicData.str;
			_ps = ShaderManager::GetInstance().LoadPixelShader(mtw(GetUnitAtomic(atomic, 0).str), "PS", "ps_5_0");
		}
	}
}

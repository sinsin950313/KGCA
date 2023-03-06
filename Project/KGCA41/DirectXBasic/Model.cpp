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
		ret += "Min Vertex\n";
		ret += Serializeable::Serialize(tabCount + 2, _minVertex);
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Max Vertex\n";
		ret += Serializeable::Serialize(tabCount + 2, _maxVertex);
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Material\n";
		for (auto iter : _materials)
		{
			ret += Serializeable::GetTabbedString(tabCount + 2);
			ret += "Material Index : ";
			ret += std::to_string(iter.first);
			ret += "\n";

			auto materialStr = iter.second->Serialize(tabCount + 2);
			ret += materialStr;
			ret += GetTabbedString(tabCount + 2);
			ret += ",\n";
		}
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Mesh\n";
		for (auto iter : _meshes)
		{
			ret += Serializeable::GetTabbedString(tabCount + 2);
			ret += "Mesh Index : ";
			ret += std::to_string(iter.first);
			ret += "\n";

			auto meshStr = iter.second->Serialize(tabCount + 2);
			ret += meshStr;
			ret += GetTabbedString(tabCount + 2);
			ret += ",\n";
		}
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Animation\n";
		for (auto iter : _animations)
		{
			ret += Serializeable::GetTabbedString(tabCount + 2);
			ret += "Animation Name : ";
			ret += iter.first;
			ret += "\n";

			auto animationStr = iter.second->Serialize(tabCount + 2);
			ret += animationStr;
			ret += GetTabbedString(tabCount + 2);
			ret += ",\n";
		}
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Pixel Shader File Name : ";
		ret += _ps->GetFileName();
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "]";

		return ret;
	}
	void Model::Deserialize(std::string serialedString)
	{
		{
			std::regex re(R"(\s*Min Vertex\n\s*\{[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+\}\n)");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			re = R"(\{[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+\})";
			std::regex_search(str, match, re);

			Float3 tmp;
			DeSerialize(match.str(), tmp);
			_minVertex = tmp;
		}

		{
			std::regex re(R"(\s*Max Vertex\n\s*\{[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+\}\n)");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			re = R"(\{[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+\})";
			std::regex_search(str, match, re);

			Float3 tmp;
			DeSerialize(match.str(), tmp);
			_maxVertex = tmp;
		}

		{
			std::regex re(R"~(\s*Material\s*Index\s*:\s*[0-9]+\s*\[[\s\S]*?\]\s*,)~");
			std::smatch match;

			while (std::regex_search(serialedString, match, re))
			{
				std::string materialDataStr = match.str();
				serialedString = match.suffix();

				int materialIndex;
				{
					std::regex re(R"(\s*Material Index : [0-9]+\n)");
					std::smatch match;

					std::regex_search(materialDataStr, match, re);
					std::string materialIndexStr = match.str();
					materialDataStr = match.suffix();

					re = R"([0-9]+)";
					std::regex_search(materialIndexStr, match, re);
					materialIndex = std::stoi(match.str());
				}

				{
					std::string materialDataPack;
					std::regex materialDataPackReg(R"~(\[[\s\S]+\])~");

					{
						std::regex_search(materialDataStr, match, materialDataPackReg);
						Material* mat = new Material;
						mat->Deserialize(match.str());
						mat->Init();
						_materials.insert(std::make_pair(materialIndex, mat));
					}
				}
			}
		}

		{
			std::regex re(R"~(\s*Mesh\s*Index\s*:\s*[0-9]+\s*\[[\s\S]*?\]\s*,)~");
			std::smatch match;

			while (std::regex_search(serialedString, match, re))
			{
				std::string meshDataStr = match.str();
				serialedString = match.suffix();

				int meshIndex;
				{
					std::regex tmpReg(R"(Mesh Index : [0-9]+)");
					std::smatch match;

					std::regex_search(meshDataStr, match, tmpReg);
					std::string meshIndexStr = match.str();
					meshDataStr = match.suffix();

					std::regex tmpReg1("[0-9]+");
					std::regex_search(meshIndexStr, match, tmpReg1);
					meshIndex = std::stoi(match.str());
				}

				{
					std::string meshDataPack;
					std::regex meshDataPackReg(R"(\[\s([\s\S]+)\])");
					if (std::regex_search(meshDataStr, match, meshDataPackReg))
					{
						meshDataStr = match.str();

						std::string vertexType;
						{
							std::regex vertexTypeReg(R"(Vertex Type : .*,\n)");
							std::regex_search(meshDataStr, match, vertexTypeReg);

							std::string tmp = match.str();
							int offset = 14;
							while (tmp[offset] != ',')
							{
								vertexType += tmp[offset];
								++offset;
							}
						}

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

						mesh->Deserialize(meshDataStr);
						mesh->Init();
						_meshes.insert(std::make_pair(meshIndex, mesh));
					}
				}
			}
		}

		{
			//std::regex re(R"(Animation Name : [\s\S]+\[[\s\S]+\]\s+,)");
			std::regex re(R"~(\s*Animation\s*Name\s*:\s*[0-9]+\s*\[[\s\S]*?\]\s*,)~");
			std::smatch match;

			while (std::regex_search(serialedString, match, re))
			{
				serialedString = match.suffix();
				std::string animationDataStr = match.str();

				std::string animationName;
				{
					std::regex animationNameReg(R"(Animation Name : \n)");
					std::smatch match;

					std::regex_search(animationDataStr, match, animationNameReg);
					std::string animationNameStr = match.str();
					animationDataStr = match.suffix();

					std::string tmp = match.str();
					int offset = 17;
					while (tmp[offset] != '\n')
					{
						animationName += tmp[offset];
						++offset;
					}
				}

				Animation* animation = new Animation;
				animation->Deserialize(animationDataStr);
				animation->Init();
				_animations.insert(std::make_pair(animationName, animation));
			}
		}

		{
			std::regex re(R"(Pixel Shader File Name : [\s\S]*?.hlsl,)");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			std::string tmp = "Pixel Shader File Name : ";
			int offset = tmp.size();
			std::string pixelShaderFileName;
			while (str[offset] != ',')
			{
				pixelShaderFileName += str[offset];
				++offset;
			}

			_ps = ShaderManager::GetInstance().LoadPixelShader(mtw(pixelShaderFileName), "PS", "ps_5_0");
		}
	}
}

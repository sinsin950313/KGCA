#include "Model.h"
#include "DXWindow.h"
#include "ShaderManager.h"
#include "Mesh.hpp"
#include "Common.h"

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
	void Model::Initialize_RegisterSocket(SocketName name, BoneIndex index)
	{
		_sockets.insert(std::make_pair(name, index));
	}
	void Model::Initialize_SetBoundingVolume(OBBData data)
	{
		_boundingVolume = data;
	}
	void Model::Initialize_SetSkeleton(Skeleton* skeleton)
	{
		_skeleton = skeleton;
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
	HMatrix44 Model::GetSocketCurrentMatrix(SocketName name)
	{
		if (_sockets.find(name) != _sockets.end())
		{
			return _currentAnimation->GetCurrentBoneMatrix(_sockets.find(name)->second);
		}
		return HMatrix44();
	}
	OBBData Model::GetBoundingVolume()
	{
		return _boundingVolume;
	}
	Model::operator OBBData()
	{
		// Not OBB - This is AABB
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
		if (_skeleton != nullptr && _currentAnimation == &DefaultAnimation)
		{
			_skeleton->Render();
		}

		if (_ps != nullptr)
		{
			_ps->Render();
		}

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
	std::string Model::SerializeText(int tabCount)
	{
		std::string ret;

		ret += SerializeableText::GetTabbedStringText(tabCount);
		ret += "[\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _minVertexStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _minVertex);
		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _maxVertexStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _maxVertex);
		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _socketDataStr;
		ret += "{\"";
		ret += std::to_string(_sockets.size());
		ret += "\"}\n";
		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += "{\n";
		for (auto socket : _sockets)
		{
			ret += SerializeableText::GetTabbedStringText(tabCount + 2);
			ret += "\"";
			ret += socket.first;
			ret += "\"";
			ret += " : ";
			ret += "\"";
			ret += std::to_string(socket.second);
			ret += "\",\n";
		}
		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += "},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _boundingVolumeStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _boundingVolume.Position);
		ret += SerializeableText::SerializeText(tabCount + 2, _boundingVolume.Rotation);
		ret += SerializeableText::SerializeText(tabCount + 2, _boundingVolume.Scale);
		Float3 boundingVolumeData{ _boundingVolume.Width, _boundingVolume.Height, _boundingVolume.Depth };
		ret += SerializeableText::SerializeText(tabCount + 2, boundingVolumeData);
		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _materialStr;
		for (auto iter : _materials)
		{
			ret += SerializeableText::GetTabbedStringText(tabCount + 2);
			ret += _materialIndexStr;
			ret += "{\"";
			ret += std::to_string(iter.first);
			ret += "\"}\n";

			auto materialStr = iter.second->SerializeText(tabCount + 2);
			ret += materialStr;
			ret += GetTabbedStringText(tabCount + 2);
			ret += ",\n";
		}
		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _meshStr;
		for (auto iter : _meshes)
		{
			ret += SerializeableText::GetTabbedStringText(tabCount + 2);
			ret += _meshIndexStr;
			ret += "{\"";
			ret += std::to_string(iter.first);
			ret += "\"}\n";

			auto meshStr = iter.second->SerializeText(tabCount + 2);
			ret += meshStr;
			ret += GetTabbedStringText(tabCount + 2);
			ret += ",\n";
		}
		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _animationStr;
		for (auto iter : _animations)
		{
			ret += SerializeableText::GetTabbedStringText(tabCount + 2);
			ret += _animationNameStr;
			ret += "{\"";
			ret += iter.first;
			ret += "\"}\n";

			auto animationStr = iter.second->SerializeText(tabCount + 2);
			ret += animationStr;
			ret += GetTabbedStringText(tabCount + 2);
			ret += ",\n";
		}
		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _pixelShaderStr;
		ret += "{\"";
		ret += _ps->GetFileName();
		ret += "\"},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount);
		ret += "]";

		return ret;
	}
	void Model::DeserializeText(std::string& serialedString)
	{
		serialedString = GetUnitObjectText(serialedString, 0).str;

		int offset = 0;
		{
			offset = serialedString.find(_minVertexStr);
			auto data = GetUnitElementText(serialedString, offset);
			offset = data.offset;
			Float3 tmp;
			SerializeableText::DeserializeText(data.str, tmp);
			_minVertex = tmp;
		}

		{
			offset = serialedString.find(_maxVertexStr);
			auto data = GetUnitElementText(serialedString, offset);
			offset = data.offset;
			Float3 tmp;
			SerializeableText::DeserializeText(data.str, tmp);
			_maxVertex = tmp;
		}

		{
			offset = serialedString.find(_socketDataStr);
			auto data = GetUnitElementText(serialedString, offset);
			offset = data.offset;
			int socketCount;
			SerializeableText::DeserializeText(data.str, socketCount);
			for (int i = 0; i < socketCount; ++i)
			{
				auto socketNameData = GetUnitAtomicText(serialedString, offset);
				offset = socketNameData.offset;
				auto boneIndexData = GetUnitAtomicText(serialedString, offset);
				offset = boneIndexData.offset;

				_sockets.insert(std::make_pair(socketNameData.str, std::stoi(boneIndexData.str)));
			}
		}

		offset = serialedString.find(_boundingVolumeStr);
		{
			auto data = GetUnitElementText(serialedString, offset);
			offset = data.offset;
			Float3 pos;
			SerializeableText::DeserializeText(data.str, pos);

			_boundingVolume.Position = pos;
		}

		{
			auto data = GetUnitElementText(serialedString, offset);
			offset = data.offset;
			Float33 rot;
			SerializeableText::DeserializeText(data.str, rot);

			_boundingVolume.Rotation = rot;
		}

		{
			auto data = GetUnitElementText(serialedString, offset);
			offset = data.offset;
			Float3 scale;
			SerializeableText::DeserializeText(data.str, scale);

			_boundingVolume.Scale = scale;
		}

		{
			auto data = GetUnitElementText(serialedString, offset);
			offset = data.offset;
			Float3 tmp;
			SerializeableText::DeserializeText(data.str, tmp);

			_boundingVolume.Width = tmp.x;
			_boundingVolume.Height = tmp.y;
			_boundingVolume.Depth = tmp.z;
		}

		while (serialedString.find(_materialIndexStr, offset) != std::string::npos)
		{
			int materialIndex;
			{
				offset = serialedString.find(_materialIndexStr, offset);
				auto data = GetUnitElementText(serialedString, offset);
				offset = data.offset;
				SerializeableText::DeserializeText(data.str, materialIndex);
			}

			auto objectData = GetUnitObjectText(serialedString, offset);
			std::string objectStr = objectData.str;
			offset = objectData.offset;
			Material* mat = new Material;
			mat->DeserializeText(objectStr);
			mat->Init();
			_materials.insert(std::make_pair(materialIndex, mat));
		}

		while (serialedString.find(_meshIndexStr, offset) != std::string::npos)
		{
			int meshIndex;
			{
				offset = serialedString.find(_meshIndexStr, offset);
				auto data = GetUnitElementText(serialedString, offset);
				offset = data.offset;
				SerializeableText::DeserializeText(data.str, meshIndex);
			}

			auto objectData = GetUnitObjectText(serialedString, offset);
			std::string objectStr = objectData.str;

			std::string vertexType;
			{
				int tmpOffset = serialedString.find(_vertexTypeStr, offset);
				std::string tmp = GetUnitElementText(serialedString, tmpOffset).str;
				vertexType = GetUnitAtomicText(tmp, 0).str;
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

			mesh->DeserializeText(objectStr);
			mesh->Init();
			_meshes.insert(std::make_pair(meshIndex, mesh));
		}

		while (serialedString.find(_animationNameStr, offset) != std::string::npos)
		{
			AnimationName animationName;
			{
				offset = serialedString.find(_animationNameStr, offset);
				auto atomic = GetUnitElementText(serialedString, offset);
				offset = atomic.offset;
				animationName = std::string(GetUnitAtomicText(atomic.str, 0).str);
			}

			auto objectData = GetUnitObjectText(serialedString, offset);
			std::string objectStr = objectData.str;
			offset = objectData.offset;
			Animation* anim = new Animation;
			anim->DeserializeText(objectStr);
			anim->Init();
			_animations.insert(std::make_pair(animationName, anim));
		}

		{
			offset = serialedString.find(_pixelShaderStr, offset);
			auto atomicData = GetUnitElementText(serialedString, offset);
			std::string atomic = atomicData.str;
			_ps = ShaderManager::GetInstance().LoadPixelShader(mtw(GetUnitAtomicText(atomic, 0).str), "PS", "ps_5_0");
		}
	}

	std::string Model::SerializeBinary()
	{
		std::string ret;

		// Min Vertex
		{
			Float3 tmp{ _minVertex.GetX(), _minVertex.GetY(), _minVertex.GetZ() };
			int size = sizeof(tmp);
			char* buf = new char[size];
			memcpy(buf, &tmp, size);
			ret += std::string(buf, size);
			delete buf;
		}

		// Max Vertex
		{
			Float3 tmp{ _maxVertex.GetX(), _maxVertex.GetY(), _maxVertex.GetZ() };
			int size = sizeof(tmp);
			char* buf = new char[size];
			memcpy(buf, &tmp, size);
			ret += std::string(buf, size);
			delete buf;
		}

		// Material
		{
			{
				int tmpSize = _materials.size();
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
			for(auto material : _materials)
			{
			{
				int tmpSize = material.first;
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
				ret += material.second->SerializeBinary();
			}
		}

		// Mesh
		{
			{
				int tmpSize = _meshes.size();
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
			for (auto mesh : _meshes)
			{
				{
					int tmpSize = mesh.first;
					char* tmpBuffer = new char[sizeof(int)];
					memcpy(tmpBuffer, &tmpSize, sizeof(int));
					std::string tmpStr(tmpBuffer, sizeof(int));
					ret += tmpStr;
					delete tmpBuffer;
				}
				{
					int tmpSize = mesh.second->GetVertexType().size();
					char* tmpBuffer = new char[sizeof(int)];
					memcpy(tmpBuffer, &tmpSize, sizeof(int));
					std::string tmpStr(tmpBuffer, sizeof(int));
					ret += tmpStr;
					delete tmpBuffer;
				}
				ret += mesh.second->GetVertexType();
				ret += mesh.second->SerializeBinary();
			}
		}

		// Animation
		{
			{
				int tmpSize = _animations.size();
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
			for (auto animation : _animations)
			{
				{
					int tmpSize = animation.first.size();
					char* tmpBuffer = new char[sizeof(int)];
					memcpy(tmpBuffer, &tmpSize, sizeof(int));
					std::string tmpStr(tmpBuffer, sizeof(int));
					ret += tmpStr;
					delete tmpBuffer;

					ret += animation.first;
				}
				ret += animation.second->SerializeBinary();
			}
		}

		// Pixel Shader
		{
			{
				int tmpSize = _ps->GetFileName().size();
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
			ret += _ps->GetFileName();
		}

		// Socket
		{
			{
				int tmpSize = (int)_sockets.size();
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
			for (auto socket : _sockets)
			{
				ret += (int)socket.first.size();
				ret += socket.first;
				ret += socket.second;
			}
		}

		// Bounding Volume
		{
			// Position
			{
				Float3 tmp{ _boundingVolume.Position.GetX(), _boundingVolume.Position.GetY(), _boundingVolume.Position.GetZ() };
				int size = sizeof(tmp);
				char* buf = new char[size];
				memcpy(buf, &tmp, size);
				ret += std::string(buf, size);
				delete buf;
			}
			// Rotation
			{
				Float33 tmp{ 
					_boundingVolume.Rotation.GetRow(0).GetX(), _boundingVolume.Rotation.GetRow(0).GetY(), _boundingVolume.Rotation.GetRow(0).GetZ(),
					_boundingVolume.Rotation.GetRow(1).GetX(), _boundingVolume.Rotation.GetRow(1).GetY(), _boundingVolume.Rotation.GetRow(1).GetZ(),
					_boundingVolume.Rotation.GetRow(2).GetX(), _boundingVolume.Rotation.GetRow(2).GetY(), _boundingVolume.Rotation.GetRow(2).GetZ(),
				};
				int size = sizeof(tmp);
				char* buf = new char[size];
				memcpy(buf, &tmp, size);
				ret += std::string(buf, size);
				delete buf;
			}
			// Scale
			{
				Float3 tmp{ _boundingVolume.Scale.GetX(), _boundingVolume.Scale.GetY(), _boundingVolume.Scale.GetZ() };
				int size = sizeof(tmp);
				char* buf = new char[size];
				memcpy(buf, &tmp, size);
				ret += std::string(buf, size);
				delete buf;
			}
			// Width, Height, Depth
			{
				Float3 tmp{ _boundingVolume.Width, _boundingVolume.Height, _boundingVolume.Depth };
				int size = sizeof(tmp);
				char* buf = new char[size];
				memcpy(buf, &tmp, size);
				ret += std::string(buf, size);
				delete buf;
			}
		}

		return ret;
	}

	void Model::DeserializeBinary(const char* buffer, int size, int& offset)
	{
		// Min Vertex
		{
			Float3 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float3));
			_minVertex = tmp;
			offset += sizeof(Float3);
		}

		// Max Vertex
		{
			Float3 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float3));
			_maxVertex = tmp;
			offset += sizeof(Float3);
		}

		// Material
		{
			int materialCount;
			memcpy(&materialCount, buffer + offset, sizeof(int));
			offset += sizeof(int);

			for (int i = 0; i < materialCount; ++i)
			{
				int materialIndex;
				memcpy(&materialIndex, buffer + offset, sizeof(int));
				offset += sizeof(int);

				Material* tmp = new Material;
				tmp->DeserializeBinary(buffer, size, offset);
				tmp->Init();
				_materials.insert(std::make_pair(materialIndex, tmp));
			}
		}

		// Mesh
		{
			int meshCount;
			memcpy(&meshCount, buffer + offset, sizeof(int));
			offset += sizeof(int);

			for (int i = 0; i < meshCount; ++i)
			{
				int meshIndex;
				{
					memcpy(&meshIndex, buffer + offset, sizeof(int));
					offset += sizeof(int);
				}

				std::string vertexType;

				int vertexTypeSize;
				memcpy(&vertexTypeSize, buffer + offset, sizeof(int));
				offset += sizeof(int);
				{
					char* meshTypeStr = new char[vertexTypeSize];
					memcpy(meshTypeStr, buffer + offset, vertexTypeSize);
					offset += vertexTypeSize;

					vertexType = std::string(meshTypeStr, vertexTypeSize);
					delete meshTypeStr;
				}

				MeshInterface* tmp;
				if (vertexType == Vertex_PCNT_Keyword)
				{
					tmp = new Mesh_Vertex_PCNT;
				}
				else if (vertexType == Vertex_PCNT_Animatable_Keyword)
				{
					tmp = new Mesh_Vertex_PCNT_Animatable;
				}
				else if (vertexType == Vertex_PCNT_Skinning_Keyword)
				{
					tmp = new Mesh_Vertex_PCNT_Skinning;
				}
				else if (vertexType == Vertex_PCNTs_Keyword)
				{
					tmp = new Mesh_Vertex_PCNTs;
				}
				else if (vertexType == Vertex_PCNTs_Animatable_Keyword)
				{
					tmp = new Mesh_Vertex_PCNTs_Animatable;
				}
				else if (vertexType == Vertex_PCNTs_Skinning_Keyword)
				{
					tmp = new Mesh_Vertex_PCNTs_Skinning;
				}
				//if (vertexType == Vertex_PC_Keyword)
				else
				{
					tmp = new Mesh_Vertex_PC;
				}

				tmp->DeserializeBinary(buffer, size, offset);
				tmp->Init();
				_meshes.insert(std::make_pair(meshIndex, tmp));
			}
		}

		// Animation
		{
			int animationCount;
			memcpy(&animationCount, buffer + offset, sizeof(int));
			offset += sizeof(int);

			for (int i = 0; i < animationCount; ++i)
			{
				Animation* tmp = new Animation;
				std::string animationName;
				{
					int animationNameSize;
					memcpy(&animationNameSize, buffer + offset, sizeof(int));
					offset += sizeof(int);

					char* animationNameBuffer = new char[animationNameSize];
					memcpy(animationNameBuffer, buffer + offset, animationNameSize);
					offset += animationNameSize;
					animationName = std::string(animationNameBuffer, animationNameSize);
					delete animationNameBuffer;
				}
				tmp->DeserializeBinary(buffer, size, offset);
				tmp->Init();
				_animations.insert(std::make_pair(animationName, tmp));
			}
		}

		// Pixel Shader
		{
			int pixelShaderFileNameCount;
			memcpy(&pixelShaderFileNameCount, buffer + offset, sizeof(int));
			offset += sizeof(int);

			char* fileNameBuffer = new char[pixelShaderFileNameCount];
			memcpy(fileNameBuffer, buffer + offset, pixelShaderFileNameCount);
			offset += pixelShaderFileNameCount;
			std::string tmpFileName(fileNameBuffer, pixelShaderFileNameCount);
			std::wstring fileName = mtw(tmpFileName);
			_ps = ShaderManager::GetInstance().LoadPixelShader(fileName, "PS", "ps_5_0");
			delete fileNameBuffer;
		}

		// Socket
		{
			int socketCount;
			memcpy(&socketCount, buffer + offset, sizeof(int));
			offset += sizeof(int);

			for (int i = 0; i < socketCount; ++i)
			{
				int socketNameCount;
				memcpy(&socketNameCount, buffer + offset, sizeof(int));
				offset += sizeof(int);

				char* socketNameBuffer = new char[socketNameCount];
				memcpy(&socketNameBuffer, buffer + offset, sizeof(socketNameCount));
				std::string socketName(socketNameBuffer, socketNameCount);
				offset += socketNameCount;

				int socketIndex;
				memcpy(&socketIndex, buffer + offset, sizeof(int));
				offset += sizeof(int);

				_sockets.insert(std::make_pair(socketName, socketIndex));
				delete socketNameBuffer;
			}
		}

		// Bounding Volume
		{
			// Position
			{
				Float3 tmp;
				memcpy(&tmp, buffer + offset, sizeof(Float3));
				offset += sizeof(Float3);
				_boundingVolume.Position = tmp;
			}
			// Rotation
			{
				Float33 tmp;
				memcpy(&tmp, buffer + offset, sizeof(Float33));
				offset += sizeof(Float33);
				_boundingVolume.Rotation = tmp;
			}
			// Scale
			{
				Float3 tmp;
				memcpy(&tmp, buffer + offset, sizeof(Float3));
				offset += sizeof(Float3);
				_boundingVolume.Scale = tmp;
			}
			// Width, Height, Depth
			{
				Float3 tmp;
				memcpy(&tmp, buffer + offset, sizeof(Float3));
				offset += sizeof(Float3);
				_boundingVolume.Width = tmp.x;
				_boundingVolume.Height = tmp.y;
				_boundingVolume.Depth = tmp.z;
			}
		}
	}

	EditableObject<Model>* Model::GetEditableObject()
	{
		EditableModelData data;

		for (auto mesh : _meshes)
		{
			data.Meshes.insert(std::make_pair(mesh.first, mesh.second->Clone()));
		}
		data.Sockets = _sockets;
		data.PixelShaderFileName = _ps->GetFileName();
		data.BoundingVolume = _boundingVolume;

		for (auto material : _materials)
		{
			data.Materials.insert(std::make_pair(material.first, material.second->Clone()));
		}
		for (auto animation : _animations)
		{
			data.Animations.insert(std::make_pair(animation.first, animation.second->Clone()));
		}

		return new EditableModelObject(data);
	}
	EditableModelObject::EditableModelObject(EditableModelData data)
		: _meshes(data.Meshes), _sockets(data.Sockets), _pixelShaderFileName(data.PixelShaderFileName), _boundingVolume(data.BoundingVolume), _materials(data.Materials), _animations(data.Animations)
	{
	}
	std::map<SocketName, BoneIndex> EditableModelObject::GetSockets()
	{
		return _sockets;
	}
	std::string EditableModelObject::GetPixelShaderFileName()
	{
		return _pixelShaderFileName;
	}
	OBBData EditableModelObject::GetBoundingVolumeData()
	{
		return _boundingVolume;
	}
	std::map<MeshIndex, MeshInterface*> EditableModelObject::GetMeshes()
	{
		std::map<MeshIndex, MeshInterface*> ret;
		for (auto mesh : _meshes)
		{
			ret.insert(std::make_pair(mesh.first, mesh.second->Clone()));
		}
		return ret;
	}
	std::map<MaterialIndex, Material*> EditableModelObject::GetMaterials()
	{
		std::map<MaterialIndex, Material*> ret;
		for (auto material : _materials)
		{
			ret.insert(std::make_pair(material.first, material.second->Clone()));
		}

		return ret;
	}
	std::map<AnimationName, Animation*> EditableModelObject::GetAnimations()
	{
		std::map<AnimationName, Animation*> ret;
		for (auto animation : _animations)
		{
			ret.insert(std::make_pair(animation.first, animation.second->Clone()));
		}

		return ret;
	}
	void EditableModelObject::ResizeBoundingVolume(OBBData data)
	{
		_boundingVolume = data;
	}
	void EditableModelObject::ChangePixelShaderFile(std::string fileName)
	{
		_pixelShaderFileName = fileName;
	}
	Model* EditableModelObject::GetResult()
	{
		Model* ret = new Model;

		for (auto socket : _sockets)
		{
			ret->Initialize_RegisterSocket(socket.first, socket.second);
		}

		ret->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(mtw(_pixelShaderFileName), "PS", "ps_5_0"));

		ret->Initialize_SetBoundingVolume(_boundingVolume);

		return ret;
	}
}

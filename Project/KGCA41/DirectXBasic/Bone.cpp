#include "Bone.h"
#include "DXWindow.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

	bool Skeleton::CreateBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(BoneSet);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = _boneSet;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_buffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
        return true;
	}

	void Skeleton::AddBone(BoneIndex index, BoneInfo info)
	{
		Bone* newBone = new Bone;
		newBone->SetInfo(info);
		//if (_bones.size() != 0)
		if (_bones.find(info.ParentIndex) != _bones.end())
		{
			newBone->SetParent(info.ParentIndex, _bones.find(info.ParentIndex)->second);
		}
		_bones.insert(std::make_pair(index, newBone));

		_boneSet->_boneUnits[index] = newBone->GetWorldMatrix().Transpose();
	}

	Skeleton::Skeleton()
	{
		_boneSet = new BoneSet;
	}

	Skeleton::~Skeleton()
	{
		Release();
		if (_boneSet != nullptr)
		{
			delete _boneSet;
		}
	}

	void Skeleton::Initialize_SetBoneData(std::map<BoneIndex, BoneInfo> bones)
	{
		for (auto bone : bones)
		{
			AddBone(bone.first, bone.second);
		}
	}
	HMatrix44 Skeleton::GetWorldMatrix(BoneIndex index)
	{
		return _bones.find(index)->second->GetWorldMatrix();
	}
	bool Skeleton::Init()
	{
		CreateBuffer();

		return true;
	}
	bool Skeleton::Frame()
	{
		return false;
	}
	bool Skeleton::Render()
	{
		g_dxWindow->GetDeviceContext()->VSSetConstantBuffers(3, 1, &_buffer);
		return true;
	}
	bool Skeleton::Release()
	{
		if (_buffer)
		{
			_buffer->Release();
			_buffer = nullptr;
		}

		return true;
	}
	EditableObject<Skeleton>* Skeleton::GetEditableObject()
	{
		EditableSkeletonData data;
		for (auto bone : _bones)
		{
			BoneInfo info;
			info.Name = bone.second->GetName();
			info.ParentIndex = bone.second->GetParentIndex();
			info.LocalMatrix = bone.second->GetLocalMatrix();

			data.Bones.insert(std::make_pair(bone.first, info));
		}

		return new EditableSkeletonObject(data);
	}
	void Skeleton::Bone::SetInfo(BoneInfo info)
	{
		_name = info.Name;
		_parentIndex = info.ParentIndex;
		_localMatrix = info.LocalMatrix;
	}
	void Skeleton::Bone::SetParent(BoneIndex parentIndex, Bone* parentBone)
	{
		_parentIndex = parentIndex;
		_parentBone = parentBone;
	}
	BoneName Skeleton::Bone::GetName()
	{
		return _name;
	}
	HMatrix44 Skeleton::Bone::GetLocalMatrix()
	{
		return _localMatrix;
	}
	BoneIndex Skeleton::Bone::GetParentIndex()
	{
		return _parentIndex;
	}
	HMatrix44 Skeleton::Bone::GetWorldMatrix()
	{
		if (_parentBone == nullptr)
		{
			return _localMatrix;
		}
		return _localMatrix * _parentBone->GetWorldMatrix();
	}
	std::string Skeleton::Bone::SerializeText(int tabCount)
	{
		std::string ret;

		ret += SerializeableText::GetTabbedStringText(tabCount);
		ret += "{\n";

		ret += SerializeableText::SerializeText(tabCount + 1, _parentIndex);

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += "\"";
		ret += _name;
		ret += "\"\n";

		Float44 tmp = _localMatrix;
		ret += SerializeableText::SerializeText(tabCount + 1, tmp);

		ret += SerializeableText::GetTabbedStringText(tabCount);
		ret += "}\n";

		return ret;
	}
	void Skeleton::Bone::DeserializeText(std::string& serialedString)
	{
		serialedString = GetUnitElementText(serialedString, 0).str;

		int offset = 1;
		{
			auto data = GetUnitElementText(serialedString, offset);
			offset = data.offset;
			SerializeableText::DeserializeText(data.str, _parentIndex);
		}
		{
			auto data = GetUnitAtomicText(serialedString, offset);
			offset = data.offset;
			_name = data.str;
		}
		{
			auto data = GetUnitElementText(serialedString, offset);
			offset = data.offset;
			Float44 tmp;
			SerializeableText::DeserializeText(data.str, tmp);
			_localMatrix = HMatrix44(
				tmp.e11, tmp.e12, tmp.e13, tmp.e14,
				tmp.e21, tmp.e22, tmp.e23, tmp.e24,
				tmp.e31, tmp.e32, tmp.e33, tmp.e34,
				tmp.e41, tmp.e42, tmp.e43, tmp.e44
			);
		}
	}
	std::string Skeleton::Bone::SerializeBinary()
	{
		std::string ret;

		{
			ret += _parentIndex;
		}

		{
			ret += (int)_name.size();
			ret += _name;
		}

		{
			Float44 mat = _localMatrix;
			char* tmpBuffer = new char[sizeof(Float44)];
			memcpy(tmpBuffer, &mat, sizeof(Float44));
			std::string tmp(tmpBuffer, sizeof(Float44));
			ret += tmp;
			delete tmpBuffer;
		}

		return ret;
	}
	void Skeleton::Bone::DeserializeBinary(const char* buffer, int size, int& offset)
	{
		{
			memcpy(&_parentIndex, buffer + offset, sizeof(int));
			offset += sizeof(int);
		}

		{
			int nameSize;
			memcpy(&nameSize, buffer + offset, sizeof(int));
			offset += sizeof(int);

			char* tmpBuffer = new char[nameSize];
			memcpy(tmpBuffer, buffer + offset, nameSize);
			offset += nameSize;
			std::string tmp(tmpBuffer, nameSize);
			_name = tmp;
			delete tmpBuffer;
		}

		{
			Float44 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float44));
			offset += sizeof(Float44);
			_localMatrix = {
				tmp.e11, tmp.e12, tmp.e13, tmp.e14,
				tmp.e21, tmp.e22, tmp.e23, tmp.e24,
				tmp.e31, tmp.e32, tmp.e33, tmp.e34,
				tmp.e41, tmp.e42, tmp.e43, tmp.e44,
			};
		}
	}
	std::string Skeleton::SerializeText(int tabCount)
	{
		std::string ret;

		ret += SerializeableText::GetTabbedStringText(tabCount);
		ret += "[\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(_bones.size());
		ret += "\"}\n";

		for (auto bone : _bones)
		{
			ret += SerializeableText::GetTabbedStringText(tabCount + 1);
			ret += "{\"";
			ret += std::to_string(bone.first);
			ret += "\"\n";
			ret += bone.second->SerializeText(tabCount + 2);
			ret += SerializeableText::GetTabbedStringText(tabCount + 1);
			ret += "},\n";
		}

		ret += SerializeableText::GetTabbedStringText(tabCount);
		ret += "]\n";

		return ret;
	}
	void Skeleton::DeserializeText(std::string& serialedString)
	{
		serialedString = GetUnitObjectText(serialedString, 0).str;

		int boneCount;
		int offset = 0;
		{
			auto data = GetUnitElementText(serialedString, offset);
			offset = data.offset;
			SerializeableText::DeserializeText(data.str, boneCount);
		}

		Bone dummyBone;
		for (int i = 0; i < boneCount; ++i)
		{
			int boneIndex;
			auto indexData = GetUnitAtomicText(serialedString, offset);
			offset = indexData.offset;
			boneIndex = stoi(indexData.str);

			auto data = GetUnitElementText(serialedString, offset);
			offset = data.offset;
			dummyBone.DeserializeText(data.str);

			BoneInfo info;
			info.Name = dummyBone.GetName();
			info.LocalMatrix = dummyBone.GetLocalMatrix();
			info.ParentIndex = dummyBone.GetParentIndex();
			AddBone(boneIndex, info);
		}
	}
	std::string Skeleton::SerializeBinary()
	{
		std::string ret;

		ret += (int)_bones.size();
		for (auto bone : _bones)
		{
			ret += bone.first;
			ret += bone.second->SerializeBinary();
		}

		return ret;
	}
	void Skeleton::DeserializeBinary(const char* buffer, int size, int& offset)
	{
		int boneCount;
		{
			memcpy(&boneCount, buffer + offset, sizeof(int));
			offset += sizeof(int);
		}

		for (int i = 0; i < boneCount; ++i)
		{
			int boneIndex;
			memcpy(&boneIndex, buffer + offset, sizeof(int));
			offset += sizeof(int);

			Bone* bone = new Bone;
			bone->DeserializeBinary(buffer, size, offset);

			_bones.insert(std::make_pair(boneIndex, bone));
		}
	}
	EditableSkeletonObject::EditableSkeletonObject(EditableSkeletonData data) : _bones(data.Bones)/*, _sockets(data.Sockets)*/
	{
	}
	BoneIndex EditableSkeletonObject::AddSocket(BoneInfo info)
	{
		BoneIndex index = _bones.size();
		_bones.insert(std::make_pair(index, info));

		return index;
	}
	std::map<BoneIndex, BoneInfo> EditableSkeletonObject::GetBones()
	{
		return _bones;
	}
	Skeleton* EditableSkeletonObject::GetResult()
	{
		Skeleton* ret = new Skeleton;

		ret->Initialize_SetBoneData(_bones);

		return ret;
	}
}
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
		if (_bones.size() != 0)
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
	std::string Skeleton::Bone::Serialize(int tabCount)
	{
		std::string ret;

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "{\n";

		ret += Serializeable::Serialize(tabCount + 1, _parentIndex);

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "\"";
		ret += _name;
		ret += "\"\n";

		Float44 tmp = _localMatrix;
		ret += Serializeable::Serialize(tabCount + 1, tmp);

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	void Skeleton::Bone::Deserialize(std::string& serialedString)
	{
		serialedString = GetUnitElement(serialedString, 0).str;

		int offset = 1;
		{
			auto data = GetUnitElement(serialedString, offset);
			offset = data.offset;
			Serializeable::Deserialize(data.str, _parentIndex);
		}
		{
			auto data = GetUnitAtomic(serialedString, offset);
			offset = data.offset;
			_name = data.str;
		}
		{
			auto data = GetUnitElement(serialedString, offset);
			offset = data.offset;
			Float44 tmp;
			Serializeable::Deserialize(data.str, tmp);
			_localMatrix = HMatrix44(
				tmp.e11, tmp.e12, tmp.e13, tmp.e14,
				tmp.e21, tmp.e22, tmp.e23, tmp.e24,
				tmp.e31, tmp.e32, tmp.e33, tmp.e34,
				tmp.e41, tmp.e42, tmp.e43, tmp.e44
			);
		}
	}
	std::string Skeleton::Serialize(int tabCount)
	{
		std::string ret;

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "[\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(_bones.size());
		ret += "\"}\n";

		for (auto bone : _bones)
		{
			ret += Serializeable::GetTabbedString(tabCount + 1);
			ret += "{\"";
			ret += std::to_string(bone.first);
			ret += "\"\n";
			ret += bone.second->Serialize(tabCount + 2);
			ret += Serializeable::GetTabbedString(tabCount + 1);
			ret += "},\n";
		}

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "]\n";

		return ret;
	}
	void Skeleton::Deserialize(std::string& serialedString)
	{
		serialedString = GetUnitObject(serialedString, 0).str;

		int boneCount;
		int offset = 0;
		{
			auto data = GetUnitElement(serialedString, offset);
			offset = data.offset;
			Serializeable::Deserialize(data.str, boneCount);
		}

		Bone dummyBone;
		for (int i = 0; i < boneCount; ++i)
		{
			int boneIndex;
			auto indexData = GetUnitAtomic(serialedString, offset);
			offset = indexData.offset;
			boneIndex = stoi(indexData.str);

			auto data = GetUnitElement(serialedString, offset);
			offset = data.offset;
			dummyBone.Deserialize(data.str);

			BoneInfo info;
			info.Name = dummyBone.GetName();
			info.LocalMatrix = dummyBone.GetLocalMatrix();
			info.ParentIndex = dummyBone.GetParentIndex();
			AddBone(boneIndex, info);
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
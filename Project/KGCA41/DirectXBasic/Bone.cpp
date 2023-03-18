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
		sd.pSysMem = &_boneSet;
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
		Bone newBone;
		newBone.SetInfo(info);
		if (_bones.size() != 0)
		{
			newBone.SetParent(info.ParentIndex, &_bones.find(info.ParentIndex)->second);
		}
		_bones.insert(std::make_pair(index, newBone));
	}

	void Skeleton::Initialize_SetBoneData(std::map<BoneIndex, BoneInfo> bones)
	{
		for (auto bone : bones)
		{
			AddBone(bone.first, bone.second);
		}
	}
	void Skeleton::Initialize_SetSocketData(std::vector<BoneIndex> sockets)
	{
		_sockets = sockets;
	}
	std::vector<BoneIndex> Skeleton::GetSocketIndex()
	{
		return _sockets;
	}
	HMatrix44 Skeleton::GetWorldMatrix(BoneIndex index)
	{
		return _bones.find(index)->second.GetWorldMatrix();
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
			info.Name = bone.second.GetName();
			info.ParentIndex = bone.second.GetParentIndex();
			info.LocalMatrix = bone.second.GetLocalMatrix();

			data.Bones.insert(std::make_pair(bone.first, info));
		}
		data.Sockets = _sockets;

		return new EditableSkeletonObject(data);
	}
	void Skeleton::Bone::SetInfo(BoneInfo info)
	{
		_name = info.Name;
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
		return _parentBone->GetWorldMatrix() * _localMatrix;
	}
	//std::string Skeleton::Serialize(int tabCount)
	//{
	//	// Do Nothing
	//	return std::string();
	//}
	//void Skeleton::Deserialize(std::string& serialedString)
	//{
	//	// Do Nothing
	//}
	EditableSkeletonObject::EditableSkeletonObject(EditableSkeletonData data) : _bones(data.Bones), _sockets(data.Sockets)
	{
	}
	BoneIndex EditableSkeletonObject::AddSocket(BoneInfo info)
	{
		BoneIndex index = _bones.size();
		_bones.insert(std::make_pair(index, info));
		_sockets.push_back(index);

		return index;
	}
	std::vector<BoneIndex> EditableSkeletonObject::GetSockets()
	{
		return _sockets;
	}
	Skeleton* EditableSkeletonObject::GetResult()
	{
		Skeleton* ret = new Skeleton;

		ret->Initialize_SetBoneData(_bones);
		ret->Initialize_SetSocketData(_sockets);

		return ret;
	}
}
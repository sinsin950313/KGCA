#include "Bone.h"
#include "DXWindow.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

	void Skeleton::SetBoneInfo()
	{
		for (int i = 0; i < _bones.size(); ++i)
		{
			_info.BoneAnimationUnit[i] = _bones.find(i)->second.Matrix;
		}
	}

	bool Skeleton::CreateBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(FrameInfo);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_info;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_buffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
        return true;
	}

	void Skeleton::Initialize_SetBoneData(std::map<BoneIndex, Bone> bones)
	{
		_bones = bones;
	}
	HMatrix44 Skeleton::GetWorldMatrix(BoneIndex index)
	{
		return _info.BoneAnimationUnit[index];
	}
	bool Skeleton::Init()
	{
		SetBoneInfo();
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
}
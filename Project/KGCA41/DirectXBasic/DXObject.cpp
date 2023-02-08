#include "DXObject.h"
#include "DXWindow.h"
#include <cassert>
#include "DXStateManager.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

	DXObject::DXObject()
	{
		_volume = &DefaultVolume;
	}
	DXObject::~DXObject()
	{
		Release();
	}
	bool DXObject::CreateConstantBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(ConstantData);
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_constantData;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&desc, &sd, &_constantBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
	}
	void DXObject::UpdateConstantBuffer()
	{
		_constantData.World = HMatrix44(_volume->GetWorldRotation(), _volume->GetWorldPosition()).Transpose();
		_constantData.View = g_dxWindow->GetMainCamera()->GetViewMatrix().Transpose();
		_constantData.Projection = g_dxWindow->GetMainCamera()->GetProjectionMatrix().Transpose();

		g_dxWindow->GetDeviceContext()->UpdateSubresource(_constantBuffer, 0, nullptr, &_constantData, 0, 0);

		for (auto child : _childObjectList)
		{
			child->UpdateConstantBuffer();
		}
	}
	void DXObject::SetParent(DXObject* object)
	{
		_parent = object;
		_volume->SetParent(object->_volume);
	}
	void DXObject::SetModel(Model* model)
	{
		if (_model)
		{
			delete _model;
		}
		_model = model;
	}
	void DXObject::AddChildObject(DXObject* child)
	{
		_childObjectList.push_back(child);
		child->SetParent(this);
	}
	void DXObject::SetVolume(Volume1* volume)
	{
		if (volume == nullptr)
		{
			//DefaultVolume.SetPosition(_volume->GetLocalPosition());
			//DefaultVolume.SetRotation(_volume->GetLocalRotation());
			//DefaultVolume.SetScale(_volume->GetLocalScale());
			volume = &DefaultVolume;
		}

		if (_volume != &DefaultVolume)
		{
			delete _volume;
		}

		_volume = volume;
	}
	void DXObject::Move(Vector3 vec)
	{
		_volume->AddPosition(vec);
	}
	void DXObject::SetPosition(Vector3 vec)
	{
		_volume->SetPosition(vec);
	}
	//void DXObject::Rotate(float yaw, float pitch, float roll)
	//{
	//	_volume->Rotate(Quaternion(yaw, pitch, roll));
	//}
	Vector3 DXObject::GetPosition()
	{
		return _volume->GetWorldPosition();
	}
	Vector3 DXObject::GetDirection()
	{
		return _volume->GetWorldRotation().GetRow(3);
	}
	HMatrix44 DXObject::GetWorldMatrix()
	{
		return HMatrix44(_volume->GetWorldRotation(), _volume->GetWorldPosition());
	}
	DXObject::operator OBBData()
	{
		OBBData data = _volume->operator SSB::OBBData();
		if (_model)
		{
			OBBData modelData = _model->operator SSB::OBBData();
			data.Width = modelData.Width;
			data.Height = modelData.Height;
			data.Depth = modelData.Depth;
		}
		return data;
	}
	bool DXObject::Init()
    {
		if(_model != nullptr)
		{
			_model->Init();
		}

		for (auto child : _childObjectList)
		{
			child->Init();
		}

		CreateConstantBuffer();

        return true;
    }
    bool DXObject::Frame()
    {
		for (auto child : _childObjectList)
		{
			child->Frame();
		}

		return true;
	}
	bool DXObject::Render()
	{
		if (g_dxWindow->GetMainCamera()->IsRender(this))
		{
			UpdateConstantBuffer();
			g_dxWindow->AddDrawable(this);
		}
		else
		{
			//OutputDebugString(L"Invisible\n");
		}

		for (auto child : _childObjectList)
		{
			child->Render();
		}

		return true;
	}
	bool DXObject::Release()
	{
		if (_volume && _volume != &DefaultVolume)
		{
			delete _volume;
			_volume = nullptr;
		}

		if (_constantBuffer)
		{
			_constantBuffer->Release();
			_constantBuffer = nullptr;
		}

		if (_model)
		{
			_model->Release();
			delete _model;
			_model = nullptr;
		}

		for (auto child : _childObjectList)
		{
			child->Release();
			delete child;
		}
		_childObjectList.clear();

        return true;
    }
    void DXObject::Draw(ID3D11DeviceContext* dc)
    {
		//{
		//	// Move to Model Frame
		//	HMatrix44 view = g_dxWindow->GetMainCamera()->GetViewMatrix();
		//	HMatrix44 projection = g_dxWindow->GetMainCamera()->GetProjectionMatrix();

		//	// Use Constant Buffer instead
		//	auto& vertexList = _direction->GetVertexList();
		//	std::vector<Vertex> update;
		//	for (int i = 0; i < vertexList.size(); ++i)
		//	{
		//		HVector4 position{ vertexList[i].position, 1.0f };
		//		position = position * view;
		//		position = position * projection;
		//		position.Normalize();

		//		Vertex vertex = vertexList[i];
		//		memcpy(&vertex.position, &position, sizeof(Float4));
		//		update.push_back(vertex);
		//	}
		//	g_dxWindow->GetDeviceContext()->UpdateSubresource(_directionVertexBuffer, NULL, NULL, &update.at(0), 0, 0);

		//	dc->IASetVertexBuffers(0, 1, &_directionVertexBuffer, &stride, &offset);
		//	dc->IASetIndexBuffer(_directionIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		//	dc->IASetInputLayout(_vertexLayout);
		//	dc->VSSetShader((ID3D11VertexShader*)_vs->GetShader(), NULL, 0);
		//	dc->PSSetShader((ID3D11PixelShader*)_ps->GetShader(), NULL, 0);
		//	dc->PSSetShaderResources(0, 1, _direction->GetSprite()->GetResource()->GetShaderResourceView());
		//	ID3D11SamplerState* ss = _direction->GetSprite()->GetSamplerState();
		//	dc->PSSetSamplers(0, 1, &ss);
		//	dc->PSSetShaderResources(1, 1, _direction->GetSprite()->GetMaskResource()->GetShaderResourceView());
		//	dc->OMSetBlendState(DXStateManager::GetInstance().GetBlendState(DXStateManager::kDefaultBlend), 0, -1);
		//	dc->DrawIndexed(_direction->GetIndexList().size(), 0, 0);
		//}

		{
			// Move to Model Frame
			//HMatrix44 view = g_dxWindow->GetMainCamera()->GetViewMatrix();
			//HMatrix44 projection = g_dxWindow->GetMainCamera()->GetProjectionMatrix();

			// Use Constant Buffer instead
			dc->OMSetBlendState(DXStateManager::GetInstance().GetBlendState(DXStateManager::kDefaultBlend), 0, -1);
			dc->VSSetConstantBuffers(0, 1, &_constantBuffer);
			_model->Render();
		}
    }
}

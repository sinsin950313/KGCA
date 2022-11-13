#include "Map.h"
#include "DXWindow.h"
#include <cassert>
#include "DXStateManager.h"
#include "WICTextureLoader.h"
#include "CommonPath.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

	void Map::CreateVertex()
	{
		int hWidthVertexCount = _widthVertexCount / 2;
		int hHeightVertexCount = _heightVertexCount / 2;

		// z x-->
		// |
		// |
		// v
		_vertexList.resize(_widthVertexCount * _heightVertexCount);
		for (int row = 0; row < _heightVertexCount; ++row)
		{
			for (int col = 0; col < _widthVertexCount; ++col)
			{
				int index = row * _widthVertexCount + col;
				_vertexList[index].position = { (float)(col - hWidthVertexCount) * _cellDistance, _heightData[row * _widthVertexCount + col] * _heightScale, (float)(hHeightVertexCount - row) * _cellDistance, 1.0f };
				_vertexList[index].color = { (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, 1.0f };
				_vertexList[index].texture = { ((float)col / (float)(_widthVertexCount - 1.0f)) * tileX, ((float)row / (float)(_heightVertexCount - 1.0f)) * tileY };
			}
		}

		// index-- -- -
		//   |  / | /|
		//   | /  |/ |
		//    ---- -- -
		_indexList.resize((_widthVertexCount - 1) * (_heightVertexCount - 1) * 2 * 3);
		unsigned int index = 0;
		for (int row = 0; row < _heightVertexCount - 1; ++row)
		{
			for (int col = 0; col < _widthVertexCount - 1; ++col)
			{
				int vIndex = row * _widthVertexCount + col;
				_indexList[index + 0] = vIndex;
				_indexList[index + 1] = vIndex + 1;
				_indexList[index + 2] = vIndex + _widthVertexCount;

				_indexList[index + 3] = vIndex + _widthVertexCount;
				_indexList[index + 4] = vIndex + 1;
				_indexList[index + 5] = vIndex + _widthVertexCount + 1;

				index += 6;
			}
		}

		CalculateVertexNormal();
	}

	bool Map::CreateVertexBuffer()
    {
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(decltype(_vertexList[0])) * _vertexList.size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_vertexList.at(0);
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_vertexBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
    }
    bool Map::CreateVertexLayout()
    {
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT iedCount = sizeof(ied) / sizeof(ied[0]);
		HRESULT hr = g_dxWindow->GetDevice()->CreateInputLayout(ied, iedCount, _vs->GetCode()->GetBufferPointer(), _vs->GetCode()->GetBufferSize(), &_vertexLayout);
		if (FAILED(hr))
		{
			return false;
		}

		g_dxWindow->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//for (auto dxObject : _childObjectList)
		//{
		//	dxObject->Init();
		//}
		return true;
    }
	bool Map::CreateConstantBuffer()
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
	void Map::UpdateConstantBuffer()
	{
		_constantData.World = GetMatrix().Transpose();
		_constantData.View = g_dxWindow->GetMainCamera()->GetViewMatrix().Transpose();
		_constantData.Projection = g_dxWindow->GetMainCamera()->GetProjectionMatrix().Transpose();

		g_dxWindow->GetDeviceContext()->UpdateSubresource(_constantBuffer, 0, nullptr, &_constantData, 0, 0);
	}
	Vector3 Map::CalculateFaceNormal(UINT i0, UINT i1, UINT i2)
	{
		Vector3 v0 = _vertexList[i0].position;
		Vector3 v1 = _vertexList[i1].position;
		Vector3 v2 = _vertexList[i2].position;

		Vector3 e0 = v1 - v2;
		Vector3 e1 = v2 - v0;
		Vector3 normal = e0.Cross(e1);
		normal.Normalize();

		return normal;
	}
	void Map::CalculateVertexNormal()
	{
		int faceCount = _indexList.size() / 3;
		std::vector<Vector3> faceNormal;
		faceNormal.resize(faceCount);
		UINT faceIndex = 0;
		for (UINT i = 0; i < _indexList.size(); i += 3)
		{
			UINT i0 = _indexList[i + 0];
			UINT i1 = _indexList[i + 1];
			UINT i2 = _indexList[i + 2];
			faceNormal[faceIndex++] = CalculateFaceNormal(i0, i1, i2);
		}

		struct VertexInfo
		{
			std::vector<UINT >  faceIndexArray;
			Vector3 normal;
		};
		std::vector<VertexInfo> vertexInfo;
		vertexInfo.resize(_vertexList.size());
		for (UINT iFace = 0; iFace < faceCount; iFace++)
		{
			for (UINT i = 0; i < 3; i++)
			{
				UINT vertexIndexConnectedWithFace = _indexList[iFace * 3 + i];
				vertexInfo[vertexIndexConnectedWithFace].faceIndexArray.push_back(iFace);
			}
		}
		for (UINT iVertex = 0; iVertex < vertexInfo.size(); iVertex++)
		{
			for (UINT i = 0; i < vertexInfo[iVertex].faceIndexArray.size(); i++)
			{
				vertexInfo[iVertex].normal += faceNormal[i];
			}
			vertexInfo[iVertex].normal.Normalize();
			_vertexList[iVertex].normal = { vertexInfo[iVertex].normal.GetX(), vertexInfo[iVertex].normal.GetY(), vertexInfo[iVertex].normal.GetZ(), 0 };

#ifdef _DEBUG
			Vector3 vLight = { 0, 1, 0 };
			float dot = vLight.Dot(_vertexList[iVertex].normal);
			_vertexList[iVertex].color = { dot ,dot ,dot , 1 };
#endif
		}
	}
	void Map::Move(Vector3 vec)
	{
		HMatrix44 trans{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			vec.GetX(), vec.GetY(), vec.GetZ(), 1
		};
		_matrix = _matrix * trans;
	}
	OBB Map::GetOBB()
	{
		OBB ret;
		ret.Width = 1.0f;
		ret.Height = 1.0f;
		ret.Depth = 1.0f;
		ret.Matrix = _matrix;
		return ret;
	}
	void Map::SetHeightMap(std::wstring fileName)
	{
		const wchar_t* filePath = (kHeightMapPath + fileName).c_str();
		ID3D11Resource* textureResource;
		HRESULT hr = DirectX::CreateWICTextureFromFileEx(
			g_dxWindow->GetDevice(), (kHeightMapPath + fileName).c_str(), 0, D3D11_USAGE_STAGING, 
			0, D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE, 0, DirectX::WIC_LOADER_DEFAULT, 
			&textureResource, nullptr);

		ID3D11Texture2D* texture2D = NULL;
		if (FAILED(textureResource->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&texture2D)))
		{
			textureResource->Release();
			return;
		}

		D3D11_TEXTURE2D_DESC textureDesc;
		texture2D->GetDesc(&textureDesc);

		_widthVertexCount = textureDesc.Width;
		_heightVertexCount = textureDesc.Height;
		_heightData.resize(textureDesc.Height * textureDesc.Width);

		D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
		if (SUCCEEDED(g_dxWindow->GetDeviceContext()->Map(texture2D, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &MappedFaceDest)))
		{
			UCHAR* pTexels = (UCHAR*)MappedFaceDest.pData;
			for (UINT row = 0; row < textureDesc.Height; row++)
			{
				UINT rowStart = row * MappedFaceDest.RowPitch;
				for (UINT col = 0; col < textureDesc.Width; col++)
				{
					UINT colStart = col * 4;
					UINT uRed = pTexels[rowStart + colStart + 0];
					_heightData[row * textureDesc.Width + col] = (float)uRed / 255.0f;
				}
			}
			g_dxWindow->GetDeviceContext()->Unmap(texture2D, D3D11CalcSubresource(0, 0, 1));
		}

		//m_iNumRows = td.Height;
		//m_iNumCols = td.Width;
		textureResource->Release();
		texture2D->Release();

	}
	bool Map::Init()
    {
		CreateVertex();
		_root = new Node(*this, 0, _widthVertexCount - 1, _widthVertexCount * (_heightVertexCount - 1), _widthVertexCount * _heightVertexCount - 1, 0);
        CreateVertexBuffer();
        CreateVertexLayout();
		CreateConstantBuffer();

		_root->Init();

        return true;
    }
    bool Map::Frame()
    {
		return true;
	}
	bool Map::Render()
	{
		UpdateConstantBuffer();
		_root->Check(_drawingNodeList, g_dxWindow->GetMainCamera());
		g_dxWindow->AddDrawable(this);

		return true;
	}
	bool Map::Release()
	{
		if (_vertexBuffer)
        {
            _vertexBuffer->Release();
			_vertexBuffer = nullptr;
        }
        if (_vertexLayout)
        {
            _vertexLayout->Release();
			_vertexLayout = nullptr;
        }
		_vs = nullptr;
		_ps = nullptr;
		if (_constantBuffer)
		{
			_constantBuffer->Release();
			_constantBuffer = nullptr;
		}

		if (_root)
		{
			_root->Release();
			delete _root;
			_root = nullptr;
		}

        return true;
    }
    void Map::Draw(ID3D11DeviceContext* dc)
	{
		UINT stride = sizeof(Vertex_PNCT);
		UINT offset = 0;

		g_dxWindow->GetDeviceContext()->UpdateSubresource(_vertexBuffer, NULL, NULL, &_vertexList.at(0), 0, 0);

		dc->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
		dc->IASetInputLayout(_vertexLayout);
		dc->VSSetShader((ID3D11VertexShader*)_vs->GetShader(), NULL, 0);
		dc->PSSetShader((ID3D11PixelShader*)_ps->GetShader(), NULL, 0);
		dc->PSSetShaderResources(0, 1, _sprite->GetResource()->GetShaderResourceView());
		ID3D11SamplerState* ss = _sprite->GetSamplerState();
		dc->PSSetSamplers(0, 1, &ss);
		dc->PSSetShaderResources(1, 1, _sprite->GetMaskResource()->GetShaderResourceView());
		dc->OMSetBlendState(DXStateManager::GetInstance().GetBlendState(DXStateManager::kDefaultBlend), 0, -1);
		dc->VSSetConstantBuffers(0, 1, &_constantBuffer);

		for (auto node : _drawingNodeList)
		{
			dc->IASetIndexBuffer(node->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
			dc->DrawIndexed(node->GetIndexList().size(), 0, 0);
		}
		_drawingNodeList.clear();
	}
	Map::Node::Node(Map& map, int leftTop, int rightTop, int leftBottom, int rightBottom, int depth) 
		: _map(map), _leftTop(leftTop), _leftBottom(leftBottom), _rightTop(rightTop), _rightBottom(rightBottom), _depth(depth)
	{
		_center = (leftTop + leftBottom + rightTop + rightBottom) / 4;

		if (depth  + 1< map._layerDepth && 2 < rightTop - leftTop)
		{
			int leftCenter = (leftTop + leftBottom) / 2;
			int rightCenter = (rightTop + rightBottom) / 2;
			int topCenter = (leftTop + rightTop) / 2;
			int bottomCenter = (leftBottom + rightBottom) / 2;

			_nodes.resize(4);
			_nodes[0] = new Node(map, leftTop, topCenter, leftCenter, _center, depth + 1);
			_nodes[1] = new Node(map, topCenter, rightTop, _center, rightCenter, depth + 1);
			_nodes[2] = new Node(map, leftCenter, _center, leftBottom, bottomCenter, depth + 1);
			_nodes[3] = new Node(map, _center, rightCenter, bottomCenter, rightBottom, depth + 1);
		}

		_indexList.resize(6);
		_indexList[0] = leftTop;
		_indexList[1] = rightTop;
		_indexList[2] = leftBottom;

		_indexList[3] = leftBottom;
		_indexList[4] = rightTop;
		_indexList[5] = rightBottom;

		auto vLeftTop = _map._vertexList[leftTop];
		auto vRightBottom = _map._vertexList[rightBottom];
		auto vLeftBottom = _map._vertexList[leftBottom];
		auto vRightTop = _map._vertexList[rightTop];
		_width = vRightBottom.position.x - vLeftTop.position.x;
		_height = vRightBottom.position.y - vLeftTop.position.y;
		_depth = vLeftTop.position.z - vRightBottom.position.z;
	}
	Map::Node::operator OBB()
	{
		HMatrix44 matrix = _map.GetMatrix();
		matrix = matrix.Translate(_map._vertexList[_center].position);
		OBB data
		{
			matrix,
			_width,
			_height,
			_depth
		};

		return data;
	}
	bool Map::Node::CreateIndexBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(decltype(_indexList[0])) * _indexList.size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_indexList.at(0);
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_indexBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
        return true;
	}
	void Map::Node::Check(std::vector<Node*>& drawingNodeList, Camera* camera)
	{
		auto state = camera->GetCollideState(*this);
		if (state != ECollideState::Out)
		{
			if (state == ECollideState::Cross)
			{
				if (!_nodes.empty())
				{
					for (auto node : _nodes)
					{
						node->Check(drawingNodeList, camera);
					}
				}
				else
				{
					drawingNodeList.push_back(this);
				}
			}
			else
			{
				drawingNodeList.push_back(this);
			}
		}
	}
	bool Map::Node::Init()
	{
		CreateIndexBuffer();
		if (!_nodes.empty())
		{
			for (auto node : _nodes)
			{
				node->Init();
			}
		}
		return true;
	}
	bool Map::Node::Frame()
	{
		return true;
	}
	bool Map::Node::Render()
	{
		return true;
	}
	bool Map::Node::Release()
	{
		if (_indexBuffer)
		{
			_indexBuffer->Release();
			_indexBuffer = nullptr;
		}

		for (auto node : _nodes)
		{
			node->Release();
			delete node;
		}
		_nodes.clear();

		return true;
	}
}

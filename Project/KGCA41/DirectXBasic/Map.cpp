//#include "Map.h"
//#include "DXWindow.h"
//#include <cassert>
//#include "DXStateManager.h"
//#include "WICTextureLoader.h"
//#include "CommonPath.h"
//#include "ShaderManager.h"
//#include "InputManager.h"
//
//namespace SSB
//{
//    extern DXWindow* g_dxWindow;
//
//	Map::MapModel::MapModel()
//	{
//	}
//
//	Vector3 Map::MapModel::CalculateFaceNormal(UINT i0, UINT i1, UINT i2)
//	{
//		Vector3 v0 = _vertexList[i0].position;
//		Vector3 v1 = _vertexList[i1].position;
//		Vector3 v2 = _vertexList[i2].position;
//
//		Vector3 e0 = v1 - v2;
//		Vector3 e1 = v2 - v0;
//		Vector3 normal = e0.Cross(e1);
//		normal.Normalize();
//
//		return normal;
//	}
//	void Map::MapModel::CalculateVertexNormal()
//	{
//		int faceCount = _indexList.size() / 3;
//		std::vector<Vector3> faceNormal;
//		faceNormal.resize(faceCount);
//		UINT faceIndex = 0;
//		for (UINT i = 0; i < _indexList.size(); i += 3)
//		{
//			UINT i0 = _indexList[i + 0];
//			UINT i1 = _indexList[i + 1];
//			UINT i2 = _indexList[i + 2];
//			faceNormal[faceIndex++] = CalculateFaceNormal(i0, i1, i2);
//		}
//
//		struct VertexInfo
//		{
//			std::vector<UINT >  faceIndexArray;
//			Vector3 normal;
//		};
//		std::vector<VertexInfo> vertexInfo;
//		vertexInfo.resize(_vertexList.size());
//		for (UINT iFace = 0; iFace < faceCount; iFace++)
//		{
//			for (UINT i = 0; i < 3; i++)
//			{
//				UINT vertexIndexConnectedWithFace = _indexList[iFace * 3 + i];
//				vertexInfo[vertexIndexConnectedWithFace].faceIndexArray.push_back(iFace);
//			}
//		}
//		for (UINT iVertex = 0; iVertex < vertexInfo.size(); iVertex++)
//		{
//			for (UINT i = 0; i < vertexInfo[iVertex].faceIndexArray.size(); i++)
//			{
//				vertexInfo[iVertex].normal += faceNormal[vertexInfo[iVertex].faceIndexArray[i]];
//			}
//			vertexInfo[iVertex].normal.Normalize();
//			_vertexList[iVertex].normal = { vertexInfo[iVertex].normal.GetX(), vertexInfo[iVertex].normal.GetY(), vertexInfo[iVertex].normal.GetZ(), 0 };
//
//#ifdef _DEBUG
//			Vector3 vLight = { 0, 1, 0 };
//			float dot = vLight.Dot(_vertexList[iVertex].normal);
//			_vertexList[iVertex].color = { dot, dot, dot, 1 };
//#endif
//		}
//	}
//	void Map::MapModel::SetSize(float widthVertexCount, float heightVertexCount)
//	{
//		_widthVertexCount = widthVertexCount; _heightVertexCount = heightVertexCount;
//	}
//	float Map::MapModel::GetCoordinateHeight(int x, int z)
//	{
//		return _vertexList[x * _widthVertexCount + z].position.y;
//	}
//	float Map::MapModel::GetHeight(int x, int z)
//	{
//		float cellX = (float)(_widthVertexCount * _cellDistance / 2.0f + x);
//		float cellZ = (float)(_heightVertexCount * _cellDistance / 2.0f - z);
//
//		cellX /= (float)_cellDistance;
//		cellZ /= (float)_cellDistance;
//
//		int coordX = cellX;
//		if (coordX < 0.0f)
//		{
//			coordX = 0.0f;
//		}
//		if (_heightVertexCount - 2 < coordX)
//		{
//			coordX = _heightVertexCount - 2;
//		}
//
//		int coordZ = cellZ;
//		if (coordZ < 0.0f)
//		{
//			coordZ = 0.0f;
//		}
//		if (_widthVertexCount - 2 < coordZ)
//		{
//			coordZ = _widthVertexCount - 2;
//		}
//
//		//  A   B
//		//  *---*
//		//  | / |
//		//  *---*  
//		//  C   D
//		float A = GetCoordinateHeight(coordX, coordZ);
//		float B = GetCoordinateHeight(coordX, coordZ + 1);
//		float C = GetCoordinateHeight(coordX + 1, coordZ);
//		float D = GetCoordinateHeight(coordX + 1, coordZ + 1);
//
//		float deltaX = cellX - coordX;
//		float deltaZ = cellZ - coordZ;
//		float height = 0.0f;
//		if (deltaX + deltaZ < 1.0f)  //ABC
//		{
//			float uy = B - A; // A->B
//			float vy = C - A; // A->C	
//							  // 두 정점의 높이값의 차이를 비교하여 델타X의 값에 따라 보간값을 찾는다.		
//			height = A + Lerp(0.0f, uy, deltaX) + Lerp(0.0f, vy, deltaZ);
//		}
//		else // DCB
//		{
//			float uy = C - D; // D->C
//			float vy = B - D; // D->B
//							  // 두 정점의 높이값의 차이를 비교하여 델타Z의 값에 따라 보간값을 찾는다.		
//			height = D + Lerp(0.0f, uy, 1.0f - deltaX) + Lerp(0.0f, vy, 1.0f - deltaZ);
//		}
//		return height;
//	}
//	std::vector<Vertex_PNCT> Map::MapModel::GetVertice()
//	{
//		return _vertexList;
//	}
//	float Map::MapModel::Lerp(float start, float end, float param)
//	{
//		return start - (start * param) + (end * param);
//	}
//	void Map::MapModel::Build()
//	{
//		int hWidthVertexCount = _widthVertexCount / 2;
//		int hDepthVertexCount = _heightVertexCount / 2;
//
//		// z x-->
//		// |
//		// |
//		// v
//		_vertexList.resize(_widthVertexCount * _heightVertexCount);
//		for (int row = 0; row < _heightVertexCount; ++row)
//		{
//			for (int col = 0; col < _widthVertexCount; ++col)
//			{
//				int index = row * _widthVertexCount + col;
//				_vertexList[index].position = { (float)(col - hWidthVertexCount) * _map->_cellDistance, _map->_heightData[row * _widthVertexCount + col] * _map->_heightScale, (float)(hDepthVertexCount - row) * _map->_cellDistance, 1.0f };
//				_vertexList[index].color = { (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, 1.0f };
//				_vertexList[index].texture = { ((float)col / (float)(_widthVertexCount - 1.0f)) * _map->tileX, ((float)row / (float)(_heightVertexCount - 1.0f)) * _map->tileY };
//			}
//		}
//
//		// index-- -- -
//		//   |  / | /|
//		//   | /  |/ |
//		//    ---- -- -
//		_indexList.resize((_widthVertexCount - 1) * (_heightVertexCount - 1) * 2 * 3);
//		unsigned int index = 0;
//		for (int row = 0; row < _heightVertexCount - 1; ++row)
//		{
//			for (int col = 0; col < _widthVertexCount - 1; ++col)
//			{
//				int vIndex = row * _widthVertexCount + col;
//				_indexList[index + 0] = vIndex;
//				_indexList[index + 1] = vIndex + 1;
//				_indexList[index + 2] = vIndex + _widthVertexCount;
//
//				_indexList[index + 3] = vIndex + _widthVertexCount;
//				_indexList[index + 4] = vIndex + 1;
//				_indexList[index + 5] = vIndex + _widthVertexCount + 1;
//
//				index += 6;
//			}
//		}
//
//		CalculateVertexNormal();
//	}
//	void Map::MapModel::SetHeightMap(std::wstring fileName)
//	{
//		const wchar_t* filePath = (kHeightMapPath + fileName).c_str();
//		ID3D11Resource* textureResource;
//		HRESULT hr = DirectX::CreateWICTextureFromFileEx(
//			g_dxWindow->GetDevice(), (kHeightMapPath + fileName).c_str(), 0, D3D11_USAGE_STAGING, 
//			0, D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE, 0, DirectX::WIC_LOADER_DEFAULT, 
//			&textureResource, nullptr);
//
//		ID3D11Texture2D* texture2D = NULL;
//		if (FAILED(textureResource->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&texture2D)))
//		{
//			textureResource->Release();
//			return;
//		}
//
//		D3D11_TEXTURE2D_DESC textureDesc;
//		texture2D->GetDesc(&textureDesc);
//
//		_widthVertexCount = textureDesc.Width;
//		_heightVertexCount = textureDesc.Height;
//		_map->_heightData.resize(textureDesc.Height * textureDesc.Width);
//
//		D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
//		float minHeight;
//		float maxHeight;
//		if (SUCCEEDED(g_dxWindow->GetDeviceContext()->Map(texture2D, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &MappedFaceDest)))
//		{
//			UCHAR* pTexels = (UCHAR*)MappedFaceDest.pData;
//			minHeight = (float)pTexels[0] / 255.0f;
//			maxHeight = (float)pTexels[0] / 255.0f;
//			for (UINT row = 0; row < textureDesc.Height; row++)
//			{
//				UINT rowStart = row * MappedFaceDest.RowPitch;
//				for (UINT col = 0; col < textureDesc.Width; col++)
//				{
//					UINT colStart = col * 4;
//					UINT uRed = pTexels[rowStart + colStart + 0];
//					float heightData = (float)uRed / 255.0f;
//					_map->_heightData[row * textureDesc.Width + col] = heightData;
//					minHeight = fmin(minHeight, heightData);
//					maxHeight = fmax(maxHeight, heightData);
//				}
//			}
//			g_dxWindow->GetDeviceContext()->Unmap(texture2D, D3D11CalcSubresource(0, 0, 1));
//		}
//		_map->_height = maxHeight - minHeight;
//
//		//m_iNumRows = td.Height;
//		//m_iNumCols = td.Width;
//		textureResource->Release();
//		texture2D->Release();
//	}
//
//	Map::Map()
//	{
//	}
//	Map::~Map()
//	{
//		Release();
//	}
//	void Map::SetSize(unsigned int widthVertexCount, unsigned int heightVertexCount)
//	{
//		_widthVertexCount = widthVertexCount;
//		_heightVertexCount = heightVertexCount;
//		_model.SetSize(widthVertexCount, heightVertexCount);
//	}
//	void Map::SetHeightMap(std::wstring fileName)
//	{
//		_model->SetHeightMap(fileName);
//	}
//	float Map::GetHeight(float x, float z)
//	{
//		return _model->GetHeight(x, z);
//	}
//	bool Map::Init()
//    {
//		DXObject::Init();
//
//		_root = new Node(*this, 0, _widthVertexCount - 1, _widthVertexCount * (_heightVertexCount - 1), _widthVertexCount * _heightVertexCount - 1, 0);
//		_root->Init();
//
//		SetVolume(new Box1Volume(_width, _height, _depth));
//
//        return true;
//    }
//    bool Map::Frame()
//    {
//		if (InputManager::GetInstance().GetKeyState('V') == EKeyState::KEY_PRESSED)
//		{
//			_bDebug = !_bDebug;
//		}
//
//		_root->Frame();
//
//		return true;
//	}
//	bool Map::Release()
//	{
//		std::vector<MapVolume*> _volumes;
//
//		bool _bDebug = false;
//		if (_model)
//		{
//			_model = nullptr;
//		}
//
//		if (_heightTexture)
//		{
//			_heightTexture->Release();
//			_heightTexture = nullptr;
//		}
//
//		for (auto volume : _volumes)
//		{
//			delete volume;
//		}
//		_volumes.clear();
//
//        return true;
//    }
// //   void Map::Draw(ID3D11DeviceContext* dc)
//	//{
//	//	for (auto node : _drawingNodeList)
//	//	{
//	//		dc->IASetIndexBuffer(node->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
//	//		dc->DrawIndexed(node->GetIndexList().size(), 0, 0);
//	//	}
//	//	_drawingNodeList.clear();
//	//}
//
//	Map::Node::Node(Map& map, int leftTop, int rightTop, int leftBottom, int rightBottom, int depth) 
//		: _map(map), _leftTop(leftTop), _leftBottom(leftBottom), _rightTop(rightTop), _rightBottom(rightBottom), _layerDepth(depth)
//	{
//		_center = (leftTop + leftBottom + rightTop + rightBottom) / 4;
//
//		if (_layerDepth + 1< map._layerDepth && 2 < rightTop - leftTop)
//		{
//			int leftCenter = (leftTop + leftBottom) / 2;
//			int rightCenter = (rightTop + rightBottom) / 2;
//			int topCenter = (leftTop + rightTop) / 2;
//			int bottomCenter = (leftBottom + rightBottom) / 2;
//
//			_nodes.resize(4);
//			_nodes[0] = new Node(map, leftTop, topCenter, leftCenter, _center, _layerDepth + 1);
//			_nodes[1] = new Node(map, topCenter, rightTop, _center, rightCenter, _layerDepth + 1);
//			_nodes[2] = new Node(map, leftCenter, _center, leftBottom, bottomCenter, _layerDepth + 1);
//			_nodes[3] = new Node(map, _center, rightCenter, bottomCenter, rightBottom, _layerDepth + 1);
//		}
//
//		int widthCellCount = rightTop - leftTop;
//		int heightCellCount = (leftBottom - leftTop) / map._widthVertexCount;
//		int cellCount = widthCellCount * heightCellCount;
//		int vertexCount = cellCount * 2 * 3;
//		_indexList.resize(vertexCount);
//		int iIndex = 0;
//		for (int i = 0; i < heightCellCount; i++)
//		{
//			for (int j = 0; j < widthCellCount; j++)
//			{
//				_indexList[iIndex + 0] = leftTop + j + (i * map._widthVertexCount);
//				_indexList[iIndex + 1] = _indexList[iIndex + 0] + 1;
//				_indexList[iIndex + 2] = leftTop + j + ((i + 1) * map._widthVertexCount);
//
//				_indexList[iIndex + 3] = _indexList[iIndex + 2];
//				_indexList[iIndex + 4] = _indexList[iIndex + 1];
//				_indexList[iIndex + 5] = _indexList[iIndex + 2] + 1;
//
//				iIndex += 6;
//			}
//		}
//
//		auto vertice = map._model.GetVertice();
//		float heightMax = vertice[_indexList[0]].position.y;
//		float heightMin = vertice[_indexList[0]].position.y;
//		float widthMax = vertice[_indexList[0]].position.x;
//		float widthMin = vertice[_indexList[0]].position.x;
//		float depthMax = vertice[_indexList[0]].position.z;
//		float depthMin = vertice[_indexList[0]].position.z;
//		for (auto index : _indexList)
//		{
//			Float4 tmp = vertice[index].position;
//			heightMax = fmax(heightMax, tmp.y);
//			heightMin = fmin(heightMin, tmp.y);
//			widthMax = fmax(widthMax, tmp.x);
//			widthMin = fmin(widthMin, tmp.x);
//			depthMax = fmax(depthMax, tmp.z);
//			depthMin = fmin(depthMin, tmp.z);
//		}
//
//		_width = fabs(widthMax - widthMin);
//		_height = fabs(heightMax - heightMin);
//		//_height = 10;
//		_depth = fabs(depthMax - depthMin);
//		Vector3 position{vertice[_center].position.x, heightMin + _height / 2.0f, vertice[_center].position.z};
//		_matrix = HMatrix44(Matrix33(), position);
//
//		class DebugBox : public DXObject
//		{
//		public:
//			bool Render() override
//			{
//				UpdateConstantBuffer();
//				g_dxWindow->AddDrawable(this);
//				return true;
//			}
//		};
//		_debugBox = new DebugBox();
//		Box* box = new Box(_width, _height, _depth);
//		box->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader.hlsl", "Main", "vs_5_0"));
//		box->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DPixelShader.hlsl", "Debug", "ps_5_0"));
//		_debugBox->SetModel(box);
//		_debugBox->Move(position);
//	}
//	bool Map::Node::CreateIndexBuffer()
//	{
//		D3D11_BUFFER_DESC bd;
//		ZeroMemory(&bd, sizeof(bd));
//		bd.ByteWidth = sizeof(decltype(_indexList[0])) * _indexList.size();
//		bd.Usage = D3D11_USAGE_DEFAULT;
//		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//
//		D3D11_SUBRESOURCE_DATA sd;
//		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
//		sd.pSysMem = &_indexList.at(0);
//		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_indexBuffer);
//		if (FAILED(hr))
//		{
//			assert(SUCCEEDED(hr));
//			return false;
//		}
//        return true;
//	}
//	ID3D11Buffer* Map::Node::GetIndexBuffer()
//	{
//		return _indexBuffer;
//	}
//	std::vector<int> Map::Node::GetIndexList()
//	{
//		return _indexList;
//	}
//	void Map::Node::Check(std::vector<Node*>& drawingNodeList, Camera* camera)
//	{
//		auto state = camera->GetCollideState(*_debugBox);
//		if (state != ECollideState::Out)
//		{
//			if (state == ECollideState::Cross)
//			{
//				if (!_nodes.empty())
//				{
//					for (auto node : _nodes)
//					{
//						node->Check(drawingNodeList, camera);
//					}
//				}
//				else
//				{
//					drawingNodeList.push_back(this);
//				}
//			}
//			else
//			{
//				drawingNodeList.push_back(this);
//			}
//		}
//		if (_map._bDebug)
//		{
//			_debugBox->Render();
//		}
//	}
//	bool Map::Node::Init()
//	{
//		CreateIndexBuffer();
//		if (!_nodes.empty())
//		{
//			for (auto node : _nodes)
//			{
//				node->Init();
//			}
//		}
//		_debugBox->Init();
//		return true;
//	}
//	bool Map::Node::Frame()
//	{
//		for (auto node : _nodes)
//		{
//			node->Frame();
//		}
//
//		_debugBox->Frame();
//
//		return true;
//	}
//	bool Map::Node::Render()
//	{
//		g_dxWindow->GetDeviceContext()->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
//		g_dxWindow->GetDeviceContext()->DrawIndexed(_indexList.size(), 0, 0);
//
//		for (auto node : _nodes)
//		{
//			node->Frame();
//		}
//
//		//_debugBox->Render();
//
//		return true;
//	}
//	bool Map::Node::Release()
//	{
//		if (_indexBuffer)
//		{
//			_indexBuffer->Release();
//			_indexBuffer = nullptr;
//		}
//
//		for (auto node : _nodes)
//		{
//			node->Release();
//			delete node;
//		}
//		_nodes.clear();
//
//		if (_debugBox)
//		{
//			_debugBox->Release();
//			delete _debugBox;
//		}
//
//		return true;
//	}
//}

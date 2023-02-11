#include "Model.h"
#include "HCCalculator.h"
#include "DXWindow.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

	const AnimationName kDefaultAnimaionName = "DefaultAnimation";
	Animation Model::DefaultAnimation;

	bool Mesh::CreateVertexBuffer()
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
	bool Mesh::CreateIndexBuffer()
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
	bool Mesh::CreateSkinningDataBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(SkinningData);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_skinningData;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_skinningDataBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
        return true;
	}
	bool Mesh::CreateBoneSpaceTransformBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(MeshData);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_meshData;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_meshDataBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
        return true;
	}
	void Mesh::SetVertexList(std::vector<Vertex_PNCT> vertexList)
	{
		_vertexList = vertexList;
	}
	void Mesh::SetIndexList(std::vector<DWORD> indexList)
	{
		_indexList = indexList;
	}
	Vector3 Mesh::GetMinVertex()
	{
		return _minVertex;
	}
	Vector3 Mesh::GetMaxVertex()
	{
		return _maxVertex;
	}
	bool Mesh::Init()
	{
        CreateVertexBuffer();
        CreateIndexBuffer();
		CreateSkinningDataBuffer();
		CreateBoneSpaceTransformBuffer();
	}
	bool Mesh::Frame()
	{

	}
	bool Mesh::Render()
	{
		ID3D11DeviceContext* dc = g_dxWindow->GetDeviceContext();

		UINT stride = sizeof(Vertex_PNCT);
		UINT offset = 0;
		std::vector<Vertex_PNCT> update;
		for (int i = 0; i < _vertexList.size(); ++i)
		{
			HVector4 position{ _vertexList[i].position, 1.0f };
			//position = position * _matrix;
			//position = position * view;
			//position = position * projection;
			//position.Normalize();

			Vertex_PNCT vertex = _vertexList[i];
			memcpy(&vertex.position, &position, sizeof(Float4));
			update.push_back(vertex);
		}
		g_dxWindow->GetDeviceContext()->UpdateSubresource(_vertexBuffer, NULL, NULL, &update.at(0), 0, 0);

		dc->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
		dc->IASetVertexBuffers(1, 1, &_skinningDataBuffer, &stride, &offset);
		dc->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		dc->VSSetConstantBuffers(2, 1, &_meshDataBuffer);

		dc->DrawIndexed(_indexList.size(), 0, 0);
	}
	bool Mesh::Release()
	{
		if (_vertexBuffer)
        {
			_vertexBuffer->Release();
			_vertexBuffer = nullptr;
        }
        if (!_indexBuffer)
        {
			_indexBuffer->Release();
			_indexBuffer = nullptr;
        }
		_indexList.clear();
	}

	Animation::Animation()
	{
	}
	Animation::~Animation()
	{
		Release();
	}
	bool Animation::CreateAnimatedFrameInfoBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(AnimatedFrameInfo);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_currentFrameInfo;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_animatedFrameBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
        return true;
	}
	HMatrix44 Animation::GetInterpolate(AnimationUnitInfo& beforeInfo, AnimationUnitInfo& afterInfo, float t)
	{
		HMatrix44 ret;

		Vector3 pos = Lerp(beforeInfo.Translate, afterInfo.Translate, t);
		Vector3 scale = Lerp(beforeInfo.Scale, afterInfo.Scale, t);
		Quaternion rotate = SLerp(beforeInfo.Rotate, afterInfo.Rotate, t);

		ret = HMatrix44::Scale(scale) * HMatrix44(rotate.GetRotateMatrix(), { 0, 0, 0 }) * HMatrix44::Translate(pos);

		return ret;
	}
	void Animation::UpdateFrameInfo()
	{
		float animationElapseTime = (float)(_animationTimer.GetElapseTime() / 1000.0f);
		int beforeIndex = animationElapseTime * _framePerSecond;
		int afterIndex = beforeIndex + 1;

		float beforeTime = beforeIndex / _framePerSecond;
		float afterTime = afterIndex / _framePerSecond;
		if (afterIndex == _data.size())
		{
			afterIndex = beforeIndex;
		}
		else if (_data.size() <= beforeIndex)
		{
			_animationTimer.Init();
			beforeIndex = beforeIndex / _data.size();
			afterIndex = afterIndex / _data.size();
		}

		beforeTime = beforeIndex / _framePerSecond;
		afterTime = afterIndex / _framePerSecond;
		float t = (animationElapseTime - beforeTime) / (afterTime - beforeTime);

		for (int i = 0; i < _meshMaxIndex; ++i)
		{
			_currentFrameInfo.MeshUnit[i] = GetInterpolate(_data[beforeIndex].MeshUnit[i], _data[afterIndex].MeshUnit[i], t);
		}

		for (int i = 0; i < _boneMaxIndex; ++i)
		{
			_currentFrameInfo.BoneUnit[i] = GetInterpolate(_data[beforeIndex].BoneUnit[i], _data[afterIndex].BoneUnit[i], t);
		}

		g_dxWindow->GetDeviceContext()->UpdateSubresource(_animatedFrameBuffer, 0, nullptr, &_currentFrameInfo, 0, 0);
	}
	bool Animation::Init()
	{
		_animationTimer.Init();
		_currentFrameInfo = DefaultFrameInfo;

		return true;
	}
	void Animation::SetAnimationFrameData(std::vector<AnimationFrameInfo> data)
	{
		_data = data;
	}
	bool Animation::Frame()
	{
		_animationTimer.Frame();
		UpdateFrameInfo();

		return true;
	}
	bool Animation::Render()
	{
		_animationTimer.Render();
		g_dxWindow->GetDeviceContext()->VSSetConstantBuffers(1, 1, &_animatedFrameBuffer);

		return true;
	}
	bool Animation::Release()
	{
		_animationTimer.Release();

		return true;
	}

	void Animation::SetMeshMaxIndex(int maxIndex)
	{
		_meshMaxIndex = maxIndex;
	}

	void Animation::SetBoneMaxIndex(int maxIndex)
	{
		_boneMaxIndex = maxIndex;
	}

	Model::Model()
	{
		_sprite = SpriteLoader::GetInstance().GetDefaultSprite();
		//_sprites.push_back(SpriteLoader::GetInstance().GetDefaultSprite());
		_animations.insert(std::make_pair(kDefaultAnimaionName, &DefaultAnimation));
		_currentAnimation = &DefaultAnimation;
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
	void Model::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		*desc = new D3D11_INPUT_ELEMENT_DESC[7];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };

		(*desc)[4] = { "AffectingBoneIndex", 0, DXGI_FORMAT_R32G32B32A32_SINT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[5] = { "Weight", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };

		count = 6;
	}
    bool Model::CreateVertexLayout()
    {
		D3D11_INPUT_ELEMENT_DESC* inputElementDesc;
		int inputElementDescCount;
		SetVertexLayoutDesc(&inputElementDesc, inputElementDescCount);

		HRESULT hr = g_dxWindow->GetDevice()->CreateInputLayout(inputElementDesc, inputElementDescCount, _vs->GetCode()->GetBufferPointer(), _vs->GetCode()->GetBufferSize(), &_vertexLayout);
		delete inputElementDesc;

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
	void Model::RegisterMesh(MeshIndex index, Mesh* mesh)
	{
		_meshes.insert(std::make_pair(index, mesh));
	}
	void Model::RegisterAnimation(AnimationName name, Animation* animation)
	{
		_animations.insert(std::make_pair(name, animation));
	}
	void Model::SetCurrentAnimation(AnimationName name)
	{
		_currentAnimation = _animations.find(name)->second;
	}
	void Model::SetVertexShader(Shader* shader)
	{
		_vs = shader;
	}
	void Model::SetPixelShader(Shader* shader)
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
	void Model::SetSprite(Sprite* sprite)
	{
		_sprite = sprite;
	}
	bool Model::Init()
	{
		//if (_animation && _animation != &DefaultAnimation)
		//{
		//	_animation->Init();
		//}

        CreateVertexLayout();

		for (auto mesh : _meshes)
		{
			mesh.second->Init();
			_meshElementMinMaxVertexList.push_back(mesh.second->GetMaxVertex());
			_meshElementMinMaxVertexList.push_back(mesh.second->GetMinVertex());
		}
		SizeCheck();

		return false;
	}
	bool Model::Frame()
	{
		_currentAnimation->Frame();
		for (auto mesh : _meshes)
		{
			mesh.second->Frame();
		}
		return false;
	}
	bool Model::Render()
	{
		auto dc = g_dxWindow->GetDeviceContext();
		dc->IASetInputLayout(_vertexLayout);

		// Need to separate this
		dc->VSSetShader((ID3D11VertexShader*)_vs->GetShader(), NULL, 0);
		dc->PSSetShader((ID3D11PixelShader*)_ps->GetShader(), NULL, 0);
		//for(int i = 0; i < _sprites.size(); ++i)
		{
			dc->PSSetShaderResources(0, 1, _sprite->GetResource()->GetShaderResourceView());
			ID3D11SamplerState* ss = _sprite->GetSamplerState();
			dc->PSSetSamplers(0, 1, &ss);
			dc->PSSetShaderResources(1, 1, _sprite->GetMaskResource()->GetShaderResourceView());
		}

		_currentAnimation->Render();

		for (auto mesh : _meshes)
		{
			mesh.second->Render();
		}

		return false;
	}
	bool Model::Release()
	{
        if (_vertexLayout)
        {
            _vertexLayout->Release();
			_vertexLayout = nullptr;
        }
		_vs = nullptr;
		_ps = nullptr;

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
		}
		_meshElementMinMaxVertexList.clear();

		//for (auto sprite : _sprites)
		{
			if (_sprite && _sprite != &(SpriteLoader::GetInstance()._defaultSprite))
			{
				_sprite->Release();
				delete _sprite;
				_sprite = nullptr;
			}
		}

		return false;
	}

	//Box::Box(float width, float height, float depth)
	//	: _width(width), _height(height), _depth(depth)
	//{
	//}
	//void Box::Build()
	//{
	//	_vertexList.resize(24);
	//	// ¾Õ¸é
	//	_vertexList[0] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
	//	_vertexList[1] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
	//	_vertexList[2] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
	//	_vertexList[3] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };
	//	// µÞ¸é
	//	_vertexList[4] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float4{0.0f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
	//	_vertexList[5] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
	//	_vertexList[6] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
	//	_vertexList[7] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };

	//	// ¿À¸¥ÂÊ
	//	_vertexList[8] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.0f, 0.0f} };
	//	_vertexList[9] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.5f, 0.0f} };
	//	_vertexList[10] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.5f, 0.5f} };
	//	_vertexList[11] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.0f, 0.5f} };

	//	// ¿ÞÂÊ
	//	_vertexList[12] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
	//	_vertexList[13] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
	//	_vertexList[14] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
	//	_vertexList[15] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };

	//	// À­¸é
	//	_vertexList[16] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.0f} };
	//	_vertexList[17] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.0f} };
	//	_vertexList[18] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.5f} };
	//	_vertexList[19] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.5f} };

	//	// ¾Æ·§¸é
	//	_vertexList[20] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.0f} };
	//	_vertexList[21] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.0f} };
	//	_vertexList[22] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.5f} };
	//	_vertexList[23] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.5f} };

	//	_indexList.resize(36);
	//	int iIndex = 0;
	//	_indexList[iIndex++] = 0; 	_indexList[iIndex++] = 1; 	_indexList[iIndex++] = 2; 	_indexList[iIndex++] = 0;	_indexList[iIndex++] = 2; 	_indexList[iIndex++] = 3;
	//	_indexList[iIndex++] = 4; 	_indexList[iIndex++] = 5; 	_indexList[iIndex++] = 6; 	_indexList[iIndex++] = 4;	_indexList[iIndex++] = 6; 	_indexList[iIndex++] = 7;
	//	_indexList[iIndex++] = 8; 	_indexList[iIndex++] = 9; 	_indexList[iIndex++] = 10; _indexList[iIndex++] = 8;	_indexList[iIndex++] = 10; _indexList[iIndex++] = 11;
	//	_indexList[iIndex++] = 12; _indexList[iIndex++] = 13; _indexList[iIndex++] = 14; _indexList[iIndex++] = 12;	_indexList[iIndex++] = 14; _indexList[iIndex++] = 15;
	//	_indexList[iIndex++] = 16; _indexList[iIndex++] = 17; _indexList[iIndex++] = 18; _indexList[iIndex++] = 16;	_indexList[iIndex++] = 18; _indexList[iIndex++] = 19;
	//	_indexList[iIndex++] = 20; _indexList[iIndex++] = 21; _indexList[iIndex++] = 22; _indexList[iIndex++] = 20;	_indexList[iIndex++] = 22; _indexList[iIndex++] = 23;
	//}
	//void Triangle::Build()
	//{
	//	_vertexList.resize(3);
	//	_vertexList[0] = Vertex_PNCT{ Float4{+0.0f, +0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 0.0f}, Float2{0, 0} };
	//	_vertexList[1] = Vertex_PNCT{ Float4{+0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 0.0f}, Float2{0, 0} };
	//	_vertexList[2] = Vertex_PNCT{ Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 0.0f}, Float4{0, 0} };

	//	_indexList.resize(3);
	//	int iIndex = 0;
	//	_indexList[iIndex++] = 0;
	//	_indexList[iIndex++] = 1;
	//	_indexList[iIndex++] = 2;
	//}
}

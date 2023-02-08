#include "Model.h"
#include "HCCalculator.h"
#include "DXWindow.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

	//void Terrain::Make(unsigned int widthVertexCount, unsigned int heightVertexCount)
	//{
	//	int hWidthVertexCount = widthVertexCount / 2;
	//	int hHeightVertexCount = heightVertexCount / 2;

	//	// z x-->
	//	// |
	//	// |
	//	// v
	//	_vertexList.resize(widthVertexCount * heightVertexCount);
	//	for (int row = 0; row < heightVertexCount; ++row)
	//	{
	//		for (int col = 0; col < widthVertexCount; ++col)
	//		{
	//			int index = row * widthVertexCount + col;
	//			_vertexList[index].position = { (float)(col - hWidthVertexCount) * _cellDistance, 0.0f, (float)(hHeightVertexCount - row) * _cellDistance, 1.0f };
	//			_vertexList[index].color = { (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, 1.0f };
	//			_vertexList[index].texture = { ((float)col / (float)(widthVertexCount - 1.0f)) * tileX, ((float)row / (float)(heightVertexCount - 1.0f)) * tileY };
	//		}
	//	}

	//	// index-- -- -
	//	//   |  / | /|
	//	//   | /  |/ |
	//	//    ---- -- -
	//	_indexList.resize((widthVertexCount - 1) * (heightVertexCount - 1) * 2 * 3);
	//	unsigned int index = 0;
	//	for (int row = 0; row < heightVertexCount - 1; ++row)
	//	{
	//		for (int col = 0; col < widthVertexCount - 1; ++col)
	//		{
	//			int vIndex = row * widthVertexCount + col;
	//			_indexList[index + 0] = vIndex;
	//			_indexList[index + 1] = vIndex + 1;
	//			_indexList[index + 2] = vIndex + widthVertexCount;

	//			_indexList[index + 3] = vIndex + widthVertexCount;
	//			_indexList[index + 4] = vIndex + 1;
	//			_indexList[index + 5] = vIndex + widthVertexCount + 1;

	Box::Box(float width, float height, float depth)
		: _width(width), _height(height), _depth(depth)
	{
	}

	//			index += 6;
	//		}
	//	}
	//}
	void Box::Build()
	{
		_vertexList.resize(24);
		// ¾Õ¸é
		_vertexList[0] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[1] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[2] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[3] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };
		// µÞ¸é
		_vertexList[4] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float4{0.0f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[5] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[6] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[7] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };

		// ¿À¸¥ÂÊ
		_vertexList[8] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[9] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[10] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[11] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.0f, 0.5f} };

		// ¿ÞÂÊ
		_vertexList[12] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[13] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[14] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[15] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };

		// À­¸é
		_vertexList[16] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[17] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[18] = Vertex_PNCT{ Float4{0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[19] = Vertex_PNCT{ Float4{-0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.5f} };

		// ¾Æ·§¸é
		_vertexList[20] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[21] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[22] = Vertex_PNCT{ Float4{0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[23] = Vertex_PNCT{ Float4{-0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.5f} };

		_indexList.resize(36);
		int iIndex = 0;
		_indexList[iIndex++] = 0; 	_indexList[iIndex++] = 1; 	_indexList[iIndex++] = 2; 	_indexList[iIndex++] = 0;	_indexList[iIndex++] = 2; 	_indexList[iIndex++] = 3;
		_indexList[iIndex++] = 4; 	_indexList[iIndex++] = 5; 	_indexList[iIndex++] = 6; 	_indexList[iIndex++] = 4;	_indexList[iIndex++] = 6; 	_indexList[iIndex++] = 7;
		_indexList[iIndex++] = 8; 	_indexList[iIndex++] = 9; 	_indexList[iIndex++] = 10; _indexList[iIndex++] = 8;	_indexList[iIndex++] = 10; _indexList[iIndex++] = 11;
		_indexList[iIndex++] = 12; _indexList[iIndex++] = 13; _indexList[iIndex++] = 14; _indexList[iIndex++] = 12;	_indexList[iIndex++] = 14; _indexList[iIndex++] = 15;
		_indexList[iIndex++] = 16; _indexList[iIndex++] = 17; _indexList[iIndex++] = 18; _indexList[iIndex++] = 16;	_indexList[iIndex++] = 18; _indexList[iIndex++] = 19;
		_indexList[iIndex++] = 20; _indexList[iIndex++] = 21; _indexList[iIndex++] = 22; _indexList[iIndex++] = 20;	_indexList[iIndex++] = 22; _indexList[iIndex++] = 23;
	}
	void Triangle::Build()
	{
		_vertexList.resize(3);
		_vertexList[0] = Vertex_PNCT{ Float4{+0.0f, +0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 0.0f}, Float2{0, 0} };
		_vertexList[1] = Vertex_PNCT{ Float4{+0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 0.0f}, Float2{0, 0} };
		_vertexList[2] = Vertex_PNCT{ Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 0.0f}, Float4{0, 0} };

		_indexList.resize(3);
		int iIndex = 0;
		_indexList[iIndex++] = 0;
		_indexList[iIndex++] = 1;
		_indexList[iIndex++] = 2;
	}
	Model::Model()
	{
		_sprite = SpriteLoader::GetInstance().GetDefaultSprite();
		//_sprites.push_back(SpriteLoader::GetInstance().GetDefaultSprite());
		//_animation = &DefaultAnimation;
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
		for (auto vertex : _vertexList)
		{
			minX = min(minX, vertex.position.x);
			minY = min(minY, vertex.position.y);
			minZ = min(minZ, vertex.position.z);

			maxX = max(maxX, vertex.position.x);
			maxY = max(maxY, vertex.position.y);
			maxZ = max(maxZ, vertex.position.z);
		}

		_minVertex = { minX, minY, minZ };
		_maxVertex = { maxX, maxY, maxZ };
	}
	bool Model::CreateVertexBuffer()
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
	bool Model::CreateIndexBuffer()
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
	void Model::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		*desc = new D3D11_INPUT_ELEMENT_DESC[4];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };

		count = 4;
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
	//void Model::SetAnimation(Animation* animation)
	//{
	//	_animation = animation;
	//}
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
	void Model::UpdateCurrentAnimation(std::string name)
	{
		//_animation->UpdateCurrentAction(name);
		//for (auto child : _childObjectList)
		//{
		//	child->UpdateCurrentAnimation(name);
		//}
	}
	bool Model::Init()
	{
		//if (_animation && _animation != &DefaultAnimation)
		//{
		//	_animation->Init();
		//}

		Build();
		SizeCheck();

        CreateVertexBuffer();
        CreateIndexBuffer();
        CreateVertexLayout();

		return false;
	}
	bool Model::Frame()
	{
		//_animation->Frame();
		return false;
	}
	bool Model::Render()
	{
		auto dc = g_dxWindow->GetDeviceContext();
		//_animation->Render();

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
		dc->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
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

		dc->DrawIndexed(_indexList.size(), 0, 0);

		return false;
	}
	bool Model::Release()
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
        if (_vertexLayout)
        {
            _vertexLayout->Release();
			_vertexLayout = nullptr;
        }
		_vs = nullptr;
		_ps = nullptr;

		//if (_animation && _animation != &DefaultAnimation)
		//{
		//	_animation->Release();
		//	delete _animation;
		//	_animation = nullptr;
		//}

		_vertexList.clear();
		_indexList.clear();

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

	//ActionInfo Animation::DefaultAction{ 0, std::vector<ActionFrameInfo>{ActionFrameInfo{}} };

	//void Animation::SetAdditionalAction(std::string name, ActionInfo info)
	//{
	//	_actionList.insert(std::make_pair(name, info));
	//}
	//HMatrix44 Animation::GetInterpolate()
	//{
	//	HMatrix44 ret;
	//	float animationElapseTime = (float)(_animationTimer.GetElapseTime() / 1000.0f);
	//	int beforeIndex = animationElapseTime * _frameSpeed;
	//	int afterIndex = beforeIndex + 1;
	//	if (afterIndex == _currentAction->EndFrame)
	//	{
	//		ret = _currentAction->FrameInfoList[beforeIndex].Matrix;
	//	}
	//	else if (_currentAction->EndFrame <= beforeIndex)
	//	{
	//		_animationTimer.Init();
	//		ret = _currentAction->FrameInfoList[0].Matrix;
	//	}
	//	else
	//	{
	//		float beforeTime = beforeIndex / _frameSpeed;
	//		float afterTime = afterIndex / _frameSpeed;
	//		float t = (animationElapseTime - beforeTime) / (afterTime - beforeTime);
	//		
	//		ActionFrameInfo beforeInfo = _currentAction->FrameInfoList[beforeIndex];
	//		ActionFrameInfo afterInfo = _currentAction->FrameInfoList[afterIndex];

	//		Vector3 pos = Lerp(beforeInfo.Translate, afterInfo.Translate, t);
	//		Vector3 scale = Lerp(beforeInfo.Scale, afterInfo.Scale, t);
	//		Quaternion rotate = SLerp(beforeInfo.Rotate, afterInfo.Rotate, t);

	//		ret = HMatrix44::Scale(scale) * HMatrix44(rotate.GetRotateMatrix(), { 0, 0, 0 }) * HMatrix44::Translate(pos);
	//	}

	//	return ret;
	//}
	//void Animation::UpdateCurrentAction(std::string name)
	//{
	//	if (_actionList.find(name) != _actionList.end())
	//	{
	//		_currentAction = &_actionList.find(name)->second;
	//	}
	//}
	//bool Animation::Init()
	//{
	//	_animationTimer.Init();
	//	_currentAction = &DefaultAction;
	//	_currentFrame = 0;

	//	return true;
	//}
	//bool Animation::Frame()
	//{
	//	_animationTimer.Frame();

	//	return true;
	//}
	//bool Animation::Render()
	//{
	//	_animationTimer.Render();
	//	return true;
	//}
	//bool Animation::Release()
	//{
	//	_actionList.clear();
	//	_currentAction = nullptr;
	//	_animationTimer.Release();

	//	return true;
	//}
}

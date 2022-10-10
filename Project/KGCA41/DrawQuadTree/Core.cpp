#pragma comment(lib, "d3dcompiler.lib")

#include "Core.h"
#include "d3dcompiler.h"

void Core::Run()
{
	Init();
	while (1)
	{
		Frame();
		Render();

		Sleep(100);
	}
	Release();
}

HRESULT Core::CreateVertexBuffer(Object2D* object)
{
	HRESULT hr;

	Vector2D center = object->GetVolume()->GetCenter();
	std::vector<Vector2D*> vertice = object->GetVolume()->GetVertexes();

	std::vector<SimpleVertex> originVertex;
	for (auto vertex : vertice)
	{
		SimpleVertex sv = GetSimpleVertex(object, center, vertex);
		originVertex.push_back(sv);
	}

	std::vector<SimpleVertex> vertexList;
	vertexList.push_back(originVertex[0]);
	vertexList.push_back(originVertex[1]);
	vertexList.push_back(originVertex[2]);
	vertexList.push_back(originVertex[2]);
	vertexList.push_back(originVertex[1]);
	vertexList.push_back(originVertex[3]);
	_verticeList.insert(std::make_pair(object, vertexList));

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * vertexList.size();
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource;
	ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));
	subResource.pSysMem = &vertexList.at(0);

	ID3D11Buffer* buffer;
	hr = _device->CreateBuffer(&bufferDesc, &subResource, &buffer);
	_buffers.insert(std::make_pair(object, buffer));

	return hr;
}

HRESULT Core::CreateVertexShader()
{
	HRESULT hr;
	ID3DBlob* errorCode = nullptr;
	hr = D3DCompileFromFile(L"VertexShader.hlsl", NULL, NULL, "main", "vs_5_0", 0, 0, &_vsCode, &errorCode);
	if (FAILED(hr))
	{
		if (errorCode != nullptr)
		{
			OutputDebugStringA((char*)errorCode->GetBufferPointer());
			errorCode->Release();
		}
		return hr;
	}

	hr = _device->CreateVertexShader(_vsCode->GetBufferPointer(), _vsCode->GetBufferSize(), NULL, &_vertexShader);

	return hr;
}

HRESULT Core::CreatePixelShader()
{
	HRESULT hr;
	ID3DBlob* errorCode = nullptr;
	hr = D3DCompileFromFile(L"PixelShader.hlsl", NULL, NULL, "main", "ps_5_0", 0, 0, &_psCode, &errorCode);
	if (FAILED(hr))
	{
		if (errorCode != nullptr)
		{
			OutputDebugStringA((char*)errorCode->GetBufferPointer());
			errorCode->Release();
		}
		return hr;
	}

	hr = _device->CreatePixelShader(_psCode->GetBufferPointer(), _psCode->GetBufferSize(), NULL, &_pixelShader);

	return hr;
}

HRESULT Core::CreateVertexLayout()
{
	HRESULT hr;

	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT elementCount = sizeof(inputElementDesc) / sizeof(inputElementDesc[0]);
	hr = _device->CreateInputLayout(inputElementDesc, elementCount, _vsCode->GetBufferPointer(), _vsCode->GetBufferSize(), &_vertexLayout);

	return hr;
}

SimpleVertex Core::GetSimpleVertex(Object2D* object, Vector2D center, Vector2D* vertex)
{
	Vector2D pos = center + *vertex;
	*pos[0] = pos.Get(0) + (_mapWidth / 2);
	*pos[0] = pos.Get(0) / _mapWidth * 2;
	*pos[0] = pos.Get(0) - 1.0f;
	*pos[1] = pos.Get(1) + (_mapHeight / 2);
	*pos[1] = pos.Get(1) / _mapHeight * 2;
	*pos[1] = pos.Get(1) - 1.0f;

	SimpleVertex sv;
	if (object == _player)
	{
		SimpleVertex tmp{ pos.Get(0), pos.Get(1), 0, 1.0f, 0.0f, 0.0f, 0.0f };
		sv = tmp;
	}
	else
	{
		SimpleVertex tmp{ pos.Get(0), pos.Get(1), 0, 0.0f, 0.0f, 0.0f, 0.0f };
		sv = tmp;
	}
	return sv;
}

void Core::UpdateVertex(Object2D* object)
{
	Vector2D center = object->GetVolume()->GetCenter();
	std::vector<Vector2D*> vertice = object->GetVolume()->GetVertexes();

	std::vector<SimpleVertex> originVertex;
	for (auto vertex : vertice)
	{
		SimpleVertex sv = GetSimpleVertex(object, center, vertex);
		originVertex.push_back(sv);
	}

	std::vector<SimpleVertex> vertexList;
	vertexList.push_back(originVertex[0]);
	vertexList.push_back(originVertex[1]);
	vertexList.push_back(originVertex[2]);
	vertexList.push_back(originVertex[2]);
	vertexList.push_back(originVertex[1]);
	vertexList.push_back(originVertex[3]);

	auto iter = _verticeList.find(object);
	iter->second = vertexList;
}

bool Core::Init()
{
	int objectCount = 100;
	for (int i = 0; i < objectCount; ++i)
	{
		float centerX = (rand() % _mapWidth) - (_mapWidth / 2);
		float centerY = (rand() % _mapHeight) - (_mapHeight / 2);
		float width = rand() % 10 + 1.0f;
		float height = rand() % 10 + 1.0f;
		Object2D* object = new Object2D(new Custom::Rectangle(centerX, centerY, width, height), Rigidbody2D());

		_staticObjects.push_back(object);
		_qt.AddStaticObject(object);
	}
	for (int i = 0; i < objectCount; ++i)
	{
		float centerX = (rand() % _mapWidth) - (_mapWidth / 2);
		float centerY = (rand() % _mapHeight) - (_mapHeight / 2);
		float width = rand() % 10 + 1.0f;
		float height = rand() % 10 + 1.0f;
		Object2D* object = new Object2D(new Custom::Rectangle(centerX, centerY, width, height), Rigidbody2D());

		float forceX = rand() % 50;
		float forceY = rand() % 50;
		object->GetRigidBody()->AddForce(Vector2D(Vector2DData{ forceX, forceY }));

		_dynamicObjects.push_back(object);
		_qt.AddDynamicObject(object);
	}

	_player = new Object2D(new Custom::Rectangle(0, 0, 20, 20), Rigidbody2D());
	_player->GetRigidBody()->AddForce(Vector2D(Vector2DData{ 30, 30 }));

	if (FAILED(CreateVertexBuffer(_player)))
	{
		return false;
	}
	for (auto object : _staticObjects)
	{
		if (FAILED(CreateVertexBuffer(object)))
		{
			return false;
		}
	}
	for (auto object : _dynamicObjects)
	{
		if (FAILED(CreateVertexBuffer(object)))
		{
			return false;
		}
	}

	if (FAILED(CreateVertexShader()))
	{
		return false;
	}
	if (FAILED(CreatePixelShader()))
	{
		return false;
	}
	if (FAILED(CreateVertexLayout()))
	{
		return false;
	}

	return true;
}

bool Core::Frame()
{
	float deltaTime = 0.1;
	_player->GetRigidBody()->Calculate(deltaTime);
	Vector2D pos = _player->GetVolume()->GetCenter() + _player->GetRigidBody()->GetVelocity() * deltaTime;
	_player->GetVolume()->Reposition(pos);
	UpdateVertex(_player);

	_qt.Frame();
	for (auto object : _dynamicObjects)
	{
		object->GetRigidBody()->Calculate(deltaTime);
		Vector2D pos = object->GetVolume()->GetCenter() + object->GetRigidBody()->GetVelocity() * deltaTime;
		object->GetVolume()->Reposition(pos);
		UpdateVertex(object);
	}

	return true;
}

bool Core::Render()
{
	auto showObjects = _qt.GetCollidedObjects(_player);
	showObjects.push_back(_player);
	for (auto object : showObjects)
	{
		ID3D11Buffer* buffer = _buffers.find(object)->second;
		std::vector<SimpleVertex> vertexList = _verticeList.find(object)->second;
		_deviceContext->UpdateSubresource(buffer, 0, NULL, &vertexList.at(0), 0, 0);

		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		_deviceContext->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
		_deviceContext->IASetInputLayout(_vertexLayout);
		_deviceContext->VSSetShader(_vertexShader, NULL, 0);
		_deviceContext->PSSetShader(_pixelShader, NULL, 0);
		_deviceContext->Draw(vertexList.size(), 0);
	}

	return true;
}

bool Core::Release()
{
	for (auto object : _staticObjects)
	{
		delete object;
	}
	for (auto object : _dynamicObjects)
	{
		delete object;
	}
	for (auto buffer : _buffers)
	{
		buffer.second->Release();
	}
	_vertexShader->Release();
	_pixelShader->Release();
	_vsCode->Release();
	_psCode->Release();
	_vertexLayout->Release();

	return true;
}

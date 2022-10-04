#include "Terrain.h"
#include "DX2DCamera.h"
#include "Collision.h"
#include <set>
#include <queue>
#include "TextureManager.h"
#include "DXStateManager.h"
#include "ShaderManager.h"

namespace SSB
{
	extern DX2DCamera* g_Camera;

	Terrain::Tile::Tile(int width, int height) : DX2DGameObject({ 0, 0 }, width, height, 0)
	{
	}

	void Terrain::Tile::SetCenter(int posX, int posY)
	{
		Move(posX, posY);
	}

	bool Terrain::Tile::IsAlive()
	{
		return IsInCamera() || IsReady();
	}

	void Terrain::Tile::LinkTop(Tile* top)
	{
		_top = top;
	}

	void Terrain::Tile::LinkBottom(Tile* bottom)
	{
		_bottom = bottom;
	}

	void Terrain::Tile::LinkLeft(Tile* left)
	{
		_left = left;
	}

	void Terrain::Tile::LinkRight(Tile* right)
	{
		_right = right;
	}

	bool Terrain::Tile::IsNeedToPrepareTile()
	{
		if (IsInCamera())
		{
			return !IsFullLinked();
		}
		return false;
	}

	bool Terrain::Tile::IsFullLinked()
	{
		if(IsLeftLinked() && IsRightLinked() && IsTopLinked() && IsBottomLinked())
		{
			return true;
		}
		return false;
	}

	void Terrain::Tile::Clear()
	{
		if (_left != nullptr)
		{
			_left->_right = nullptr;
			_left = nullptr;
		}
		if (_right != nullptr)
		{
			_right->_left = nullptr;
			_right = nullptr;
		}
		if (_top != nullptr)
		{
			_top->_bottom = nullptr;
			_top = nullptr;
		}
		if (_bottom != nullptr)
		{
			_bottom->_top = nullptr;
			_bottom = nullptr;
		}
	}

	bool Terrain::Tile::IsInCamera()
	{
		return Collision::IsCollide(*g_Camera->GetCaptureArea()->GetVolume(), *GetPhysicsObject()->GetVolume());
	}

	bool Terrain::Tile::IsReady()
	{
		if (_left != nullptr)
		{
			if (_left->IsInCamera())
			{
				return true;
			}
		}

		if (_top != nullptr)
		{
			if (_top->IsInCamera())
			{
				return true;
			}
		}

		if (_right != nullptr)
		{
			if (_right->IsInCamera())
			{
				return true;
			}
		}

		if (_bottom != nullptr)
		{
			if (_bottom->IsInCamera())
			{
				return true;
			}
		}

		return false;
	}

	bool Terrain::Tile::Init()
	{
		GetDXObject()->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
		GetDXObject()->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithoutMask", "ps_5_0"));
		GetDXObject()->SetSprite(SpriteLoader::GetInstance().Load(L"Sea.bmp", L"Sea1", DXStateManager::kDefaultWrapSample));

		DX2DGameObject::Init();

		_left = nullptr;
		_top = nullptr;
		_right = nullptr;
		_right = nullptr;

		return true;
	}

	bool Terrain::Tile::Frame()
	{
		DX2DGameObject::Frame();

		return true;
	}

	bool Terrain::Tile::Render()
	{
		DX2DGameObject::Render();

		return true;
	}

	bool Terrain::Tile::Release()
	{
		DX2DGameObject::Release();

		if (_left != nullptr)
		{
			_left->_right = nullptr;
		}
		_left = nullptr;

		if (_right != nullptr)
		{
			_right->_left = nullptr;
		}
		_right = nullptr;

		if (_top != nullptr)
		{
			_top->_bottom = nullptr;
		}
		_top = nullptr;

		if (_bottom != nullptr)
		{
			_bottom->_top = nullptr;
		}
		_bottom = nullptr;

		return true;
	}

	void Terrain::Tile::PreInit()
	{
		Render();
	}

	Terrain::TileMemoryPool::TileMemoryPool(int widthUnit, int heightUnit) : _widthUnit(widthUnit), _heightUnit(heightUnit)
	{
		SpriteLoader::GetInstance().RegisterSpriteFromFile(L"Sea.bmp", L"Sea");
	}

	Terrain::TileMemoryPool::~TileMemoryPool()
	{
		for (auto tile : _tileList)
		{
			tile->Release();
			delete tile;
		}
		_tileList.clear();
	}

	Terrain::Tile* Terrain::TileMemoryPool::GetTile()
	{
		for (auto tile : _tileList)
		{
			if (!tile->IsUsing())
			{
				tile->SetUse();
				int index = rand() % 6 + 1;
				std::wstring seaName = L"Sea" + std::to_wstring(index);
				tile->GetDXObject()->SetSprite(SpriteLoader::GetInstance().Load(L"Sea.bmp", seaName, DXStateManager::kDefaultWrapSample));
				return tile;
			}
		}

		RequireMemory(_tileCount + 10);
		return GetTile();
	}

	Terrain::Tile * Terrain::TileMemoryPool::GetTile(int posX, int posY)
	{
		Tile* tile = GetTile();
		tile->SetCenter(posX, posY);
		return tile;
	}

	std::pair<int, int> Terrain::TileMemoryPool::GetLeftPosition(Tile* tile)
	{
		return std::pair<int, int>(tile->GetCenter().Get(0) - _widthUnit, tile->GetCenter().Get(1));
	}

	std::pair<int, int> Terrain::TileMemoryPool::GetRightPosition(Tile* tile)
	{
		return std::pair<int, int>(tile->GetCenter().Get(0) + _widthUnit, tile->GetCenter().Get(1));
	}

	std::pair<int, int> Terrain::TileMemoryPool::GetTopPosition(Tile* tile)
	{
		return std::pair<int, int>(tile->GetCenter().Get(0), tile->GetCenter().Get(1) + _heightUnit);
	}

	std::pair<int, int> Terrain::TileMemoryPool::GetBottomPosition(Tile* tile)
	{
		return std::pair<int, int>(tile->GetCenter().Get(0), tile->GetCenter().Get(1) - _heightUnit);
	}

	void Terrain::TileMemoryPool::RequireMemory(int newCount)
	{
		_tileList.resize(newCount);
		for (int i = _tileCount; i < newCount; ++i)
		{
			auto tile = new Tile(_widthUnit, _heightUnit);
			tile->Init();
			_tileList[i] = tile;
		}
		_tileCount = newCount;
	}

	Terrain::Terrain(int mapWidth, int mapHeight)
	{
		_widthCount = mapWidth / _widthUnit;
		_heightCount = mapHeight / _heightUnit;
	}

	bool Terrain::ShouldBeAlive(Terrain::Tile* tile)
	{
		return tile->IsAlive();
	}

	void Terrain::LinkTile(std::queue<std::pair<std::pair<int, int>, Tile*>>& q, Tile* tile)
	{
		if (tile->IsNeedToPrepareTile())
		{
			if (!tile->IsLeftLinked())
			{
				auto newPos = _memoryPool->GetLeftPosition(tile);
				Tile* newTile;
				if (_tiles.find(newPos) != _tiles.end())
				{
					newTile = _tiles.find(newPos)->second;
				}
				else
				{
					newTile = _memoryPool->GetTile(newPos.first, newPos.second);
					auto pair = std::make_pair(newPos, newTile);
					_tiles.insert(pair);
					q.push(pair);
				}
				tile->LinkLeft(newTile);
				newTile->LinkRight(tile);
			}
			if (!tile->IsRightLinked())
			{
				auto newPos = _memoryPool->GetRightPosition(tile);
				Tile* newTile;
				if (_tiles.find(newPos) != _tiles.end())
				{
					newTile = _tiles.find(newPos)->second;
				}
				else
				{
					newTile = _memoryPool->GetTile(newPos.first, newPos.second);
					auto pair = std::make_pair(newPos, newTile);
					_tiles.insert(pair);
					q.push(pair);
				}
				tile->LinkRight(newTile);
				newTile->LinkLeft(tile);
			}
			if (!tile->IsTopLinked())
			{
				auto newPos = _memoryPool->GetTopPosition(tile);
				Tile* newTile;
				if (_tiles.find(newPos) != _tiles.end())
				{
					newTile = _tiles.find(newPos)->second;
				}
				else
				{
					newTile = _memoryPool->GetTile(newPos.first, newPos.second);
					auto pair = std::make_pair(newPos, newTile);
					_tiles.insert(pair);
					q.push(pair);
				}
				tile->LinkTop(newTile);
				newTile->LinkBottom(tile);
			}
			if (!tile->IsBottomLinked())
			{
				auto newPos = _memoryPool->GetBottomPosition(tile);
				Tile* newTile;
				if (_tiles.find(newPos) != _tiles.end())
				{
					newTile = _tiles.find(newPos)->second;
				}
				else
				{
					newTile = _memoryPool->GetTile(newPos.first, newPos.second);
					auto pair = std::make_pair(newPos, newTile);
					_tiles.insert(pair);
					q.push(pair);
				}
				tile->LinkBottom(newTile);
				newTile->LinkTop(tile);
			}
		}
	}

	bool Terrain::Init()
	{
		_memoryPool = new TileMemoryPool(_widthUnit, _heightUnit);

		std::queue<std::pair<std::pair<int, int>, Tile*>> q;

		{
			auto newTile = _memoryPool->GetTile(0, 0);
			auto pair = std::make_pair(std::make_pair(0, 0), newTile);
			_tiles.insert(pair);
			q.push(pair);
		}

		while (!q.empty())
		{
			auto currentWorkingPair = q.front();
			q.pop();

			auto tile = currentWorkingPair.second;
			LinkTile(q, tile);
		}

		return true;
	}

	bool Terrain::Frame()
	{
		std::set<std::pair<int, int>> deadTiles;
		std::queue<std::pair<std::pair<int, int>, Tile*>> q;
		for (auto tile : _tiles)
		{
			tile.second->Frame();
			q.push(tile);
		}

		while(!q.empty())
		{
			auto currentWorkingPair = q.front();
			q.pop();
			auto tile = currentWorkingPair.second;

			if (!ShouldBeAlive(tile))
			{
				deadTiles.insert(currentWorkingPair.first);
			}
			else
			{
				LinkTile(q, tile);
			}
		}

		for (auto deadTile : deadTiles)
		{
			auto tile = _tiles.find(deadTile)->second;
			tile->SetUnUse();
			tile->Clear();
			_tiles.erase(deadTile);
		}

		for (auto tile : _tiles)
		{
			auto center = g_Camera->PhysicsToDisplay(tile.second->GetCenter());
			tile.second->GetDXObject()->SetCenter(center);

			auto vertice = tile.second->GetPhysicsObject()->GetVolume()->GetVertexes();
			float minX = FLT_MAX;
			float maxX = FLT_MIN;
			float minY = FLT_MAX;
			float maxY = FLT_MIN;
			for (auto vertex : vertice)
			{
				minX = std::fmin(minX, vertex->Get(0));
				maxX = std::fmax(maxX, vertex->Get(0));
				minY = std::fmin(minY, vertex->Get(1));
				maxY = std::fmax(maxY, vertex->Get(1));
			}

			float physicsWidth = maxX - minX;
			float physicsHeight = maxY - minY;

			Rectangle* captureArea = static_cast<Rectangle*>(g_Camera->GetCaptureArea()->GetVolume());
			float screenWidth = physicsWidth / captureArea->GetWidth() * g_Camera->GetWidth();
			float screenHeight = physicsHeight / captureArea->GetHeight() * g_Camera->GetHeight();

			tile.second->GetDXObject()->Resize(screenWidth, screenHeight);
		}

		return true;
	}

	bool Terrain::Render()
	{
		for (auto tile : _tiles)
		{
			tile.second->Render();
		}

		return true;
	}

	bool Terrain::Release()
	{
		_tiles.clear();

		if (_memoryPool)
		{
			delete _memoryPool;
			_memoryPool = nullptr;
		}

		return true;
	}

}

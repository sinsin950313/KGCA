#pragma once

#include <vector>
#include "Common.h"
#include "DX2DGameObject.h"
#include <map>
#include <queue>

namespace SSB
{
	class Terrain : public Common
	{
		class Tile : public DX2DGameObject
		{
			Tile* _left;
			Tile* _top;
			Tile* _right;
			Tile* _bottom;
			bool _used;

		public:
			Tile(int width, int height);

		public:
			void SetCenter(int posX, int posY);
			bool IsAlive();
			void LinkTop(Tile* top);
			void LinkBottom(Tile* bottom);
			void LinkLeft(Tile* left);
			void LinkRight(Tile* right);
			bool IsNeedToPrepareTile();
			bool IsFullLinked();
			bool IsLeftLinked() { return _left != nullptr; }
			bool IsRightLinked() { return _right != nullptr; }
			bool IsTopLinked() { return _top != nullptr; }
			bool IsBottomLinked() { return _bottom != nullptr; }
			bool IsUsing() { return _used; }
			void SetUse() { _used = true; }
			void SetUnUse() { _used = false; }
			void Clear();

		private:
			bool IsInCamera();
			bool IsReady();

		public:
			bool Init() override;
			bool Frame() override;
			bool Render() override;
			bool Release() override;
			void PreInit() override;
		};

		class TileMemoryPool
		{
			std::vector<Tile*> _tileList;
			int _tileCount = 0;
			const int _widthUnit;
			const int _heightUnit;

		public:
			TileMemoryPool(int widthUnit, int heightUnit);
			~TileMemoryPool();

		public:
			Tile* GetTile();
			Tile* GetTile(int posX, int posY);
			std::pair<int, int> GetLeftPosition(Tile* tile);
			std::pair<int, int> GetRightPosition(Tile* tile);
			std::pair<int, int> GetTopPosition(Tile* tile);
			std::pair<int, int> GetBottomPosition(Tile* tile);

		private:
			void RequireMemory(int newCount);
		};

		TileMemoryPool* _memoryPool;
		std::map<std::pair<int, int>, Tile*> _tiles;
		int _widthCount;
		int _heightCount;
		const int _widthUnit = 20;
		const int _heightUnit = 20;

	public:
		Terrain(int mapWidth, int mapHeight);

	private:
		bool ShouldBeAlive(Tile* tile);
		void LinkTile(std::queue<std::pair<std::pair<int, int>, Tile*>>& q, Tile* tile);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}

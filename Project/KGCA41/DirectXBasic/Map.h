#pragma once

#include "Common.h"
#include "DXDrawableInterface.h"
#include <vector>
#include "Shader.h"
#include "Matrix.h"
#include "DXObject.h"
#include "Camera.h"
#include "CollisionDetector.h"
#include "Box1.h"
#include "CollisionDetector.h"

namespace SSB
{
	class Map : public DXObject
	{
	private:
		class MapModel : public Model
		{
		private:
			class MapModelVolume : public Box1Volume
			{
			private:
				std::vector<MapModelVolume*> _childs;
			};

		private:
			MapModelVolume* _root;
			std::vector<MapModelVolume*> _renderVolumeList;

		private:
			float _celldistance = 1.0f;
			float _heightScale = 100;
			float tileX = 1.0f;
			float tileY = 1.0f;
			unsigned int _widthVertexCount = 256 + 1u;
			unsigned int _heightVertexCount = 256 + 1u;

		public:
			MapModel();

		private:
			Vector3 CalculateFaceNormal(UINT i0, UINT i1, UINT i2);
			void CalculateVertexNormal();
			float GetCoordinateHeight(int x, int z);
			float Lerp(float start, float end, float param);

		private:
			void Build() override;

		public:
			void SetSize(float widthVertexCount, float heightVertexCount);
			void SetHeightMap(std::wstring fileName);
			float GetHeight(int x, int z);

		public:
			// Render space division works here
			bool Render() override;
		};
		class MapVolume : public Box1Volume
		{
		public:
			std::vector<TriangleData> GetWorldBaseTriangles() override;
		};
		class RayToMapVolumeCollisionDetector : public CollisionDetectorInterface
		{
		public:
			bool IsCollide(CollisionSystemVolume* ray, CollisionSystemVolume* mapVolume) override;
			bool IsIn(CollisionSystemVolume* ray, CollisionSystemVolume* mapVolume) override;
			std::vector<Vector3> GetIntersections(CollisionSystemVolume* ray, CollisionSystemVolume* mapVolume) override;
		};

	private:
		MapModel* _model;
		ID3D11Texture2D* _heightTexture;
		std::vector<MapVolume*> _volumes;

		bool _bDebug = false;

	public:
		Map();
		~Map() override;

	public:
		void SetComponentCount(unsigned int widthCount, unsigned int heightCount);
		void SetSectionCount(unsigned int widthCount, unsigned int heightCount);
		void SetSectionSize(unsigned int size);
		void SetHeightMap(std::wstring fileName);
		float GetHeight(float x, float z);

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;
	};
}

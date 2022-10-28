#pragma once

#include "Common.h"
#include "DXDrawableInterface.h"
#include <vector>
#include "Model.h"
#include "DXObject.h"

namespace SSB
{
	class Map : public Common
	{
	private:
		class Node : public DXObject
		{
		private:
			std::vector<Node*> _nodes;

		public:
			bool Init() override;
			bool Frame() override;
			bool Render() override;
			bool Release() override;
			void Draw(ID3D11DeviceContext* dc) override;
			void UpdateParentData(Position2D parentCenter, float parentRadian) override { }
		};
		Terrain* _terrain;
		Node* _root;

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}

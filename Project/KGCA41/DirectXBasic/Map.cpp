#include "Map.h"

namespace SSB
{
	bool Map::Init()
	{
		//DXObject::Init();

		class SubTerrain : public Model
		{
			void Build() override
			{

			}
		};

		_root = new Node();
		_root->SetModel(new SubTerrain);
		//_root = new Node(lt, lb, rt, rb, terrain->GetWidth(), terrain->GetDepth());

		return true;
	}
	bool Map::Render()
	{
		//std::vector<Node*> drawNodeList = _root->GetDrawNodeList();
		//for (auto node : drawNodeList)
		//{
		//	node->Render();
		//}
	}
}

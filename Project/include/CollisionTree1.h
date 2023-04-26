#pragma once

#include "Common.h"
#include "Volume1.h"
#include "Box1.h"

namespace SSB
{
	class CollisionTree1 : public Common, public Box1Volume
	{
	protected:
		class Node : public Box1Volume
		{
		private:
			std::vector<Volume1*> _staticObjects;
			std::vector<Volume1*> _dynamicObjects;

		protected:
			std::vector<Node*> _childNodes;

		public:
			Node(int currentLayer, Vector3 lbn, Vector3 rtf, CollisionTree1* tree);
			~Node();

		public:
			//Consider totally in stuation, not overlap
			bool IsIn(Volume1* object);
			void AddStaticCollider(Volume1* object);
			void AddDynamicCollider(Volume1* object);
			std::vector<Volume1*> GetCollidedObjects(Volume1* target);

		public:
			void ClearDynamicObjects();
			void Clear();
		};

	private:
		int _maxLayer = 3;
		std::vector<Volume1*> _dynamicColliderList;

	protected:
		Node* _root = nullptr;

	public:
		CollisionTree1(int maxLayer = 3) : _maxLayer(maxLayer) { }
		virtual ~CollisionTree1() { delete _root; }

	public:
		int GetMaxLayer() { return _maxLayer; }
		void AddStaticCollider(Volume1* collider) { _root->AddStaticCollider(collider); }
		void AddDynamicCollider(Volume1* collider) { _root->AddDynamicCollider(collider); _dynamicColliderList.push_back(collider); }
		void UpdateDynamicCollider(Volume1* collider);
		std::vector<Volume1*> GetCollidedObjects(Volume1* target) { return _root->GetCollidedObjects(target); }
		bool Frame() override
		{
			_root->ClearDynamicObjects();
			for (auto iter = _dynamicColliderList.begin(); iter != _dynamicColliderList.end(); ++iter)
			{
				UpdateDynamicCollider(*iter);
			}
			return true;
		}
		void ClearDynamicObject()
		{
			_root->ClearDynamicObjects();
		}
		void Clear()
		{
			_dynamicColliderList.clear();
			_root->Clear();
		}
	};

	class QuadTree : public CollisionTree1
	{
	private:
		class QuadTreeNode : public Node
		{
		public:
			QuadTreeNode(int currentLayer, Vector3 lbn, Vector3 rtf, CollisionTree1* tree);
		};

	public:
		bool Init() override;
		bool Render() override { return true; }
		bool Release() override { return true; }
	};
	//class OctTree : public CollisionTree1
	//{
	//	
	//};
}

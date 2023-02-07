#pragma once

#include "Common.h"
#include "Volume1.h"
#include "Box1.h"
#include "VolumeFactory.h"
#include <map>
#include <set>
#include "CollisionDetector.h"

namespace SSB
{
	class CollisionTree1 : public Common, public Box1Volume
	{
	protected:
		class Node : public Common
		{
		private:
			std::set<Volume1*> _staticObjects;
			std::set<Volume1*> _dynamicObjects;
			SphereToSphereCollisionDetector _ssColCheck;
			AABBToAABBCollisionDetector _aaColCheck;
			OBBToOBBCollisionDetector _ooColCheck;

		protected:
			int _currentLayer;
			CollisionTree1* _owner;
			std::vector<Node*> _childNodes;

		public:
			Node(int currentLayer, CollisionTree1* tree);
			~Node();

		private:
			bool RoughCollisionCheck(Volume1* target, Volume1* object);

		protected:
			virtual bool IsIn(Volume1* object) = 0;		//Consider totally in stuation, not overlap

		public:
			int GetCurrentLayer();
			void AddStaticCollider(Volume1* object);
			void AddDynamicCollider(Volume1* object);
			std::vector<Volume1*> GetCollidedObjects(Volume1* target);
			std::vector<Vector3> GetIntersections(Volume1* target);
			void Remove(Volume1* volume);
			void ClearDynamicObjects();
			void Clear();

		public:
			bool Frame() override;
			bool Render() override;
			bool Release() override;
		};

	private:
		int _maxLayer = 3;
		std::set<Volume1*> _dynamicColliderList;
		std::map<VolumeType, std::map<VolumeType, CollisionDetectorInterface*>> _volumeTypeToDetectorMap;
		std::map<Volume1*, VolumeType> _volumeToTypeMap;
		std::map<VolumeType, std::set<Volume1*>> _volumeTypeToVolumeSetMap;

	private:
		std::map<VolumeType, CollisionDetectorInterface*> _volumeTypeToDetectorMapForNode;

	protected:
		Node* _root = nullptr;

	public:
		CollisionTree1(int maxLayer = 3);
		virtual ~CollisionTree1();

	private:
		void UpdateDynamicCollider(Volume1* collider);

	public:
		int GetMaxLayer();
		void Register(VolumeType fromType, CollisionDetectorInterface* detector, VolumeType toType);
		void AddStaticCollider(VolumeType type, Volume1* collider);
		void AddDynamicCollider(VolumeType type, Volume1* collider);
		std::vector<Volume1*> GetCollidedObjects(Volume1* target);
		std::vector<Vector3> GetIntersections(Volume1* volume);
		VolumeType GetVolumeType(Volume1* volume);
		CollisionDetectorInterface* GetCollisionDetector(VolumeType fromType, VolumeType toType);
		void Remove(Volume1* volume);
		void ClearDynamicObject();
		void Clear();

	public:
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class QuadTree : public CollisionTree1
	{
	private:
		class QuadTreeNode : public Node
		{
		private:
			Volume1* _volume;

		public:
			QuadTreeNode(int currentLayer, CollisionTree1* tree, Volume1* parentVolume = nullptr);

		public:
			void SetPosition(Vector3 position);
			void SetRotation(float yaw, float pitch, float roll);
			void SetScale(float width, float height, float depth);

		protected:
			bool IsIn(Volume1* object) override;

		public:
			bool Init() override;
		};

	public:
		QuadTree();

	public:
		void SetPosition(Vector3 position);
		void SetRotation(float yaw, float pitch, float roll);
		void SetScale(float width, float height, float depth);

	public:
		bool Init() override;
	};

	//class OctTree : public CollisionTree1
	//{
	//	
	//};
}

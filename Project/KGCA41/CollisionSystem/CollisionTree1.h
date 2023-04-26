#pragma once

#include "Common.h"
#include "CollisionSystemVolume.h"
#include "Box1.h"
#include "VolumeFactory.h"
#include <map>
#include <set>
#include "CollisionDetector.h"

namespace SSB
{
	class CollisionTree1 : public Common
	{
	protected:
		class Node : public Common
		{
		private:
			std::set<CollisionSystemVolume*> _staticObjects;
			std::set<CollisionSystemVolume*> _dynamicObjects;
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
			bool RoughCollisionCheck(CollisionSystemVolume* target, CollisionSystemVolume* object);

		protected:
			virtual bool IsIn(CollisionSystemVolume* target) = 0;		//Consider totally in stuation, not overlap

		public:
			int GetCurrentLayer();
			void AddStaticCollider(CollisionSystemVolume* object);
			void AddDynamicCollider(CollisionSystemVolume* object);
			std::vector<CollisionSystemVolume*> GetCollidedObjects(CollisionSystemVolume* target);
			void Remove(CollisionSystemVolume* volume);
			void ClearDynamicObjects();
			void Clear();

		public:
			bool Frame() override;
			bool Render() override;
			bool Release() override;
		};

	private:
		int _maxLayer = 3;
		std::set<CollisionSystemVolume*> _dynamicColliderList;
		std::map<VolumeType, std::map<VolumeType, CollisionDetectorInterface*>> _volumeTypeToDetectorMap;
		std::map<CollisionSystemVolume*, VolumeType> _volumeToTypeMap;
		std::map<VolumeType, std::set<CollisionSystemVolume*>> _volumeTypeToVolumeSetMap;		// Does this useful?

	protected:
		Node* _root = nullptr;

	public:
		CollisionTree1(int maxLayer = 3);
		virtual ~CollisionTree1();

	private:
		void ClearDynamicObject();
		void UpdateDynamicCollider(CollisionSystemVolume* collider);
		VolumeType GetVolumeType(CollisionSystemVolume* volume);
		CollisionDetectorInterface* GetCollisionDetector(VolumeType fromType, VolumeType toType);

	public:
		int GetMaxLayer();
		void Register(VolumeType fromType, CollisionDetectorInterface* detector, VolumeType toType);
		void AddCollider(CollisionSystemVolume* collider);
		std::vector<CollisionSystemVolume*> GetCollidedObjects(CollisionSystemVolume* target);
		std::vector<CollisionSystemVolume*> GetCollidedObjects(CollisionSystemVolume* target, VolumeType finalType);
		std::vector<Vector3> GetIntersections(CollisionSystemVolume* volume);
		std::vector<Vector3> GetIntersections(CollisionSystemVolume* volume, VolumeType finalType);
		void Remove(CollisionSystemVolume* volume);
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

		private:
			bool IsIn(CollisionSystemVolume* target) override;

		public:
			void SetPosition(Vector3 position);
			//void SetRotation(float yaw, float pitch, float roll);
			void SetScale(float width, float height, float depth);

		public:
			bool Init() override;
		};

	public:
		QuadTree();

	public:
		void SetPosition(Vector3 position);
		//void SetRotation(float yaw, float pitch, float roll);
		void SetScale(float width, float height, float depth);

	public:
		bool Init() override;
	};

	//class OctTree : public CollisionTree1
	//{
	//	
	//};
}

#include "CollisionTree1.h"

namespace SSB
{
	CollisionTree1::Node::Node(int currentLayer, CollisionTree1* tree) : _currentLayer(currentLayer), _owner(tree)
	{
	}
	CollisionTree1::Node::~Node()
	{
		_staticObjects.clear();
		_dynamicObjects.clear();
		for (auto node : _childNodes)
		{
			delete node;
		}
		_childNodes.clear();
	}
	int CollisionTree1::Node::GetCurrentLayer()
	{
		return _currentLayer;
	}
	void SSB::CollisionTree1::Node::AddStaticCollider(Volume1* object)
	{
		bool in = false;
		if (IsIn(object))
		{
			for (auto node : _childNodes)
			{
				if (node->IsIn(object))
				{
					in = true;
					node->AddStaticCollider(object);
					break;
				}
			}
		}

		if (!in)
		{
			_staticObjects.insert(object);
		}
	}
	void SSB::CollisionTree1::Node::AddDynamicCollider(Volume1* object)
	{
		bool in = false;
		if (IsIn(object))
		{
			for (auto node : _childNodes)
			{
				if (node->IsIn(object))
				{
					in = true;
					node->AddDynamicCollider(object);
					break;
				}
			}
		}

		if (!in)
		{
			_dynamicObjects.insert(object);
		}
	}
	std::vector<Volume1*> CollisionTree1::Node::GetCollidedObjects(Volume1* target)
	{
		std::vector<Volume1*> ret;
		for (auto node : _childNodes)
		{
			auto tmp = node->GetCollidedObjects(target);
			ret.insert(ret.end(), tmp.begin(), tmp.end());
		}

		VolumeType fromVolumeType = _owner->GetVolumeType(target);
		for (auto object : _staticObjects)
		{
			VolumeType toVolumeType = _owner->GetVolumeType(object);
			CollisionDetectorInterface* detector = _owner->GetCollisionDetector(fromVolumeType, toVolumeType);
			if (detector != nullptr)
			{
				if (detector->IsCollide(target, object))
				{
					ret.push_back(target);
				}
			}
		}

		for (auto object : _dynamicObjects)
		{
			VolumeType toVolumeType = _owner->GetVolumeType(object);
			CollisionDetectorInterface* detector = _owner->GetCollisionDetector(fromVolumeType, toVolumeType);
			if (detector != nullptr)
			{
				if (detector->IsCollide(target, object))
				{
					ret.push_back(target);
				}
			}
		}

		return ret;
	}
	std::vector<Vector3> CollisionTree1::Node::GetIntersections(Volume1* target)
	{
		std::vector<Vector3> ret;
		for (auto node : _childNodes)
		{
			auto tmp = node->GetIntersections(target);
			ret.insert(ret.end(), tmp.begin(), tmp.end());
		}

		VolumeType fromVolumeType = _owner->_volumeToTypeMap.find(target)->second;
		for (auto object : _staticObjects)
		{
			VolumeType toVolumeType = _owner->_volumeToTypeMap.find(object)->second;
			CollisionDetectorInterface* detector = _owner->_volumeTypeToDetectorMap.find(fromVolumeType)->second.find(toVolumeType)->second;
			if(detector->IsCollide(target, object))
			{
				auto returnList = detector->GetIntersections(target, object);
				ret.insert(ret.end(), returnList.begin(), returnList.end());
			}
		}

		for (auto object : _dynamicObjects)
		{
			VolumeType toVolumeType = _owner->_volumeToTypeMap.find(object)->second;
			CollisionDetectorInterface* detector = _owner->_volumeTypeToDetectorMap.find(fromVolumeType)->second.find(toVolumeType)->second;
			if(detector->IsCollide(target, object))
			{
				auto returnList = detector->GetIntersections(target, object);
				ret.insert(ret.end(), returnList.begin(), returnList.end());
			}
		}

		return ret;
	}
	void CollisionTree1::Node::Remove(Volume1* volume)
	{
		if (_staticObjects.find(volume) != _staticObjects.end())
		{
			_staticObjects.erase(volume);
		}

		if (_dynamicObjects.find(volume) != _staticObjects.end())
		{
			_dynamicObjects.erase(volume);
		}

		for (auto child : _childNodes)
		{
			child->Remove(volume);
		}
	}
	void CollisionTree1::Node::ClearDynamicObjects()
	{
		_dynamicObjects.clear();
		for (auto node : _childNodes)
		{
			node->ClearDynamicObjects();
		}
	}
	void CollisionTree1::Node::Clear()
	{
		_staticObjects.clear();
		_dynamicObjects.clear();
		for (auto node : _childNodes)
		{
			node->Clear();
		}
	}
	bool CollisionTree1::Node::Frame()
	{
		for (auto child : _childNodes)
		{
			if (!child->Frame())
			{
				return false;
			}
		}
		return true;
	}
	bool CollisionTree1::Node::Render()
	{
		for (auto child : _childNodes)
		{
			if (!child->Render())
			{
				return false;
			}
		}
		return true;
	}
	bool CollisionTree1::Node::Release()
	{
		for (auto child : _childNodes)
		{
			if (!child->Release())
			{
				return false;
			}
		}
		return true;
	}
	CollisionTree1::CollisionTree1(int maxLayer) : _maxLayer(maxLayer)
	{
	}
	CollisionTree1::~CollisionTree1()
	{
		delete _root;
	}
	int CollisionTree1::GetMaxLayer()
	{
		return _maxLayer;
	}
	void CollisionTree1::Register(VolumeType fromType, CollisionDetectorInterface* detector, VolumeType toType)
	{
		std::map<VolumeType, std::map<VolumeType, CollisionDetectorInterface*>>::iterator iter;
		if (_volumeTypeToDetectorMap.find(fromType) == _volumeTypeToDetectorMap.end())
		{
			_volumeTypeToDetectorMap.insert(std::make_pair(fromType, std::map<VolumeType, CollisionDetectorInterface*>()));
		}
		iter = _volumeTypeToDetectorMap.find(fromType);

		if (iter->second.find(toType) == iter->second.end())
		{
			iter->second.insert(std::make_pair(toType, detector));
		}
	}
	void CollisionTree1::AddStaticCollider(VolumeType type, Volume1* collider)
	{
		_volumeToTypeMap.insert(std::make_pair(collider, type));
		_volumeTypeToVolumeSetMap.find(type)->second.insert(collider);

		_root->AddStaticCollider(collider);
	}
	void CollisionTree1::AddDynamicCollider(VolumeType type, Volume1* collider)
	{
		_volumeToTypeMap.insert(std::make_pair(collider, type));
		_volumeTypeToVolumeSetMap.find(type)->second.insert(collider);

		_root->AddDynamicCollider(collider);
		_dynamicColliderList.insert(collider);
	}
	void CollisionTree1::UpdateDynamicCollider(Volume1* collider)
	{
		_root->AddDynamicCollider(collider);
	}
	std::vector<Volume1*> CollisionTree1::GetCollidedObjects(Volume1* target)
	{
		return _root->GetCollidedObjects(target);
	}
	std::vector<Vector3> CollisionTree1::GetIntersections(Volume1* volume)
	{
		return _root->GetIntersections(volume);
	}
	VolumeType CollisionTree1::GetVolumeType(Volume1* volume)
	{
		return _volumeToTypeMap.find(volume)->second;
	}
	CollisionDetectorInterface* CollisionTree1::GetCollisionDetector(VolumeType fromType, VolumeType toType)
	{
		if (_volumeTypeToDetectorMap.find(fromType) != _volumeTypeToDetectorMap.end())
		{
			auto iter = _volumeTypeToDetectorMap.find(fromType);
			if (iter->second.find(toType) != iter->second.end())
			{
				return iter->second.find(toType)->second;
			}
		}
		return nullptr;
	}
	void CollisionTree1::Remove(Volume1* volume)
	{
		_root->Remove(volume);
		if (_dynamicColliderList.find(volume) != _dynamicColliderList.end())
		{
			_dynamicColliderList.erase(volume);
		}
	}
	void CollisionTree1::ClearDynamicObject()
	{
		_root->ClearDynamicObjects();
	}
	void CollisionTree1::Clear()
	{
		_dynamicColliderList.clear();
		_root->Clear();
	}
	bool CollisionTree1::Frame()
	{
		_root->Frame();
		_root->ClearDynamicObjects();
		for (auto iter = _dynamicColliderList.begin(); iter != _dynamicColliderList.end(); ++iter)
		{
			UpdateDynamicCollider(*iter);
		}
		return true;
	}
	bool CollisionTree1::Render()
	{
		_root->Render();
		return true;
	}
	bool CollisionTree1::Release()
	{
		_root->Release();
		return true;
	}
	QuadTree::QuadTree()
	{
		_root = new QuadTreeNode(0, this);
	}
	void QuadTree::SetPosition(Vector3 position)
	{
		((QuadTreeNode*)_root)->SetPosition(position);
	}
	void QuadTree::SetRotation(float yaw, float pitch, float roll)
	{
		((QuadTreeNode*)_root)->SetRotation(yaw, pitch, roll);
	}
	void QuadTree::SetScale(float width, float height, float depth)
	{
		((QuadTreeNode*)_root)->SetScale(width, height, depth);
	}
	bool QuadTree::Init()
	{
		return _root->Init();
	}
	QuadTree::QuadTreeNode::QuadTreeNode(int currentLayer, CollisionTree1* tree, Volume1* parentVolume)
		: Node(currentLayer, tree)
	{
		_volume = new AABB1Volume;
		if (parentVolume != nullptr)
		{
			_volume->SetParent(parentVolume);
		}

		if (currentLayer + 1 < tree->GetMaxLayer())
		{
			_childNodes.resize(4);
			for (int i = 0; i < 4; ++i)
			{
				_childNodes[i] = new QuadTreeNode(currentLayer + 1, tree, _volume);
			}
		}
	}
	void QuadTree::QuadTreeNode::SetPosition(Vector3 position)
	{
		_volume->SetPosition(position);
	}
	void QuadTree::QuadTreeNode::SetRotation(float yaw, float pitch, float roll)
	{
		_volume->SetRotation(yaw, pitch, roll);
	}
	void QuadTree::QuadTreeNode::SetScale(float width, float height, float depth)
	{
		_volume->SetScale(width, height, depth);
	}
	bool QuadTree::QuadTreeNode::IsIn(Volume1* object)
	{
		VolumeType volumeType = _owner->GetVolumeType(object);
		auto detector = _owner->GetCollisionDetector(AABB, volumeType);
		if (detector != nullptr)
		{
			return detector->IsIn(_volume, object);
		}
		return false;
	}
	bool QuadTree::QuadTreeNode::Init()
	{
		if (_currentLayer + 1 < _owner->GetMaxLayer())
		{
			Vector3 center = _volume->GetLocalPosition();
			float hWidth = _volume->GetLocalScale().GetX() / 2.0f;
			float hHeight = _volume->GetLocalScale().GetY() / 2.0f;
			float hDepth = _volume->GetLocalScale().GetZ() / 2.0f;

			int lbnDx[4]{ -1, +0, -1, +0 };
			int lbnDy[4]{ -1, -1, -1, -1 };
			int lbnDz[4]{ +0, +0, -1, -1 };
			int rtfDx[4]{ +0, +1, +0, +1 };
			int rtfDy[4]{ +1, +1, +1, +1 };
			int rtfDz[4]{ +1, +1, +0, +0 };

			// 0 1
			// 2 3
			_childNodes.resize(4);
			for (int i = 0; i < 4; ++i)
			{
				Vector3 templbn(
					center.GetX() + lbnDx[i] * hWidth,
					center.GetY() + lbnDy[i] * hHeight,
					center.GetZ() + lbnDz[i] * hDepth);
				Vector3 temprtf(
					center.GetX() + rtfDx[i] * hWidth,
					center.GetY() + rtfDy[i] * hHeight,
					center.GetZ() + rtfDz[i] * hDepth);

				((QuadTreeNode*)_childNodes[i])->SetPosition((templbn + temprtf) / 2);
				((QuadTreeNode*)_childNodes[i])->SetScale(hWidth, hHeight, hDepth);
				_childNodes[i]->Init();
			}

			//{
			//	Vector3 templbn(center.GetX() - hWidth, center.GetY() - hHeight, center.GetZ());
			//	Vector3 temprtf(center.GetX(), center.GetY() + hHeight, center.GetZ() + hDepth);
			//	_childNodes[0] = new QuadTreeNode(currentLayer + 1, templbn, temprtf, tree);
			//}
			//{
			//	Vector3 templbn(center.GetX(), center.GetY() - hHeight, center.GetZ());
			//	Vector3 temprtf(center.GetX() + hWidth, center.GetY() + hHeight, center.GetZ() + hDepth);
			//	_childNodes[1] = new QuadTreeNode(currentLayer + 1, templbn, temprtf, tree);
			//}
			//{
			//	Vector3 templbn(center.GetX() - hWidth, center.GetY() - hHeight, center.GetZ() - hDepth);
			//	Vector3 temprtf(center.GetX(), center.GetY() + hHeight, center.GetZ());
			//	_childNodes[2] = new QuadTreeNode(currentLayer + 1, templbn, temprtf, tree);
			//}
			//{
			//	Vector3 templbn(center.GetX(), center.GetY() - hHeight, center.GetZ() - hDepth);
			//	Vector3 temprtf(center.GetX() + hWidth, center.GetY() + hHeight, center.GetZ());
			//	_childNodes[3] = new QuadTreeNode(currentLayer + 1, templbn, temprtf, tree);
			//}
		}
		return true;
	}
}
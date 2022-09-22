#pragma once

#include "VolumeInterface.h"
#include "Rectangle.h"
#include "Box.h"
#include <vector>
#include "Object.h"
#include "Collision.h"

namespace SSB
{
	template<int dimension>
	class SpaceDivider
	{
	public:
		/// <summary>
		/// Return divided Volume
		/// </summary>
		/// <param name="volume">Map volume</param>
		/// <returns></returns>
		virtual std::vector<Volume<dimension>*> Divide(const Volume<dimension>& volume) = 0;
	};

	/// <summary>
	/// Currently, don't separate WorldDimension and DivideDimension.
	/// Too many things to consider.
	/// WorldDimension = DivideDimension
	/// </summary>
	template<int dimension>
	class CollisionTree
	{
	private:
		class Node : public VolumeInterface<dimension>
		{
		private:
			const int _divideCount;
			Node** _child;
			Volume<dimension>* _space;
			std::vector<Object<dimension>*> _staticObjects;
			std::vector<Object<dimension>*> _dynamicObjects;

		public:
			Node(int divideCount, float layer, int maxLayer, Volume<dimension>* volume, SpaceDivider<dimension>&& divider);
			~Node();
			//Consider totally in stuation, not overlap
			bool IsIn(Object<dimension>* object);
			void AddStaticObject(Object<dimension>* object);
			void AddDynamicObject(Object<dimension>* object);
			void AddStaticObjectForce(Object<dimension>* object);
			void AddDynamicObjectForce(Object<dimension>* object);
			std::vector<Object<dimension>*> GetCollidedObjects(Object<dimension>* obj);

		public:
			const Volume<dimension>* GetVolume() override { return _space; }
			void ClearDynamicObjects();
			void Clear();
		};

	private:
		Node* _root;
		std::vector<Object<dimension>*> _dynamicObjectList;

	public:
		CollisionTree(int divideCount, int maxLayer, Volume<dimension>* volume, SpaceDivider<dimension>&& divider)
		{
			_root = new Node(divideCount, 0, maxLayer, volume, std::forward<SpaceDivider<dimension>&&>(divider));
		}
		virtual ~CollisionTree() { delete _root; }
		void AddStaticObject(Object<dimension>* object);
		void AddDynamicObject(Object<dimension>* object);
		void UpdateDynamicObject(Object<dimension>* object);
		std::vector<Object<dimension>*> GetCollidedObjects(Object<dimension>* obj);
		void Frame()
		{
			_root->ClearDynamicObjects();
			for (auto iter = _dynamicObjectList.begin(); iter != _dynamicObjectList.end(); ++iter)
			{
				UpdateDynamicObject(*iter);
			}
		}
		void ClearDynamicObject()
		{
			_root->ClearDynamicObjects();
		}
		void Clear()
		{
			_dynamicObjectList.clear();
			_root->Clear();
		}
	};

	class QuadTreeDivider : public SpaceDivider<2>
	{
	public:
		virtual std::vector<Volume<2>*> Divide(const Volume<2>& volume);
	};

	class QuadTree : public CollisionTree<2>
	{
	public:
		QuadTree(float width, float height, int maxLayer)
			: CollisionTree(4, maxLayer, new SSB::Rectangle(0, 0, width, height), QuadTreeDivider())
		{

		}
	};

	class OctTreeDivider : public SpaceDivider<3>
	{
	public:
		virtual std::vector<Volume<3>*> Divide(const Volume<3>& volume);
	};

	class OctTree : public CollisionTree<3>
	{
	public:
		OctTree(float width, float height, float depth, float maxLayer)
			: CollisionTree(8, maxLayer, new Box(Vector3D(Vector3DData{ 0, 0, 0 }), width, height, depth), OctTreeDivider())
		{

		}
	};

	template<int dimension>
	inline CollisionTree<dimension>::Node::Node(int divideCount, float layer, int maxLayer, Volume<dimension>* volume, SpaceDivider<dimension>&& divider)
		: _divideCount(divideCount), _space(volume)
	{
		_child = new Node * [divideCount];

		if (layer + 1 < maxLayer)
		{
			std::vector<Volume<dimension>*> dividedVolumes = divider.Divide(*volume);
			for (int i = 0; i < divideCount; ++i)
			{
				_child[i] = new Node(_divideCount, layer + 1, maxLayer, dividedVolumes[i], std::forward<SpaceDivider<dimension>&&>(divider));
			}
		}
		else
		{
			for (int i = 0; i < divideCount; ++i)
			{
				_child[i] = nullptr;
			}
		}
	}

	template<int dimension>
	inline CollisionTree<dimension>::Node::~Node()
	{
		for (int i = 0; i < _divideCount; ++i)
		{
			delete _child[i];
		}
		delete _child;
	}

	template<int dimension>
	inline bool CollisionTree<dimension>::Node::IsIn(Object<dimension>* object)
	{
		return Collision::IsIn(*_space, *object->GetVolume());
	}

	template<int dimension>
	void CollisionTree<dimension>::Node::AddStaticObject(Object<dimension>* object)
	{
		if (IsIn(object))
		{
			bool success = false;
			for (int i = 0; i < _divideCount; ++i)
			{
				if (_child[i] != nullptr && _child[i]->IsIn(object))
				{
					_child[i]->AddStaticObject(object);
					success = true;
				}
			}

			if (!success)
			{
				_staticObjects.push_back(object);
			}
		}
	}

	template<int dimension>
	inline void CollisionTree<dimension>::Node::AddDynamicObject(Object<dimension>* object)
	{
		if (IsIn(object))
		{
			bool success = false;
			for (int i = 0; i < _divideCount; ++i)
			{
				if (_child[i] != nullptr && _child[i]->IsIn(object))
				{
					_child[i]->AddDynamicObject(object);
					success = true;
				}
			}

			if (!success)
			{
				_dynamicObjects.push_back(object);
			}
		}
	}

	template<int dimension>
	void CollisionTree<dimension>::Node::AddStaticObjectForce(Object<dimension>* object)
	{
		_staticObjects.push_back(object);
	}

	template<int dimension>
	inline void CollisionTree<dimension>::Node::AddDynamicObjectForce(Object<dimension>* object)
	{
		_dynamicObjects.push_back(object);
	}

	template<int dimension>
	std::vector<Object<dimension>*> CollisionTree<dimension>::Node::GetCollidedObjects(Object<dimension>* obj)
	{
		const Volume<dimension>* objectVolume = obj->GetVolume();
		std::vector<Object<dimension>*> ret;
		for (auto iter = _staticObjects.begin(); iter != _staticObjects.end(); ++iter)
		{
			if (Collision::IsCollide<dimension>(*(*iter)->GetVolume(), *objectVolume))
			{
				ret.push_back(*iter);
			}
		}
		for (auto iter = _dynamicObjects.begin(); iter != _dynamicObjects.end(); ++iter)
		{
			if (Collision::IsCollide<dimension>(*(*iter)->GetVolume(), *objectVolume))
			{
				ret.push_back(*iter);
			}
		}

		for (int i = 0; i < _divideCount; ++i)
		{
			if (_child[i] != nullptr)
			{
				if (Collision::IsCollide(*_child[i]->GetVolume(), *objectVolume))
				{
					auto collisionObjects = _child[i]->GetCollidedObjects(obj);
					ret.insert(ret.end(), collisionObjects.begin(), collisionObjects.end());
				}
			}
		}
		return ret;
	}

	template<int dimension>
	inline void CollisionTree<dimension>::Node::ClearDynamicObjects()
	{
		_dynamicObjects.clear();
		for (int i = 0; i < _divideCount; ++i)
		{
			if (_child[i] != nullptr)
			{
				_child[i]->ClearDynamicObjects();
			}
		}
	}

	template<int dimension>
	inline void CollisionTree<dimension>::Node::Clear()
	{
		_staticObjects.clear();
		_dynamicObjects.clear();
		for (int i = 0; i < _divideCount; ++i)
		{
			if (_child[i] != nullptr)
			{
				_child[i]->Clear();
			}
		}
	}

	template<int dimension>
	inline void CollisionTree<dimension>::AddStaticObject(Object<dimension>* object)
	{
		if (_root->IsIn(object))
		{
			_root->AddStaticObject(object);
		}
		else
		{
			_root->AddStaticObjectForce(object);
		}
	}

	template<int dimension>
	inline void CollisionTree<dimension>::AddDynamicObject(Object<dimension>* object)
	{
		if (_root->IsIn(object))
		{
			_root->AddDynamicObject(object);
		}
		else
		{
			_root->AddDynamicObjectForce(object);
		}
		_dynamicObjectList.push_back(object);
	}

	template<int dimension>
	inline void CollisionTree<dimension>::UpdateDynamicObject(Object<dimension>* object)
	{
		if (_root->IsIn(object))
		{
			_root->AddDynamicObject(object);
		}
		else
		{
			_root->AddDynamicObjectForce(object);
		}
	}

	template<int dimension>
	inline std::vector<Object<dimension>*> CollisionTree<dimension>::GetCollidedObjects(Object<dimension>* obj)
	{
		return _root->GetCollidedObjects(obj);
	}
}

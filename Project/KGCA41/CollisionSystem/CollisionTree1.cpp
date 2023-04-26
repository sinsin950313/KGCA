#include "CollisionTree1.h"

namespace SSB
{
	CollisionTree1::Node::Node(int currentLayer, Vector3 lbn, Vector3 rtf, CollisionTree1* tree)
	{
		Vector3 tmp = rtf - lbn;
		SetScale(tmp.GetX(), tmp.GetY(), tmp.GetZ());

		SetPosition((rtf + lbn) / 2);
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
	bool CollisionTree1::Node::IsIn(Volume1* object)
	{
		return object->IsIn(this);
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
			_staticObjects.push_back(object);
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
			_dynamicObjects.push_back(object);
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

		for (auto object : _staticObjects)
		{
			if (object->IsCollide(target) || target->IsCollide(object))
			{
				ret.push_back(target);
			}
		}

		for (auto object : _dynamicObjects)
		{
			if (object->IsCollide(target) || target->IsCollide(object))
			{
				ret.push_back(target);
			}
		}

		return ret;
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
	void CollisionTree1::UpdateDynamicCollider(Volume1* collider)
	{
		AddDynamicCollider(collider);
	}
	bool QuadTree::Init()
	{
		auto scale = GetScale();
		Vector3 lbn(-scale.GetX() / 2.0f, -scale.GetY() / 2.0f, -scale.GetZ() / 2.0f);
		Vector3 rtf(scale.GetX() / 2.0f, scale.GetY() / 2.0f, scale.GetZ() / 2.0f);
		_root = new QuadTreeNode(0, lbn, rtf, this);

		return true;
	}
	QuadTree::QuadTreeNode::QuadTreeNode(int currentLayer, Vector3 lbn, Vector3 rtf, CollisionTree1* tree)
		: Node(currentLayer, lbn, rtf, tree)
	{
		if (currentLayer + 1 < tree->GetMaxLayer())
		{
			Vector3 center = (lbn + rtf) / 2.0f;
			Vector3 delta = rtf - lbn;
			float hWidth = delta.GetX() / 2.0f;
			float hHeight = delta.GetY() / 2.0f;
			float hDepth = delta.GetZ() / 2.0f;

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
				_childNodes[i] = new QuadTreeNode(currentLayer + 1, templbn, temprtf, tree);
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
	}
}
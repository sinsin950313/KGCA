#pragma once

#include "CustomBST.h"

class AVL : public BST
{
private:
	int GetBalanceFactor(Node* node)
	{
		return node != nullptr ? GetHeight(node->GetLeft()) - GetHeight(node->GetRight()) : 0;
	}
	int GetHeight(Node* node)
	{
		return (node != nullptr && !node->IsDeleted()) ? node->GetHeight() : 0;
	}
	void Balancing(Node* w)
	{
		Node* x = w;
		while (abs(GetBalanceFactor(x)) < 2)
		{
			x = x->GetParent();
			if (x == nullptr)
			{
				return;
			}
		}
		if (abs(GetBalanceFactor(x)) != 2)
		{
			return;
		}

		Node* y = GetHeight(x->GetLeft()) < GetHeight(x->GetRight()) ? x->GetRight() : x->GetLeft();
		Node* z = GetHeight(y->GetLeft()) < GetHeight(y->GetRight()) ? y->GetRight() : y->GetLeft();

		if (x->GetLeft() == y)
		{
			if (y->GetRight() == z)
			{
				Node* newTopNode = LeftRotate(y, z);
				SetLeft(x, newTopNode);
				SetParent(newTopNode, x);

				Node* tmp = y;
				y = z;
				z = tmp;
			}

			Node* grand = x->GetParent();
			Node* newTopNode = RightRotate(x, y);

			if (grand != nullptr)
			{
				if (grand->GetRight() == x)
				{
					SetRight(grand, newTopNode);
				}
				else
				{
					SetLeft(grand, newTopNode);
				}
			}

			SetParent(newTopNode, grand);
		}
		else
		{
			if (y->GetLeft() == z)
			{
				Node* newTopNode = RightRotate(y, z);
				SetRight(x, newTopNode);
				SetParent(newTopNode, x);

				Node* tmp = y;
				y = z;
				z = tmp;
			}

			Node* grand = x->GetParent();
			Node* newTopNode = LeftRotate(x, y);

			if (grand != nullptr)
			{
				if (grand->GetRight() == x)
				{
					SetRight(grand, newTopNode);
				}
				else
				{
					SetLeft(grand, newTopNode);
				}
			}

			SetParent(newTopNode, grand);
		}

		if (x == _root)
		{
			_root = y;
			SetParent(_root, nullptr);
		}
	}
	Node* LeftRotate(Node* parent, Node* child)
	{
		Node* tmp = child->GetLeft();
		SetLeft(child, parent);
		SetParent(parent, child);
		SetRight(parent, tmp);
		SetParent(tmp, parent);
		return child;
	}
	Node* RightRotate(Node* parent, Node* child)
	{
		Node* tmp = child->GetRight();
		SetRight(child, parent);
		SetParent(parent, child);
		SetLeft(parent, tmp);
		SetParent(tmp, parent);
		return child;
	}

public:
	void insert(int val) override
	{
		BST::insert(val);
		Balancing(Find(val));
	}
	void Erase(Node* node) override
	{
		BST::Erase(node);
		Balancing(node);
	}
};

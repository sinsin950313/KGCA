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
		return node != nullptr ? node->GetHeight() : 0;
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
				SetLeft(x, LeftRotate(y, z));
				Node* tmp = y;
				y = z;
				z = tmp;
			}
			Node* tmp = RightRotate(x, y);
			if (x->GetParent() != nullptr)
			{
				if (x->GetParent()->GetRight() == x)
				{
					SetRight(x->GetParent(), y);
				}
				else
				{
					SetLeft(x->GetParent(), y);
				}
			}
		}
		else
		{
			if (y->GetLeft() == z)
			{
				SetRight(x, RightRotate(y, z));
				Node* tmp = y;
				y = z;
				z = tmp;
			}
			Node* tmp = LeftRotate(x, y);
			if (x->GetParent() != nullptr)
			{
				if (x->GetParent()->GetRight() == x)
				{
					SetRight(x->GetParent(), y);
				}
				else
				{
					SetLeft(x->GetParent(), y);
				}
			}
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
		//SetParent(child, parent->GetParent());
		//SetParent(parent, child);
		SetRight(parent, tmp);
		return child;
	}
	Node* RightRotate(Node* parent, Node* child)
	{
		Node* tmp = child->GetRight();
		SetRight(child, parent);
		//SetParent(child, parent->GetParent());
		//SetParent(parent, child);
		SetLeft(parent, tmp);
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

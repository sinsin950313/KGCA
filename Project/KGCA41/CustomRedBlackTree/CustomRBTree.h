#pragma once

#include "CustomBST.h"

enum class RBColor { RED, BLACK };

class RBNode : public Node
{
private:
	RBColor _color = RBColor::RED;

public:
	RBNode(int val) : Node(val) { }
	virtual ~RBNode() override { cout << "Destroy RB Node called" << endl; }
	void SetColor(RBColor color) { _color = color; }
	RBColor GetColor() { return _color; }
};

class RBTree : public BST
{
protected:
	virtual Node* GetNewNode(int val) override { return new RBNode(val); }
	
private:
	void Balancing(Node* pNode)
	{
		RBNode* child = static_cast<RBNode*>(pNode);
		while (child->GetParent() != nullptr && static_cast<RBNode*>(child->GetParent())->GetColor() == RBColor::RED)
		{
			if (child->GetParent() == child->GetParent()->GetParent()->GetLeft())
			{
				RBNode* uncle = static_cast<RBNode*>(child->GetParent()->GetParent()->GetRight());
				RBNode* grand = static_cast<RBNode*>(child->GetParent()->GetParent());
				if (uncle != nullptr && uncle->GetColor() == RBColor::RED)
				{
					static_cast<RBNode*>(child->GetParent())->SetColor(RBColor::BLACK);
					uncle->SetColor(RBColor::BLACK);
					grand->SetColor(RBColor::RED);
					child = grand;
				}
				else if (child == child->GetParent()->GetRight())
				{
					Node* parent = child->GetParent();
					child = static_cast<RBNode*>(child->GetParent());
					Node* newTopNode = LeftRotate(child->GetParent(), child);
					SetRight(parent, newTopNode);
				}
				if (child->GetParent() != nullptr)
				{
					static_cast<RBNode*>(child->GetParent())->SetColor(RBColor::BLACK);
					if (child->GetParent()->GetParent() != nullptr)
					{
						grand = static_cast<RBNode*>(child->GetParent()->GetParent());
						grand->SetColor(RBColor::RED);

						Node* gGrand = grand->GetParent();
						Node* newTopNode = RightRotate(grand, child->GetParent());
						SetLeft(grand, newTopNode);
						if (gGrand != nullptr)
						{
							SetParent(newTopNode, gGrand);
						}
						else
						{
							_root = newTopNode;
							SetParent(_root, nullptr);
						}
					}
				}
			}
			else
			{
				RBNode* uncle = static_cast<RBNode*>(child->GetParent()->GetParent()->GetLeft());
				RBNode* grand = static_cast<RBNode*>(child->GetParent()->GetParent());
				if (uncle != nullptr && uncle->GetColor() == RBColor::RED)
				{
					static_cast<RBNode*>(child->GetParent())->SetColor(RBColor::BLACK);
					uncle->SetColor(RBColor::BLACK);
					grand->SetColor(RBColor::RED);
					child = grand;
				}
				else if (child == child->GetParent()->GetLeft())
				{
					Node* parent = child->GetParent();
					child = static_cast<RBNode*>(child->GetParent());
					Node* newTopNode = RightRotate(child->GetParent(), child);
					SetLeft(parent, newTopNode);
				}
				if (child->GetParent() != nullptr)
				{
					static_cast<RBNode*>(child->GetParent())->SetColor(RBColor::BLACK);
					if (child->GetParent()->GetParent() != nullptr)
					{
						grand = static_cast<RBNode*>(child->GetParent()->GetParent());
						grand->SetColor(RBColor::RED);

						Node* gGrand = grand->GetParent();
						Node* newTopNode = LeftRotate(grand, child->GetParent());
						SetRight(gGrand, newTopNode);
						if (gGrand != nullptr)
						{
							SetParent(newTopNode, gGrand);
						}
						else
						{
							_root = newTopNode;
							SetParent(_root, nullptr);
						}
					}
				}
			}
		}

		static_cast<RBNode*>(_root)->SetColor(RBColor::BLACK);
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
	RBTree() = default;
	virtual ~RBTree() { }
	void insert(int val) override
	{
		BST::insert(val);
		RBNode* node = static_cast<RBNode*>(Find(val));
		node->SetColor(RBColor::RED);
		Balancing(node);

		if (node == _root)
		{
			node->SetColor(RBColor::BLACK);
		}
	}
	void Erase(Node* node) override
	{
		BST::Erase(node);
		//Balancing(node);
	}
};

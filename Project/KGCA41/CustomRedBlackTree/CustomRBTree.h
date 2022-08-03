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
					Node* newTopNode = LeftRotate(parent, child);
					SetLeft(grand, newTopNode);

					Node* tmp = parent;
					parent = child;
					child = static_cast<RBNode*>(tmp);
				}
				else
				{
					Node* parent = child->GetParent();
					Node* gGrand = grand->GetParent();
					Node* newTopNode = RightRotate(grand, parent);

					SetParent(newTopNode, gGrand);
					static_cast<RBNode*>(newTopNode)->SetColor(RBColor::BLACK);
					grand->SetColor(RBColor::RED);

					if(gGrand == nullptr)
					{
						_root = newTopNode;
						SetParent(_root, nullptr);
					}
					else
					{
						if (grand == gGrand->GetLeft())
						{
							SetLeft(gGrand, newTopNode);
						}
						else
						{
							SetRight(gGrand, newTopNode);
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
					Node* newTopNode = RightRotate(parent, child);
					SetRight(grand, newTopNode);

					Node* tmp = parent;
					parent = child;
					child = static_cast<RBNode*>(tmp);
				}
				else
				{
					Node* parent = child->GetParent();
					Node* gGrand = grand->GetParent();
					Node* newTopNode = LeftRotate(grand, parent);

					SetParent(newTopNode, gGrand);
					static_cast<RBNode*>(newTopNode)->SetColor(RBColor::BLACK);
					grand->SetColor(RBColor::RED);

					if(gGrand == nullptr)
					{
						_root = newTopNode;
						SetParent(_root, nullptr);
					}
					else
					{
						if (grand == gGrand->GetLeft())
						{
							SetLeft(gGrand, newTopNode);
						}
						else
						{
							SetRight(gGrand, newTopNode);
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
	}
	void Erase(Node* node) override
	{
		BST::Erase(node);
		//Balancing(node);
	}
};

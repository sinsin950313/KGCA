#pragma once

#include "CustomBST.h"
#include <stack>
#include <queue>

class AVL : public BST
{
private:
	void Balancing(Node* w)
	{
		stack<Node*> s;
		s.push(_root);

		queue<Node*> q;
		q.push(_root);
		while (!q.empty())
		{
			Node* pNode = q.front();
			q.pop();

			if (pNode->GetLeft() != nullptr && !pNode->GetLeft()->IsDeleted())
			{
				q.push(pNode->GetLeft());
				s.push(pNode->GetLeft());
			}

			if (pNode->GetRight() != nullptr && !pNode->GetRight()->IsDeleted())
			{
				q.push(pNode->GetRight());
				s.push(pNode->GetRight());
			}
		}

		while (!s.empty())
		{
			Node* pNode = s.top();
			s.pop();

			int balanaceFactor;
			if (pNode->GetLeft() != nullptr && pNode->GetRight() != nullptr)
			{
				balanaceFactor = pNode->GetLeft()->GetHeight() - pNode->GetRight()->GetHeight();
			}
			else if (pNode->GetLeft() != nullptr)
			{
				balanaceFactor = pNode->GetLeft()->GetHeight();
			}
			else if (pNode->GetRight() != nullptr)
			{
				balanaceFactor = -pNode->GetRight()->GetHeight();
			}
			else
			{
				balanaceFactor = 0;
			}

			if (balanaceFactor == 2)
			{
				Node* grand = _root;
				while (grand->GetLeft() != pNode && grand->GetRight() != pNode)
				{
					if (grand->GetLeft() != nullptr)
					{
						if (grand->GetLeft()->GetData() < pNode->GetData())
						{
							grand = grand->GetLeft()->GetRight();
						}
						else
						{
							grand = grand->GetLeft()->GetLeft();
						}
					}
					if (grand->GetRight() != nullptr)
					{
						if (grand->GetRight()->GetData() < pNode->GetData())
						{
							grand = grand->GetRight()->GetRight();
						}
						else
						{
							grand = grand->GetRight()->GetLeft();
						}
					}
				}

				Node* x = pNode;
				Node* y = pNode->GetLeft();
				Node* z = y->GetData() < w->GetData() ? y->GetRight() : y->GetLeft();

				if (y->GetData() < w->GetData())
				{
					LR(x, y, z);
					Node* tmp = y;
					y = z;
					z = tmp;
				}
				LL(grand, x, y, z);
			}

			if (balanaceFactor == -2)
			{
				Node* grand = _root;
				while (grand->GetLeft() != pNode && grand->GetRight() != pNode)
				{
					if (grand->GetLeft() != nullptr)
					{
						if (grand->GetLeft()->GetData() < pNode->GetData())
						{
							grand = grand->GetLeft()->GetRight();
						}
						else
						{
							grand = grand->GetLeft()->GetLeft();
						}
					}
					if (grand->GetRight() != nullptr)
					{
						if (grand->GetRight()->GetData() < pNode->GetData())
						{
							grand = grand->GetRight()->GetRight();
						}
						else
						{
							grand = grand->GetRight()->GetLeft();
						}
					}
				}

				Node* x = pNode;
				Node* y = pNode->GetRight();
				Node* z = y->GetData() < w->GetData() ? y->GetRight() : y->GetLeft();

				if (w->GetData() < y->GetData())
				{
					RL(x, y, z);
					Node* tmp = y;
					y = z;
					z = tmp;
				}
				RR(grand, x, y, z);
			}
		}
	}
	void LL(Node* grand, Node* x, Node* y, Node* z)
	{
		SetLeft(grand, y);
		Node* tmp = y->GetRight();
		SetRight(y, x);
		SetLeft(x, tmp);
	}
	void LR(Node* x, Node* y, Node* z)
	{
		SetLeft(x, z);
		Node* tmp = z->GetLeft();
		SetLeft(z, y);
		SetRight(y, tmp);
	}
	void RL(Node* x, Node* y, Node* z)
	{
		SetRight(x, z);
		Node* tmp = z->GetRight();
		SetRight(z, y);
		SetLeft(y, tmp);
	}
	void RR(Node* grand, Node* x, Node* y, Node* z)
	{
		SetLeft(grand, y);
		Node* tmp = y->GetLeft();
		SetLeft(y, x);
		SetRight(x, tmp);
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

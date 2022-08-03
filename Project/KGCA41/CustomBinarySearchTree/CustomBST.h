#pragma once

#include <iostream>
#include <queue>

using namespace std;

class Node
{
private:
	Node* _parent = nullptr;
	Node* _left = nullptr;
	Node* _right = nullptr;
	int _data;

public:
	Node(int data) : _data(data) { _deleted = false; }
	virtual ~Node() { cout << _data << " is destroyed" << endl; }
	Node* GetLeft() { return _left; }
	Node* GetRight() { return _right; }
	Node* GetParent() { return _parent; }
	int GetData() { return _data; }

private:
	void SetParent(Node* node) { _parent = node; }
	void SetLeft(Node* node) { _left = node; }
	void SetRight(Node* node) { _right = node; }

private:
	bool _deleted = false;;
	void SetData(int data) { _data = data; _deleted = false; }
	void Delete() { cout << _data << " is deleted" << endl; _deleted = true; }
	friend class BST;

public:
	bool IsDeleted() { return _deleted; }

public:
	int GetHeight()
	{
		if ((_left != nullptr && !_left->IsDeleted()) && (_right != nullptr && !_right->IsDeleted()))
		{
			return max(_left->GetHeight(), _right->GetHeight()) + 1;
		}
		else if (_left != nullptr && !_left->IsDeleted())
		{
			return _left->GetHeight() + 1;
		}
		else if (_right != nullptr && !_right->IsDeleted())
		{
			return _right->GetHeight() + 1;
		}
		else
		{
			return 1;
		}
	}
};

class BST
{
protected:
	Node* _root = nullptr;
	virtual Node* GetNewNode(int val) { return new Node(val); }

public:
	BST() = default;
	virtual ~BST()
	{
		queue<Node*> q;
		q.push(_root);
		_root = nullptr;

		while (!q.empty())
		{
			Node* pNode = q.front();
			q.pop();
			
			if (pNode->GetLeft() != nullptr)
			{
				q.push(pNode->GetLeft());
			}

			if (pNode->GetRight() != nullptr)
			{
				q.push(pNode->GetRight());
			}

			delete pNode;
		}
	}
	virtual void insert(int val)
	{
		if (_root == nullptr)
		{
			_root = GetNewNode(val);
		}
		else
		{
			Node* pNode = _root;
			while (1)
			{
				Node* pNextNode = nullptr;
				if (pNode->IsDeleted())
				{
					pNode->SetData(val);
					break;
				}
				else if (pNode->GetData() < val)
				{
					if (pNode->GetRight() == nullptr)
					{
						Node* newNode = GetNewNode(val);
						pNode->SetRight(newNode);
						newNode->SetParent(pNode);
						break;
					}
					else
					{
						pNextNode = pNode->GetRight();
					}
				}
				else if (val < pNode->GetData())
				{
					if (pNode->GetLeft() == nullptr)
					{
						Node* newNode = GetNewNode(val);
						pNode->SetLeft(newNode);
						newNode->SetParent(pNode);
						break;
					}
					else
					{
						pNextNode = pNode->GetLeft();
					}
				}
				else
				{
					cout << val << " is already Exist" << endl;
					break;
				}

				if (pNextNode != nullptr)
				{
					pNode = pNextNode;
				}
				else
				{
					break;
				}
			}
		}
	}
	virtual void Erase(Node* node)
	{
		Node* pLeft = node->GetLeft();
		Node* pRight = node->GetRight();

		if((pLeft != nullptr && !pLeft->IsDeleted()) && (pRight != nullptr && !pRight->IsDeleted()))
		{
			Node* pGrandChild = nullptr;
			if (pLeft->GetRight() != nullptr && !pLeft->GetRight()->IsDeleted())
			{
				pGrandChild = pLeft->GetRight();
				node->SetData(pGrandChild->GetData());
				Erase(pGrandChild);
			}
			else if (pRight->GetLeft() != nullptr && !pRight->GetLeft()->IsDeleted())
			{
				pGrandChild = pRight->GetLeft();
				node->SetData(pGrandChild->GetData());
				Erase(pGrandChild);
			}
			else
			{
				node->SetData(pLeft->GetData());
				Erase(node->GetLeft());
			}
		}
		else if (pLeft != nullptr && !pLeft->IsDeleted())
		{
			node->SetData(pLeft->GetData());
			Erase(node->GetLeft());
		}
		else if(pRight != nullptr && !pRight->IsDeleted())
		{
			node->SetData(pRight->GetData());
			Erase(node->GetRight());
		}
		else
		{
			node->Delete();
		}
	}
	Node* Find(int seekValue)
	{
		Node* pNode = _root;
		while (pNode->GetData() != seekValue)
		{
			if (pNode == nullptr || pNode->IsDeleted())
			{
				cout << seekValue << " is not Exist" << endl;
				break;
			}
			else
			{
				cout << pNode->GetData() << " ";
				if (pNode->GetData() < seekValue)
				{
					pNode = pNode->GetRight();
				}
				else
				{
					pNode = pNode->GetLeft();
				}
			}
		}
		cout << endl;


		return pNode;
	}

protected:
	void SetLeft(Node* pNode, Node* left) { if(pNode != nullptr) pNode->SetLeft(left); }
	void SetRight(Node* pNode, Node* right) { if(pNode != nullptr) pNode->SetRight(right); }
	void SetParent(Node* pNode, Node* parent) { if(pNode != nullptr) pNode->SetParent(parent); }
};

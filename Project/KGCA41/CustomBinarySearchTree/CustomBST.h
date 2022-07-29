#pragma once

#include <iostream>

using namespace std;

class Node
{
private:
	Node* _left = nullptr;
	Node* _right = nullptr;
	int _data;

public:
	Node(int data) : _data(data) { }
	void SetLeft(Node* node) { _left = node; }
	void SetRight(Node* node) { _right = node; }
	Node* GetLeft() { return _left; }
	Node* GetRight() { return _right; }
	int GetData() { return _data; }

private:
	void SetData(int data) { _data = data; }
	friend class BST;
};

class BST
{
private:
	Node* _root = nullptr;

public:
	BST() = default;
	~BST()
	{
		while (_root != nullptr)
		{
			Erase(_root);
		}
	}
	void insert(int val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
		}
		else
		{
			Node* pNode = _root;
			while (1)
			{
				Node* pNextNode = nullptr;
				if (pNode->GetData() < val)
				{
					if (pNode->GetRight() == nullptr)
					{
						pNode->SetRight(new Node(val));
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
						pNode->SetLeft(new Node(val));
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
	void Erase(Node* node)
	{
		//Need parent?
		Node* pLeft = node->GetLeft();
		Node* pRight = node->GetRight();

		if(pLeft != nullptr && pRight != nullptr)
		{
			Node* pGrandChild = nullptr;
			if (pLeft->GetRight() != nullptr)
			{
				pGrandChild = pLeft->GetRight();
				node->SetData(pGrandChild->GetData());
				Erase(pGrandChild);
			}
			else if (pRight->GetLeft() != nullptr)
			{
				pGrandChild = pRight->GetLeft();
				node->SetData(pGrandChild->GetData());
				Erase(pGrandChild);
			}
			else
			{
				node->SetData(pLeft->GetData());
				node->SetLeft(pLeft->GetLeft());
				node->SetRight(pLeft->GetRight());
				delete pLeft;
			}
		}
		else if (pLeft != nullptr)
		{
			node->SetData(pLeft->GetData());
			node->SetLeft(pLeft->GetLeft());
			node->SetRight(pLeft->GetRight());
			delete pLeft;
		}
		else if(pRight != nullptr)
		{
			node->SetData(pRight->GetData());
			node->SetLeft(pLeft->GetLeft());
			node->SetRight(pRight->GetRight());
			delete pLeft;
		}
		else
		{

		}
	}
	Node* Find(int seekValue)
	{
		Node* pNode = _root;
		do
		{
			if (pNode == nullptr)
			{
				cout << seekValue << " is not Exist" << endl;
				break;
			}

			cout << pNode->GetData() << " ";
		} while (pNode->GetData() != seekValue);

		return pNode;
	}
};

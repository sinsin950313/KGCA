#include "Source.h"
#include <iostream>

using namespace std;

int Calculate(int N, int K)
{
	CircularLinkedList cll(N);
	int start = 0;
	while (cll.GetListSize() != 1)
	{
		cll.Erase(start, K);
		start += (K - 1);
		start %= (cll.GetListSize() + 1);
	}
	return cll.GetNode(0)->GetValue();
}

Node::Node(int val)
{
	_val = val;
}

Node::~Node()
{
	cout << _val << endl;
}

Node* Node::GetPrevNode()
{
	return _pPrevNode;
}

Node* Node::GetNextNode()
{
	return _pNextNode;
}

int Node::GetValue()
{
	return _val;
}

Node& Node::LinkPrev(Node* prev)
{
	if (prev != nullptr)
	{
		prev->_pNextNode = this;
	}
	this->_pPrevNode = prev;

	return *this;
}

Node& Node::LinkNext(Node* next)
{
	if (next != nullptr)
	{
		next->_pPrevNode = this;
	}
	this->_pNextNode = next;

	return *this;
}

CircularLinkedList::CircularLinkedList(int nodeCount)
{
	for (int i = 0; i < nodeCount; ++i)
	{
		PushBack(i + 1);
	}
}

CircularLinkedList::~CircularLinkedList()
{
	while (_pHead != _pTail)
	{
		Node* pNode = _pHead;
		_pHead = _pHead->GetNextNode();
		delete pNode;
	}
	delete _pHead;
}

void CircularLinkedList::PushBack(int val)
{
	Node* pNode = new Node(val);
	if(_nodeCount == 0)
	{
		_pHead = _pTail = pNode;
	}
	else if (_nodeCount == 1)
	{
		_pTail = pNode;
		_pHead->LinkNext(_pTail);
	}
	else
	{
		_pTail->LinkNext(pNode);
		_pTail = _pTail->GetNextNode();
	}
	_pTail->LinkNext(_pHead);
	++_nodeCount;
}

//index : start 0
void CircularLinkedList::Erase(int index)
{
	while (index < 0)
	{
		index += _nodeCount;
	}

	Node* pNode = GetNode(index);
	Erase(pNode);
}

//from : start 0
//to : start 1
void CircularLinkedList::Erase(int from, int to)
{
	if (to < 1)
	{
		to = 1;
	}
	while (from < 0)
	{
		from += _nodeCount;
	}

	Node* pNode = GetNode(from, to);
	Erase(pNode);
}

void CircularLinkedList::Erase(Node* pNode)
{
	if (_nodeCount == 0)
	{
		return;
	}
	else if (_nodeCount == 1)
	{
		_pHead = nullptr;
		_pTail = nullptr;
	}
	else
	{
		if (pNode == _pHead)
		{
			_pHead = _pHead->GetNextNode();
		}

		if (pNode == _pTail)
		{
			_pTail = _pTail->GetPrevNode();
		}

		Node* pPrev = pNode->GetPrevNode();
		Node* pNext = pNode->GetNextNode();
		pPrev->LinkNext(pNext);
	}

	delete pNode;
	--_nodeCount;
}

int CircularLinkedList::GetListSize()
{
	return _nodeCount;
}

Node* CircularLinkedList::GetNode(int index)
{
	index = index % _nodeCount;

	Node* pNode = _pHead;
	for (int i = 1; i < index; ++i)
	{
		pNode = pNode->GetNextNode();
	}
	return pNode;
}

Node* CircularLinkedList::GetNode(int from, int to)
{
	return GetNode(from + to);
}

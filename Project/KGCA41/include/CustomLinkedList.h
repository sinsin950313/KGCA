#pragma once

#include <iostream>

using namespace std;

namespace Custom
{
	template<typename T>
	class LinkedList
	{
	private:
		class Node
		{
		private:
			Node* _pNext;
			Node* _pPrev;
			T* _data;
			
		public:
			Node();
			Node(const Node& node) = delete;
			Node(Node&& node);
			Node(const T& data) = delete;
			Node(T&& data);
			~Node();

		public:
			void SetData(const T& data);
			void SetData(T&& data);
			T* Get();
			Node* GetNext();
			Node* GetPrev();

			friend class LinkedList<T>;
		};

	private:
		Node* _pHead;
		Node* _pTail;
		void Link(Node* prev, Node* curr, Node* next);
		void unLink(Node* prev, Node* curr, Node* next);

	public:
		LinkedList();
		~LinkedList();

	public:
		void PushBack(const T& data);
		void PushBack(T&& data);
		void PushFront(const T& data);
		void PushFront(T&& data);
		void EraseBack();
		void EraseFront();
		bool IsEmpty();
		T* GetFront();
		T* GetBack();
	};
}

template<typename T>
Custom::LinkedList<T>::Node::Node()
{
	_data = new T;
	_pPrev = nullptr;
	_pNext = nullptr;
}

template<typename T>
Custom::LinkedList<T>::Node::Node(Node&& node)
{
	_data = node._data;
	_pPrev = node._pPrev;
	_pNext = node._pNext;
}

template<typename T>
Custom::LinkedList<T>::Node::Node(T&& data)
{
	_data = data;
}

template<typename T>
Custom::LinkedList<T>::Node::~Node()
{
	delete _data;
}

template<typename T>
void Custom::LinkedList<T>::Node::SetData(const T& data)
{
	*_data = data;
}

template<typename T>
void Custom::LinkedList<T>::Node::SetData(T&& data)
{
	delete _data;
	_data = data;
}

template<typename T>
T* Custom::LinkedList<T>::Node::Get()
{
	return _data;
}

template<typename T>
typename Custom::LinkedList<T>::Node* Custom::LinkedList<T>::Node::GetNext()
{
	return _pNext;
}

template<typename T>
typename Custom::LinkedList<T>::Node* Custom::LinkedList<T>::Node::GetPrev()
{
	return _pPrev;
}

template<typename T>
void Custom::LinkedList<T>::Link(Node* prev, Node* curr, Node* next)
{
	prev->_pNext = curr;
	curr->_pNext = next;

	next->_pPrev = curr;
	curr->_pPrev = prev;
}

template<typename T>
void Custom::LinkedList<T>::unLink(Node* prev, Node* curr, Node* next)
{
	prev->_pNext = next;
	next->_pPrev = prev;

	delete curr;
}

template<typename T>
Custom::LinkedList<T>::LinkedList()
{
	_pHead = new Node;
	_pTail = new Node;
	_pHead->_pNext = _pTail;
	_pTail->_pPrev = _pHead;
}

template<typename T>
Custom::LinkedList<T>::~LinkedList()
{
	delete _pHead;
	delete _pTail;
}

template<typename T>
void Custom::LinkedList<T>::PushBack(const T& data)
{
	Node* newNode = new Node;
	newNode->SetData(data);
	Link(_pTail->GetPrve(), newNode, _pTail);
}

template<typename T>
void Custom::LinkedList<T>::PushBack(T&& data)
{
	Node* newNode = new Node;
	newNode->SetData(data);
	Link(_pTail->GetPrev(), newNode, _pTail);
}

template<typename T>
void Custom::LinkedList<T>::PushFront(const T& data)
{
	Node* newNode = new Node;
	newNode->SetData(data);
	Link(_pHead, newNode, _pHead->GetNext());
}

template<typename T>
void Custom::LinkedList<T>::PushFront(T&& data)
{
	Node* newNode = new Node;
	newNode->SetData(data);
	Link(_pHead, newNode, _pHead->GetNext());
}

template<typename T>
void Custom::LinkedList<T>::EraseBack()
{
	if (IsEmpty())
	{
		cout << "Linked List Empty" << endl;
		return;
	}
	Node* pNode = _pTail->GetPrev();
	unLink(pNode->GetPrev(), pNode, _pTail);
}

template<typename T>
void Custom::LinkedList<T>::EraseFront()
{
	if (IsEmpty())
	{
		cout << "Linked List Empty" << endl;
		return;
	}
	Node* pNode = _pHead->GetNext();
	unLink(_pHead, pNode, pNode->GetNext());
}

template<typename T>
bool Custom::LinkedList<T>::IsEmpty()
{
	return _pHead->GetNext() == _pTail;
}

template<typename T>
inline T* Custom::LinkedList<T>::GetFront()
{
	return IsEmpty() ? nullptr : _pTail->GetPrev().Get();
}

template<typename T>
inline T* Custom::LinkedList<T>::GetBack()
{
	return IsEmpty() ? nullptr : _pHead->GetNext().Get();
}

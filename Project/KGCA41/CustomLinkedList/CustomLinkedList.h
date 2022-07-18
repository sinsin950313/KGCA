#pragma once

#include <iostream>

using namespace std;

//template<typename T>
//class Custom::LinkedList<T>;

namespace Custom
{
	template<typename T>
	class Node
	{
	private:
		Node* _pNext;
		Node* _pPrev;
		T* _data;

	public:
		Node()
		{
			_data = new T;
			_pPrev = nullptr;
			_pNext = nullptr;
		}
		Node(const Node& node) = delete;
		Node(Node&& node)
		{
			_data = node._data;
			_pPrev = node._pPrev;
			_pNext = node._pNext;
		}
		Node(const T& data) = delete;
		Node(T&& data)
		{
			_data = data;
		}
		~Node()
		{
			delete _data;
		}

	public:
		void SetData(const T& data)
		{
			*_data = data;
		}
		void SetData(T&& data)
		{
			delete _data;
			_data = data;
		}
		T* Get()
		{
			return _data;
		}
		Node* GetNext()
		{
			return _pNext;
		}
		Node* GetPrev()
		{
			return _pPrev;
		}

		template<typename>
		friend class LinkedList;
	};

	template<typename T>
	class Iterator
	{
	private:
		Node<T>* _ptr;

	public:
		Iterator(Node<T>* ptr)
		{
			_ptr = ptr;
		}
		Iterator(Iterator&& iter)
		{
			_ptr = iter._ptr;
		}
		Iterator& operator++(void)
		{
			_ptr = _ptr->GetNext();
			return *this;
		}
		Iterator& operator--(void)
		{
			_ptr = _ptr->GetPrev();
			return *this;
		}
		T& Get()
		{
			return *_ptr;
		}
	};

	template<typename T>
	class LinkedList
	{
	private:
		Node<T>* _pHead;
		Node<T>* _pTail;
		void Link(Node<T>* prev, Node<T>* curr, Node<T>* next)
		{
			prev->_pNext = curr;
			curr->_pNext = next;

			next->_pPrev = curr;
			curr->_pPrev = prev;
		}
		void unLink(Node<T>* prev, Node<T>* curr, Node<T>* next)
		{
			prev->_pNext = next;
			next->_pPrev = prev;

			delete curr;
		}

	public:
		LinkedList()
		{
			_pHead = new Node<T>;
			_pTail = new Node<T>;
			_pHead->_pNext = _pTail;
			_pTail->_pPrev = _pHead;
		}
		~LinkedList()
		{
			delete _pHead;
			delete _pTail;
		}

	public:
		void PushBack(const T& data)
		{
			Node<T>* newNode = new Node<T>;
			newNode->SetData(data);
			Link(_pTail->GetPrve(), newNode, _pTail);
		}
		void PushBack(T&& data)
		{
			Node<T>* newNode = new Node<T>;
			newNode->SetData(data);
			Link(_pTail->GetPrev(), newNode, _pTail);
		}
		void PushFront(const T& data)
		{
			Node<T>* newNode = new Node<T>;
			newNode->SetData(data);
			Link(_pHead, newNode, _pHead->GetNext());
		}
		void PushFront(T&& data)
		{
			Node<T>* newNode = new Node<T>;
			newNode->SetData(data);
			Link(_pHead, newNode, _pHead->GetNext());
		}
		void EraseBack()
		{
			if (IsEmpty())
			{
				cout << "Linked List Empty" << endl;
				return;
			}
			Node<T>* pNode = _pTail->GetPrev();
			unLink(pNode->GetPrev(), pNode, _pTail);
		}
		void EraseFront()
		{
			if (IsEmpty())
			{
				cout << "Linked List Empty" << endl;
				return;
			}
			Node<T>* pNode = _pHead->GetNext();
			unLink(_pHead, pNode, pNode->GetNext());
		}
		bool IsEmpty()
		{
			return _pHead->GetNext() == _pTail;
		}
		T* GetFront()
		{
			return IsEmpty() ? nullptr : _pTail->GetPrev().Get();
		}
		T* GetBack()
		{
			return IsEmpty() ? nullptr : _pHead->GetNext().Get();
		}
		Iterator<T> Begin()
		{
			return Iterator<Node<T>>(_pHead->GetNext());
		}
		Iterator<T> End()
		{
			return Iterator<Node<T>>(_pTail->GetPrev());
		}
	};
}

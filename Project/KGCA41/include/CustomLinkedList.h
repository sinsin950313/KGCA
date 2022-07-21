#pragma once

#include <iostream>

using namespace std;

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
		Node(const Node& node)
		{
			_data = new T(node._data);
			_pPrev = nullptr;
			_pNext = nullptr;
		}
		Node(Node&& node)
		{
			_data = node._data;
			node._data = nullptr;
			_pPrev = node._pPrev;
			_pNext = node._pNext;
		}
		Node(const T& data)
		{
			_data = new T(data);
			_pPrev = nullptr;
			_pNext = nullptr;
		}
		Node(T&& data)
		{
			_data = data;
			_pPrev = nullptr;
			_pNext = nullptr;
		}
		~Node()
		{
			delete _data;
		}

	public:
		void SetData(const T& data)
		{
			delete _data;
			_data = new T(data);
		}
		void SetData(T&& data)
		{
			delete _data;
			_data = data;
		}
		T& Get()
		{
			return *_data;
		}
		Node* GetNext() const
		{
			return _pNext;
		}
		Node* GetPrev() const
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
			iter._ptr = nullptr;
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
			return _ptr->Get();
		}
		void operator=(const Iterator& iter)
		{
			_ptr = iter._ptr;
		}
		void operator=(Iterator&& iter)
		{
			_ptr = iter._ptr;
			iter._ptr = nullptr;
		}
		bool operator==(Iterator<T> cmp)
		{
			return cmp._ptr == _ptr;
		}
		bool operator!=(Iterator<T> cmp)
		{
			return cmp._ptr != _ptr;
		}
	};

	template<typename T>
	class LinkedList
	{
	private:
		Node<T>* _pHead;
		Node<T>* _pTail;

	private:
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
		LinkedList(const LinkedList<T>& copy)
		{
			_pHead = new Node<T>;
			_pTail = new Node<T>;
			_pHead->_pNext = _pTail;
			_pTail->_pPrev = _pHead;

			operator=(copy);
		}
		~LinkedList()
		{
			Clear();
			delete _pHead;
			delete _pTail;
		}

	public:
		void operator=(const LinkedList<T>& copy)
		{
			Clear();

			Node<T>* copyCurr = copy._pHead->GetNext();
			do
			{
				PushBack(copyCurr->Get());
				copyCurr = copyCurr->GetNext();
			} while (copyCurr != copy._pTail);
		}

	public:
		void PushBack(const T& data)
		{
			Node<T>* newNode = new Node<T>;
			newNode->SetData(data);
			Link(_pTail->GetPrev(), newNode, _pTail);
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
		Iterator<T> Begin() const
		{
			return Iterator<T>(_pHead->GetNext());
		}
		Iterator<T> End() const
		{
			return Iterator<T>(_pTail);
		}
		void Clear()
		{
			while (!IsEmpty())
			{
				EraseFront();
			}
		}
	};
}

#pragma once

#include "CustomLinkedList.h"
#include <iostream>

namespace Custom
{
	class TreeNode
	{
	private:
		int _data = 0;
		TreeNode** _pChild;

	public:
		TreeNode(int childCount) { _pChild = new TreeNode * [childCount](); }
		~TreeNode() { delete _pChild; std::cout << "Erased : " << _data << std::endl; }
		TreeNode* GetChild(int index) { return _pChild[index]; }
		void Link(TreeNode* pNewNode, int index) { _pChild[index] = pNewNode; }
		void SetData(int data) { _data = data;  }
		int GetData() { return _data; }
	};

	class Tree
	{
	private:
		TreeNode* _root = nullptr;
		const int _branchCount;
		int _index = 0;

		void Erase(Custom::LinkedList<TreeNode*>& list)
		{
			if (list.IsEmpty())
			{
				return;
			}

			TreeNode* pNode = list.GetBack();
			list.EraseFront();

			for (int i = 0; i < _branchCount; ++i)
			{
				if (pNode->GetChild(i) != nullptr)
				{
					list.PushBack(pNode->GetChild(i));
				}
			}

			delete pNode;

			Erase(list);
		}
		TreeNode* GetNode(int index)
		{
			if (index == 0)
			{
				return _root;
			}
			else
			{
				int parentIndex = GetParentIndex(index);
				TreeNode* parentNode = GetNode(parentIndex);
				int childIndex = GetChildIndex(parentIndex, index);
				return parentNode->GetChild(childIndex);
			}
		}
		int GetParentIndex(int myIndex)
		{
			return (myIndex - 1) / 2;
		}
		int GetChildIndex(int myIndex, int childIndex)
		{
			for (int i = 1; i <= _branchCount; ++i)
			{
				if (_branchCount * myIndex + i == childIndex)
				{
					return i - 1;
				}
			}
		}

	public:
		Tree(int branchCount) : _branchCount(branchCount) { }
		~Tree()
		{
			Custom::LinkedList<TreeNode*> list;
			if (_root != nullptr)
			{
				list.PushBack(_root);
			}
			Erase(list);
		}
		void Add(int data)
		{
			TreeNode* pNewNode = new TreeNode(_branchCount);
			pNewNode->SetData(data);

			if (_index == 0)
			{
				_root = pNewNode;
			}
			else
			{
				TreeNode* parentNode = GetNode(GetParentIndex(_index));
				parentNode->Link(pNewNode, GetChildIndex(GetParentIndex(_index), _index));
			}
			++_index;
		}
		int Get(int index)
		{
			return GetNode(index)->GetData();
		}
	};
}

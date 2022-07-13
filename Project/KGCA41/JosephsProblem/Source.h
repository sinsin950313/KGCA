#pragma once

int Calculate(int N, int K);

class Node
{
private:
	int _val;
	Node* _pPrevNode = nullptr;
	Node* _pNextNode = nullptr;

public:
	Node(int val);
	~Node();
	int GetValue();
	Node& LinkPrev(Node* prev);
	Node& LinkNext(Node* next);
	Node* GetNextNode();
	Node* GetPrevNode();
};

class CircularLinkedList
{
private:
	Node* _pHead = nullptr;
	Node* _pTail = nullptr;
	int _nodeCount = 0;

private:
	void Erase(Node* pNode);
	//startIndex : start 0
	//count : start 1
	Node* GetNode(int startIndex, int count);
	//startIndex : start 0
	//count : start 1
	int getIndex(int startIndex, int count);

public:
	CircularLinkedList(int nodeCount);
	~CircularLinkedList();
	int GetListSize();
	void PushBack(int val);
	void Erase(int index);
	//startIndex : start 0
	//count : start 1
	void Erase(int startIndex, int count);
	Node* GetNode(int index);
};

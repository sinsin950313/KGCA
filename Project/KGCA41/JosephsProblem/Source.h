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
	Node* GetNode(int from, int to);

public:
	CircularLinkedList(int nodeCount);
	~CircularLinkedList();
	int GetListSize();
	void PushBack(int val);
	void Erase(int index);
	void Erase(int from, int to);
	Node* GetNode(int index);
};

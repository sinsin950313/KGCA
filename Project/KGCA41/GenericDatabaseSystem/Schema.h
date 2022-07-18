#pragma once

#include "CustomLinkedList.h"

class Buffer;

using namespace Custom;

//C string 20 characters
const int NameLength = 21;

class SchemaNode
{
private:
	char _type;
	char _name[NameLength];

public:
	SchemaNode(Buffer& buffer);
	SchemaNode(SchemaNode&& node);
	char GetType();
	const char* GetName();
};

class Schema
{
private:
	LinkedList<SchemaNode> _nodes;

private:
	void AddNode(char type, char* name);

public:
	Schema(Buffer* buffer);
	Iterator<SchemaNode> CreateIterator();
	//Print template Version
	void PrintSchema();
};

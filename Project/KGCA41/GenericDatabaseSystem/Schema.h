#pragma once

#include "CustomLinkedList.h"

class Buffer;

using namespace Custom;

//C string 20 characters
static const int NameLength = 21;
static int GetNameLength();

const int DELETED = -1;
const int KEEPED = 0;
const int CREATED = 1;

class SchemaNode
{
private:
	char _type;
	char _name[NameLength] = { 0, };
	int _state;

public:
	SchemaNode();
	SchemaNode(char type, const char* name, int state);
	SchemaNode(Buffer& copy, int state);
	SchemaNode(const SchemaNode& copy);
	SchemaNode(SchemaNode&& move);
	void Erase() { _state = DELETED; }
	bool IsAlive() { return _state != DELETED; }
	char GetType() { return _type; }
	const char* GetName() { return _name; }
};

//Schema : [type, name][type, name]...
class Schema
{
private:
	LinkedList<SchemaNode> _nodes;

public:
	Schema() = default;
	Schema(Buffer& buffer);
	Schema(const Schema& copy);
	Iterator<SchemaNode> CreateIterator();
	Iterator<SchemaNode> End();
	void Add(char type, const char* name);
	void Erase(Iterator<SchemaNode>& iterator);
	Iterator<SchemaNode> GetIterator();
	Buffer GetSchema();
};

#pragma once

#include "CustomLinkedList.h"
#include "Common.h"

class Buffer;

using namespace Custom;

//C string 20 characters
static const int NameLength = 21;
static int GetNameLength();

static const int DELETED = -1;
static const int KEEPED = 0;
static const int CREATED = 1;

class SchemaNode
{
private:
	SchemaDataType _type;
	char _name[NameLength] = { 0, };
	int _state;

public:
	SchemaNode();
	SchemaNode(SchemaDataType type, const char* name, int state);
	//SchemaNode(Buffer& copy, int state);
	SchemaNode(const SchemaNode& copy);
	SchemaNode(SchemaNode&& move);
	void Erase() { _state = DELETED; }
	bool IsAlive() const { return _state != DELETED; }
	SchemaDataType GetType() const { return _type; }
	const char* GetName() const { return _name; }
};


/// <summary>
/// Schema : [type, name][type, name]...
/// </summary>
class Schema
{
private:
	LinkedList<SchemaNode> _nodes;

public:
	Schema() = default;
	Schema(Buffer& buffer);
	Schema(const Schema& copy);
	void Set(Buffer& copy);
	Iterator<SchemaNode> CreateIterator() const;
	Iterator<SchemaNode> End() const;
	void Add(SchemaDataType type, const char* name);
	void Erase(Iterator<SchemaNode>& iterator);
	Buffer GetSchema();

public:
	static char ToChar(SchemaDataType type);
	static SchemaDataType ToType(char type);

public:
	static const char* GetDefaultValue(SchemaDataType type);
	/// <returns>DefaultValue string size</returns>
	static int GetDefaultSize(SchemaDataType type);
};

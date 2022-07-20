#include "Schema.h"
#include "Buffer.h"

int GetNameLength()
{
	return NameLength - 1;
}

SchemaNode::SchemaNode()
{
	_type = 0;
	memcpy(_name, "", GetNameLength());
	_state = DELETED;
}

SchemaNode::SchemaNode(char type, const char* name, int state)
{
	_type = type;
	memcpy(_name, name, GetNameLength());
	_state = state;
}

SchemaNode::SchemaNode(Buffer& copy, int state)
{
	const char* str = copy.GetString();
	int size = copy.GetSize();

	_type = str[0];
	memcpy(_name, str + 1, GetNameLength());
	_state = state;
}

SchemaNode::SchemaNode(const SchemaNode& copy)
{
	_type = copy._type;
	memcpy(_name, copy._name, GetNameLength());
}

SchemaNode::SchemaNode(SchemaNode&& move)
{
	_type = move._type;
	memcpy(_name, move._name, GetNameLength());
}

Schema::Schema(Buffer& buffer)
{
	const char* str = buffer.GetBuffer();
	int size = buffer.GetSize();

	char name[NameLength]{ 0, };
	int i = 0;
	while (i < size)
	{
		memset(name, 0, NameLength);

		++i;					//"["
		char type = str[i++];	//"(type)"
		i += 2;					//", "
		memcpy(name, str + i, GetNameLength());
		i += GetNameLength();	//"(name)"
		++i;					//"]"

		_nodes.PushBack(SchemaNode(type, name, KEEPED));
	}
}

Schema::Schema(const Schema& copy)
{
	_nodes = copy._nodes;
}

Iterator<SchemaNode> Schema::CreateIterator()
{
	return _nodes.Begin();
}

Iterator<SchemaNode> Schema::End()
{
	return _nodes.End();
}

void Schema::Add(char type, const char* name)
{
	_nodes.PushBack(SchemaNode(type, name, CREATED));
}

void Schema::Erase(Iterator<SchemaNode>& iterator)
{
	iterator.Get().Erase();
}

Iterator<SchemaNode> Schema::GetIterator()
{
	return Iterator<SchemaNode>(_nodes.Begin());
}

Buffer Schema::GetSchema()
{
	Buffer buffer;
	for (auto iter = _nodes.Begin(); iter != _nodes.End(); ++iter)
	{
		if (iter.Get().IsAlive())
		{
			buffer.Push("[", 1);
			char type = iter.Get().GetType();
			buffer.Push(&type, 1);
			buffer.Push(", ", 2);
			buffer.Push(iter.Get().GetName(), GetNameLength());
			buffer.Push("]", 1);
		}
	}
	return buffer;
}

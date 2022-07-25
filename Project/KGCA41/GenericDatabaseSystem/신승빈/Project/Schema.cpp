#include "Schema.h"
#include "Buffer.h"

int GetNameLength()
{
	return NameLength - 1;
}

SchemaNode::SchemaNode()
{
	_type = SchemaDataType::DEFAULT_TYPE;
	memcpy(_name, "", GetNameLength());
	_state = DELETED;
}

SchemaNode::SchemaNode(SchemaDataType type, const char* name, int state)
{
	_type = type;
	memcpy(_name, name, GetNameLength());
	_state = state;
}
//
//SchemaNode::SchemaNode(Buffer& copy, int state)
//{
//	const char* str = copy.GetString();
//	int size = copy.GetSize();
//
//	_type = ToType(str[0]);
//	memcpy(_name, str + 1, GetNameLength());
//	_state = state;
//}

SchemaNode::SchemaNode(const SchemaNode& copy)
{
	_type = copy._type;
	memcpy(_name, copy._name, GetNameLength());
	_state = copy._state;
}

SchemaNode::SchemaNode(SchemaNode&& move)
{
	_type = move._type;
	memcpy(_name, move._name, GetNameLength());
	_state = move._state;
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

		_nodes.PushBack(SchemaNode(ToType(type), name, KEEPED));
	}
}

Schema::Schema(const Schema& copy)
{
	_nodes = copy._nodes;
}

void Schema::Set(Buffer& copy)
{
	const char* str = copy.GetBuffer();

	int i = 0;
	while (i < copy.GetSize())
	{
		++i;					//"["
		char type = str[i];
		++i;					//type
		i += 2;					//", "
		char name[NameLength];
		memcpy(name, str + i, GetNameLength());
		i += GetNameLength();	//name
		++i;					//"]"
		_nodes.PushBack(SchemaNode(ToType(type), name, KEEPED));
	}
}

Iterator<SchemaNode> Schema::CreateIterator() const
{
	return _nodes.Begin();
}

Iterator<SchemaNode> Schema::End() const
{
	return _nodes.End();
}

void Schema::Add(SchemaDataType type, const char* name)
{
	char arr[NameLength]{ 0, };
	for (int i = 0; i < NameLength - 1; ++i)
	{
		if (name[i] == 0)
		{
			break;
		}
		arr[i] = name[i];
	}
	_nodes.PushBack(SchemaNode(type, arr, CREATED));
}

void Schema::Erase(Iterator<SchemaNode>& iterator)
{
	iterator.Get().Erase();
}

Buffer Schema::GetSchema()
{
	Buffer buffer;
	for (auto iter = _nodes.Begin(); iter != _nodes.End(); ++iter)
	{
		if (iter.Get().IsAlive())
		{
			buffer.Push("[", 1);
			char type = ToChar(iter.Get().GetType());
			buffer.Push(&type, 1);
			buffer.Push(", ", 2);
			buffer.Push(iter.Get().GetName(), GetNameLength());
			buffer.Push("]", 1);
		}
	}
	return buffer;
}

char Schema::ToChar(SchemaDataType type)
{
	switch (type)
	{
	case SchemaDataType::INT:
		return 'I';
		break;
	case SchemaDataType::FLOAT:
		return 'F';
		break;
	case SchemaDataType::STRING:
		return 'S';
		break;
	default:
		return 'D';
		break;
	}
}

SchemaDataType Schema::ToType(char type)
{
	switch (type)
	{
	case 'I': case 'i':
		return SchemaDataType::INT;
	case 'F': case 'f':
		return SchemaDataType::FLOAT;
	case 'S': case 's':
		return SchemaDataType::STRING;
	default:
		return SchemaDataType::DEFAULT_TYPE;
		break;
	}
}

const char* Schema::GetDefaultValue(SchemaDataType type)
{
	switch (type)
	{
	case SchemaDataType::INT:
		return "0";
		break;
	case SchemaDataType::FLOAT:
		return "0.0f";
		break;
	case SchemaDataType::STRING:
		return "Empty";
		break;
	default:
		return "";
		break;
	}
}

int Schema::GetDefaultSize(SchemaDataType type)
{
	switch (type)
	{
	case SchemaDataType::INT:
		return 1;
		break;
	case SchemaDataType::FLOAT:
		return 4;
		break;
	case SchemaDataType::STRING:
		return 5;
		break;
	default:
		return 0;
		break;
	}
}

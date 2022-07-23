#include "Data.h"
#include "IOManager.h"

Data::Data(const Schema* schema, const Buffer& serialData) : _schema(schema)
{
	Parallelize(serialData);
}

void Data::Parallelize(const Buffer& serialData)
{
	const char* str = serialData.GetBuffer();
	Buffer tmp;
	for (int i = 0; i < serialData.GetSize(); ++i)
	{
		if (str[i] == ' ')
		{
			_datas.PushBack(tmp);
			tmp.Clear();
		}
		else
		{
			tmp.Push(&str[i], 1);
		}
	}
}

Buffer Data::Serialize(const Schema* schema, const Custom::LinkedList<Buffer>& parallelDatas)
{
	auto schemaIter = schema->CreateIterator();
	auto dataIter = parallelDatas.Begin();

	Buffer ret;
	while (1)
	{
		if (schemaIter.Get().IsAlive())
		{
			if (dataIter != parallelDatas.End())
			{
				ret.Push(dataIter.Get().GetBuffer(), dataIter.Get().GetSize());
			}
			else
			{
				ret.Push(Schema::GetDefaultValue(schemaIter.Get().GetType()), Schema::GetDefaultSize(schemaIter.Get().GetType()));
			}
			ret.Push(" ", 1);
		}

		++schemaIter;
		if (dataIter != parallelDatas.End())
		{
			++dataIter;
		}

		if (schemaIter == schema->End())
		{
			break;
		}
	}

	return ret;
}

const Custom::LinkedList<Buffer>& Data::GetDatas()
{
	return _datas;
}

void Data::Update(Buffer fieldName, Buffer data)
{
	auto dataIter = _datas.Begin();
	for (auto iter = _schema->CreateIterator(); iter != _schema->End(); ++iter, ++dataIter)
	{
		if (iter.Get().IsAlive())
		{
			if (strcmp(iter.Get().GetName(), fieldName.GetString()) == 0)
			{
				dataIter.Get().Clear();
				dataIter.Get().Push(data.GetBuffer(), data.GetSize());
				break;
			}
		}
	}
}

Buffer Data::Serialize()
{
	return Serialize(_schema, _datas);
}

void Data::NewSchema(char type)
{
	Buffer buffer;
	buffer.Push(Schema::GetDefaultValue(Schema::ToType(type)), Schema::GetDefaultSize(Schema::ToType(type)));
	_datas.PushBack(buffer);
}

DataFactory* DataFactory::_instance = nullptr;

DataFactory::~DataFactory()
{
	delete _instance;
}

DataFactory& DataFactory::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new DataFactory();
	}
	return *_instance;
}

Data* DataFactory::CreateData(const Schema* schema)
{
	Custom::LinkedList<Buffer> defaultDatas;
	for (auto iter = schema->CreateIterator(); iter != schema->End(); ++iter)
	{
		Buffer buffer;
		buffer.Push(Schema::GetDefaultValue(iter.Get().GetType()), Schema::GetDefaultSize(iter.Get().GetType()));
		defaultDatas.PushBack(buffer);
	}

	Buffer serializedDatas = Data::Serialize(schema, defaultDatas);

	return CreateData(schema, serializedDatas);
}

Data* DataFactory::CreateData(const Schema* schema, const Buffer& serializedBuffer)
{
	return new Data(schema, serializedBuffer);
}

#pragma once

#include "Buffer.h"
#include "Schema.h"
#include "CustomLinkedList.h"

/// <summary>
/// Create, Delete is not Data's responsibility.
/// Serial Pattern : "(data) (data) ..."
/// </summary>
class Data
{
private:
	Custom::LinkedList<Buffer> _datas;
	const Schema* const _schema;

private:
	Data(const Schema* schema, const Buffer& serialData);

	/// <summary>
	/// Parallelize suppose that every serialData which is input is all alive.
	/// </summary>
	/// <param name="serialData">Variable serialData should be all alive.</param>
	void Parallelize(const Buffer& serialData);
	static Buffer Serialize(const Schema* schema, const Custom::LinkedList<Buffer>& parallelDatas);

public:
	void Read();
	void Update(Buffer fieldName, Buffer data);
	Buffer Serialize();

private:
	friend class DataFactory;
};

class DataFactory
{
private:
	DataFactory() = default;
	static DataFactory* _instance;

public:
	~DataFactory();
	static DataFactory& GetInstance();
	Data* CreateData(const Schema* schema);
	Data* CreateData(const Schema* schema, const Buffer& serializedBuffer);
};

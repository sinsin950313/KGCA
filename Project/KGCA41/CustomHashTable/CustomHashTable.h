#pragma once

class HashTable
{
	const int _length;
	int* _hashTable;

public:
	HashTable(int tableLength) : _length(tableLength) { _hashTable = new int[_length]; }
	~HashTable() { delete _hashTable; }
	void Push(int val) { _hashTable[Hash(val)] = val; }

private:
	int Hash(int val)
	{
		return (val * val) % _length;
	}
};

#pragma once
#include <queue>
#include <stdexcept>
#include <memory>

using std::shared_ptr;

template<typename T>
class ClassPool
{
protected:
	static const size_t DefalultChunkSize = 10;
	size_t _chunkSize;
	std::queue<shared_ptr<T>> _list;

protected:
	void AllocateChunk();

public:
	ClassPool(size_t chunkSize = DefalultChunkSize);
	shared_ptr<T> NewChunk();
	void DeleteChunk(shared_ptr<T> obj);
};
template<typename T>
ClassPool<T>::ClassPool(size_t chunkSize)
{
	_chunkSize = chunkSize;
	AllocateChunk();
}
template<typename T>
void ClassPool<T>::AllocateChunk()
{
	for (size_t i = 0; i < _chunkSize; i++)
	{
		_list.push(std::make_shared<T>());
	}
}
template<typename T>
shared_ptr<T> ClassPool<T>::NewChunk()
{
	if (_list.empty())
	{
		_list.push(std::make_shared<T>());
		_chunkSize++;
	}
	auto chunk = _list.front();
	_list.pop();
	return chunk;
}
template<typename T>
void ClassPool<T>::DeleteChunk(shared_ptr<T> obj)
{
	_list.push(obj);
}

#pragma once
#include <queue>
#include <stdexcept>
#include <memory>

using std::shared_ptr;

template<typename T>
class ObjectPool
{
public:
	enum
	{
		POOL_MAX_SIZE = 4096,// 2n½Â
		POOL_SIZE_MASK = POOL_MAX_SIZE - 1,
	};

private:
	static void* _pool[POOL_MAX_SIZE];
	static long long _headPosition;
	static long long _tailPosition;

public:
	static void Allocation();
	static void Release();
	static void* operator new (size_t size);
	static void operator delete (void* obj);
};

template<typename T>
void* ObjectPool<T>::_pool[POOL_MAX_SIZE] = {};
template<typename T>
long long ObjectPool<T>::_headPosition(0);
template<typename T>
long long ObjectPool<T>::_tailPosition(0);

template<typename T>
static void ObjectPool<T>::Allocation()
{
	for (size_t i = 0; i < POOL_MAX_SIZE; i++)
	{
		_pool[i] = _aligned_malloc(sizeof(T), MEMORY_ALLOCATION_ALIGNMENT);
	}
	InterlockedAdd64(&_tailPosition, POOL_MAX_SIZE);
}
template<typename T>
static void ObjectPool<T>::Release()
{
	for (size_t i = 0; i < POOL_MAX_SIZE; i++)
	{
		_aligned_free(_pool[i]);
	}
}
template<typename T>
static void* ObjectPool<T>::operator new (size_t size)
{
	size_t pos = InterlockedIncrement64(&_headPosition) - 1;
	size_t realpos = pos & POOL_SIZE_MASK;
	void* ret = InterlockedExchangePointer(&_pool[realpos], nullptr);
	if (ret != nullptr)
	{
		return ret;
	}
	return _aligned_malloc(sizeof(T), MEMORY_ALLOCATION_ALIGNMENT);
}
template<typename T>
static void ObjectPool<T>::operator delete (void* obj)
{
	size_t pos = InterlockedIncrement64(&_tailPosition) - 1;
	size_t realpos = pos & POOL_SIZE_MASK;
	void* ret = InterlockedExchangePointer(&_pool[realpos], obj);
	if (ret != nullptr)
	{
		_aligned_free(ret);
	}
}

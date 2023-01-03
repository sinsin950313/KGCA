#pragma once

namespace Custom
{
	class Array
	{
	protected:
		int* _arr = nullptr;
		const int _size;
		int _index = 0;

	public:
		Array(int length);
		~Array();
		virtual void Push(int val);
		const int* Get();
	};
}

#include "CommonSocket.h"

namespace SSB
{
	SerialData::SerialData(int length, Byte* data)
	{
		_length = length;
		_data = data;
	}
	SerialData::SerialData(SerialData&& data)
	{
		_length = data._length;
		_data = data._data;
		data._data = nullptr;
	}
	SerialData::~SerialData()
	{
		delete _data;
		_data = nullptr;
	}
	SerialData&& SerialData::operator=(SerialData&& data)
	{
		return SerialData(data._length, data._data);
	}
}

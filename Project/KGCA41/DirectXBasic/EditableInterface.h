#pragma once

namespace SSB
{
	template<typename ObjectType>
	class EditableObject abstract
	{
	public:
		virtual ObjectType* GetResult() = 0;
	};

	template<typename ObjectType>
	class EditableInterface abstract
	{
	public:
		virtual EditableObject<ObjectType>* GetEditableObject() = 0;
	};
}

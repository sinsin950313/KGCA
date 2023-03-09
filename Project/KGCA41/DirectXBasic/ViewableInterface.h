#pragma once

namespace SSB
{
	template<typename Class>
	class ViewerObject
	{
		virtual Class Clone() = 0;
	};

	template<typename Class>
	class Viewable abstract
	{
	public:
		virtual ViewerObject<Class>* GetViewer() = 0;
	};
}

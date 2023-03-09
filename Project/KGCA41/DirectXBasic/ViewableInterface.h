#pragma once

namespace SSB
{
	template<typename Class>
	class ViewerObject
	{
		// What should ViewObject to do??
	};

	template<typename Class>
	class Viewable abstract
	{
	public:
		virtual ViewerObject<Class>* GetViewer() = 0;
	};
}

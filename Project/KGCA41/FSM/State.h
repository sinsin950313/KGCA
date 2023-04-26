#pragma once

#include <map>

namespace SSB
{
	typedef int StateMachineEvent;

	class State
	{
	private:
		std::map<StateMachineEvent, State*> _eventMap;

	public:
		void AddTransition(StateMachineEvent stateMachineEvent, State* state);
		State* EventOccured(StateMachineEvent stateMachineEvent);

	public:
		virtual void Process() = 0;
	};
}

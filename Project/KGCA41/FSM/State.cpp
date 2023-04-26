#include "State.h"

namespace SSB
{
	void State::AddTransition(StateMachineEvent stateMachineEvent, State* state)
	{
		_eventMap.insert(std::make_pair(stateMachineEvent, state));
	}

	State* State::EventOccured(StateMachineEvent stateMachineEvent)
	{
		auto iter = _eventMap.find(stateMachineEvent);
		return iter == _eventMap.end() ? this : iter->second;
	}
}

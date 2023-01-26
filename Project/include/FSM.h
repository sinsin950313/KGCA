#pragma once

#include "State.h"

namespace SSB
{
	class FSM
	{
	private:
		State* _currentState;

	public:
		FSM(State* beginState);
		~FSM();

	public:
		void EventOccured(StateMachineEvent stateMachineEvent);
		void Run();
	};
}

#include "FSM.h"

namespace SSB
{
	FSM::FSM(State* beginState) : _currentState(beginState)
	{
	}
	FSM::~FSM()
	{
		_currentState = nullptr;
	}
	void FSM::EventOccured(StateMachineEvent stateMachineEvent)
	{
		_currentState = _currentState->EventOccured(stateMachineEvent);
	}
	void FSM::Run()
	{
		_currentState->Process();
	}
}

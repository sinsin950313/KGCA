#pragma once

#include "Texture.h"
#include "Timer.h"
#include <string>
#include <map>

namespace SSB
{
	class DX2DAnimation : public Texture
	{
	private:
		struct AnimationState
		{
			std::string _name;
			float _requiredTimeForStateTransition;
			Texture* _texture;
			RECT _area;
			std::map<std::string, AnimationState*> _changableState;
		};
		Timer _timer;
		std::map<std::string, AnimationState*> _stateList;
		AnimationState* _currentState;
		AnimationState* _nextState;

	public:
		void AddState(std::string stateName, Texture* resource, RECT area, float transitionTime);
		void LinkState(std::string fromState, std::string toState);
		std::map<std::string, AnimationState*>& GetNextPossibleState() { return _currentState->_changableState; }
		void SetNextState(std::string stateName) { _nextState = _currentState->_changableState.find(stateName)->second; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}

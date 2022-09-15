#pragma once

#include "TTexture.h"
#include "TTimer.h"
#include <string>
#include <map>

class TDX2DAnimation : public TTexture
{
private:
	struct AnimationState
	{
		std::string _name;
		float _requiredTimeForStateTransition;
		TTexture* _texture;
		RECT _area;
		std::map<std::string, AnimationState*> _changableState;
	};
	TTimer _timer;
	std::map<std::string, AnimationState*> _stateList;
	AnimationState* _currentState;
	AnimationState* _nextState;

public:
	void AddState(std::string stateName, TTexture* texture, RECT area, float transitionTime);
	void LinkState(std::string fromState, std::string toState);
	std::map<std::string, AnimationState*>& GetNextPossibleState() { return _currentState->_changableState; }
	void SetNextState(std::string stateName) { _nextState = _currentState->_changableState.find(stateName)->second; }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

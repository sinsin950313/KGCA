#include "DX2DProjectController.h"
#include "InputManager.h"

SSB::DX2DProjectController::DX2DProjectController(DX2DGameObject* controlledObject)
{
	SetControlledObject(controlledObject);
}

SSB::DX2DProjectController::~DX2DProjectController()
{
	Release();
}

void SSB::DX2DProjectController::SetControlledObject(DX2DGameObject* controlledObject)
{
	_controlledObject = controlledObject;
}

bool SSB::DX2DProjectController::Init()
{
	return true;
}

bool SSB::DX2DProjectController::Frame()
{
	Logic();
	_controlledObject->Frame();
	return true;
}

bool SSB::DX2DProjectController::Render()
{
	return true;
}

bool SSB::DX2DProjectController::Release()
{
	_controlledObject = nullptr;
	return true;
}

SSB::PlayerController::PlayerController(DX2DGameObject* controlledObject) : DX2DProjectController(controlledObject)
{
}

SSB::PlayerController::~PlayerController()
{
	Release();
}

void SSB::PlayerController::Logic()
{
}

bool SSB::PlayerController::Init()
{
	DX2DProjectController::Init();
	return true;
}

bool SSB::PlayerController::Frame()
{
	DX2DProjectController::Frame();

	float vel = 0.01f;
	if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
	{
		_controlledObject->Move(_controlledObject->GetCenter().Get(0), _controlledObject->GetCenter().Get(1) + vel);

		if (InputManager::GetInstance().GetKeyState(VK_SHIFT) == EKeyState::KEY_HOLD)
		{
			_controlledObject->RiseUp();
		}
		else if (InputManager::GetInstance().GetKeyState(VK_CONTROL) == EKeyState::KEY_HOLD)
		{
			_controlledObject->FallDown();
		}
		else
		{
			_controlledObject->ParallelTranslation();
		}
	}
	if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
	{
		_controlledObject->Move(_controlledObject->GetCenter().Get(0) - vel, _controlledObject->GetCenter().Get(1));
	}
	if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
	{
		_controlledObject->Move(_controlledObject->GetCenter().Get(0), _controlledObject->GetCenter().Get(1) - vel);
	}
	if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
	{
		_controlledObject->Move(_controlledObject->GetCenter().Get(0) + vel, _controlledObject->GetCenter().Get(1));
	}

	return true;
}

bool SSB::PlayerController::Render()
{
	DX2DProjectController::Frame();
	return true;
}

bool SSB::PlayerController::Release()
{
	DX2DProjectController::Frame();
	return true;
}

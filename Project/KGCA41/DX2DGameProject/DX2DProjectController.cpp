#include "DX2DProjectController.h"
#include "InputManager.h"
#include "Text.h"
#include "TextManager.h"
#include "DXWindow.h"

namespace SSB
{
	extern DXWindow* g_dxWindow;
}

SSB::DX2DProjectController::DX2DProjectController(DX2DInGameObject* controlledObject)
{
	SetControlledObject(controlledObject);
}

SSB::DX2DProjectController::~DX2DProjectController()
{
	Release();
}

void SSB::DX2DProjectController::SetControlledObject(DX2DInGameObject* controlledObject)
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

SSB::PlayerController::PlayerController(DX2DInGameObject* controlledObject) : DX2DProjectController(controlledObject)
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

	int horizontal = 0;
	int vertical = 0;

	static bool debug = true;
	if (InputManager::GetInstance().GetKeyState('V') == EKeyState::KEY_PRESSED)
	{
		debug = !debug;
	}

	// For Debug
	if (debug)
	{
        static Text* text = new Text(L"", { 300, 0, 600, 50 });
        text->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
        text->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
        text->Init();

		if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
		{
			if (InputManager::GetInstance().GetKeyState(VK_SHIFT) == EKeyState::KEY_HOLD)
			{
				vertical += 1;
			}
			if (InputManager::GetInstance().GetKeyState(VK_CONTROL) == EKeyState::KEY_HOLD)
			{
				vertical -= 1;
			}
		}
		if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
		{
			horizontal -= 1;
		}
		if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
		{
			//horizontal -= 1;
		}
		if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
		{
			horizontal += 1;
		}

		if (vertical == 0)
		{
			if (horizontal == -1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::LEFT);
				text->SetString(L"LEFT");
			}
			else if (horizontal == 1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::RIGHT);
				text->SetString(L"RIGHT");
			}
			else
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::STRAIGHT);
				text->SetString(L"STRAIGHT");
			}
		}
		else if (vertical == 1)
		{
			if (horizontal == -1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::LEFT_TOP);
				text->SetString(L"LEFT_TOP");
			}
			else if (horizontal == 1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::RIGHT_TOP);
				text->SetString(L"RIGHT_TOP");
			}
			else
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::TOP);
				text->SetString(L"TOP");
			}
		}
		else
		{
			if (horizontal == -1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::LEFT_BOTTOM);
				text->SetString(L"LEFT_BOTTOM");
			}
			else if (horizontal == 1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::RIGHT_BOTTOM);
				text->SetString(L"RIGHT_BOTTOM");
			}
			else
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::BOTTOM);
				text->SetString(L"BOTTOM");
			}
		}
		g_dxWindow->AddTextable(text);
	}
	else
	{
		float vel = 0.01f;
		if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
		{
			_controlledObject->Move(_controlledObject->GetCenter().Get(0), _controlledObject->GetCenter().Get(1) + vel);
			if (InputManager::GetInstance().GetKeyState(VK_SHIFT) == EKeyState::KEY_HOLD)
			{
				vertical += 1;
			}
			if (InputManager::GetInstance().GetKeyState(VK_CONTROL) == EKeyState::KEY_HOLD)
			{
				vertical -= 1;
			}
		}
		if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
		{
			_controlledObject->Move(_controlledObject->GetCenter().Get(0) - vel, _controlledObject->GetCenter().Get(1));
			horizontal -= 1;
		}
		if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
		{
			//horizontal -= 1;
			_controlledObject->Move(_controlledObject->GetCenter().Get(0), _controlledObject->GetCenter().Get(1) - vel);
		}
		if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
		{
			horizontal += 1;
			_controlledObject->Move(_controlledObject->GetCenter().Get(0) + vel, _controlledObject->GetCenter().Get(1));
		}

		if (vertical == 0)
		{
			if (horizontal == -1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::LEFT);
			}
			else if (horizontal == 1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::RIGHT);
			}
			else
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::STRAIGHT);
			}
		}
		else if (vertical == 1)
		{
			if (horizontal == -1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::LEFT_TOP);
			}
			else if (horizontal == 1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::RIGHT_TOP);
			}
			else
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::TOP);
			}
		}
		else
		{
			if (horizontal == -1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::LEFT_BOTTOM);
			}
			else if (horizontal == 1)
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::RIGHT_BOTTOM);
			}
			else
			{
				_controlledObject->FlightStateChangeOrder(EAireplaneFlightState::BOTTOM);
			}
		}
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

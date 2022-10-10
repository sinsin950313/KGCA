#include "DX2DProjectController.h"
#include "InputManager.h"
#include "Text.h"
#include "TextManager.h"
#include "DXWindow.h"
#include "DXCore.h"

namespace SSB
{
	extern DXWindow* g_dxWindow;
	extern DXCore* g_DXCore;
	bool g_Debug = false;

	EnemyController::EnemyController(DX2DInGameObject* controlledObject) : DX2DProjectController(controlledObject)
	{
	}

	EnemyController::~EnemyController()
	{
		Release();
	}

	void EnemyController::Logic()
	{
		if (_lastDecisionTime + _decisionTime < g_DXCore->GetGlobalTime())
		{
			_decisionTime = rand() % _maxDecisionTime;

			EXAxis xAxis;
			EYAxis yAxis;
			EZAxis zAxis;

			if (_offensive)
			{
				if (_enemy->GetCurrentMapLayer() < _controlledObject->GetCurrentMapLayer())
				{
					yAxis = EYAxis::BOTTOM;
				}
				else if (_enemy->GetCurrentMapLayer() > _controlledObject->GetCurrentMapLayer())
				{
					yAxis = EYAxis::TOP;
				}
				else
				{
					yAxis = EYAxis::STEADY;
				}

				if (_enemy->GetCenter().Get(0) < _controlledObject->GetCenter().Get(0))
				{
					xAxis = EXAxis::LEFT;
				}
				else if (_enemy->GetCenter().Get(0) > _controlledObject->GetCenter().Get(0))
				{
					xAxis = EXAxis::RIGHT;
				}
				else
				{
					xAxis = EXAxis::STEADY;
				}

				if (_enemy->GetCenter().Get(1) - 20 < _controlledObject->GetCenter().Get(1))
				{
					zAxis = EZAxis::DECELERATE;
				}
				else if (_enemy->GetCenter().Get(1) + 20 > _controlledObject->GetCenter().Get(1))
				{
					zAxis = EZAxis::ACCELERATE;
				}
				else
				{
					zAxis = EZAxis::STEADY;
				}
			}
			else
			{
				int x = rand() % 3 - 1;
				if (x == -1)
				{
					xAxis = EXAxis::LEFT;
				}
				else if (x == 1)
				{
					xAxis = EXAxis::RIGHT;
				}
				else
				{
					xAxis = EXAxis::STEADY;
				}

				int y = rand() % 3 - 1;
				if (y == -1)
				{
					yAxis = EYAxis::BOTTOM;
				}
				else if (y == 1)
				{
					yAxis = EYAxis::TOP;
				}
				else
				{
					yAxis = EYAxis::STEADY;
				}

				int z = rand() % 3 - 1;
				if (z == -1)
				{
					zAxis = EZAxis::DECELERATE;
				}
				else if (z == 1)
				{
					zAxis = EZAxis::ACCELERATE;
				}
				else
				{
					zAxis = EZAxis::STEADY;
				}
			}
			_controlledObject->FlightAccelerateDirection(xAxis, yAxis, zAxis);

			_lastDecisionTime = g_DXCore->GetGlobalTime();
		}
	}

	bool EnemyController::Init()
	{
		DX2DProjectController::Init();

		return true;
	}

	bool EnemyController::Frame()
	{
		DX2DProjectController::Frame();

		return true;
	}
	bool EnemyController::Render()
	{
		DX2DProjectController::Render();

		return true;
	}
	bool EnemyController::Release()
	{
		DX2DProjectController::Release();

		return true;
	}
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

	if (InputManager::GetInstance().GetKeyState('V') == EKeyState::KEY_PRESSED)
	{
		g_Debug = !g_Debug;
	}

	int xAxis = 0;
	int yAxis = 0;
	int zAxis = 0;

	if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
	{
		zAxis += 1;
	}
	if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
	{
		xAxis -= 1;
	}
	if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
	{
		zAxis -= 1;
	}
	if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
	{
		xAxis += 1;
	}

	const int mouseDelta = 100;
	if ((int)(g_dxWindow->GetClientHeight() / 2 - mouseDelta) > (int)(InputManager::GetInstance().GetMousePosition().y))
	{
		//yAxis += 1;
		yAxis -= 1;
	}
	if ((int)(g_dxWindow->GetClientHeight() / 2 + mouseDelta) < (int)(InputManager::GetInstance().GetMousePosition().y))
	{
		//yAxis -= 1;
		yAxis += 1;
	}

	if (g_Debug)
	{
        static Text* text = new Text(L"", { 300, 100, 600, 50 });
        text->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
        text->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
        text->Init();

		if (yAxis == 0)
		{
			if (xAxis == -1)
			{
				text->SetString(L"LEFT");
			}
			else if (xAxis == 1)
			{
				text->SetString(L"RIGHT");
			}
			else
			{
				if (zAxis == 1)
				{
					text->SetString(L"ACCELERATE");
				}
				else if (zAxis == -1)
				{
					text->SetString(L"DECELERATE");
				}
				else
				{
					text->SetString(L"STEADY");
				}
			}
		}
		else if (yAxis == 1)
		{
			if (xAxis == -1)
			{
				text->SetString(L"LEFT_TOP");
			}
			else if (xAxis == 1)
			{
				text->SetString(L"RIGHT_TOP");
			}
			else
			{
				text->SetString(L"TOP");
			}
		}
		else
		{
			if (xAxis == -1)
			{
				text->SetString(L"LEFT_BOTTOM");
			}
			else if (xAxis == 1)
			{
				text->SetString(L"RIGHT_BOTTOM");
			}
			else
			{
				text->SetString(L"BOTTOM");
			}
		}
		g_dxWindow->AddTextable(text);
	}
	//else
	{
		EXAxis x;
		if (xAxis == -1)
		{
			x = EXAxis::LEFT;
		}
		else if (xAxis == 1)
		{
			x = EXAxis::RIGHT;
		}
		else
		{
			x = EXAxis::STEADY;
		}
		EYAxis y;
		if (yAxis == -1)
		{
			y = EYAxis::BOTTOM;
		}
		else if (yAxis == 1)
		{
			y = EYAxis::TOP;
		}
		else
		{
			y = EYAxis::STEADY;
		}
		EZAxis z;
		if (zAxis == -1)
		{
			z = EZAxis::DECELERATE;
		}
		else if (zAxis == 1)
		{
			z = EZAxis::ACCELERATE;
		}
		else
		{
			z = EZAxis::STEADY;
		}
		_controlledObject->FlightAccelerateDirection(x, y, z);
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
	DX2DProjectController::Release();

	return true;
}

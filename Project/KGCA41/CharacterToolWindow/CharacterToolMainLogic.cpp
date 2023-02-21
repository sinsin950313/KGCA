#include "pch.h"
#include "CharacterToolMainLogic.h"
#include "FBXLoader.h"
#include "InputManager.h"

namespace SSB
{
	CharacterToolMainLogic::CharacterToolMainLogic(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXWindow(name, hInstance, nCmdShow)
	{
	}
	CharacterToolMainLogic::CharacterToolMainLogic(HWND hwnd) : DXWindow(hwnd)
	{
	}
	bool CharacterToolMainLogic::Init()
	{
		DXWindow::Init();

		_tool.Init();
		//_tool.RegisterObjectFileName("Swat.FBX");
		//_tool.RegisterScriptFileName("CharacterToolTest.FBXScript");
		//_tool.Import();

		//_tool.RegisterActionFileName("Swat@strafe.fbx");
		//_tool.Import();

		//_tool.SelectCurrentAction(_tool.kNewActionName);

		////_tool.ChangeActionName("strafe");
		////_tool.ChangeEndFrame(20);

		//_tool.RegisterScriptFileName("CharacterToolResult.FBXScript");
		//_tool.Export();

		//_tool.SelectCurrentAction("backward");

		//_camera = new ModelViewCamera();
		_toolCamera = new DebugCamera();
		ChangeMainCamera(_toolCamera);
		GetMainCamera()->Move({ 0, 0, -10 });

		_pieCamera = new ModelViewCamera();

		return true;
	}
	bool CharacterToolMainLogic::Frame()
	{
		DXWindow::Frame();

		_tool.Frame();

		if (_object != _tool.GetTargetObject())
		{
			_object = _tool.GetTargetObject();
		}

		Vector3 direction;
		if (_playInEditor)
		{
			if (!_isPIEChanged)
			{
				ChangeMainCamera(_pieCamera);
				_pieCamera->SetTarget(_object);
				GetMainCamera()->Move({ 0, 0, -10 });
				_isPIEChanged = false;
			}

			if(InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
			{
				direction += {0, 0, 1};
			}
			if(InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
			{
				direction += {-1, 0, 0};
			}
			if(InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
			{
				direction += {0, 0, -1};
			}
			if(InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
			{
				direction += {1, 0, 0};
			}

			if (_object != nullptr)
			{
				_object->Move(direction * 1);
				_object->Frame();
			}
		}
		else
		{
			if (_isPIEChanged)
			{
				ChangeMainCamera(_toolCamera);
				if (_object != nullptr)
				{
					_object->UpdatePosition({ 0, 0, 0 });
				}
				_toolCamera->SetPosition({ 0, 0, -10 });
				_isPIEChanged = false;
			}
		}

		return true;
	}
	bool CharacterToolMainLogic::Release()
	{
		_tool.Release();
		_toolCamera->Release();
		_pieCamera->Release();

		DXWindow::Release();
		return true;
	}
	bool CharacterToolMainLogic::PreRender()
	{
		DXWindow::PreRender();

		_tool.Render();
		_toolCamera->Render();
		_pieCamera->Render();

		return true;
	}
	CharacterTool* SSB::CharacterToolMainLogic::GetTool()
	{
		return &_tool;
	}
	void SSB::CharacterToolMainLogic::ChangePIEState()
	{
		_playInEditor = !_playInEditor;
		_isPIEChanged = !_isPIEChanged;
	}
}

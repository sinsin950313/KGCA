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
		_camera = new DebugCamera();
		ChangeMainCamera(_camera);
		GetMainCamera()->Move({ 0, 0, -10 });

		return true;
	}
	bool CharacterToolMainLogic::Frame()
	{
		DXWindow::Frame();

		_tool.Frame();
		_camera->Frame();

		if (_object != _tool.GetTargetObject())
		{
			_object = _tool.GetTargetObject();
			_isObjectSetting = false;
		}

		if (!_isObjectSetting)
		{
			//_camera->SetTarget(_object);
			GetMainCamera()->Move({ 0, 0, -10 });
			_isObjectSetting = true;
		}

		Vector3 direction;
		if (_playInEditor)
		{
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
				direction += {1, 0, 0};
			}
			if(InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
			{
				direction += {0, 0, -1};
			}

			if (_object != nullptr)
			{
				_object->Rotate(0, 0.1f);
				_object->Move(direction * 100);
				_object->Frame();
			}
		}

		return true;
	}
	bool CharacterToolMainLogic::Release()
	{
		_tool.Release();
		_camera->Release();

		DXWindow::Release();
		return true;
	}
	bool CharacterToolMainLogic::PreRender()
	{
		DXWindow::PreRender();

		_tool.Render();
		_camera->Render();

		return true;
	}
	CharacterTool* SSB::CharacterToolMainLogic::GetTool()
	{
		return &_tool;
	}
}

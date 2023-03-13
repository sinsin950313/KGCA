#include "pch.h"
#include "CharacterToolMainLogic.h"
#include "FBXLoader.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include "DXStateManager.h"
#include "HCCalculator.h"
#include "CommonUtility.h"

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

		_toolCamera = new DebugCamera();
		_toolCamera->Init();
		ChangeMainCamera(_toolCamera);
		GetMainCamera()->Move({ 0, 0, -50 });

		_tool.RegisterScriptFileName(kSocketViewObjectStr);
		_tool.Import();
		_socketViewObject = _tool.GetPreviewObject();

		//_pieCamera = new ModelViewCamera();

  //      _terrain = new Map();
  //      SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"KGCABK.bmp", L"Background", { 0, 0, 1024, 768 });
  //      _terrain->SetSprite(SpriteLoader::GetInstance().Load(L"KGCABK.bmp", L"Background", DXStateManager::kDefaultWrapSample));
  //      _terrain->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader.hlsl", "Main", "vs_5_0"));
  //      _terrain->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DPixelShader.hlsl", "Main", "ps_5_0"));
		//_terrain->SetSize(513, 513);
  //      //_terrain->SetHeightMap(L"heightMap513.bmp");
  //      _terrain->Init();
  //      _terrain->Move({ 0, 0, 0 });

		return true;
	}
	bool CharacterToolMainLogic::Frame()
	{
		DXWindow::Frame();
		InputManager::GetInstance().Frame();

		if (_object != nullptr)
		{
			_object->Frame();
		}

		_tool.Frame();

		if (_socketViewObject != nullptr)
		{
			_socketViewObject->Frame();
		}

		//_tool.Frame();
		//if (_object != _tool.GetTargetObject())
		//{
		//	_object = _tool.GetTargetObject();
		//	if (_object != nullptr)
		//	{
		//		Matrix33 rot = Quaternion::GetRotateQuaternion(Vector3(0, 1, 0), 3.1415f).GetRotateMatrix();
		//		_object->SetModelOffset(HMatrix44(rot, Vector3()));
		//	}
		//	_isPIEChanged = true;
		//}

		Vector3 direction;
		//if (_playInEditor)
		//{
		//	if (_isPIEChanged)
		//	{
		//		ChangeMainCamera(_pieCamera);
		//		_pieCamera->SetTarget(_object);
		//		GetMainCamera()->Move({ 0, 0, -10 });
		//		_isPIEChanged = false;
		//		_object->UpdateCurrentAnimation("Idle");
		//	}

		//	if(InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
		//	{
		//		direction += {0, 0, 1};
		//	}
		//	if(InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
		//	{
		//		direction += {-1, 0, 0};
		//	}
		//	if(InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
		//	{
		//		direction += {0, 0, -1};
		//	}
		//	if(InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
		//	{
		//		direction += {1, 0, 0};
		//	}

		//	if (_object != nullptr)
		//	{
		//		_hopeActionName = "Idle";

		//		Vector3 cameraForward = _pieCamera->GetMatrix().GetRow(2);
		//		cameraForward = Vector3(cameraForward.GetX(), 0, cameraForward.GetZ());
		//		cameraForward.Normalize();
		//		cameraForward = cameraForward * direction.GetZ();

		//		Vector3 cameraRight = _pieCamera->GetMatrix().GetRow(0);
		//		cameraRight = Vector3(cameraRight.GetX(), 0, cameraRight.GetZ());
		//		cameraRight.Normalize();
		//		cameraRight = cameraRight * direction.GetX();

		//		Vector3 movementDirection = cameraForward + cameraRight;
		//		_object->Move(movementDirection);

		//		if(0 < direction.Length())
		//		{
		//			direction.Normalize();

		//			Vector3 cameraForward = _pieCamera->GetMatrix().GetRow(2);
		//			cameraForward = Vector3(cameraForward.GetX(), 0, cameraForward.GetZ());
		//			cameraForward.Normalize();
		//			Quaternion dirToCamSpace = Quaternion::GetRotateQuaternion(Vector3(0, 0, 1), cameraForward);
		//			direction = direction * dirToCamSpace.GetRotateMatrix();

		//			Vector3 forward = _object->GetMatrix().GetRow(2);
		//			forward = Vector3(forward.GetX(), 0, forward.GetZ());
		//			forward.Normalize();

		//			Quaternion quat = Quaternion::GetRotateQuaternion(forward, direction);
		//			float radian = acos(quat._f.w) * 2;

		//			if (!isnan(radian))
		//			{
		//				_object->Rotate(0, radian);
		//			}

		//			_hopeActionName = "Run";
		//		}

		//		if (InputManager::GetInstance().GetKeyState(VK_SPACE) == EKeyState::KEY_HOLD)
		//		{
		//			_hopeActionName = "Jump";
		//		}

		//		if (_currentActionName != _hopeActionName)
		//		{
		//			_object->UpdateCurrentAnimation(_hopeActionName);
		//			_currentActionName = _hopeActionName;
		//		}
		//		_object->Frame();

		//		HVector4 pos = _object->GetMatrix().GetRow(3);
		//		_object->UpdatePosition({ pos.GetX(), _terrain->GetHeight(pos.GetX(), pos.GetZ()), pos.GetZ() });
		//	}
		//}
		//else
		//{
		//	if (_isPIEChanged)
		//	{
		//		ChangeMainCamera(_toolCamera);
		//		if (_object != nullptr)
		//		{
		//			_object->UpdatePosition({ 0, 0, 0 });
		//		}
		//		_toolCamera->SetPosition({ 0, 0, -10 });
		//		_isPIEChanged = false;
		//	}
		//}

		return true;
	}
	bool CharacterToolMainLogic::Release()
	{
		_tool.Release();
		_toolCamera->Release();
		//_pieCamera->Release();

		if (_object != nullptr)
		{
			_object->Release();
			delete _object;
			_object = nullptr;
		}

		DXWindow::Release();
		return true;
	}
	bool CharacterToolMainLogic::PreRender()
	{
		DXWindow::PreRender();

		_tool.Render();
		_toolCamera->Render();
		//_pieCamera->Render();
		//if (_playInEditor)
		//{
		//	_terrain->Render();
		//}

		if(_object != nullptr)
		{
			_object->Render();
		}

		return true;
	}
	void SSB::CharacterToolMainLogic::GetPreview()
	{
		if (_object != nullptr)
		{
			delete _object;
			_object = nullptr;
		}
		_object = _tool.GetPreviewObject();
	}
	void SSB::CharacterToolMainLogic::Import(std::string fileName)
	{
		auto split = SSB::SplitPath(mtw(fileName));
		if ((!split[3].empty()) && strcmp(wtm(split[3]).c_str(), ".Script") != 0)
		{
			_tool.RegisterObjectFileName(fileName);
		}
		else
		{
			_tool.RegisterScriptFileName(fileName);
		}
		_tool.Import();
		GetPreview();
	}
	void SSB::CharacterToolMainLogic::Export(std::string fileName)
	{
		_tool.RegisterScriptFileName(fileName);
		_tool.Export();
	}
	void SSB::CharacterToolMainLogic::AddAnimation(std::string animationFileName)
	{
		_tool.AddAction(animationFileName);
		GetPreview();
	}
	void SSB::CharacterToolMainLogic::RemoveAnimation(std::string actionName)
	{
		_tool.RemoveAction(actionName);
		GetPreview();
	}
	void SSB::CharacterToolMainLogic::CutAnimation(std::string newActionName, FrameIndex pivotFrame)
	{
		_tool.CutSelectedAnimataion(newActionName, pivotFrame);
		GetPreview();
	}
	void SSB::CharacterToolMainLogic::ChangeAnimationData(std::string newActionName, FrameIndex pivotFrame)
	{
		if (pivotFrame == 0)
		{
			pivotFrame = CharacterTool::kEmptyFrame;
		}
		_tool.ChangeSelectedAnimationData(newActionName, pivotFrame);
		GetPreview();
	}
	std::vector<SSB::ActionData> SSB::CharacterToolMainLogic::GetActionList()
	{
		std::vector<SSB::ActionData> ret;
		auto actions = _tool.GetActions();
		for (auto action : actions)
		{
			ActionData data;
			data.AnimationName = action.first;
			data.AnimationPointer = nullptr;
			data.EndFrame = action.second->GetFrameSize();
			ret.push_back(data);
		}
		return ret;
	}
	std::map<BoneName, Bone> SSB::CharacterToolMainLogic::GetBones()
	{
		return _tool.GetBones();
	}
	void SSB::CharacterToolMainLogic::SetCurrentAnimation(AnimationName name)
	{
		_tool.SelectCurrentAction(name);
		GetPreview();
	}
	void SSB::CharacterToolMainLogic::SetSocketViewerObjectMatrix(HMatrix44 matrix)
	{
		_socketViewObject->SetMatrix(matrix);
	}
	void SSB::CharacterToolMainLogic::AddSocket(SocketName name, BoneIndex parentIndex, HMatrix44 matrix)
	{
		_tool.AddSocket(name, parentIndex, matrix);
	}
	HMatrix44 SSB::CharacterToolMainLogic::GetBoneMatrix(BoneIndex index)
	{
		_tool.GetBoneMatrix(index);
	}
	BoneIndex SSB::CharacterToolMainLogic::GetBoneIndex(BoneName name)
	{
		auto bones = _tool.GetBones();
		return bones.find(name)->second.Index;
	}
}

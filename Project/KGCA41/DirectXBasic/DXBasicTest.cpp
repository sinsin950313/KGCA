#include "DXBasicTest.h"
#include "ShaderManager.h"
#include "DXStateManager.h"
#include "TextureManager.h"
#include "InputManager.h"

namespace SSB
{
    bool SSB::DXBasicTest::Init()
    {
        DXWindow::Init();
        ShaderManager::GetInstance().Init();
        DXStateManager::GetInstance().Init();
        TextureResourceManager::GetInstance().Init();
        SpriteLoader::GetInstance().Init();
        InputManager::GetInstance().Init();
        
        _object = new DXObject();
        _object->SetModel(new Box);
        _object->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader.hlsl", "Main", "vs_5_0"));
        _object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"DefaultPixelShader.hlsl", "Main", "ps_5_0"));
        _object->Init();

        _dCamera = new DebugCamera();
        ChangeMainCamera(_dCamera);
        GetMainCamera()->Move({ 0, 0, -5 });

        return false;
    }

    bool SSB::DXBasicTest::Frame()
    {
        DXWindow::Frame();
        InputManager::GetInstance().Frame();

		Float3 vPos{ 0, 10, 0 };
        float rotX = 0;
        float rotY = 0;
		float coeff = 0.0001f;
		if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
		{
			vPos.z += 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
		{
			vPos.z -= 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
		{
			vPos.x -= 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
		{
			vPos.x += 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('Q') == EKeyState::KEY_HOLD)
		{
			vPos.y += 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('E') == EKeyState::KEY_HOLD)
		{
			vPos.y -= 10.0f * coeff;
		}
        if (InputManager::GetInstance().GetKeyState(VK_RBUTTON) == EKeyState::KEY_HOLD)
        {
            POINT delta = InputManager::GetInstance().GetDeltaPosition();
            rotX += delta.x * 0.1f;
            rotY += delta.y * 0.1f;
        }
        _dCamera->Move(vPos.z, vPos.x);
        _dCamera->Rotate(rotY, rotX);

        _object->Frame();

        return false;
    }

    bool SSB::DXBasicTest::Release()
    {
        DXWindow::Release();
        return false;
    }

    bool SSB::DXBasicTest::PreRender()
    {
        DXWindow::PreRender();
        _object->Render();
        return true;
    }
}

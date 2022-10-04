#include "DX2DGameProject.h"
#include "SceneList.h"

namespace SSB
{
	DX2DGameProject::DX2DGameProject(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXCore(name, hInstance, nCmdShow)
	{
		NewScene("TitleScene", new TitleScene);
		NewScene("BattleScene", new BattleScene);
		NewScene("ChangeScene", new ChangeScene);
		NewScene("EndScene", new EndScene);

		GetScene("TitleScene")->LinkNewScene("DefenseScene", GetScene("BattleScene"));
		GetScene("BattleScene")->LinkNewScene("ChangeScene", GetScene("ChangeScene"));
		GetScene("ChangeScene")->LinkNewScene("OffenseScene", GetScene("BattleScene"));
		GetScene("BattleScene")->LinkNewScene("EndScene", GetScene("EndScene"));

		SetCurrentScene("TitleScene");
	}
}

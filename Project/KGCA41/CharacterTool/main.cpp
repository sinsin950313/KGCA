#pragma once

#include "CharacterTool.h"

using namespace SSB;

int main()
{
	CharacterTool tool;
	tool.Init();
	tool.RegisterObjectFileName("Swat.FBX");
	tool.RegisterScriptFileName("Swat.FBXScript");

	tool.Import();

	tool.RegisterActionFileName("Swat@strafe.fbx");
	tool.Import();

	tool.RegisterCurrentAction("strafe");
	tool.RegisterEndFrame(20);
	tool.GenerateAction();

	tool.Export();

	tool.Release();
}

#include "Core.h"
#include <Windows.h>

using namespace std;

int main()
{
	Core core;
	core.Init();

	while (1)
	{
		core.Run();
		Sleep(100);
		system("cls");
	}
}

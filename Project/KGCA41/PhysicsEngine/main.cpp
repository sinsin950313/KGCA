#include "Core.h"

int main()
{
	Core<2> qtCore;
	qtCore.UseQuadTree();
	qtCore.Init();
	qtCore.Run();

	Core<3> otCore;
	otCore.UseOctTree();
	otCore.Init();
	otCore.Run();
}

#include "CollisionTree1.h"
#include "Box1.h"
#include "VolumeFactory.h"
#include "CollisionCalculator.h"

using namespace SSB;

namespace SSB
{
	CollisionTree1* kCollisionSystem = nullptr;
	DefaultCollisionCalculator kDefaultCollisionCalculator;
}

int main()
{
	QuadTree qt;
	qt.SetScale(100, 100, 10);
	qt.Init();
	kCollisionSystem = &qt;

	BoxVolumeFactory factory;

	factory.Set(1, 1, 1);
	CollisionSystemVolume* b1 = factory.New();
	qt.AddStaticCollider(Box, b1->GetVolumeOrigin());

	factory.Set(2, 2, 2);
	CollisionSystemVolume* b2 = factory.New();
	qt.AddDynamicCollider(Box, b2->GetVolumeOrigin());

	qt.GetCollidedObjects(b2->GetVolumeOrigin());

	int i = 0;
}
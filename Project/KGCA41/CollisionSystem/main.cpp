#include "CollisionTree1.h"
#include "Box1.h"
#include "VolumeFactory.h"

using namespace SSB;

int main()
{
	QuadTree qt;
	BoxVolumeFactory factory;

	factory.Set();
	CollisionSystemVolume* b1 = factory.New();

	factory.Set();
	CollisionSystemVolume* b2 = factory.New();

	qt.GetCollidedObjects(b2);
}
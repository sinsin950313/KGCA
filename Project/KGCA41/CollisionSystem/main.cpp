#include "CollisionTree1.h"
#include "Box1.h"
#include "VolumeFactory.h"
#include "CollisionCalculator.h"

using namespace SSB;

namespace SSB
{
	CollisionTree1* kCollisionSystem = nullptr;
}

int main()
{
	QuadTree qt;
	qt.SetScale(100, 10, 100);
	qt.Init();
	kCollisionSystem = &qt;

	BoxVolumeFactory boxFactory;
	RayVolumeFactory rayFactory;
	SphereVolumeFactory sphereFactory;

	boxFactory.Set(1, 1, 1);
	CollisionSystemVolume* b1 = boxFactory.New();

	boxFactory.Set(2, 2, 2);
	CollisionSystemVolume* b2 = boxFactory.New();
	b2->SetDynamic();

	auto colObject = qt.GetCollidedObjects(b2);
	b2->SetPosition({ 50, 0, 50 });

	rayFactory.Set({ 0, 0, -10 }, { 0, 0, 1 });
	CollisionSystemVolume* ray = rayFactory.New();
	colObject = qt.GetCollidedObjects(ray);
	auto intersection = qt.GetIntersections(ray);
	b1->SetPosition({ 25, 0, 25 });

	sphereFactory.Set(1);
	CollisionSystemVolume* sphere = sphereFactory.New();
	colObject = qt.GetCollidedObjects(ray);
	intersection = qt.GetIntersections(ray);

	b1->SetPosition({ 25, 0, 25 });
	sphere->SetPosition({ 24, 0, 25 });
	colObject = qt.GetCollidedObjects(b1);

	int i = 0;
}
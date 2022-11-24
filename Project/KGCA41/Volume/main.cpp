//#include "Volume.h"
//#include "Rectangle.h"
//#include "PhysicsVector.h"
//#include "Box.h"

#include "Volume1.h"
#include "Box1.h"
#include "Sphere1.h"
#include "Common.h"

using namespace SSB;

int main()
{
	//SSB::Rectangle standard(0, 0, 20, 20);
	//standard.Print();

	//std::cout << std::boolalpha;
	//SSB::Rectangle collide(0, 10, 10, 10);
	//collide.Print();
	//std::cout << standard.IsCollide(collide) << std::endl;

	//SSB::Rectangle unCollide(0, 20, 10, 10);
	//std::cout << standard.IsCollide(unCollide) << std::endl;
	////Rectangle rectIn(0, 0, 10, 10);
	//std::cout << std::noboolalpha;

	//standard.Resize(30, 30);
	//SSB::Vector2D newPos(SSB::Vector2DData{30, 30});
	//standard.Reposition(newPos);
	//standard.Print();

	//SSB::Rectangle comp(30, 30, 30, 30);
	//std::cout << std::boolalpha << (standard == comp) << std::noboolalpha << std::endl;

	//SSB::Box standardBox(SSB::Vector3D(SSB::Vector3DData{0, 0, 0}), 10, 10, 10);
	//standardBox.Print();
	//SSB::Vector3D newPos3D(SSB::Vector3DData{ 10, 10, 10 });
	//standardBox.Reposition(newPos3D);
	//standardBox.Resize(20, 20, 20);
	//standardBox.Print();

	//SSB::Box collideBox(SSB::Vector3D(SSB::Vector3DData{0, 0, 0}), 10, 10, 10);
	//std::cout << std::boolalpha << standardBox.IsCollide(collideBox) << std::noboolalpha << std::endl;

	//SSB::Box nonCollideBox(SSB::Vector3D(SSB::Vector3DData{40, 40, 40}), 10, 10, 10);
	//std::cout << std::boolalpha << standardBox.IsCollide(nonCollideBox) << std::noboolalpha << std::endl;

	bool isCollide;
	{
		Box box1;
		Box box2;

		isCollide = box1.IsCollide(&box2);

		box1.SetScale(1, 2, 3);
		isCollide = box1.IsCollide(&box2);
		isCollide = box2.IsCollide(&box1);

		box1.SetPosition({ 0, 1, 1.5 });
		isCollide = box1.IsCollide(&box2);
		isCollide = box2.IsCollide(&box1);

		box2.SetRotation(0, DegreeToRadian(45), 0);
		isCollide = box1.IsCollide(&box2);
		isCollide = box2.IsCollide(&box1);

		box1.AddPosition({ 10, 0, 0 });
		box2.AddPosition({ 10, 0, 0 });
		isCollide = box1.IsCollide(&box2);
		isCollide = box2.IsCollide(&box1);
	}

	{
		Sphere sphere1;
		Sphere sphere2;

		isCollide = sphere1.IsCollide(&sphere2);

		sphere1.SetScale(2, 0, 0);
		sphere2.SetPosition({ 4, 0, 0 });
		isCollide = sphere1.IsCollide(&sphere2);
		isCollide = sphere2.IsCollide(&sphere1);

		sphere2.SetScale(2, 0, 0);
		isCollide = sphere1.IsCollide(&sphere2);
		isCollide = sphere2.IsCollide(&sphere1);
	}

	{
		Sphere sphere;
		Box box;
		isCollide = box.IsCollide(&sphere);
		isCollide = sphere.IsCollide(&box);

		box.SetScale(1, 2, 3);
		sphere.SetPosition({ 0.5, 1, 1 });
		isCollide = box.IsCollide(&sphere);
		isCollide = sphere.IsCollide(&box);
	}

	int i = 0;
}
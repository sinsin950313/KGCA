#include "Volume.h"
#include "Rectangle.h"
#include "PhysicsVector.h"
#include "Box.h"

int main()
{
	SSB::Rectangle standard(0, 0, 20, 20);
	standard.Print();

	std::cout << std::boolalpha;
	SSB::Rectangle collide(0, 10, 10, 10);
	collide.Print();
	std::cout << standard.IsCollide(collide) << std::endl;

	SSB::Rectangle unCollide(0, 20, 10, 10);
	std::cout << standard.IsCollide(unCollide) << std::endl;
	//Rectangle rectIn(0, 0, 10, 10);
	std::cout << std::noboolalpha;

	standard.Resize(30, 30);
	SSB::Vector2D newPos(SSB::Vector2DData{30, 30});
	standard.Reposition(newPos);
	standard.Print();

	SSB::Rectangle comp(30, 30, 30, 30);
	std::cout << std::boolalpha << (standard == comp) << std::noboolalpha << std::endl;

	SSB::Box standardBox(SSB::Vector3D(SSB::Vector3DData{0, 0, 0}), 10, 10, 10);
	standardBox.Print();
	SSB::Vector3D newPos3D(SSB::Vector3DData{ 10, 10, 10 });
	standardBox.Reposition(newPos3D);
	standardBox.Resize(20, 20, 20);
	standardBox.Print();

	SSB::Box collideBox(SSB::Vector3D(SSB::Vector3DData{0, 0, 0}), 10, 10, 10);
	std::cout << std::boolalpha << standardBox.IsCollide(collideBox) << std::noboolalpha << std::endl;

	SSB::Box nonCollideBox(SSB::Vector3D(SSB::Vector3DData{40, 40, 40}), 10, 10, 10);
	std::cout << std::boolalpha << standardBox.IsCollide(nonCollideBox) << std::noboolalpha << std::endl;
}
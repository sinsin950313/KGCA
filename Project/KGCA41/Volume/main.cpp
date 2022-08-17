#include "Volume.h"
#include "Rectangle.h"
#include "PhysicsVector.h"

int main()
{
	Rectangle standard(0, 0, 20, 20);
	standard.Print();

	std::cout << std::boolalpha;
	Rectangle collide(0, 10, 10, 10);
	collide.Print();
	std::cout << standard.IsCollide(collide) << std::endl;

	Rectangle unCollide(0, 20, 10, 10);
	std::cout << standard.IsCollide(unCollide) << std::endl;
	//Rectangle rectIn(0, 0, 10, 10);
	std::cout << std::noboolalpha;

	standard.Resize(30, 30);
	Vector2D newPos(Vector2DData{30, 30});
	standard.Reposition(newPos);
	standard.Print();

	Rectangle comp(30, 30, 30, 30);
	std::cout << std::boolalpha << (standard == comp) << std::noboolalpha << std::endl;
}
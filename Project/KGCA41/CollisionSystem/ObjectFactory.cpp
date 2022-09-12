#include "ObjectFactory.h"
#include "Rectangle.h"

Object2D* Object2DFactory::CreateStaticObject(Volume<2>* volume, float mass)
{
	Rigidbody2D rigidbody(mass);
	Object2D* object = new Object2D(volume, rigidbody);
	_ct->AddStaticObject(object);

	return object;
}

Object2D* Object2DFactory::CreateDynamicObject(Volume<2>* volume, float mass)
{
	Rigidbody2D rigidbody(mass);
	Object2D* object = new Object2D(volume, rigidbody);
	_ct->AddDynamicObject(object);

	return object;
}

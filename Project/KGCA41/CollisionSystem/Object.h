#pragma once

#include "VolumeInterface.h"
#include "Rectangle.h"
#include "Rigidbody.h"

template<int dimension>
class Object : public VolumeInterface
{
private:
	Volume _volume;
	Rigidbody<dimension> _rigidBody;

public:
	Object(Volume volume, Rigidbody<dimension> rigidbody) : _volume(volume), _rigidBody(rigidbody) { }
	Volume* GetVolume() override { return &_volume; }
	Rigidbody* GetRigidBody() { return &_rigidBody; }
};

using Object2D = Object<2>;
using Object3D = Object<3>;

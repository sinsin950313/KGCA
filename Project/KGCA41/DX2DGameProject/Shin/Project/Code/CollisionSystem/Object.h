#pragma once

#include "VolumeInterface.h"
#include "Volume.h"
#include "Rigidbody.h"

namespace SSB
{
	template<int dimension>
	class Object : public VolumeInterface<dimension>
	{
	private:
		Volume<dimension>* _volume;
		Rigidbody<dimension> _rigidBody;

	public:
		Object(Volume<dimension>* volume, Rigidbody<dimension> rigidbody) : _volume(volume), _rigidBody(rigidbody) { }
		virtual ~Object();
		Volume<dimension>* GetVolume() override { return _volume; }
		Rigidbody<dimension>* GetRigidBody() { return &_rigidBody; }
	};

	using Object2D = Object<2>;
	using Object3D = Object<3>;

	template<int dimension>
	inline Object<dimension>::~Object()
	{
		delete _volume;
	}
}

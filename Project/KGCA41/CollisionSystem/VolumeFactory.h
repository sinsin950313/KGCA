#pragma once

#include "Volume1.h"
#include "CollisionDetector.h"
#include "CollisionSystemVolume.h"
#include "CollisionSystemVolumeType.h"

namespace SSB
{
	class VolumeFactoryInterface
	{
	protected:
		struct DetectorRegisterData
		{
			VolumeType FromType;
			CollisionDetectorInterface* Detector;
			VolumeType ToType;
		};
		VolumeFactoryInterface(std::vector<DetectorRegisterData> registerData);

	protected:
		virtual Volume1* Create() = 0;

	public:
		CollisionSystemVolume* New();

	public:
		virtual VolumeType GetType() = 0;
	};

	class CollisionSystemRayVolume : public CollisionSystemVolume
	{
	public:
		operator RayData();
	};

	class RayVolumeFactory : public VolumeFactoryInterface
	{
	private:
		Vector3 _origin;
		Vector3 _direction;

	public:
		RayVolumeFactory();

	public:
		void Set(Vector3 origin, Vector3 direction);

	protected:
		virtual Volume1* Create() override;

	public:
		VolumeType GetType() override;
	};

	class BoxVolumeFactory : public VolumeFactoryInterface
	{
	private:
		float _width = 1.0f;
		float _height = 1.0f;
		float _depth = 1.0f;

	public:
		BoxVolumeFactory();

	public:
		void Set(float width, float height, float depth);

	protected:
		virtual Volume1* Create() override;

	public:
		VolumeType GetType() override;
	};

	class SphereVolumeFactory : public VolumeFactoryInterface
	{
	private:
		float _radius = 1.0f;

	public:
		SphereVolumeFactory();

	public:
		void Set(float radius);

	protected:
		virtual Volume1* Create() override;

	public:
		VolumeType GetType() override;
	};
}

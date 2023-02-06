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
			CollisionDetectorInterface* Detector;
			VolumeType ToType;
		};
		VolumeFactoryInterface(VolumeType fromType, std::vector<DetectorRegisterData> registerData);

	protected:
		virtual Volume1* Create() = 0;

	public:
		CollisionSystemVolume* New();

	public:
		virtual VolumeType GetType() = 0;
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

	class AABBVolumeFactory : public VolumeFactoryInterface
	{
	private:
		Vector3 _center;
		float _width;
		float _height;
		float _depth;

	public:
		AABBVolumeFactory();

	public:
		void Set(Vector3 center, float width, float height, float depth);

	protected:
		virtual Volume1* Create() override;

	public:
		VolumeType GetType() override;
	};
}

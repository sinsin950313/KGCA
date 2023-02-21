#pragma once

#include "DXObject.h"
#include "Volume1.h"

namespace SSB
{
	class Light : public DXObject
	{
	private:
		Volume1* _volume;

	public:
		Light(Volume1* volume);

	private:
		void CreateLightConstantBuffer();
		void UpdateLightConstantBuffer();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}

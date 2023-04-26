//#pragma once
//
//#include "Common.h"
//#include "Volume1.h"
//#include <d3d11.h>
//
//namespace SSB
//{
//	class Light : public Common
//	{
//	private:
//		Volume1* _volume;
//
//		struct LightDefaultData
//		{
//			Float3 Position;
//			float Padding1;
//			Float3 Direction;
//			float Padding2;
//			Float3 Color;
//			float Padding3;
//		};
//		LightDefaultData _lightDefaultData;
//		ID3D11Buffer* _lightDefaultBuffer;
//
//	public:
//		Light(Volume1* volume);
//
//	private:
//		void CreateLightBuffer();
//		void UpdateLightData();
//		void UpdateLightBuffer();
//
//	public:
//		bool Init() override;
//		bool Frame() override;
//		bool Render() override;
//		bool Release() override;
//	};
//
//	class DirectionalLight : public Light
//	{
//	public:
//		bool Init() override;
//		bool Frame() override;
//		bool Render() override;
//		bool Release() override;
//	};
//
//	class PointLight : public Light
//	{
//	private:
//		float _radius;
//		ID3D11Buffer* _pointLightBuffer;
//
//	private:
//		void CreateLightBuffer();
//		void UpdateLightBuffer();
//
//	public:
//		bool Init() override;
//		bool Frame() override;
//		bool Render() override;
//		bool Release() override;
//	};
//
//	class SpotLight : public Light
//	{
//	private:
//		float _inCornRadian;
//		float _outCornRadian;
//		ID3D11Buffer* _spotLightBuffer;
//
//	private:
//		void CreateLightBuffer();
//		void UpdateLightBuffer();
//
//	public:
//		bool Init() override;
//		bool Frame() override;
//		bool Render() override;
//		bool Release() override;
//	};
//}

#pragma once

#include "Common.h"
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Timer.h"
#include <vector>
#include <d3d11.h>
#include "Serializeable.h"
#include "SerializeableDataType.h"

namespace SSB
{
	typedef unsigned int FrameIndex;

	class Animation : public Common, public Serializeable
	{
	private:
		static const AnimationFrameInfo kDefaultFrameInfo;

	private:
		float _framePerSecond = 30;
		Timer _animationTimer;

		int _boneAnimationUnitMaxCount = 0;
		int _meshAnimationUnitMaxCount = 0;
		std::vector<AnimationFrameInfo> _data;

		FrameIndex _startFrame;
		FrameIndex _endFrame;

		// Consider maximum Stack size
		AnimationFrameInfo _currentFrameInfo;
		ID3D11Buffer* _animatedFrameBuffer;

	public:
		Animation();
		~Animation();

	private:
		bool CreateAnimatedFrameInfoBuffer();
		HMatrix44 GetInterpolate(AnimationUnitInfo& beforeInfo, AnimationUnitInfo& afterInfo, float t);
		void UpdateFrameInfo();

	public:
		void Initialize_SetAnimationFrameData(std::vector<AnimationFrameInfo> data);
		void Initialize_SetFrameInterval(FrameIndex start, FrameIndex end);
		void Initialize_SetAnimationUnitMaximumCount(int boneCount, int meshCount);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		std::vector<std::string> Serialize(int tabCount) override;
		void Deserialize() override;
	};
}

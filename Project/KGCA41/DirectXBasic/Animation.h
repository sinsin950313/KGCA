#pragma once

#include "Common.h"
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Timer.h"
#include <vector>
#include <d3d11.h>

namespace SSB
{
	static const int kAnimationUnitMaxIndex = 255;
	struct AnimationUnitInfo
	{
		HMatrix44 Matrix;
		Vector3 Translate;
		float Padding1 = 0;
		Vector3 Scale{ 1, 1, 1 };
		float Padding2 = 0;
		Quaternion Rotate;
	};
	struct AnimationFrameInfo
	{
		AnimationUnitInfo AnimationUnit[kAnimationUnitMaxIndex];
	};

	typedef unsigned int FrameIndex;

	class Animation : public Common
	{
	private:
		static const AnimationFrameInfo kDefaultFrameInfo;

	private:
		float _framePerSecond = 30;
		Timer _animationTimer;

		int _animationUnitMaxCount = 0;
		std::vector<AnimationFrameInfo> _data;

		FrameIndex _startFrame;
		FrameIndex _endFrame;

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
		void SetAnimationFrameData(std::vector<AnimationFrameInfo> data);
		void SetFrameInterval(FrameIndex start, FrameIndex end);
		void SetAnimationUnitMaximumCount(int count);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}

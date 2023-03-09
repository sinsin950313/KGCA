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
#include "EditableInterface.h"

namespace SSB
{
	typedef unsigned int FrameIndex;

	class DefaultAnimation
	{
	private:
		AnimationFrameInfo* _frameInfo;

	public:
		DefaultAnimation();
		~DefaultAnimation();

	public:
		const AnimationFrameInfo* GetAnimationFrameInfo() const;
	};

	static const DefaultAnimation kAnimationInitializer;

	class Animation : public Common, public Serializeable, public EditableInterface<Animation>
	{
	private:
		struct FrameMatrixInfo
		{
			HMatrix44 BoneMatrix[255];
			HMatrix44 MeshMatrix[255];
		};
	private:
		float _framePerSecond = 30;
		Timer _animationTimer;

		int _boneAnimationUnitMaxCount = 0;
		int _meshAnimationUnitMaxCount = 0;
		std::vector<AnimationFrameInfo*> _data;

		FrameIndex _startFrame;
		FrameIndex _endFrame;

		AnimationFrameInfo* _currentFrameInfo;
		FrameMatrixInfo _frameMatrixInfo;
		ID3D11Buffer* _animatedFrameBuffer;

	public:
		Animation();
		~Animation();

	private:
		bool CreateAnimatedFrameInfoBuffer();
		HMatrix44 GetInterpolate(AnimationUnitInfo& beforeInfo, AnimationUnitInfo& afterInfo, float t);
		void UpdateFrameInfo();

	public:
		void Initialize_SetAnimationFrameData(std::vector<AnimationFrameInfo*> data);
		void Initialize_SetFrameInterval(FrameIndex start, FrameIndex end);
		void Initialize_SetAnimationUnitMaximumCount(int boneCount, int meshCount);

	public:
		FrameIndex GetFrameSize();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		std::string Serialize(int tabCount) override;
		void Deserialize(std::string& serialedString) override;
		EditableObject<Animation>* GetEditableObject() override;

	public:
		Animation* Clone();
	};

	class EditableAnimationObject : public EditableObject<Animation>
	{
	private:
		float _framePerSecond = 30;

		int _boneAnimationUnitMaxCount = 0;
		int _meshAnimationUnitMaxCount = 0;
		std::vector<AnimationFrameInfo*> _data;

		FrameIndex _startFrame;
		FrameIndex _endFrame;

	public:
		EditableAnimationObject(int boneMaxUnit, int meshMaxUnit, std::vector<AnimationFrameInfo*> frameData, FrameIndex start, FrameIndex end);
		~EditableAnimationObject();

	public:
		FrameIndex GetStartFrame();
		FrameIndex GetEndFrame();
		void EditFrame(FrameIndex start, FrameIndex end);

	public:
		Animation* GetResult() override;
	};
}

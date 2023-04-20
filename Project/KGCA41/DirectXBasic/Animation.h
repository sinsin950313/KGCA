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
#include "Bone.h"
#include <map>

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

	class Animation : public Common, public SerializeableText, public SerializeableBinary, public EditableInterface<Animation>
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

		//Really need this?
		AnimationFrameInfo* _currentFrameInfo;

		FrameMatrixInfo _frameMatrixInfo;
		ID3D11Buffer* _animatedFrameBuffer;

		bool _isLoop = false;;

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
		void Initialize_SetLoop(bool loop);

	public:
		FrameIndex GetFrameSize();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		EditableObject<Animation>* GetEditableObject() override;
		HMatrix44 GetCurrentBoneMatrix(BoneIndex index);

	public:
		std::string SerializeText(int tabCount) override;
		void DeserializeText(std::string& serialedString) override;
		std::string SerializeBinary() override;
		void DeserializeBinary(const char* buffer, int size, int& offset) override;

	public:
		Animation* Clone();
	};

	struct EditableAnimationData
	{
		float FramePerSecond = 30;

		int BoneAnimationUnitMaxCount = 0;
		int MeshAnimationUnitMaxCount = 0;
		std::vector<AnimationFrameInfo*> FrameData;

		FrameIndex StartFrame = 0;
		FrameIndex EndFrame = 0;

		bool IsLoop = false;
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

		bool _isLoop;

	public:
		EditableAnimationObject(EditableAnimationData data);
		~EditableAnimationObject();

	public:
		void AddSocketAnimation(BoneIndex index, BoneIndex parentIndex, HMatrix44 localMatrix);
		void EditFrame(FrameIndex start, FrameIndex end);
		void Reverse();
		FrameIndex GetStartFrame();
		FrameIndex GetEndFrame();

	public:
		Animation* GetResult() override;
	};
}

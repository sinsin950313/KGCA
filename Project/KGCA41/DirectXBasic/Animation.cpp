#include "Animation.h"
#include "HCCalculator.h"
#include "DXWindow.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

	Animation::Animation()
	{
		_currentFrameInfo = new AnimationFrameInfo;
	}
	Animation::~Animation()
	{
		Release();
		if (_currentFrameInfo != nullptr)
		{
			delete _currentFrameInfo;
			_currentFrameInfo = nullptr;
		}
	}
	bool Animation::CreateAnimatedFrameInfoBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(FrameMatrixInfo);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_frameMatrixInfo;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_animatedFrameBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
        return true;
	}
	HMatrix44 Animation::GetInterpolate(AnimationUnitInfo& beforeInfo, AnimationUnitInfo& afterInfo, float t)
	{
		HMatrix44 ret;

		Vector3 pos = Lerp(beforeInfo.Translate, afterInfo.Translate, t);
		Vector3 scale = Lerp(beforeInfo.Scale, afterInfo.Scale, t);
		Quaternion rotate = SLerp(beforeInfo.Rotate, afterInfo.Rotate, t);

		ret = HMatrix44::Scale(scale) * HMatrix44(rotate.GetRotateMatrix(), { 0, 0, 0 }) * HMatrix44::Translate(pos);

		return ret;
	}
	void Animation::UpdateFrameInfo()
	{
		float animationElapseTime = (float)(_animationTimer.GetElapseTime() / 1000.0f);
		int beforeIndex = animationElapseTime * _framePerSecond;
		int afterIndex = beforeIndex + 1;
		if (afterIndex == _data.size())
		{
			afterIndex = beforeIndex;
		}
		else if (_data.size() <= beforeIndex)
		{
			_animationTimer.Init();
			beforeIndex = beforeIndex % _data.size();
			afterIndex = afterIndex % _data.size();
		}

		float beforeTime = beforeIndex / _framePerSecond;
		float afterTime = afterIndex / _framePerSecond;
		float t = (animationElapseTime - beforeTime) / (afterTime - beforeTime);
		if (afterTime - beforeTime < 0.001f)
		{
			t = 0;
		}

		for (int i = 0; i < _boneAnimationUnitMaxCount; ++i)
		{
			_frameMatrixInfo.BoneMatrix[i] = GetInterpolate(_data[beforeIndex]->BoneAnimationUnit[i], _data[afterIndex]->BoneAnimationUnit[i], t);
			_frameMatrixInfo.BoneMatrix[i] = _frameMatrixInfo.BoneMatrix[i].Transpose();
		}
		for (int i = 0; i < _meshAnimationUnitMaxCount; ++i)
		{
			_frameMatrixInfo.MeshMatrix[i] = GetInterpolate(_data[beforeIndex]->MeshAnimationUnit[i], _data[afterIndex]->MeshAnimationUnit[i], t);
			_frameMatrixInfo.MeshMatrix[i] = _frameMatrixInfo.MeshMatrix[i].Transpose();
		}
	}
	bool Animation::Init()
	{
		_animationTimer.Init();
		const AnimationFrameInfo* ptr = kAnimationInitializer.GetAnimationFrameInfo();
		memcpy(_currentFrameInfo, ptr, sizeof(AnimationFrameInfo));
		CreateAnimatedFrameInfoBuffer();

		return true;
	}
	void Animation::Initialize_SetAnimationFrameData(std::vector<AnimationFrameInfo*> data)
	{
		_data = data;
	}
	void Animation::Initialize_SetFrameInterval(FrameIndex start, FrameIndex end)
	{
		_startFrame = start;
		_endFrame = end;
	}
	void Animation::Initialize_SetAnimationUnitMaximumCount(int boneCount, int meshCount)
	{
		_boneAnimationUnitMaxCount = boneCount;
		_meshAnimationUnitMaxCount = meshCount;
	}
	bool Animation::Frame()
	{
		_animationTimer.Frame();
		if (!_data.empty())
		{
			UpdateFrameInfo();
		}

		g_dxWindow->GetDeviceContext()->UpdateSubresource(_animatedFrameBuffer, 0, nullptr, &_frameMatrixInfo, 0, 0);

		return true;
	}
	bool Animation::Render()
	{
		_animationTimer.Render();
		g_dxWindow->GetDeviceContext()->VSSetConstantBuffers(3, 1, &_animatedFrameBuffer);

		return true;
	}
	bool Animation::Release()
	{
		_animationTimer.Release();

		for (auto frameInfo : _data)
		{
			delete frameInfo;
		}
		_data.clear();

		_currentFrameInfo = nullptr;

		if (_animatedFrameBuffer)
		{
			_animatedFrameBuffer->Release();
			_animatedFrameBuffer = nullptr;
		}

		return true;
	}
	FrameIndex Animation::GetFrameSize()
	{
		return _endFrame - _startFrame;
	}
	std::string Animation::Serialize(int tabCount)
	{
		std::string ret;

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "[\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _framePerSecondStr;
		ret += "{\"";
		ret += std::to_string(_framePerSecond);
		ret += "\"},\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _boneAnimationUnitMaxCountStr;
		ret += "{\"";
		ret += std::to_string(_boneAnimationUnitMaxCount);
		ret += "\"},\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _meshAnimationUnitMaxCountStr;
		ret += "{\"";
		ret += std::to_string(_meshAnimationUnitMaxCount);
		ret += "\"},\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _startFrameStr;
		ret += "{\"";
		ret += std::to_string(_startFrame);
		ret += "\"},\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _endFrameStr;
		ret += "{\"";
		ret += std::to_string(_endFrame);
		ret += "\"},\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _frameInfoPerSecondStr;

		ret += Serializeable::GetTabbedString(tabCount + 2);
		ret += _maxFrameCountStr;
		ret += "{\"";
		ret += std::to_string(_data.size());
		ret += "\"}\n";
		for(int i = 0; i < _data.size(); ++i)
		{
			ret += Serializeable::GetTabbedString(tabCount + 2);
			ret += _frameStr;
			ret += "{\"";
			ret += std::to_string(i);
			ret += "\"}\n";

			ret += Serializeable::Serialize(tabCount + 2, *_data[i]);

			ret += Serializeable::GetTabbedString(tabCount + 2);
			ret += ",\n";
		}

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "]\n";

		return ret;
	}
	EditableObject<Animation>* Animation::GetEditableObject()
	{
		return new EditableAnimationObject(_boneAnimationUnitMaxCount, _meshAnimationUnitMaxCount, _data, _startFrame, _endFrame);
	}
	void Animation::Deserialize(std::string& serialedString)
	{
		auto data = GetUnitObject(serialedString, 0);
		serialedString = data.str;

		int offset = 0;
		{
			offset = serialedString.find(_framePerSecondStr, offset);
			auto data = GetUnitElement(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			Serializeable::Deserialize(atomic, _framePerSecond);
		}

		{
			offset = serialedString.find(_boneAnimationUnitMaxCountStr, offset);
			auto data = GetUnitElement(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			Serializeable::Deserialize(atomic, _boneAnimationUnitMaxCount);
		}

		{
			offset = serialedString.find(_meshAnimationUnitMaxCountStr, offset);
			auto data = GetUnitElement(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			Serializeable::Deserialize(atomic, _meshAnimationUnitMaxCount);
		}

		{
			offset = serialedString.find(_startFrameStr, offset);
			auto data = GetUnitElement(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			Serializeable::Deserialize(atomic, _startFrame);
		}

		{
			offset = serialedString.find(_endFrameStr, offset);
			auto data = GetUnitElement(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			Serializeable::Deserialize(atomic, _endFrame);
		}

		int maxFrameCount;
		offset = serialedString.find(_frameInfoPerSecondStr, offset);
		{
			offset = serialedString.find(_maxFrameCountStr, offset);
			auto data = GetUnitElement(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			Serializeable::Deserialize(atomic, maxFrameCount);
		}

		_data.resize(maxFrameCount);

		{
			for (int i = 0; i < maxFrameCount; ++i)
			{
				{
					offset = serialedString.find(_frameStr, offset);
					auto elemData = GetUnitElement(serialedString, offset);
					std::string elem = elemData.str;
					offset = elemData.offset;
				}

				auto data = GetUnitElement(serialedString, offset);
				offset = data.offset;
				AnimationFrameInfo* frameInfo = new AnimationFrameInfo;
				Serializeable::Deserialize(data.str, *frameInfo);
				_data[i] = frameInfo;
			}
		}
	}
	DefaultAnimation::DefaultAnimation()
	{
		_frameInfo = new AnimationFrameInfo;
		for (int i = 0; i < kAnimationUnitMaxIndex; ++i)
		{
			_frameInfo->BoneAnimationUnit[i].Matrix = HMatrix44();
			_frameInfo->BoneAnimationUnit[i].Rotate = Quaternion();
			_frameInfo->BoneAnimationUnit[i].Scale = Vector3();
			_frameInfo->BoneAnimationUnit[i].Translate = Vector3();

			_frameInfo->MeshAnimationUnit[i].Matrix = HMatrix44();
			_frameInfo->MeshAnimationUnit[i].Rotate = Quaternion();
			_frameInfo->MeshAnimationUnit[i].Scale = Vector3();
			_frameInfo->MeshAnimationUnit[i].Translate = Vector3();
		}
	}
	DefaultAnimation::~DefaultAnimation()
	{
		delete _frameInfo;
		_frameInfo = nullptr;
	}
	const AnimationFrameInfo* DefaultAnimation::GetAnimationFrameInfo() const
	{
		return _frameInfo;
	}
	EditableAnimationObject::EditableAnimationObject(int boneMaxUnit, int meshMaxUnit, std::vector<AnimationFrameInfo*> frameData, FrameIndex start, FrameIndex end) : _boneAnimationUnitMaxCount(boneMaxUnit), _meshAnimationUnitMaxCount(meshMaxUnit), _data(frameData), _startFrame(start), _endFrame(end)
	{
	}
	EditableAnimationObject::~EditableAnimationObject()
	{
		for (auto data : _data)
		{
			delete data;
		}
		_data.clear();
	}
	void EditableAnimationObject::EditFrame(FrameIndex start, FrameIndex end)
	{
		_startFrame = start;
		_endFrame = end;
	}
	FrameIndex EditableAnimationObject::GetStartFrame()
	{
		return _startFrame;
	}
	FrameIndex EditableAnimationObject::GetEndFrame()
	{
		return _endFrame;
	}
	Animation* EditableAnimationObject::GetResult()
	{
		Animation* ret = new Animation;

		std::vector<AnimationFrameInfo*> data;
		for (int i = _startFrame; i < _endFrame; ++i)
		{
			AnimationFrameInfo* tmp = new AnimationFrameInfo;
			memcpy(tmp, data[i], sizeof(AnimationFrameInfo));
			data.push_back(tmp);
		}
		ret->Initialize_SetAnimationFrameData(data);
		ret->Initialize_SetAnimationUnitMaximumCount(_boneAnimationUnitMaxCount, _meshAnimationUnitMaxCount);
		ret->Initialize_SetFrameInterval(0, _endFrame - _startFrame);
		ret->Init();

		return ret;
	}
}

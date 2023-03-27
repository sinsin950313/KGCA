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
			if (_isLoop)
			{
				_animationTimer.Init();
				beforeIndex = beforeIndex % _data.size();
				afterIndex = afterIndex % _data.size();
			}
			else
			{
				beforeIndex = _data.size() - 1;
				afterIndex = _data.size() - 1;
			}
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
	void Animation::Initialize_SetLoop(bool loop)
	{
		_isLoop = loop;
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
	EditableObject<Animation>* Animation::GetEditableObject()
	{
		std::vector<AnimationFrameInfo*> frameData;
		for (auto frameInfo : _data)
		{
			AnimationFrameInfo* tmp = new AnimationFrameInfo;
			memcpy(tmp, frameInfo, sizeof(AnimationFrameInfo));
			frameData.push_back(tmp);
		}

		EditableAnimationData data;
		data.BoneAnimationUnitMaxCount = _boneAnimationUnitMaxCount;
		data.MeshAnimationUnitMaxCount = _meshAnimationUnitMaxCount;
		data.FrameData = frameData;
		data.StartFrame = _startFrame;
		data.EndFrame = _endFrame;
		data.IsLoop = _isLoop;

		return new EditableAnimationObject(data);
	}
	HMatrix44 Animation::GetCurrentBoneMatrix(BoneIndex index)
	{
		if (_data.empty())
		{
			return HMatrix44();
		}

		return _frameMatrixInfo.BoneMatrix[index].Transpose();
	}
	Animation* Animation::Clone()
	{
		Animation* ret = new Animation;

		std::vector<AnimationFrameInfo*> data;
		for (auto frameInfo : _data)
		{
			AnimationFrameInfo* info = new AnimationFrameInfo;
			memcpy(info, frameInfo, sizeof(AnimationFrameInfo));
			data.push_back(info);
		}
		ret->Initialize_SetAnimationFrameData(data);
		ret->Initialize_SetAnimationUnitMaximumCount(_boneAnimationUnitMaxCount, _meshAnimationUnitMaxCount);
		ret->Initialize_SetFrameInterval(_startFrame, _endFrame);
		ret->Initialize_SetLoop(_isLoop);
		ret->Init();

		return ret;
	}
	std::string Animation::SerializeText(int tabCount)
	{
		std::string ret;

		ret += SerializeableText::GetTabbedStringText(tabCount);
		ret += "[\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _isLoopStr;
		ret += "{\"";
		ret += std::to_string(_isLoop);
		ret += "\"},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _framePerSecondStr;
		ret += "{\"";
		ret += std::to_string(_framePerSecond);
		ret += "\"},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _boneAnimationUnitMaxCountStr;
		ret += "{\"";
		ret += std::to_string(_boneAnimationUnitMaxCount);
		ret += "\"},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _meshAnimationUnitMaxCountStr;
		ret += "{\"";
		ret += std::to_string(_meshAnimationUnitMaxCount);
		ret += "\"},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _startFrameStr;
		ret += "{\"";
		ret += std::to_string(_startFrame);
		ret += "\"},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _endFrameStr;
		ret += "{\"";
		ret += std::to_string(_endFrame);
		ret += "\"},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _frameInfoPerSecondStr;

		ret += SerializeableText::GetTabbedStringText(tabCount + 2);
		ret += _maxFrameCountStr;
		ret += "{\"";
		ret += std::to_string(_data.size());
		ret += "\"}\n";
		for(int i = 0; i < _data.size(); ++i)
		{
			ret += SerializeableText::GetTabbedStringText(tabCount + 2);
			ret += _frameStr;
			ret += "{\"";
			ret += std::to_string(i);
			ret += "\"}\n";

			ret += SerializeableText::SerializeText(tabCount + 2, *_data[i], _boneAnimationUnitMaxCount, _meshAnimationUnitMaxCount);

			ret += SerializeableText::GetTabbedStringText(tabCount + 2);
			ret += ",\n";
		}

		ret += SerializeableText::GetTabbedStringText(tabCount);
		ret += "]\n";

		return ret;
	}
	void Animation::DeserializeText(std::string& serialedString)
	{
		auto data = GetUnitObjectText(serialedString, 0);
		serialedString = data.str;

		int offset = 0;
		{
			offset = serialedString.find(_isLoopStr, offset);
			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;

			auto atomic = GetUnitAtomicText(elem, 0);
			if (atomic.str == "1")
			{
				_isLoop = true;
			}
			else
			{
				_isLoop = false;
			}
		}

		{
			offset = serialedString.find(_framePerSecondStr, offset);
			auto data = GetUnitElementText(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(atomic, _framePerSecond);
		}

		{
			offset = serialedString.find(_boneAnimationUnitMaxCountStr, offset);
			auto data = GetUnitElementText(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(atomic, _boneAnimationUnitMaxCount);
		}

		{
			offset = serialedString.find(_meshAnimationUnitMaxCountStr, offset);
			auto data = GetUnitElementText(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(atomic, _meshAnimationUnitMaxCount);
		}

		{
			offset = serialedString.find(_startFrameStr, offset);
			auto data = GetUnitElementText(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(atomic, _startFrame);
		}

		{
			offset = serialedString.find(_endFrameStr, offset);
			auto data = GetUnitElementText(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(atomic, _endFrame);
		}

		int maxFrameCount;
		offset = serialedString.find(_frameInfoPerSecondStr, offset);
		{
			offset = serialedString.find(_maxFrameCountStr, offset);
			auto data = GetUnitElementText(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(atomic, maxFrameCount);
		}

		_data.resize(maxFrameCount);

		{
			for (int i = 0; i < maxFrameCount; ++i)
			{
				{
					offset = serialedString.find(_frameStr, offset);
					auto elemData = GetUnitElementText(serialedString, offset);
					std::string elem = elemData.str;
					offset = elemData.offset;
				}

				auto data = GetUnitElementText(serialedString, offset);
				offset = data.offset;
				AnimationFrameInfo* frameInfo = new AnimationFrameInfo;
				SerializeableText::DeserializeText(data.str, *frameInfo, _boneAnimationUnitMaxCount, _meshAnimationUnitMaxCount);
				_data[i] = frameInfo;
			}
		}
	}
	std::string Animation::SerializeBinary()
	{
		std::string ret;

		// FramePerSecond
		{
			float tmpSize = _framePerSecond;
			char* tmpBuffer = new char[sizeof(float)];
				memcpy(tmpBuffer, &tmpSize, sizeof(float));
			std::string tmpStr(tmpBuffer, sizeof(float));
			ret += tmpStr;
			delete tmpBuffer;
		}

		// BoneAnimationUnitMaxCount
		{
			int tmpSize = _boneAnimationUnitMaxCount;
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		// MeshAnimationUnitMaxCount;
		{
			int tmpSize = _meshAnimationUnitMaxCount;
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		// Frame Data
		{
			int tmpSize = _data.size();
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		{
			int size = sizeof(Float44) + sizeof(Float3) + sizeof(Float3) + sizeof(Float4);
			char* tmpBuffer = new char[size * 255];
			for (auto data : _data)
			{
				{
					int offset = 0;
					for (int i = 0; i < _boneAnimationUnitMaxCount; ++i)
					{
						{
							Float44 tmp = data->BoneAnimationUnit[i].Matrix;
							memcpy(tmpBuffer + offset, &tmp, sizeof(Float44));
							offset += sizeof(Float44);
						}
						{
							Float3 tmp = data->BoneAnimationUnit[i].Translate;
							memcpy(tmpBuffer + offset, &tmp, sizeof(Float3));
							offset += sizeof(Float3);
						}
						{
							Float3 tmp = data->BoneAnimationUnit[i].Scale;
							memcpy(tmpBuffer + offset, &tmp, sizeof(Float3));
							offset += sizeof(Float3);
						}
						{
							Float4 tmp = data->BoneAnimationUnit[i].Rotate;
							memcpy(tmpBuffer + offset, &tmp, sizeof(Float4));
							offset += sizeof(Float4);
						}
					}
					std::string tmp(tmpBuffer, size * _boneAnimationUnitMaxCount);
					ret += tmp;
				}

				{
					int offset = 0;
					for (int i = 0; i < _meshAnimationUnitMaxCount; ++i)
					{
						{
							Float44 tmp = data->MeshAnimationUnit[i].Matrix;
							memcpy(tmpBuffer + offset, &tmp, sizeof(Float44));
							offset += sizeof(Float44);
						}
						{
							Float3 tmp = data->MeshAnimationUnit[i].Translate;
							memcpy(tmpBuffer + offset, &tmp, sizeof(Float3));
							offset += sizeof(Float3);
						}
						{
							Float3 tmp = data->MeshAnimationUnit[i].Scale;
							memcpy(tmpBuffer + offset, &tmp, sizeof(Float3));
							offset += sizeof(Float3);
						}
						{
							Float4 tmp = data->MeshAnimationUnit[i].Rotate;
							memcpy(tmpBuffer + offset, &tmp, sizeof(Float4));
							offset += sizeof(Float4);
						}
					}
					std::string tmp(tmpBuffer, size * _meshAnimationUnitMaxCount);
					ret += tmp;
				}
			}
			delete tmpBuffer;
		}

		// Start Frame
		{
			int tmpSize = _startFrame;
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		// End Frame
		{
			int tmpSize = _endFrame;
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		// Loop
		{
			int tmpSize = _isLoop;
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		return ret;
	}
	void Animation::DeserializeBinary(const char* buffer, int size, int& offset)
	{
		// FramePerSecond
		{
			memcpy(&_framePerSecond, buffer + offset, sizeof(float));
			offset += sizeof(float);
		}

		// BoneAnimationUnitMaxCount
		{
			memcpy(&_boneAnimationUnitMaxCount, buffer + offset, sizeof(int));
			offset += sizeof(int);
		}

		// MeshAnimationUnitMaxCount;
		{
			memcpy(&_meshAnimationUnitMaxCount, buffer + offset, sizeof(int));
			offset += sizeof(int);
		}

		// Frame Data
		{
			int frameDataCount;
			memcpy(&frameDataCount, buffer + offset, sizeof(int));
			offset += sizeof(int);

			_data.resize(frameDataCount);
			for (int i = 0; i < frameDataCount; ++i)
			{
				_data[i] = new AnimationFrameInfo;
				for (int j = 0; j < _boneAnimationUnitMaxCount; ++j)
				{
					{
						Float44 matrix;
						memcpy(&matrix, buffer + offset, sizeof(Float44));
						offset += sizeof(Float44);

						_data[i]->BoneAnimationUnit[j].Matrix = {
							matrix.e11, matrix.e12, matrix.e13, matrix.e14,
							matrix.e21, matrix.e22, matrix.e23, matrix.e24,
							matrix.e31, matrix.e32, matrix.e33, matrix.e34,
							matrix.e41, matrix.e42, matrix.e43, matrix.e44,
						};
					}
					{
						Float3 translate;
						memcpy(&translate, buffer + offset, sizeof(Float3));
						offset += sizeof(Float3);
						_data[i]->BoneAnimationUnit[j].Translate = translate;
					}
					{
						Float3 scale;
						memcpy(&scale, buffer + offset, sizeof(Float3));
						offset += sizeof(Float3);
						_data[i]->BoneAnimationUnit[j].Scale = scale;
					}
					{
						Float4 rotate;
						memcpy(&rotate, buffer + offset, sizeof(Float4));
						offset += sizeof(Float4);
						_data[i]->BoneAnimationUnit[j].Rotate = {
							rotate.x, rotate.y, rotate.z, rotate.w
						};
					}
				}

				for (int j = 0; j < _meshAnimationUnitMaxCount; ++j)
				{
					{
						Float44 matrix;
						memcpy(&matrix, buffer + offset, sizeof(Float44));
						offset += sizeof(Float44);

						_data[i]->MeshAnimationUnit[j].Matrix = {
							matrix.e11, matrix.e12, matrix.e13, matrix.e14,
							matrix.e21, matrix.e22, matrix.e23, matrix.e24,
							matrix.e31, matrix.e32, matrix.e33, matrix.e34,
							matrix.e41, matrix.e42, matrix.e43, matrix.e44,
						};
					}
					{
						Float3 translate;
						memcpy(&translate, buffer + offset, sizeof(Float3));
						offset += sizeof(Float3);
						_data[i]->MeshAnimationUnit[j].Translate = translate;
					}
					{
						Float3 scale;
						memcpy(&scale, buffer + offset, sizeof(Float3));
						offset += sizeof(Float3);
						_data[i]->MeshAnimationUnit[j].Scale = scale;
					}
					{
						Float4 rotate;
						memcpy(&rotate, buffer + offset, sizeof(Float4));
						offset += sizeof(Float4);
						_data[i]->MeshAnimationUnit[j].Rotate = {
							rotate.x, rotate.y, rotate.z, rotate.w
						};
					}
				}
			}
		}

		// Start Frame
		{
			memcpy(&_startFrame, buffer + offset, sizeof(int));
			offset += sizeof(int);
		}

		// End Frame
		{
			memcpy(&_endFrame, buffer + offset, sizeof(int));
			offset += sizeof(int);
		}

		// Loop
		{
			int tmpLoop;
			memcpy(&tmpLoop, buffer + offset, sizeof(int));
			offset += sizeof(int);

			_isLoop = tmpLoop;
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
	EditableAnimationObject::EditableAnimationObject(EditableAnimationData data)
		: _boneAnimationUnitMaxCount(data.BoneAnimationUnitMaxCount), _meshAnimationUnitMaxCount(data.MeshAnimationUnitMaxCount), _data(data.FrameData), _startFrame(data.StartFrame), _endFrame(data.EndFrame), _isLoop(data.IsLoop)
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
	void EditableAnimationObject::AddSocketAnimation(BoneIndex index, BoneIndex parentIndex, HMatrix44 localMatrix)
	{
		for (auto data : _data)
		{
			AnimationUnitInfo parentData = data->BoneAnimationUnit[parentIndex];
			AnimationUnitInfo socketData;
			socketData.Matrix = localMatrix * parentData.Matrix;
			Decompose(socketData.Matrix, socketData.Scale, socketData.Rotate, socketData.Translate);
			data->BoneAnimationUnit[index] = socketData;
		}
		++_boneAnimationUnitMaxCount;
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
			memcpy(tmp, _data[i], sizeof(AnimationFrameInfo));
			data.push_back(tmp);
		}
		ret->Initialize_SetAnimationFrameData(data);
		ret->Initialize_SetAnimationUnitMaximumCount(_boneAnimationUnitMaxCount, _meshAnimationUnitMaxCount);
		ret->Initialize_SetFrameInterval(0, _endFrame - _startFrame);
		ret->Initialize_SetLoop(_isLoop);
		ret->Init();

		return ret;
	}
}

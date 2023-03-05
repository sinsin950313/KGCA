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
			beforeIndex = beforeIndex / _data.size();
			afterIndex = afterIndex / _data.size();
		}

		float beforeTime = beforeIndex / _framePerSecond;
		float afterTime = afterIndex / _framePerSecond;
		float t = (animationElapseTime - beforeTime) / (afterTime - beforeTime);

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

		return true;
	}
	std::string Animation::Serialize(int tabCount)
	{
		std::string ret;

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "[\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Frame Per Speed : ";
		ret += std::to_string(_framePerSecond);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Bone Animation Unit Max Count : ";
		ret += std::to_string(_boneAnimationUnitMaxCount);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Mesh Animation Unit Max Count : ";
		ret += std::to_string(_meshAnimationUnitMaxCount);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Start Frame : ";
		ret += std::to_string(_startFrame);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "End Frame : ";
		ret += std::to_string(_endFrame);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Frame Info Per Second\n";
		for(int i = 0; i < _data.size(); ++i)
		{
			ret += Serializeable::GetTabbedString(tabCount + 2);
			ret += "Frame : ";
			ret += std::to_string(i);
			ret += "\n";

			ret += Serializeable::Serialize(tabCount + 2, *_data[i]);

			ret += Serializeable::GetTabbedString(tabCount + 2);
			ret += ",\n";
		}

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "]\n";

		return ret;
	}
	void Animation::Deserialize(std::string serialedString)
	{
		{
			std::regex re("[\n");
			std::smatch match;

			std::regex_search(serialedString, match, re);

			serialedString = match.suffix();
		}

		{
			std::regex re("Frame Per Speed : [0-9.e+-]+,\n");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			re = "[0-9]+";
			std::regex_search(str, match, re);

			_framePerSecond = std::stof(match.str());
		}

		{
			std::regex re("Bone Animation Unit Max Count : [0-9.e+-]+,\n");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			re = "[0-9]+";
			std::regex_search(str, match, re);

			_boneAnimationUnitMaxCount = std::stoi(match.str());
		}

		{
			std::regex re("Mesh Animation Unit Max Count : [0-9.e+-]+,\n");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			re = "[0-9]+";
			std::regex_search(str, match, re);

			_meshAnimationUnitMaxCount = std::stoi(match.str());
		}

		{
			std::regex re("Start Frame : [0-9.e+-]+,\n");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			re = "[0-9]+";
			std::regex_search(str, match, re);

			_startFrame = std::stoi(match.str());
		}

		{
			std::regex re("End Frame : [0-9.e+-]+,\n");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			re = "[0-9]+";
			std::regex_search(str, match, re);

			_endFrame = std::stoi(match.str());
		}

		{
			std::regex re(
R"(
[\t]*{\n
[\t]*[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+,\n
[\t]*[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+,\n
[\t]*[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+,\n
[\t]*[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+\n
[\t]*}\n
[\t]*,\n
[\t]*{[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+}\n
[\t]*,\n
[\t]*{[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+}\n
[\t]*,\n
[\t]*{[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+}\n
[\t]*}\n
)"
			);
			std::smatch match;

			while (std::regex_search(serialedString, match, re))
			{
				std::string str = match.str();
				serialedString = match.suffix();

				AnimationFrameInfo* tmp = new AnimationFrameInfo;
				DeSerialize(str, *tmp);

				_data.push_back(tmp);
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
}

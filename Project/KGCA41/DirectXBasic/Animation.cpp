//#include "Animation.h"
//#include "HCCalculator.h"
//#include "DXWindow.h"
//
//namespace SSB
//{
//    extern DXWindow* g_dxWindow;
//
//	const AnimationFrameInfo Animation::kDefaultFrameInfo;
//
//	Animation::Animation()
//	{
//		_data.push_back(AnimationFrameInfo());
//	}
//	Animation::~Animation()
//	{
//		Release();
//	}
//	bool Animation::CreateAnimatedFrameInfoBuffer()
//	{
//		D3D11_BUFFER_DESC bd;
//		ZeroMemory(&bd, sizeof(bd));
//		bd.ByteWidth = sizeof(AnimationFrameInfo);
//		bd.Usage = D3D11_USAGE_DEFAULT;
//		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//
//		D3D11_SUBRESOURCE_DATA sd;
//		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
//		sd.pSysMem = &_currentFrameInfo;
//		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_animatedFrameBuffer);
//		if (FAILED(hr))
//		{
//			assert(SUCCEEDED(hr));
//			return false;
//		}
//        return true;
//	}
//	HMatrix44 Animation::GetInterpolate(AnimationUnitInfo& beforeInfo, AnimationUnitInfo& afterInfo, float t)
//	{
//		HMatrix44 ret;
//
//		Vector3 pos = Lerp(beforeInfo.Translate, afterInfo.Translate, t);
//		Vector3 scale = Lerp(beforeInfo.Scale, afterInfo.Scale, t);
//		Quaternion rotate = SLerp(beforeInfo.Rotate, afterInfo.Rotate, t);
//
//		ret = HMatrix44::Scale(scale) * HMatrix44(rotate.GetRotateMatrix(), { 0, 0, 0 }) * HMatrix44::Translate(pos);
//
//		return ret;
//	}
//	void Animation::UpdateFrameInfo()
//	{
//		float animationElapseTime = (float)(_animationTimer.GetElapseTime() / 1000.0f);
//		int beforeIndex = animationElapseTime * _framePerSecond;
//		int afterIndex = beforeIndex + 1;
//
//		float beforeTime = beforeIndex / _framePerSecond;
//		float afterTime = afterIndex / _framePerSecond;
//		if (afterIndex == _data.size())
//		{
//			afterIndex = beforeIndex;
//		}
//		else if (_data.size() <= beforeIndex)
//		{
//			_animationTimer.Init();
//			beforeIndex = beforeIndex / _data.size();
//			afterIndex = afterIndex / _data.size();
//		}
//
//		beforeTime = beforeIndex / _framePerSecond;
//		afterTime = afterIndex / _framePerSecond;
//		float t = (animationElapseTime - beforeTime) / (afterTime - beforeTime);
//
//		for (int i = 0; i < _animationUnitMaxCount; ++i)
//		{
//			_currentFrameInfo.AnimationUnit[i].Matrix = GetInterpolate(_data[beforeIndex].AnimationUnit[i], _data[afterIndex].AnimationUnit[i], t);
//		}
//
//		g_dxWindow->GetDeviceContext()->UpdateSubresource(_animatedFrameBuffer, 0, nullptr, &_currentFrameInfo, 0, 0);
//	}
//	bool Animation::Init()
//	{
//		_animationTimer.Init();
//		_currentFrameInfo = kDefaultFrameInfo;
//		CreateAnimatedFrameInfoBuffer();
//
//		return true;
//	}
//	void Animation::SetAnimationFrameData(std::vector<AnimationFrameInfo> data)
//	{
//		_data = data;
//	}
//	void Animation::SetFrameInterval(FrameIndex start, FrameIndex end)
//	{
//		_startFrame = start;
//		_endFrame = end;
//	}
//	void Animation::SetAnimationUnitMaximumCount(int count)
//	{
//		_animationUnitMaxCount = count;
//	}
//	bool Animation::Frame()
//	{
//		_animationTimer.Frame();
//		UpdateFrameInfo();
//
//		return true;
//	}
//	bool Animation::Render()
//	{
//		_animationTimer.Render();
//		g_dxWindow->GetDeviceContext()->VSSetConstantBuffers(2, 1, &_animatedFrameBuffer);
//
//		return true;
//	}
//	bool Animation::Release()
//	{
//		_animationTimer.Release();
//
//		return true;
//	}
//}

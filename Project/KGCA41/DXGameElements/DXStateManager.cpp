#include "DXStateManager.h"

namespace SSB
{
	const std::string DXStateManager::kDefaultWrapSample = "DefaultWrapSample";
	const std::string DXStateManager::kDefaultSolidRasterizer = "DefaultSolidRasterizer";
	const std::string DXStateManager::kDefaultWireFrameRasterizer = "DefaultWireFrameRasterizer";
	DXStateManager* DXStateManager::_instance = nullptr;

	DXStateManager& DXStateManager::GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new DXStateManager;
		}
		return *_instance;
	}

	DXStateManager::~DXStateManager()
	{
		Release();
	}

	void SSB::DXStateManager::AddSamplerState(std::string name, SamplerStateFactoryInterface* factory)
	{
		_samplerStateFactory.insert(std::make_pair(name, factory));
	}

	void SSB::DXStateManager::AddRasterizerState(std::string name, RasterizerStateFactoryInterface* factory)
	{
		_rasterizerStateFactory.insert(std::make_pair(name, factory));
	}

	ID3D11SamplerState* SSB::DXStateManager::GetSamplerState(std::string name)
	{
		if (_samplerStateList.find(name) == _samplerStateList.end())
		{
			ID3D11SamplerState* state = _samplerStateFactory.find(name)->second->Create();
			_samplerStateList.insert(std::make_pair(name, state));
		}
		return _samplerStateList.find(name)->second;
	}

	ID3D11RasterizerState* SSB::DXStateManager::GetRasterizerState(std::string name)
	{
		if (_rasterizerList.find(name) == _rasterizerList.end())
		{
			ID3D11RasterizerState* state = _rasterizerStateFactory.find(name)->second->Create();
			_rasterizerList.insert(std::make_pair(name, state));
		}
		return _rasterizerList.find(name)->second;
	}

	bool SSB::DXStateManager::Init()
	{
		AddSamplerState(kDefaultWrapSample, new DefaultWrapSamplerFactory);
		AddRasterizerState(kDefaultSolidRasterizer, new DefaultSolidRasterizerFactory);
		AddRasterizerState(kDefaultWireFrameRasterizer, new DefaultWireFrameRasterizerFactory);

		return true;
	}

	bool SSB::DXStateManager::Frame()
	{
		return true;
	}

	bool SSB::DXStateManager::Render()
	{
		return true;
	}

	bool SSB::DXStateManager::Release()
	{
		for (auto iter : _samplerStateFactory)
		{
			delete iter.second;
		}
		_samplerStateFactory.clear();

		for (auto iter : _rasterizerStateFactory)
		{
			delete iter.second;
		}
		_rasterizerStateFactory.clear();

		for (auto iter : _samplerStateList)
		{
			iter.second->Release();
		}
		_samplerStateList.clear();

		for (auto iter : _rasterizerList)
		{
			iter.second->Release();
		}
		_rasterizerList.clear();

		return true;
	}
}

#include "DXStateManager.h"

namespace SSB
{
	const std::string DXStateManager::kDefaultWrapSample = "DefaultWrapSample";
	const std::string DXStateManager::kDefaultWrapLinearSample = "DefaultWrapLinearSample";
	const std::string DXStateManager::kDefaultSolidRasterizer = "DefaultSolidRasterizer";
	const std::string DXStateManager::kDefaultWireFrameRasterizer = "DefaultWireFrameRasterizer";
	const std::string DXStateManager::kDefaultBlend = "DefaultBlendState";
	const std::string DXStateManager::kDefaultDepthStencil = "DefaultDepthStencilState";

	DXStateManager DXStateManager::_instance;

	DXStateManager& DXStateManager::GetInstance()
	{
		return _instance;
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

	void DXStateManager::AddBlendState(std::string name, BlendStateFactoryInterface* factory)
	{
		_blendStateFactory.insert(std::make_pair(name, factory));
	}

	void DXStateManager::AddDepthStencilState(std::string name, DepthStencilStateFactoryInterface* factory)
	{
		_depthStencilStateFactory.insert(std::make_pair(name, factory));
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

	ID3D11BlendState* DXStateManager::GetBlendState(std::string name)
	{
		if (_blendStateList.find(name) == _blendStateList.end())
		{
			ID3D11BlendState* state = _blendStateFactory.find(name)->second->Create();
			_blendStateList.insert(std::make_pair(name, state));
		}
		return _blendStateList.find(name)->second;
	}

	ID3D11DepthStencilState* DXStateManager::GetDepthStencilState(std::string name)
	{
		if (_depthStencilStateList.find(name) == _depthStencilStateList.end())
		{
			ID3D11DepthStencilState* state = _depthStencilStateFactory.find(name)->second->Create();
			_depthStencilStateList.insert(std::make_pair(name, state));
		}
		return _depthStencilStateList.find(name)->second;
	}

	bool SSB::DXStateManager::Init()
	{
		AddSamplerState(kDefaultWrapSample, new DefaultWrapSamplerFactory);
		AddSamplerState(kDefaultWrapLinearSample, new DefaultWrapLinearSamplerFactory);
		AddRasterizerState(kDefaultSolidRasterizer, new DefaultSolidRasterizerFactory);
		AddRasterizerState(kDefaultWireFrameRasterizer, new DefaultWireFrameRasterizerFactory);
		AddBlendState(kDefaultBlend, new DefaultBlendFactory);
		AddDepthStencilState(kDefaultDepthStencil, new DefaultDepthStencilStateFactory);

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

		for (auto iter : _blendStateFactory)
		{
			delete iter.second;
		}
		_blendStateFactory.clear();

		for (auto iter : _depthStencilStateFactory)
		{
			delete iter.second;
		}
		_depthStencilStateFactory.clear();

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

		for (auto iter : _blendStateList)
		{
			iter.second->Release();
		}
		_blendStateList.clear();

		for (auto iter : _depthStencilStateList)
		{
			iter.second->Release();
		}
		_depthStencilStateList.clear();

		return true;
	}
}

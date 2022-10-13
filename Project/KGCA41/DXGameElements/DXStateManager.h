#pragma once

#include <map>
#include <string>
#include <d3d11.h>
#include "Common.h"
#include "DXWindow.h"

namespace SSB
{
	extern DXWindow* g_dxWindow;

    class SamplerStateFactoryInterface
    {
    public:
        virtual ID3D11SamplerState* Create() = 0;
    };

    class DefaultWrapLinearSamplerFactory : public SamplerStateFactoryInterface
    {
    public:
        ID3D11SamplerState* Create()
        {
            D3D11_SAMPLER_DESC samplerDesc;
            ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
            samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
            samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
            samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
            samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

            ID3D11SamplerState* samplerState;
            g_dxWindow->GetDevice()->CreateSamplerState(&samplerDesc, &samplerState);

            return samplerState;
        }
    };

    class DefaultWrapSamplerFactory : public SamplerStateFactoryInterface
    {
    public:
        ID3D11SamplerState* Create()
        {
            D3D11_SAMPLER_DESC samplerDesc;
            ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
            samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
            samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
            samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
            samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

            ID3D11SamplerState* samplerState;
            g_dxWindow->GetDevice()->CreateSamplerState(&samplerDesc, &samplerState);

            return samplerState;
        }
    };

    class RasterizerStateFactoryInterface
    {
    public:
        virtual ID3D11RasterizerState* Create() = 0;
    };

    class DefaultSolidRasterizerFactory : public RasterizerStateFactoryInterface
    {
    public:
        ID3D11RasterizerState* Create()
        {
            D3D11_RASTERIZER_DESC desc;
            ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
            desc.FillMode = D3D11_FILL_SOLID;
            desc.CullMode = D3D11_CULL_BACK;

            ID3D11RasterizerState* state;
            g_dxWindow->GetDevice()->CreateRasterizerState(&desc, &state);

            return state;
        }
    };

    class DefaultWireFrameRasterizerFactory : public RasterizerStateFactoryInterface
    {
    public:
        ID3D11RasterizerState* Create()
        {
            D3D11_RASTERIZER_DESC desc;
            ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
            desc.FillMode = D3D11_FILL_WIREFRAME;
            desc.CullMode = D3D11_CULL_BACK;

            ID3D11RasterizerState* state;
            g_dxWindow->GetDevice()->CreateRasterizerState(&desc, &state);

            return state;
        }
    };

    class BlendStateFactoryInterface
    {
    public:
        virtual void SetRenderTargetIndex(int index) = 0;
        virtual ID3D11BlendState* Create() = 0;
    };

    class DefaultBlendFactory : public BlendStateFactoryInterface
    {
    private:
        int _renderTargetIndex = 0;
    public:
        void SetRenderTargetIndex(int index) override
        {
            _renderTargetIndex = index;
        }
        ID3D11BlendState* Create() override
        {
            D3D11_BLEND_DESC desc;
            ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));

            desc.RenderTarget[_renderTargetIndex].BlendEnable = TRUE;
            desc.RenderTarget[_renderTargetIndex].SrcBlend = D3D11_BLEND_SRC_ALPHA;
            desc.RenderTarget[_renderTargetIndex].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
            desc.RenderTarget[_renderTargetIndex].BlendOp = D3D11_BLEND_OP_ADD;

            desc.RenderTarget[_renderTargetIndex].SrcBlendAlpha = D3D11_BLEND_ONE;
            desc.RenderTarget[_renderTargetIndex].DestBlendAlpha = D3D11_BLEND_ZERO;
            desc.RenderTarget[_renderTargetIndex].BlendOpAlpha = D3D11_BLEND_OP_ADD;

            desc.RenderTarget[_renderTargetIndex].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

            ID3D11BlendState* state;
            g_dxWindow->GetDevice()->CreateBlendState(&desc, &state);
            return state;
        }
    };

    class DXStateManager : Common
    {
    private:
        std::map<std::string, SamplerStateFactoryInterface*> _samplerStateFactory;
        std::map<std::string, RasterizerStateFactoryInterface*> _rasterizerStateFactory;
        std::map<std::string, BlendStateFactoryInterface*> _blendStateFactory;

        std::map<std::string, ID3D11SamplerState*> _samplerStateList;
        std::map<std::string, ID3D11RasterizerState*> _rasterizerList;
        std::map<std::string, ID3D11BlendState*> _blendStateList;

    public:
        const static std::string kDefaultWrapSample;
		const static std::string kDefaultWrapLinearSample;
		const static std::string kDefaultSolidRasterizer;
		const static std::string kDefaultWireFrameRasterizer;
        const static std::string kDefaultBlend;

    private:
        static DXStateManager* _instance;
        DXStateManager() { }

    public:
        static DXStateManager& GetInstance();
        ~DXStateManager();

    public:
        void AddSamplerState(std::string name, SamplerStateFactoryInterface* factory);
        void AddRasterizerState(std::string name, RasterizerStateFactoryInterface* factory);
        void AddBlendState(std::string name, BlendStateFactoryInterface* factory);

        ID3D11SamplerState* GetSamplerState(std::string name);
        ID3D11RasterizerState* GetRasterizerState(std::string name);
        ID3D11BlendState* GetBlendState(std::string name);

    public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
    };
}

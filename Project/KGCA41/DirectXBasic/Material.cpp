#include "Material.h"
#include "DXWindow.h"

namespace SSB
{
	extern DXWindow* g_dxWindow;

	Material::Material() : _materialIndex(0)
	{
		_textureArray = new Texture * [kTextureTypeCount];
	}

	Material::~Material()
	{
		Release();
		delete _textureArray;
	}

	void Material::Initialize_SetMaterialIndex(MaterialIndex materialIndex)
	{
		_materialIndex = materialIndex;
	}

	void Material::Initialize_SetTexture(TextureType textureType, Texture* texture)
	{
		_textureArray[textureType] = texture;
	}

	bool Material::Init()
	{
		return true;
	}

	bool Material::Frame()
	{
		return true;
	}

	bool Material::Render()
	{
		auto shaderResourceView = _textureArray[kDiffuse]->GetResource()->GetShaderResourceView();
		g_dxWindow->GetDeviceContext()->PSSetShaderResources(_materialIndex, 1, &shaderResourceView);

		auto sampler = _textureArray[kDiffuse]->GetSamplerState();
		g_dxWindow->GetDeviceContext()->PSSetSamplers(_materialIndex, 1, &sampler);

		return true;
	}

	bool Material::Release()
	{
		_materialIndex = -1;

		for (int i = 0; i < kTextureTypeCount; ++i)
		{
			_textureArray[i] = nullptr;
		}

		return true;
	}
}

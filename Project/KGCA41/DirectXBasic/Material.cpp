#include "Material.h"
#include "DXWindow.h"
#include "TextureManager.h"
#include "DXStateManager.h"

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
	std::string Material::Serialize(int tabCount)
	{
		std::string ret;
		ret += Serializeable::GetTabbedString(tabCount);
		ret += "[\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += _materialIndexStr;
		ret += "{\"";
		ret += std::to_string(_materialIndex);
		ret += "\"},\n";

		for(int i = 0; i < kTextureTypeCount; ++i)
		{
			ret += Serializeable::GetTabbedString(tabCount + 1);
			ret += "{\"";
			if (_textureArray[i] != nullptr)
			{
				ret += _textureArray[i]->GetResource()->GetFileName();
			}
			else
			{
				ret += "Empty";
			}
			ret += "\"},\n";
		}

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "]\n";

		return ret;
	}
	void Material::Deserialize(std::string& serialedString)
	{
		serialedString = GetUnitObject(serialedString, 0).str;

		int offset = 0;
		{
			offset = serialedString.find(_materialIndexStr, offset);
			auto data = GetUnitElement(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			Serializeable::Deserialize(atomic, _materialIndex);
		}

		for (int i = 0; i < kTextureTypeCount; ++i)
		{
			auto data = GetUnitElement(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			_textureArray[i] = TextureLoader::GetInstance().Load(mtw(GetUnitAtomic(data.str, 0).str), DXStateManager::kDefaultWrapSample);
		}
	}
	Material* Material::Clone()
	{
		Material* ret = new Material;
		ret->Initialize_SetMaterialIndex(_materialIndex);

		for (int i = 0; i < kTextureTypeCount; ++i)
		{
			ret->Initialize_SetTexture(i, _textureArray[i]);
		}
		ret->Init();

		return ret;
	}
}

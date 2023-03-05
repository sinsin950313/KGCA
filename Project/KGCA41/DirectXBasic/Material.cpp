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
		ret += "Material Index : ";
		ret += std::to_string(_materialIndex);
		ret += ",\n";

		for(int i = 0; i < kTextureTypeCount; ++i)
		{
			ret += Serializeable::GetTabbedString(tabCount + 1);
			if (_textureArray[i] != nullptr)
			{
				ret += _textureArray[i]->GetResource()->GetFileName();
			}
			else
			{
				ret += "Empty";
			}
			ret += ",\n";
		}

		ret += Serializeable::GetTabbedString(tabCount);
		ret += "]\n";

		return ret;
	}
	void Material::Deserialize(std::string serialedString)
	{
		{
			std::regex re("[\n");
			std::smatch match;

			std::regex_search(serialedString, match, re);

			serialedString = match.suffix();
		}

		{
			std::regex re("Material Index : [0-9.e+-]+,\n");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			re = "[0-9]+";
			std::regex_search(str, match, re);

			_materialIndex = std::stof(match.str());
		}

		for(int i = 0; i < kTextureTypeCount; ++i)
		{
			std::regex re("*.*,\n");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			re = "[^\t]+.*[^,\n]";
			std::regex_search(str, match, re);
			std::string fileName = match.str();
			_textureArray[i] = TextureLoader::GetInstance().Load(mtw(fileName), DXStateManager::kDefaultWrapSample);
		}
	}
}

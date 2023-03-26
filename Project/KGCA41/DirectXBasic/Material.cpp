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
	std::string Material::SerializeText(int tabCount)
	{
		std::string ret;
		ret += SerializeableText::GetTabbedStringText(tabCount);
		ret += "[\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _materialIndexStr;
		ret += "{\"";
		ret += std::to_string(_materialIndex);
		ret += "\"},\n";

		for(int i = 0; i < kTextureTypeCount; ++i)
		{
			ret += SerializeableText::GetTabbedStringText(tabCount + 1);
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

		ret += SerializeableText::GetTabbedStringText(tabCount);
		ret += "]\n";

		return ret;
	}
	void Material::DeserializeText(std::string& serialedString)
	{
		serialedString = GetUnitObjectText(serialedString, 0).str;

		int offset = 0;
		{
			offset = serialedString.find(_materialIndexStr, offset);
			auto data = GetUnitElementText(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(atomic, _materialIndex);
		}

		for (int i = 0; i < kTextureTypeCount; ++i)
		{
			auto data = GetUnitElementText(serialedString, offset);
			std::string atomic = data.str;
			offset = data.offset;
			_textureArray[i] = TextureLoader::GetInstance().Load(mtw(GetUnitAtomicText(data.str, 0).str), DXStateManager::kDefaultWrapSample);
		}
	}
	std::string Material::SerializeBinary()
	{
		std::string ret;

		ret += _materialIndex;

		for(int i = 0; i < kTextureTypeCount; ++i)
		{
			if (_textureArray[i] != nullptr)
			{
				std::string fileName = _textureArray[i]->GetResource()->GetFileName();
				ret += (int)fileName.size();
				ret += fileName;
			}
			else
			{
				ret += 5;
				ret += "Empty";
			}
		}

		return ret;
	}
	void Material::DeserializeBinary(const char* buffer, int size, int& offset)
	{
		{
			memcpy(&_materialIndex, buffer + offset, sizeof(int));
			offset += sizeof(int);
		}

		{
			for (int i = 0; i < kTextureTypeCount; ++i)
			{
				int fileNameSize;
				memcpy(&fileNameSize, buffer + offset, sizeof(int));

				char* fileNameBuffer = new char[fileNameSize];
				memcpy(fileNameBuffer, buffer + offset, fileNameSize);
				std::string fileName(fileNameBuffer, fileNameSize);
				if (fileName != "Empty")
				{
					_textureArray[i] = TextureLoader::GetInstance().Load(mtw(fileName), DXStateManager::kDefaultWrapSample);
				}
				delete[] fileNameBuffer;
			}
		}
	}
	EditableObject<Material>* Material::GetEditableObject()
	{
		EditableMaterialData data;

		data.MaterialIndex = _materialIndex;

		data.TextureFileNameArray.resize(kTextureTypeCount);
		for (int i = 0; i < kTextureTypeCount; ++i)
		{
			data.TextureFileNameArray[i] = _textureArray[i]->GetResource()->GetFileName();
		}

		return new EditableMaterialObject(data);
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
	EditableMaterialObject::EditableMaterialObject(EditableMaterialData data) : _materialIndex(data.MaterialIndex), _textureFileNameArray(data.TextureFileNameArray)
	{
	}
	void EditableMaterialObject::ChangeTexture(TextureType type, std::string fileName)
	{
		_textureFileNameArray[type] = fileName;
	}
	Material* EditableMaterialObject::GetResult()
	{
		Material* ret = new Material;

		ret->Initialize_SetMaterialIndex(_materialIndex);

		for(int i = 0; i < kTextureTypeCount; ++i)
		{
			Texture* tex = TextureLoader::GetInstance().Load(mtw(_textureFileNameArray[i]), DXStateManager::kDefaultWrapSample);
			ret->Initialize_SetTexture(i, tex);
		}

		return ret;
	}
}

#pragma once

#include "Common.h"
#include "Texture.h"
#include "Shader.h"
#include "Serializeable.h"
#include "EditableInterface.h"

namespace SSB
{
	typedef int MaterialIndex;

	typedef int TextureType;
	static const int kTextureTypeCount = 1;
	static const TextureType kDiffuse = 0;
	//static const TextureType kNormal = 1;
	//static const TextureType kSpecular = 2;

	class Material : public Common, public SerializeableText, public SerializeableBinary, public EditableInterface<Material>
	{
	private:
		MaterialIndex _materialIndex;
		Texture** _textureArray;

	public:
		Material();
		~Material();

	public:
		void Initialize_SetMaterialIndex(MaterialIndex materialIndex);
		void Initialize_SetTexture(TextureType textureType, Texture* texture);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;

	public:
		std::string SerializeText(int tabCount) override;
		void DeserializeText(std::string& serialedString) override;
		std::string SerializeBinary() override;
		void DeserializeBinary(const char* buffer, int size, int& offset) override;
		EditableObject<Material>* GetEditableObject() override;

	public:
		Material* Clone();
	};

	struct EditableMaterialData
	{
		MaterialIndex MaterialIndex;
		std::vector<std::string> TextureFileNameArray;
	};
	class EditableMaterialObject : public EditableObject<Material>
	{
	private:
		MaterialIndex _materialIndex;
		std::vector<std::string> _textureFileNameArray;

	public:
		EditableMaterialObject(EditableMaterialData data);

	public:
		void ChangeTexture(TextureType type, std::string fileName);

	public:
		Material* GetResult() override;
	};
}

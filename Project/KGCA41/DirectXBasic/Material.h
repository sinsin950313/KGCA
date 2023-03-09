#pragma once

#include "Common.h"
#include "Texture.h"
#include "Shader.h"
#include "Serializeable.h"

namespace SSB
{
	typedef int MaterialIndex;

	typedef int TextureType;
	static const int kTextureTypeCount = 1;
	static const TextureType kDiffuse = 0;
	//static const TextureType kNormal = 1;
	//static const TextureType kSpecular = 2;

	class Material : public Common, public Serializeable
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
		std::string Serialize(int tabCount) override;
		void Deserialize(std::string& serialedString) override;

	public:
		Material* Clone();
	};
}

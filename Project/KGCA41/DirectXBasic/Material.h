#pragma once

#include "Common.h"
#include "Texture.h"
#include "Shader.h"

namespace SSB
{
	typedef int MaterialIndex;

	typedef int TextureType;
	static const int kTextureTypeCount = 1;
	static const TextureType kDiffuse = 0;
	//static const TextureType kNormal = 1;
	//static const TextureType kSpecular = 2;

	class Material : public Common
	{
	private:
		MaterialIndex _materialIndex;
		Texture** _textureArray;

	public:
		Material();
		~Material();

	public:
		void SetMaterialIndex(MaterialIndex materialIndex);
		void SetTexture(TextureType textureType, Texture* texture);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}

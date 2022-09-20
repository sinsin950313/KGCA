#pragma once

#include "Common.h"
#include <map>
#include <string>
#include "Texture.h"

class ID3D11Device;
class ID3D11DeviceContext;
class ID3D11SamplerState;

namespace SSB
{
	class TextureResourceManager : public Common
	{
	private:
		std::map<std::wstring, TextureResource*> _resourceData;
		std::wstring _path = L"../../Resource/Texture/";

	private:
		static TextureResourceManager* _instance;
		TextureResourceManager() { }

	public:
		~TextureResourceManager();

	public:
		static TextureResourceManager& GetInstance();

	public:
		void ChangePath(std::wstring path) { _path = path; }
		TextureResource* Load(std::wstring resourceFileName);

	private:
		std::wstring GetPath(std::wstring resourceFileName) { return _path + resourceFileName; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
	
	struct TextureData
	{
		TextureResource* resource;
		std::map<std::string, TexturePartRelative> textureParts;
	};

	class TextureLoader : public Common
	{
	private:
		std::map<std::wstring, TextureData> _textureDatas;
		std::wstring _path = L"../../Resource/Data/Texture/";

	private:
		static TextureLoader* _instance;
		TextureLoader() { }

	public:
		static TextureLoader& GetInstance();
		~TextureLoader();

	public:
		void ChangePath(std::wstring path) { _path = path; }
		/// <summary>
		/// InfoFile should be relative data.
		/// </summary>
		/// <param name="infoFileName"></param>
		void RegisterTexturePartFromFile(std::wstring resourceFileName, std::wstring infoFileName);
		void RegisterTexturePartWithRelativeValue(std::wstring resourceFileName, std::wstring partName, TexturePartRelative part);
		void RegisterTexturePartWithCoordinateValue(std::wstring resourceFileName, std::wstring partName, TexturePartCoordinate part);
		Texture* Load(std::wstring resourceFileName, std::wstring partName, std::string samplerName);
		//TexturePartRelative GetTexturePart(std::wstring resourceFileName, std::wstring partName);

	private:
		std::wstring GetPath(std::wstring infoFileName) { return _path + infoFileName + L".textureInfo"; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	struct SpriteData
	{
		TextureResource* resource;
		std::map<std::string, std::vector<TexturePartRelative>> sequenceDatas;
	};

	class SpriteLoader : public Common
	{
	private:
		std::map<std::wstring, SpriteData> _spriteDatas;
		std::wstring _path = L"../../Resource/Data/Sprite/";

	private:
		static SpriteLoader* _instance;
		SpriteLoader() { }

	public:
		static SpriteLoader& GetInstance();
		~SpriteLoader();

	public:
		void ChangePath(std::wstring path) { _path = path; }
		/// <summary>
		/// InfoFile should be relative.
		/// </summary>
		/// <param name="resourceFileName"></param>
		/// <param name="actionName"></param>
		/// <param name="infoFileName"></param>
		void RegisterSpriteFromFile(std::wstring resourceFileName, std::wstring infoFileName);
		void RegisterSpriteWithRelativeValue(std::wstring resourceFileName, std::wstring actionName, std::vector<TexturePartRelative> sequenceRel);
		void RegisterSpriteWithCoordinateValue(std::wstring resourceFileName, std::wstring actionName, std::vector<TexturePartCoordinate> sequenceCoord);
		Sprite* Load(std::wstring resourceFileName, std::wstring actionName, std::string samplerName);

	private:
		std::wstring GetPath(std::wstring infoFileName) { return _path + infoFileName + L".spriteInfo"; }
		void ParseSpriteData(std::wstring infoFileName);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}

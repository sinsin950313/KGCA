#pragma once

#include "Common.h"
#include "CommonPath.h"
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
		std::wstring _path = kTextureResourcePath;

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
	
	struct SpriteData
	{
		TextureResource* resource;
		TextureResource* maskResource;
		std::map<std::string, TexturePartRelative> textureParts;
	};

	// Never use extension name to infoFileName
	class SpriteLoader : public Common
	{
	private:
		std::map<std::wstring, SpriteData> _spriteDatas;
		std::wstring _path = kSpritePath;

	private:
		static SpriteLoader* _instance;
		SpriteLoader() { }

	public:
		static SpriteLoader& GetInstance();
		~SpriteLoader();

	public:
		void ChangePath(std::wstring path) { _path = path; }
		/// <summary>
		/// InfoFile should be relative data.
		/// </summary>
		/// <param name="infoFileName"></param>
		void RegisterSpriteFromFile(std::wstring resourceFileName, std::wstring infoFileName);
		void RegisterSpriteWithRelativeValue(std::wstring resourceFileName, std::wstring spriteName, TexturePartRelative part);
		void RegisterSpriteWithCoordinateValue(std::wstring resourceFileName, std::wstring spriteName, TexturePartCoordinate part);
		Sprite* Load(std::wstring resourceFileName, std::wstring spriteName, std::string samplerName);
		TexturePartRelative GetTexturePart(std::wstring resourceFileName, std::wstring spriteName);

	private:
		std::wstring GetPath(std::wstring infoFileName) { return _path + infoFileName + L".SpriteInfo"; }
		std::wstring GetMaskFileName(std::wstring originFileName);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	struct SpriteActionData
	{
		TextureResource* resource;
		TextureResource* maskResource;
		std::map<std::string, std::vector<TexturePartRelative>> sequenceDatas;
	};

	// Never use extension name to infoFileName
	class SpriteActionLoader : public Common
	{
	private:
		std::map<std::wstring, SpriteActionData> _spriteActionDatas;
		std::wstring _path = kSpriteActionPath;

	private:
		static SpriteActionLoader* _instance;
		SpriteActionLoader() { }

	public:
		static SpriteActionLoader& GetInstance();
		~SpriteActionLoader();

	public:
		void ChangePath(std::wstring path) { _path = path; }
		/// <summary>
		/// InfoFile should be relative.
		/// </summary>
		/// <param name="resourceFileName"></param>
		/// <param name="actionName"></param>
		/// <param name="infoFileName"></param>
		void RegisterSpriteActionFromFile(std::wstring resourceFileName, std::wstring infoFileName);
		void RegisterSpriteActionWithRelativeValue(std::wstring resourceFileName, std::wstring actionName, std::vector<TexturePartRelative> sequenceRel);
		void RegisterSpriteActionWithCoordinateValue(std::wstring resourceFileName, std::wstring actionName, std::vector<TexturePartCoordinate> sequenceCoord);
		SpriteAction* Load(std::wstring resourceFileName, std::wstring actionName, std::string samplerName);
		std::vector<TexturePartRelative> GetSpriteAction(std::wstring resourceFileName, std::wstring actionName);

	private:
		std::wstring GetPath(std::wstring infoFileName) { return _path + infoFileName + L".spriteActionInfo"; }
		std::wstring GetMaskFileName(std::wstring originFileName);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}

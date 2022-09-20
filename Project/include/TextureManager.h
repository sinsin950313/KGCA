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
		TextureResource* Load(std::wstring fileName);

	private:
		std::wstring GetPath(std::wstring fileName) { return _path + fileName; }

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

	private:
		static TextureLoader* _instance;
		TextureLoader() { }

	public:
		static TextureLoader& GetInstance();
		~TextureLoader();

	public:
		/// <summary>
		/// InfoFile should be relative data.
		/// </summary>
		/// <param name="infoFileName"></param>
		void RegisterTexturePartFromFile(std::wstring infoFileName);
		void RegisterTexturePartWithRelativeValue(std::wstring fileName, std::wstring partName, TexturePartRelative part);
		void RegisterTexturePartWithCoordinateValue(std::wstring fileName, std::wstring partName, TexturePartCoordinate part);
		Texture* Load(std::wstring fileName, std::wstring partName, std::string samplerName);
		TexturePartRelative GetTexturePart(std::wstring fileName, std::wstring partName);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	//struct SpriteData
	//{
	//	std::string actionName;
	//	std::vector<RECT> actionSequence;
	//};

	//class SpriteLoader : public Common
	//{
	//private:
	//	std::map<std::wstring, SpriteData> _spriteData;
	//	std::wstring _spritePath = L"../../Resource/SpriteData/";

	//private:
	//	static SpriteLoader* _instance;
	//	SpriteLoader() { }

	//public:
	//	static SpriteLoader& GetInstance();
	//	~SpriteLoader();

	//public:
	//	Sprite* Load(Texture* resource, std::string samplerName, std::string actionName);

	//private:
	//	std::wstring GetSpritePath(std::wstring fileName) { return _spritePath + fileName; }
	//	std::wstring GetActionName(Texture* resource, std::string actionName);
	//	void ParseSpriteData(std::wstring infoFileName);

	//public:
	//	bool Init() override;
	//	bool Frame() override;
	//	bool Render() override;
	//	bool Release() override;
	//};
}

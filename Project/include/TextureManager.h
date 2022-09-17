#pragma once

#include "Common.h"
#include <map>
#include <string>

class ID3D11Device;
class ID3D11DeviceContext;
class ID3D11SamplerState;

namespace SSB
{
	class Texture;

	class TextureManager : public Common
	{
	private:
		std::map<std::wstring, Texture*> _textureData;
		std::map<std::wstring, ID3D11SamplerState*> _samplerData;
		std::wstring _path = L"../../Resource/Texture/";

	private:
		static TextureManager* _instance;
		TextureManager();

	public:
		~TextureManager();

	public:
		static TextureManager& GetInstance();

	public:
		void SetPath(std::wstring path) { _path = path; }
		Texture* Load(std::wstring fileName);
		ID3D11SamplerState* LoadSampler(std::wstring stateName);

	private:
		std::wstring GetPath(std::wstring fileName) { return _path + fileName; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}

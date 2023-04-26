#pragma once

#include "Common.h"
#include <string>
#include <map>
#include "CommonPath.h"

class ID3D11Device;

namespace SSB
{
	class Shader;

	class ShaderManager : public Common
	{
	private:
		std::map<std::wstring, Shader*> _vertexShaderData;
		std::map<std::wstring, Shader*> _pixelShaderData;
		std::wstring _path = kShaderPath;

	private:
		static ShaderManager _instance;
		ShaderManager();

	public:
		~ShaderManager();

	public:
		static ShaderManager& GetInstance();

	private:
		template<typename func> Shader* LoadShader(std::wstring fileName, std::string entryPoint, std::string target, std::map<std::wstring, Shader*>& data, func);
		std::wstring GetPath(std::wstring fileName) { return _path + fileName; }
		std::wstring GetKey(std::wstring fileName, std::string entryPoint);

	public:
		void SetPath(std::wstring path) { _path = path; }
		Shader* LoadVertexShader(std::wstring fileName, std::string entryPoint, std::string target);
		Shader* LoadPixelShader(std::wstring fileName, std::string entryPoint, std::string target);

	private:
		bool Init() override;
		bool Release() override;

	public:
		bool Frame() override;
		bool Render() override;
	};
}

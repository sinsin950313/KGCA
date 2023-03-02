#pragma once

#include "Common.h"
#include <string>
#include <map>
#include "CommonPath.h"
#include <d3dcompiler.h>

class ID3D11Device;
class ID3D11DeviceChild;

namespace SSB
{
	class Shader;
	class VertexShader;
	class PixelShader;

	class ShaderManager : public Common
	{
	private:
		class ShaderFactory
		{
		protected:
            std::string _fileName;
			ID3D11DeviceChild* _shader;
			ID3DBlob* _code;

		public:
			void SetShader(ID3D11DeviceChild* shader);
			void SetCode(ID3DBlob* code);
			void SetFileName(std::string fileName);

		public:
			virtual Shader* New() = 0;
		};

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
		template<typename ShaderCreater>
		Shader* LoadShader(std::wstring fileName, std::string entryPoint, std::string target, std::map<std::wstring, Shader*>& data, ShaderCreater createrFunction, ShaderFactory* factory);
		std::wstring GetPath(std::wstring fileName) { return _path + fileName; }
		std::wstring GetKey(std::wstring fileName, std::string entryPoint);

	public:
		void SetPath(std::wstring path) { _path = path; }
		VertexShader* LoadVertexShader(std::wstring fileName, std::string entryPoint, std::string target);
		PixelShader* LoadPixelShader(std::wstring fileName, std::string entryPoint, std::string target);

	private:
		bool Init() override;
		bool Release() override;

	public:
		bool Frame() override;
		bool Render() override;
	};

}
